#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_celestial.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static s8 FindOtherDestinyHeroGyIndex(u8 fixedDuelist, u8 skipIndex)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId;

    if (i == skipIndex)
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (IsDestinyHeroMonster(cardId))
      return (s8)i;
  }

  return -1;
}

u8 CanActivateDestinyHeroCelestialGy(u8 fixedDuelist, u8 gyIndex)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);

  if (!GraveyardExpand_IsEnabled())
    return FALSE;
  /* ponytail: except-turn-sent not tracked; EffectOpt ≈ once/turn. */
  if (EffectOpt_IsUsed(DESTINY_HERO_CELESTIAL))
    return FALSE;
  if (gyIndex >= GraveyardExpand_GetCount(fixedDuelist))
    return FALSE;
  if (GraveyardExpand_GetCardAt(fixedDuelist, gyIndex) != DESTINY_HERO_CELESTIAL)
    return FALSE;
  if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) != 0)
    return FALSE;

  return FindOtherDestinyHeroGyIndex(fixedDuelist, gyIndex) >= 0;
}

void ActivateDestinyHeroCelestialGy(u8 fixedDuelist, u8 gyIndex)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  s8 otherIndex;
  u8 first;
  u8 second;

  if (!CanActivateDestinyHeroCelestialGy(fixedDuelist, gyIndex))
    return;

  otherIndex = FindOtherDestinyHeroGyIndex(fixedDuelist, gyIndex);
  if (otherIndex < 0)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_CELESTIAL, 9);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_CELESTIAL);

  /* Banish higher index first so lower index stays valid. */
  first = gyIndex > (u8)otherIndex ? gyIndex : (u8)otherIndex;
  second = gyIndex > (u8)otherIndex ? (u8)otherIndex : gyIndex;
  Duel_BanishGraveyardAtFixed(fixedDuelist, first);
  Duel_BanishGraveyardAtFixed(fixedDuelist, second);

  if (Duel_DrawCards(turnDuelist, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

static u8 IsFaceUpOppSpell(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_SPELL)
    return FALSE;

  return zone->isFaceUp || IsCardFaceUp(zone);
}

static u8 FieldHasFaceUpOppSpell(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppSpell(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveDestroySpell(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpOppSpell(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -500, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppSpell(OPPONENT_BACKROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

void TryDestinyHeroCelestialOnAttackDeclared(struct DuelCard *attacker, struct DuelCard *defender)
{
  u8 col;
  struct DuelCard *spell = NULL;

  (void)defender;

  if (gHideEffectText || attacker == NULL || attacker->id != DESTINY_HERO_CELESTIAL)
    return;

  {
    u8 fixedRow;
    u8 fixedCol;
    u8 oppBackrow;
    u8 spellOwner;

    if (!Duel_FindFixedMonsterZone(attacker, &fixedRow, &fixedCol))
      return;

    oppBackrow = fixedRow == PLAYER_MONSTER_ROW ? OPPONENT_BACKROW : PLAYER_BACKROW;
    spellOwner = fixedRow == PLAYER_MONSTER_ROW ? INACTIVE_DUELIST : ACTIVE_DUELIST;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[oppBackrow][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;
      if (GetTypeGroup(zone->id) != TYPE_GROUP_SPELL)
        continue;
      if (!zone->isFaceUp && !IsCardFaceUp(zone))
        continue;

      spell = zone;
      break;
    }

    if (spell == NULL)
      return;

    if (Duel_DestroyZone(spell, spellOwner, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    NotifyDynamicEquipFieldChanged();

    if (IsDuelOver() == TRUE)
      return;

    Duel_ShowEffectTextTyped(DESTINY_HERO_CELESTIAL, 3);
    Duel_ChangeLp(spellOwner, -500, TRUE);
  }
}

unsigned char CanActivateDESTINY_HERO_CELESTIAL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_CELESTIAL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_CELESTIAL)
    return FALSE;

  /* Attack-declare destroy via TryDestinyHeroCelestialOnAttackDeclared.
   * GY empty-hand draw via CanActivateDestinyHeroCelestialGy / gy_ignition.
   * OPT destroy 1 face-up opp Spell + burn 500. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceUpOppSpell();
}

void ActivateDESTINY_HERO_CELESTIALEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_CELESTIAL, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpOppSpell, ResolveDestroySpell, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
