#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "destiny_hero_dasher.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "gladiator_beast_battled.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct DasherActionData {
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

extern struct DasherActionData sActionData;

static u8 sDasherDefAtBpEndRow APPEND_DATA = {0xFF};
static u8 sDasherDefAtBpEndCol APPEND_DATA = {0};
static u8 sDasherDrawSsUsed APPEND_DATA = {0};

extern u8 gDrawPhaseNormalDrawActive;

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->id != DESTINY_HERO_DASHER;
}

static u8 FieldHasTributeTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTributeTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* OPT tribute 1 other → +2 tempStage (~1000 ATK until EP via ResetTempStagesForAllCards). */
  if (self->tempStage < 126)
    self->tempStage += 2;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 bestCol = 0;
  u8 found = FALSE;
  u16 lowestAtk = 0xFFFF;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidTributeTarget(*outRow, col))
      continue;

    zone = gFixedZones[*outRow][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (!found || atk < lowestAtk) {
      found = TRUE;
      lowestAtk = atk;
      bestCol = col;
    }
  }

  if (!found)
    return FALSE;

  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateDESTINY_HERO_DASHER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DASHER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DASHER)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTributeTarget();
}

void ActivateDESTINY_HERO_DASHEREffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DASHER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTributeTarget, ResolveTributeTarget, CancelTargeting,
                     AiPickTributeTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static u8 DasherInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == DESTINY_HERO_DASHER;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_DASHER)
      return TRUE;
  }

  return FALSE;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void MarkDasherDefAtBattlePhaseEnd(u8 fixedRow, u8 fixedCol)
{
  sDasherDefAtBpEndRow = fixedRow;
  sDasherDefAtBpEndCol = fixedCol;
}

void MarkDestinyHeroDasherAttackedFromBattle(void)
{
  if (gHideEffectText)
    return;

  if (sActionData.opponentCardId == CARD_NONE
      || GetTypeGroup(sActionData.opponentCardId) != TYPE_GROUP_MONSTER)
    return;

  if (sActionData.playerCardId == DESTINY_HERO_DASHER)
    MarkDasherDefAtBattlePhaseEnd(sActionData.playerMonsterRow, sActionData.unkA);
  else if (sActionData.opponentCardId == DESTINY_HERO_DASHER)
    MarkDasherDefAtBattlePhaseEnd(sActionData.opponentMonsterRow, sActionData.unk16);
}

void TryApplyDestinyHeroDasherBattlePhaseEnd(void)
{
  struct DuelCard *zone;

  if (sDasherDefAtBpEndRow == 0xFF)
    return;

  zone = gFixedZones[sDasherDefAtBpEndRow][sDasherDefAtBpEndCol];
  sDasherDefAtBpEndRow = 0xFF;

  if (zone == NULL || zone->id != DESTINY_HERO_DASHER)
    return;

  zone->isDefending = TRUE;
  zone->isFaceUp = TRUE;
  RefreshFieldMonsterStatOverlays();
}

void TryApplyDestinyHeroDasherOnDraw(u8 duelist, u16 cardDrawn, u8 handSlot)
{
  u8 fixedDuelist;
  struct DuelSummonOpts opts;
  struct DuelCard *drawnCard;

  if (!gDrawPhaseNormalDrawActive || sDasherDrawSsUsed)
    return;

  if (duelist != WhoseTurn())
    return;

  if (GetTypeGroup(cardDrawn) != TYPE_GROUP_MONSTER)
    return;

  fixedDuelist = FixedDuelistForTurnDuelist(duelist);
  if (!DasherInGy(fixedDuelist))
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  drawnCard = SixCardHand_GetFixed(duelist, handSlot);
  if (drawnCard == NULL || drawnCard->id != cardDrawn)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DASHER, 3);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHandZone(duelist, handSlot, opts) != DUEL_ACTION_OK)
    return;

  sDasherDrawSsUsed = TRUE;
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
