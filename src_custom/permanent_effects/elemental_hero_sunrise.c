#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "elemental_hero_sunrise.h"
#include "god_card.h"
#include "six_card_hand.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

#define SUNRISE_ATK_PER_ATTRIBUTE 200
#define SUNRISE_DESTROY_NONE 0xFF

void ClearElementalHeroSunriseOptFlags(void)
{
  gElementalHeroSunriseSearchUsed = FALSE;
  gElementalHeroSunriseDestroyUsed = FALSE;
}

void ClearElementalHeroSunriseDestroyPending(void)
{
  gElementalHeroSunriseDestroyRow = SUNRISE_DESTROY_NONE;
  gElementalHeroSunriseDestroyCol = SUNRISE_DESTROY_NONE;
}

static u8 IsActiveFaceUpSunrise(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_SUNRISE)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static struct DuelCard *FindActiveSunriseOnRow(u8 fixedMonsterRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedMonsterRow][col];

    if (!IsActiveFaceUpSunrise(zone))
      continue;

    if (outCol != NULL)
      *outCol = col;
    return zone;
  }

  return NULL;
}

static u8 CountDistinctAttributesOnMonsterRow(u8 fixedMonsterRow)
{
  u8 seen[12];
  u8 count = 0;
  u8 col;
  u8 i;

  for (i = 0; i < 12; i++)
    seen[i] = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedMonsterRow][col];
    u8 attr;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (gCardData_NEW[zone->id].type >= TYPE_SPELL)
      continue;

    attr = gCardData_NEW[zone->id].attribute;
    if (attr >= 12 || seen[attr])
      continue;

    seen[attr] = TRUE;
    count++;
  }

  return count;
}

void ApplyElementalHeroSunriseAtkBoost(const struct DuelCard *zone)
{
  u8 row;
  u8 col;
  u8 attrCount;
  u32 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  /* gCardInfo.type check avoids SetCardInfo clobber during overlay pass. */
  if (gCardInfo.id != zone->id || gCardInfo.type >= TYPE_SPELL)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 zoneOnRow = FALSE;
    u8 hasSunrise = FALSE;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *rowZone = gFixedZones[row][col];

      if (rowZone == zone)
        zoneOnRow = TRUE;
      if (IsActiveFaceUpSunrise(rowZone))
        hasSunrise = TRUE;
    }

    if (!zoneOnRow || !hasSunrise)
      continue;

    attrCount = CountDistinctAttributesOnMonsterRow(row);
    if (attrCount == 0)
      return;

    atk = (u32)gCardInfo.atk + (u32)attrCount * SUNRISE_ATK_PER_ATTRIBUTE;
    gCardInfo.atk = Duel_ClampStat(atk);
    return;
  }
}

void ElementalHeroSunrise_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone != NULL && zone->id == ELEMENTAL_HERO_SUNRISE)
    UpdateDuelGfxExceptField();
}

void TryElementalHeroSunriseOnMonsterPlacement(struct DuelCard *zone)
{
  /* Never RefreshFieldMonsterStatOverlays here. Placement often runs with
   * updateGfx=FALSE (AI summon / fusion). Overlay-only stamps without a full field
   * draw leave level stars and ATK/DEF tiles on undrawn card faces — field-wide
   * glitch on the opponent's turn. ATK boost applies via ApplyFieldZoneStatsToCardInfo
   * on the next real gfx update. */
  (void)zone;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 AddMiracleFusionFromDeckToHand(void)
{
  u8 fixedDuelist;
  s16 deckIndex;
  s8 handZone;
  u16 cardId;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, MIRACLE_FUSION);
  if (deckIndex < 0)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)(handZone)), cardId);
  return TRUE;
}

void ElementalHeroSunrise_OnFusionSummoned(void)
{
  if (gElementalHeroSunriseSearchUsed)
    return;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, MIRACLE_FUSION) < 0)
    return;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return;

  gElementalHeroSunriseSearchUsed = TRUE;

  Duel_ShowCardEffectText(ELEMENTAL_HERO_SUNRISE, CARD_EFFECT_TEXT_ELEMENTAL_HERO_SUNRISE_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  if (!AddMiracleFusionFromDeckToHand())
    return;

  UpdateDuelGfxExceptField();
}

static u8 ZoneIsOtherHeroYouControl(struct DuelCard *zone, u8 sunriseOwner)
{
  if (zone == NULL || zone->id == CARD_NONE || zone->id == ELEMENTAL_HERO_SUNRISE)
    return FALSE;

  if (GetDuelistForZone(zone) != sunriseOwner)
    return FALSE;

  return Duel_IsElementalHeroCard(zone->id);
}

static u8 AttackInvolvesOtherHeroYouControl(struct DuelCard *sunrise, struct DuelCard *attacker,
                                            struct DuelCard *defender)
{
  u8 sunriseOwner;

  if (sunrise == NULL)
    return FALSE;

  sunriseOwner = GetDuelistForZone(sunrise);
  if (sunriseOwner == 0xFF)
    return FALSE;

  if (ZoneIsOtherHeroYouControl(attacker, sunriseOwner))
    return TRUE;

  return ZoneIsOtherHeroYouControl(defender, sunriseOwner);
}

