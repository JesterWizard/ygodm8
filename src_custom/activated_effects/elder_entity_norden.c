#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForOwner(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLevel4OrLowerMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].level >= 1 && gCardData_NEW[cardId].level <= 4;
}

static u8 HasLevel4OrLowerInGraveyard(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsLevel4OrLowerMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLevel4OrLowerMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static s8 FindBestGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsLevel4OrLowerMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    if (IsLevel4OrLowerMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
      return (s8)(i - 1);
  }

  return -1;
}

static void MarkSummonedMonsterNegated(u16 cardId)
{
  u8 col;
  u8 row = ACTIVE_DUELIST_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone != NULL && zone->id == cardId) {
      /* Ceiling: banish-when-leaves needs leave-field hook; unk4 marks negated. */
      zone->unk4 |= 0x80;
      return;
    }
  }
}

static enum DuelActionResult SpecialSummonGyLv4DefNegated(u8 fixedDuelist, u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsLevel4OrLowerMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) != DUEL_ACTION_OK)
      return DUEL_ACTION_NO_TARGET;

    MarkSummonedMonsterNegated(cardId);
    return DUEL_ACTION_OK;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsLevel4OrLowerMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return DUEL_ACTION_NO_TARGET;

  MarkSummonedMonsterNegated(cardId);
  return DUEL_ACTION_OK;
}

unsigned char CanActivateELDER_ENTITY_NORDEN(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForOwner();

  if (gMonEffect.id != ELDER_ENTITY_NORDEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELDER_ENTITY_NORDEN)
    return FALSE;

  /* Ceiling: SS-trigger timing + banish-when-leaves need summon/leave hooks.
   * OPT SS Lv≤4 from GY face-up DEF with unk4 negated mark. */
  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HasLevel4OrLowerInGraveyard(fixedDuelist);
}

void ActivateELDER_ENTITY_NORDENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForOwner();
  s8 gyIndex;

  Duel_ShowEffectTextTyped(ELDER_ENTITY_NORDEN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0
      || !HasLevel4OrLowerInGraveyard(fixedDuelist))
    return;

  gyIndex = FindBestGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return;

  if (SpecialSummonGyLv4DefNegated(fixedDuelist, (u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
