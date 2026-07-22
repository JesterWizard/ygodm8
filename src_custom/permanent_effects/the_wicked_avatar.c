#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "the_wicked_avatar.h"
#include "mini_card.h"

void UpdateDuelGfxExceptField(void);

extern u8 gAiSimInBatch;

#define THE_WICKED_AVATAR_LOCK_TURNS 2
#define THE_WICKED_AVATAR_STAT_BONUS 100
#define WICKED_AVATAR_LOCK_ARMED 2

static u8 IsActiveWickedAvatar(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_WICKED_AVATAR)
    return FALSE;

  if (IsCardFaceUp((struct DuelCard *)zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 AvatarIsActiveOnField(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsActiveWickedAvatar(gFixedZones[row][col]))
        return TRUE;
    }
  }

  return FALSE;
}

static u16 FindHighestFaceUpMonsterAtkExceptAvatar(void)
{
  u8 row;
  u8 col;
  u16 highestAtk = 0;
  u8 found = FALSE;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];
      u16 atk;

      if (zone == NULL || zone->id == CARD_NONE || zone->id == THE_WICKED_AVATAR)
        continue;
      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;
      if (!ZoneShowsCombatStats(zone))
        continue;

      atk = Duel_GetZoneFinalAtk(zone);
      if (!found || atk > highestAtk) {
        highestAtk = atk;
        found = TRUE;
      }
    }
  }

  return found ? highestAtk : 0;
}

static u8 OpponentFixedDuelistForSummoner(u8 summonerFixedDuelist)
{
  if (summonerFixedDuelist == DUEL_PLAYER)
    return DUEL_OPPONENT;
  if (summonerFixedDuelist == DUEL_OPPONENT)
    return DUEL_PLAYER;
  return 0xFF;
}

static u8 FixedDuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  return 0xFF;
}

static u8 FixedDuelistForMonsterFixedRow(u8 fixedRow)
{
  if (fixedRow == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return DUEL_OPPONENT;
  return 0xFF;
}

static u8 OtherDuelist(u8 duelist)
{
  if (duelist == DUEL_PLAYER)
    return DUEL_OPPONENT;
  if (duelist == DUEL_OPPONENT)
    return DUEL_PLAYER;
  return 0xFF;
}

static void ArmOpponentSpellTrapLock(u8 summonerFixedDuelist)
{
  u8 opponent = OpponentFixedDuelistForSummoner(summonerFixedDuelist);

  if (opponent == 0xFF)
    return;

  gTheWickedAvatarLockFixedDuelist = opponent;
  gTheWickedAvatarLockTurnsRemaining = THE_WICKED_AVATAR_LOCK_TURNS;
}

static void ResolveTheWickedAvatarNormalSummon(struct DuelCard *zone, u8 summonerFixedDuelist)
{
  Duel_ShowCardEffectText(THE_WICKED_AVATAR, CARD_EFFECT_TEXT_THE_WICKED_AVATAR_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  ArmOpponentSpellTrapLock(summonerFixedDuelist);
  zone->unk4 |= WICKED_AVATAR_LOCK_ARMED;
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

void FinishTheWickedAvatarTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  u8 summoner;

  (void)fixedCol;

  if (zone == NULL || zone->id != THE_WICKED_AVATAR)
    return;
  if (zone->unk4 & WICKED_AVATAR_LOCK_ARMED)
    return;

  summoner = FixedDuelistForMonsterFixedRow(fixedRow);
  if (summoner == 0xFF)
    return;

  ResolveTheWickedAvatarNormalSummon(zone, summoner);
}

void ClearTheWickedAvatarLock(void)
{
  gTheWickedAvatarLockFixedDuelist = 0xFF;
  gTheWickedAvatarLockTurnsRemaining = 0;
}

u8 TheWickedAvatar_IsSpellTrapActivationLocked(void)
{
  if (gTheWickedAvatarLockTurnsRemaining == 0)
    return FALSE;
  if (gTheWickedAvatarLockFixedDuelist >= 2)
    return FALSE;

  return WhoseTurn() == gTheWickedAvatarLockFixedDuelist;
}

void TheWickedAvatar_TryDecrementLockAtTurnEnd(void)
{
  u8 finishedDuelist;

  if (gTheWickedAvatarLockTurnsRemaining == 0)
    return;
  if (gTheWickedAvatarLockFixedDuelist >= 2)
    return;

  /* after SwitchTurn(), zone POV is still the ended turn until the next
   * UpdateDuelZonePtrs — use gWhoseTurn (new active) not INACTIVE_DUELIST. */
  finishedDuelist = OtherDuelist(WhoseTurn());
  if (finishedDuelist != gTheWickedAvatarLockFixedDuelist)
    return;

  gTheWickedAvatarLockTurnsRemaining--;
}

u8 TheWickedAvatar_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 highest;
  u16 stat;

  if (zone == NULL || zone->id != THE_WICKED_AVATAR)
    return FALSE;

  highest = FindHighestFaceUpMonsterAtkExceptAvatar();
  stat = (u16)(highest + THE_WICKED_AVATAR_STAT_BONUS);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

void TryTheWickedAvatarOnMonsterPlacement(struct DuelCard *zone)
{
  (void)zone;

  if (AvatarIsActiveOnField())
    RefreshFieldMonsterStatOverlays();
}

void TheWickedAvatar_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone != NULL && zone->id == THE_WICKED_AVATAR && !gAiSimInBatch)
    UpdateDuelGfxExceptField();

  TryTheWickedAvatarOnMonsterPlacement(NULL);
}

unsigned char ShouldActivateTheWickedAvatar(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != THE_WICKED_AVATAR)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return (zone->unk4 & WICKED_AVATAR_LOCK_ARMED) == 0;
}

void ActivateTheWickedAvatar(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  u8 summoner = FixedDuelistForMonsterTurnRow(gActiveEffect.turnRow);

  if (summoner == 0xFF)
    return;

  ResolveTheWickedAvatarNormalSummon(zone, summoner);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheWickedAvatar_SelfCheck(void)
{
  ClearTheWickedAvatarLock();
  if (TheWickedAvatar_IsSpellTrapActivationLocked())
    __builtin_trap();
}
#endif
