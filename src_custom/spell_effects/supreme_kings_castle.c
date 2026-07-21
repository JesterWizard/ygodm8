#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"
#include "supreme_kings_castle.h"

void SetDuelFieldGfx(u8 field);
extern int NumCardsInDeck(unsigned char);
extern struct DuelDeck gDuelDecks[2];

static u8 sSupremeKingsCastleBattleUsed APPEND_DATA = {0};

static const char sEvilHeroArchetypeName[] APPEND_RODATA = "Evil HERO";

struct SupremeKingsActionData {
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

extern struct SupremeKingsActionData sActionData;

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == SUPREME_KINGS_CASTLE || cardId == PSEUDO_SPACE || cardId == HARPIES_HUNTING_GROUND
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE || cardId == NEO_SPACE)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

static void SUPREME_KINGS_CASTLE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(SUPREME_KINGS_CASTLE);

  /* ponytail: "Fusion Summon monsters that must be Special Summoned with Dark
   * Fusion, with effects other than Dark Fusion" needs Evil HERO summon gates
   * to check SupremeKingsCastle_IsActive. Ceiling: face-up field only. */
}

u8 SupremeKingsCastle_IsActive(void)
{
  return Duel_FindBackrowCard(DUEL_PLAYER, SUPREME_KINGS_CASTLE, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, SUPREME_KINGS_CASTLE, TRUE) != NULL;
}

void SupremeKingsCastle_ClearOnTurnBoundary(void)
{
  sSupremeKingsCastleBattleUsed = FALSE;
}

static u8 IsEvilHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sEvilHeroArchetypeName);
}

static u8 TrySendEvilHeroFromDeck(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u8 found = 0xFF;
  u16 cardId;

  for (i = top; i < deckSize; i++) {
    if (IsEvilHeroMonster(gDuelDecks[fixedDuelist].cards[i])) {
      found = i;
      break;
    }
  }

  if (found == 0xFF)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[found];
  for (i = found; i > top; i--)
    gDuelDecks[fixedDuelist].cards[i] = gDuelDecks[fixedDuelist].cards[i - 1];
  gDuelDecks[fixedDuelist].cardsDrawn++;
  GraveyardExpand_PushTurn(
      gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
          ? ACTIVE_DUELIST
          : INACTIVE_DUELIST,
      cardId);
  return TRUE;
}

void ApplySupremeKingsCastleBattleAtkBoost(void)
{
  u8 attackerDuelist;
  u16 attackerCardId;
  u16 *attackerAtk;
  u16 defenderCardId;
  u8 fixedDuelist;
  struct DuelCard *attackerZone;
  u8 attackerRow;
  u8 attackerCol;

  if (!SupremeKingsCastle_IsActive() || sSupremeKingsCastleBattleUsed)
    return;
  if (!(sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4
        || sActionData.id == 5 || sActionData.id == 6))
    return;

  if (sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4) {
    attackerDuelist = DUEL_PLAYER;
    attackerCardId = sActionData.playerCardId;
    attackerAtk = &sActionData.playerCardAtkOrLifePointsMod;
    defenderCardId = sActionData.opponentCardId;
    attackerRow = sActionData.playerMonsterRow;
    attackerCol = sActionData.unkA;
  } else {
    attackerDuelist = DUEL_OPPONENT;
    attackerCardId = sActionData.opponentCardId;
    attackerAtk = &sActionData.opponentCardAtkOrLifePointsMod;
    defenderCardId = sActionData.playerCardId;
    attackerRow = sActionData.opponentMonsterRow;
    attackerCol = sActionData.unk16;
  }

  if (attackerCardId == CARD_NONE || defenderCardId == CARD_NONE)
    return;
  if (!Duel_CardHasMonsterType(attackerCardId, TYPE_FIEND))
    return;
  if (WhoseTurn() != attackerDuelist)
    return;

  fixedDuelist = attackerDuelist;
  /* ponytail: Deck/Extra Evil HERO pick UI skipped — first Deck match auto-sent. */
  if (!TrySendEvilHeroFromDeck(fixedDuelist))
    return;

  attackerZone = gFixedZones[attackerRow][attackerCol];
  SetCardInfo(attackerCardId);
  *attackerAtk = Duel_ClampStat((u32)*attackerAtk + (u32)gCardInfo.level * 200);
  if (attackerZone != NULL && attackerZone->id == attackerCardId)
    (void)attackerZone;
  sSupremeKingsCastleBattleUsed = TRUE;
  Duel_ShowEffectText(SUPREME_KINGS_CASTLE);
}

APPEND_TEXT void EffectSUPREME_KINGS_CASTLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(SUPREME_KINGS_CASTLE, SUPREME_KINGS_CASTLE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SUPREME_KINGS_CASTLE_SelfCheck(void)
{
  if (!IsEvilHeroMonster(EVIL_HERO_MALICIOUS_EDGE))
    while (1)
      ;
  if (IsEvilHeroMonster(ELEMENTAL_HERO_AVIAN))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(SUPREME_KINGS_CASTLE))
    while (1)
      ;
}
#endif
