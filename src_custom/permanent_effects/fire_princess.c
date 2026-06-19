#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "fire_princess.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern void HandleAtkAndLifePointsAction(void);
extern void DeclareLoser(unsigned char);

struct FirePrincessActionData {
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

extern struct FirePrincessActionData sActionData;

static u8 ZoneHasFaceUpFirePrincess(const struct DuelCard *zone)
{
  /* ponytail: normal hand summon copies isFaceUp=0; attack-position monsters still count */
  return zone != NULL
      && zone->id == FIRE_PRINCESS
      && (zone->isFaceUp || !zone->isDefending);
}

static u8 ControllerHasFaceUpFirePrincess(u8 controller)
{
  u8 row = controller == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (ZoneHasFaceUpFirePrincess(gFixedZones[row][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 LpGainAlreadyHandledForDuelist(u8 gainingDuelist)
{
  u16 currentLp;
  u16 lastHandledLp;

  if (!gFirePrincessLpGainHandled)
    return FALSE;

  currentLp = gDuelLifePoints[gainingDuelist];
  lastHandledLp = gLastHandledLpGainLp[gainingDuelist];

  return currentLp <= lastHandledLp;
}

static void MarkLpGainHandled(void)
{
  gLastHandledLpGainLp[DUEL_PLAYER] = gDuelLifePoints[DUEL_PLAYER];
  gLastHandledLpGainLp[DUEL_OPPONENT] = gDuelLifePoints[DUEL_OPPONENT];
  gFirePrincessLpGainHandled = TRUE;
}

void ClearFirePrincessPending(void)
{
  gPendingFirePrincessTarget = FIRE_PRINCESS_PENDING_NONE;
  gSuppressFirePrincessDamage = FALSE;
  gFirePrincessLpGainHandled = FALSE;
  gLastHandledLpGainLp[DUEL_PLAYER] = 0;
  gLastHandledLpGainLp[DUEL_OPPONENT] = 0;
}

static void DeclareLoserFlagsFromAction(void)
{
  if (sActionData.flags & 4)
    DeclareLoser(DUEL_PLAYER);
  if (sActionData.flags & 16)
    DeclareLoser(DUEL_OPPONENT);
}

static u8 ShouldDeferFirePrincessResolve(void)
{
  if (gHideEffectText)
    return FALSE;

  return gCardEffectTextData.cardId == CARD_NONE;
}

static void ApplyFirePrincessDamage(u8 targetDuelist)
{
  u8 hideEffectText = gHideEffectText;

  gSuppressFirePrincessDamage = TRUE;

  if (targetDuelist == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(FIRE_PRINCESS_DAMAGE);
  else
    SetOpponentLifePointsToSubtract(FIRE_PRINCESS_DAMAGE);

  if (!hideEffectText)
    Duel_ShowEffectTextTyped(FIRE_PRINCESS, 8);

  gHideEffectText = TRUE;
  HandleAtkAndLifePointsAction();
  gHideEffectText = hideEffectText;
  DeclareLoserFlagsFromAction();

  gSuppressFirePrincessDamage = FALSE;
}

static void ApplyFirePrincessForGainer(u8 gainingDuelist)
{
  u8 targetDuelist = gainingDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (!ControllerHasFaceUpFirePrincess(gainingDuelist))
    return;

  ApplyFirePrincessDamage(targetDuelist);
}

void ResolveFirePrincessEffect(void)
{
  u8 gainingDuelist;

  if (gSuppressFirePrincessDamage || IsDuelOver() == TRUE)
    return;

  gainingDuelist = gPendingFirePrincessTarget;
  if (gainingDuelist == FIRE_PRINCESS_PENDING_NONE)
    return;

  gPendingFirePrincessTarget = FIRE_PRINCESS_PENDING_NONE;
  ApplyFirePrincessForGainer(gainingDuelist);
}

void TryNotifyFirePrincessOnLpGainAction(void)
{
  if (gPendingFirePrincessTarget != FIRE_PRINCESS_PENDING_NONE)
    return;

  if (sActionData.id == 7 && sActionData.playerCardAtkOrLifePointsMod > 0)
    TryApplyFirePrincessAfterLpGain(DUEL_PLAYER);
  else if (sActionData.id == 10 && sActionData.opponentCardAtkOrLifePointsMod > 0)
    TryApplyFirePrincessAfterLpGain(DUEL_OPPONENT);
}

void TryApplyFirePrincessAfterLpGain(u8 gainingDuelist)
{
  if (gSuppressFirePrincessDamage || IsDuelOver() == TRUE)
    return;

  if (LpGainAlreadyHandledForDuelist(gainingDuelist))
    return;

  if (IsSkillDrainActiveOnField())
    return;

  if (!ControllerHasFaceUpFirePrincess(gainingDuelist))
    return;

  if (ShouldDeferFirePrincessResolve()) {
    gPendingFirePrincessTarget = gainingDuelist;
    MarkLpGainHandled();
    return;
  }

  ApplyFirePrincessForGainer(gainingDuelist);
  MarkLpGainHandled();
}
