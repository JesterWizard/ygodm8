#include "global.h"
#include "common-chax.h"
#include "amazoness_sage.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct AmazonessSageActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct AmazonessSageActionData sActionData;

static u8 OppBackrowFixedForSage(u8 sageFixedRow)
{
  return sageFixedRow == PLAYER_MONSTER_ROW ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 IsSpellTrapOnBackrow(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 OppHasSpellTrap(u8 sageFixedRow)
{
  u8 col;
  u8 back = OppBackrowFixedForSage(sageFixedRow);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsSpellTrapOnBackrow(back, col))
      return TRUE;
  }

  return FALSE;
}

static u8 GraveyardDuelistForBackrow(u8 fixedRow)
{
  return fixedRow == OPPONENT_BACKROW ? DUEL_OPPONENT : DUEL_PLAYER;
}

static u8 IsValidSageTarget(u8 fixedRow, u8 fixedCol)
{
  if (gAmazonessSagePendingRow == AMAZONESS_SAGE_PENDING_NONE)
    return FALSE;

  if (fixedRow != OppBackrowFixedForSage(gAmazonessSagePendingRow))
    return FALSE;

  return IsSpellTrapOnBackrow(fixedRow, fixedCol);
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self;

  if (!IsValidSageTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForBackrow(fixedRow), TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  self = gFixedZones[gAmazonessSagePendingRow][gAmazonessSagePendingCol];
  if (self != NULL && self->id == AMAZONESS_SAGE)
    MarkMonsterEffectUsed(self);

  ClearAmazonessSagePending();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  ClearAmazonessSagePending();
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 back;

  if (gAmazonessSagePendingRow == AMAZONESS_SAGE_PENDING_NONE)
    return FALSE;

  back = OppBackrowFixedForSage(gAmazonessSagePendingRow);
  *outRow = back;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsSpellTrapOnBackrow(back, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

void ClearAmazonessSagePending(void)
{
  gAmazonessSagePendingRow = AMAZONESS_SAGE_PENDING_NONE;
  gAmazonessSagePendingCol = 0;
}

static u8 SageAttackedAndSurvived(u8 *outRow, u8 *outCol)
{
  if (sActionData.playerCardId == AMAZONESS_SAGE
      && (sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    *outRow = sActionData.playerMonsterRow;
    *outCol = sActionData.unkA;
    return TRUE;
  }

  if (sActionData.opponentCardId == AMAZONESS_SAGE
      && (sActionData.id == 3 || sActionData.id == 5 || sActionData.id == 6)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    *outRow = sActionData.opponentMonsterRow;
    *outCol = sActionData.unk16;
    return TRUE;
  }

  return FALSE;
}

void ApplyAmazonessSageBattleEffect(void)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;

  if (gHideEffectText)
    return;

  if (!SageAttackedAndSurvived(&row, &col))
    return;

  zone = gFixedZones[row][col];
  if (zone == NULL || zone->id != AMAZONESS_SAGE)
    return;

  if (!OppHasSpellTrap(row))
    return;

  gAmazonessSagePendingRow = row;
  gAmazonessSagePendingCol = col;

  if (gUnk2023EA0.unk18 == 0)
    ResolveAmazonessSageBattleEffect();
}

void ResolveAmazonessSageBattleEffect(void)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;

  row = gAmazonessSagePendingRow;
  if (row == AMAZONESS_SAGE_PENDING_NONE)
    return;

  col = gAmazonessSagePendingCol;
  zone = gFixedZones[row][col];
  if (zone == NULL || zone->id != AMAZONESS_SAGE || !OppHasSpellTrap(row)) {
    ClearAmazonessSagePending();
    return;
  }

  Duel_ShowEffectTextTyped(AMAZONESS_SAGE, 3);
  if (IsDuelOver() == TRUE) {
    ClearAmazonessSagePending();
    return;
  }

  gDuelCursor.destY = row;
  gDuelCursor.destX = col;

  Duel_SetupPickZone(IsValidSageTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER && row == PLAYER_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

unsigned char CanActivateAMAZONESS_SAGE(void)
{
  if (gMonEffect.id != AMAZONESS_SAGE)
    return FALSE;

  /* End-of-Damage-Step destroy is live via ApplyAmazonessSageBattleEffect. */
  return FALSE;
}

void ActivateAMAZONESS_SAGEEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_SAGE, 2);
}