static u8 OpponentMonsterRowForSunriseRow(u8 sunriseRow)
{
  return sunriseRow == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u8 OpponentBackrowForSunriseRow(u8 sunriseRow)
{
  return sunriseRow == PLAYER_MONSTER_ROW ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 RowIsOpponentFieldForSunrise(u8 sunriseRow, u8 fixedRow)
{
  return fixedRow == OpponentMonsterRowForSunriseRow(sunriseRow)
      || fixedRow == OpponentBackrowForSunriseRow(sunriseRow);
}

static u8 ZoneIsOpponentDestroyTarget(u8 sunriseRow, u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!RowIsOpponentFieldForSunrise(sunriseRow, fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OpponentFieldHasDestroyTarget(u8 sunriseRow)
{
  u8 rows[2];
  u8 r;
  u8 col;

  rows[0] = OpponentMonsterRowForSunriseRow(sunriseRow);
  rows[1] = OpponentBackrowForSunriseRow(sunriseRow);

  for (r = 0; r < 2; r++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (ZoneIsOpponentDestroyTarget(sunriseRow, rows[r], col))
        return TRUE;
    }
  }

  return FALSE;
}

void TryArmElementalHeroSunriseOnAttackDeclared(struct DuelCard *attacker,
                                                struct DuelCard *defender)
{
  u8 row;
  u8 col;
  struct DuelCard *sunrise;

  if (gHideEffectText)
    return;

  if (gElementalHeroSunriseDestroyUsed)
    return;

  if (gElementalHeroSunriseDestroyRow != SUNRISE_DESTROY_NONE)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    sunrise = FindActiveSunriseOnRow(row, &col);
    if (sunrise == NULL)
      continue;

    if (!AttackInvolvesOtherHeroYouControl(sunrise, attacker, defender))
      continue;

    if (!OpponentFieldHasDestroyTarget(row))
      continue;

    gElementalHeroSunriseDestroyRow = row;
    gElementalHeroSunriseDestroyCol = col;
    return;
  }
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  u8 opponentSide = (fixedRow == OPPONENT_MONSTER_ROW || fixedRow == OPPONENT_BACKROW);

  if (opponentSide)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 ZoneIsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  return ZoneIsOpponentDestroyTarget(gDuelCursor.destY, fixedRow, fixedCol);
}

static u8 PickAiDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 sunriseRow = gDuelCursor.destY;
  u8 opponentMonsterRow = OpponentMonsterRowForSunriseRow(sunriseRow);
  u8 opponentBackrow = OpponentBackrowForSunriseRow(sunriseRow);
  u8 col;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!ZoneIsValidDestroyTarget(opponentMonsterRow, col))
      continue;

    zone = gFixedZones[opponentMonsterRow][col];
    if (zone->isDefending && !zone->isFaceUp)
      atk = gCardData_NEW[zone->id].atk;
    else
      atk = Duel_GetZoneFinalAtk(zone);

    if (bestRow == 0xFF || atk > bestAtk) {
      bestRow = opponentMonsterRow;
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestRow != 0xFF) {
    *outRow = bestRow;
    *outCol = bestCol;
    return TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!ZoneIsValidDestroyTarget(opponentBackrow, col))
      continue;

    *outRow = opponentBackrow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (!ZoneIsValidDestroyTarget(targetRow, targetCol))
    return;

  gElementalHeroSunriseDestroyUsed = TRUE;

  if (Duel_DestroyZone(zone, GraveyardDuelistForFixedRow(targetRow), TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
}

static void CancelDestroyTargeting(void)
{
  /* Optional effect — cancelling still consumes the once-per-turn window. */
  gElementalHeroSunriseDestroyUsed = TRUE;
}

static void DestroyFirstAutoTarget(u8 originRow, u8 originCol)
{
  u8 targetRow;
  u8 targetCol;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  if (!PickAiDestroyTarget(&targetRow, &targetCol))
    return;

  ResolveDestroyTarget(targetRow, targetCol);
  UpdateDuelGfxExceptField();
}

static void BeginDestroyTargeting(u8 originRow, u8 originCol)
{
  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  Duel_SetupPickZone(ZoneIsValidDestroyTarget, ResolveDestroyTarget, CancelDestroyTargeting,
                     PickAiDestroyTarget);
  Duel_EnterPickZoneTargeting();
}

void ResolveElementalHeroSunriseDestroyEffect(void)
{
  u8 originRow = gElementalHeroSunriseDestroyRow;
  u8 originCol = gElementalHeroSunriseDestroyCol;
  struct DuelCard *zone;
  u8 hideEffectText;

  if (originRow == SUNRISE_DESTROY_NONE || originCol == SUNRISE_DESTROY_NONE)
    return;

  ClearElementalHeroSunriseDestroyPending();

  if (gElementalHeroSunriseDestroyUsed)
    return;

  zone = gFixedZones[originRow][originCol];
  if (!IsActiveFaceUpSunrise(zone))
    return;

  if (!OpponentFieldHasDestroyTarget(originRow))
    return;

  /* True timing is attack declaration; resolve post-battle so PickZone can run
   * from the main loop (same pattern as Core). Opponent-turn textboxes corrupt
   * field VRAM — auto-resolve silently. */
  if (WhoseTurn() != DUEL_PLAYER) {
    DestroyFirstAutoTarget(originRow, originCol);
    return;
  }

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(ELEMENTAL_HERO_SUNRISE, CARD_EFFECT_TEXT_ELEMENTAL_HERO_SUNRISE_POPUP_2);
  gHideEffectText = hideEffectText;

  if (IsDuelOver() == TRUE)
    return;

  BeginDestroyTargeting(originRow, originCol);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroSunrise_SelfCheck(void)
{
  if (SUNRISE_ATK_PER_ATTRIBUTE != 200)
    while (1)
      ;
}
#endif
