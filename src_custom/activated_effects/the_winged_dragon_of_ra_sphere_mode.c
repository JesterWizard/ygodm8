#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "graveyard_effects.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ReturnMonstersToOwner(void);

/* Force popup even when turn_off_visual_scanner has gHideEffectText set. */
static void ShowSphereModePopup(u16 effectTextId)
{
  u8 hideEffectText = gHideEffectText;
  const u8 *text = GetCardEffectText(effectTextId);

  if (text == NULL)
    return;

  gHideEffectText = FALSE;
  ResetCardEffectTextData();
  gCardEffectTextData.cardId = THE_WINGED_DRAGON_OF_RA_SPHERE_MODE;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94((u8 *)text, THE_WINGED_DRAGON_OF_RA_SPHERE_MODE, 0, 0, 0);
  SetCardInfo(THE_WINGED_DRAGON_OF_RA_SPHERE_MODE);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
  gHideEffectText = hideEffectText;
}

#define SPHERE_MODE_OPPONENT_TRIBUTES 3

static u8 IsSphereModeTributeTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return IsGodCard(cardId) != TRUE;
}

static u8 CountTributeTargetsOnRow(u8 monsterRow)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsSphereModeTributeTarget(gTurnZones[monsterRow][i]->id))
      count++;
  }

  return count;
}

/* ponytail: hand permanent-effect scan is skipped when turn_off_visual_scanner is on
 * (gHideEffectText), so use Blue Eyes Shining-style post-board-scan auto-summon. */
static u8 TryAutoSummonSphereModeForOwner(u8 ownerDuelist)
{
  u8 opponentDuelist = ownerDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  u8 opponentMonsterRow = ownerDuelist == ACTIVE_DUELIST
      ? INACTIVE_DUELIST_MONSTER_ROW
      : ACTIVE_DUELIST_MONSTER_ROW;
  s8 handCol;
  u8 i;
  u8 paid;
  u8 zone;
  struct DuelCard **monsterZones;
  struct DuelCard *handZone;
  struct DuelCard *summonZone;

  if (!RowHasCardMatch(gTurnHands[ownerDuelist], THE_WINGED_DRAGON_OF_RA_SPHERE_MODE))
    return FALSE;

  handCol = GetFirstCardMatchZoneId(gTurnHands[ownerDuelist],
                                    THE_WINGED_DRAGON_OF_RA_SPHERE_MODE);

  if (CountTributeTargetsOnRow(opponentMonsterRow) < SPHERE_MODE_OPPONENT_TRIBUTES)
    return FALSE;

  monsterZones = gTurnZones[opponentMonsterRow];
  handZone = gTurnHands[ownerDuelist][handCol];

  ShowSphereModePopup(CARD_EFFECT_TEXT_THE_WINGED_DRAGON_OF_RA_SPHERE_MODE_POPUP_1);

  for (i = 0, paid = 0; i < MAX_ZONES_IN_ROW && paid < SPHERE_MODE_OPPONENT_TRIBUTES; i++) {
    struct DuelCard *target = monsterZones[i];

    if (!IsSphereModeTributeTarget(target->id))
      continue;

    ClearZoneAndSendMonToGraveyard(target, opponentDuelist);
    paid++;
  }

  zone = FirstEmptyZoneInRow(monsterZones);
  if (zone >= MAX_ZONES_IN_ROW)
    return FALSE;

  summonZone = monsterZones[zone];
  CopyCard(summonZone, handZone);
  ClearZone(handZone);
  FlipCardFaceUp(summonZone);
  /* Vanilla ReturnMonstersToOwner moves willChangeSides monsters at turn end. */
  summonZone->willChangeSides = TRUE;
  return TRUE;
}

u8 TryAutoSummonTheWingedDragonOfRaSphereMode(void)
{
  if (IsDuelOver() == TRUE)
    return FALSE;

  if (TryAutoSummonSphereModeForOwner(ACTIVE_DUELIST))
    return TRUE;

  if (TryAutoSummonSphereModeForOwner(INACTIVE_DUELIST))
    return TRUE;

  return FALSE;
}

