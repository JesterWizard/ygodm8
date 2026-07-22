#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"
#include "spell_striker.h"

void UpdateDuelGfxExceptField(void);

struct SpellStrikerActionData {
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

extern struct SpellStrikerActionData sActionData;

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 OwnGyHasSpell(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return IsSpellCard(gDuel.duelistbattleState[fixedDuelist].graveyard);

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static s8 FindFirstOwnSpellGyIndex(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsSpellCard(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 BanishOneOwnSpellFromGy(u8 fixedDuelist)
{
  s8 gyIndex = FindFirstOwnSpellGyIndex(fixedDuelist);

  if (gyIndex < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  return Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)gyIndex) != CARD_NONE;
}

unsigned char CanActivateSPELL_STRIKER(void)
{
  if (gMonEffect.id != SPELL_STRIKER)
    return FALSE;

  /* Direct attack + no self battle damage via CanSpellStrikerAttackDirectly /
   * ApplySpellStrikerNoSelfBattleDamage. */
  return FALSE;
}

void ActivateSPELL_STRIKEREffect(void)
{
  Duel_ShowEffectTextTyped(SPELL_STRIKER, 2);
}

u8 CanSpellStrikerAttackDirectly(u16 cardId)
{
  return cardId == SPELL_STRIKER;
}

void ApplySpellStrikerNoSelfBattleDamage(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4
      && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (sActionData.playerCardId == SPELL_STRIKER && playerDamage > 0) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= (u8)~4;
  }

  if (sActionData.opponentCardId == SPELL_STRIKER && opponentDamage > 0) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= (u8)~16;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

u8 CanSpecialSummonSpellStrikerFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForActive();

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != SPELL_STRIKER)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return OwnGyHasSpell(fixedDuelist);
}

u8 TrySpecialSummonSpellStrikerFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();

  if (!CanSpecialSummonSpellStrikerFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(SPELL_STRIKER, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!BanishOneOwnSpellFromGy(fixedDuelist))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK;
}