/* Called at turn end (before SwitchTurn): popup_2 then vanilla control return. */
void TryReturnSphereModeAtTurnEnd(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone->id != THE_WINGED_DRAGON_OF_RA_SPHERE_MODE || !zone->willChangeSides)
      continue;

    ShowSphereModePopup(CARD_EFFECT_TEXT_THE_WINGED_DRAGON_OF_RA_SPHERE_MODE_POPUP_2);
    break;
  }

  ReturnMonstersToOwner();
}

static u8 DuelistForMonsterRow(u8 row)
{
  if (row == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (row == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 HandOrDeckHasBattleMode(u8 turnDuelist)
{
  if (RowHasCardMatch(gTurnHands[turnDuelist], THE_WINGED_DRAGON_OF_RA_BATTLE_MODE))
    return TRUE;

  return Duel_FindDeckCardIndex(turnDuelist, THE_WINGED_DRAGON_OF_RA_BATTLE_MODE) >= 0;
}

/* ponytail: in-place tribute replacement; Duel_SpecialSummon* needs an empty zone */
static void SummonBattleModeInZone(struct DuelCard *zone)
{
  zone->id = THE_WINGED_DRAGON_OF_RA_BATTLE_MODE;
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 2;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
  zone->effectExhausted = 0;
  zone->effectUsedThisTurn = 0;
}

static u8 TryTakeBattleModeFromHandOrDeck(u8 turnDuelist)
{
  s8 handZone;
  s16 deckIndex;

  if (RowHasCardMatch(gTurnHands[turnDuelist], THE_WINGED_DRAGON_OF_RA_BATTLE_MODE)) {
    handZone = GetFirstCardMatchZoneId(gTurnHands[turnDuelist],
                                       THE_WINGED_DRAGON_OF_RA_BATTLE_MODE);
    ClearZone(gTurnHands[turnDuelist][handZone]);
    return TRUE;
  }

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, THE_WINGED_DRAGON_OF_RA_BATTLE_MODE);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  return TRUE;
}

u8 SphereMode_CanAttackMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_WINGED_DRAGON_OF_RA_SPHERE_MODE)
    return TRUE;

  return FALSE;
}

u8 SphereMode_CanDeclareAttack(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_WINGED_DRAGON_OF_RA_SPHERE_MODE)
    return TRUE;

  return FALSE;
}

unsigned char CanActivateTheWingedDragonOfRaSphereMode(void)
{
  struct DuelCard *zone;
  u8 turnDuelist;

  if (gMonEffect.id != THE_WINGED_DRAGON_OF_RA_SPHERE_MODE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  turnDuelist = DuelistForMonsterRow(gMonEffect.row);
  return HandOrDeckHasBattleMode(turnDuelist);
}

void ActivateTheWingedDragonOfRaSphereModeEffect(void)
{
  struct DuelCard *sphereZone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 turnDuelist = DuelistForMonsterRow(gMonEffect.row);
  u16 sphereId;

  ShowSphereModePopup(CARD_EFFECT_TEXT_THE_WINGED_DRAGON_OF_RA_SPHERE_MODE_POPUP_3);

  if (IsDuelOver() == TRUE)
    return;

  if (!HandOrDeckHasBattleMode(turnDuelist))
    return;

  if (!TryTakeBattleModeFromHandOrDeck(turnDuelist))
    return;

  /* Self-tribute must bypass targeting immunity on Sphere Mode. */
  sphereId = sphereZone->id;
  NoteGraveyardMonsterSend(sphereZone);
  GraveyardExpand_PushTurn(turnDuelist, sphereId);
  ClearZone(sphereZone);
  SummonBattleModeInZone(sphereZone);

  gDuelCursor.currentX = gMonEffect.zone;
  gDuelCursor.currentY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  gDuelCursor.destY = gMonEffect.row;
  DisplayCardInfoBar();
  sub_8041E70(PLAYER_HAND, gMonEffect.row);
}
