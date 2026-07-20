#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sDarkMagicianGirlName[] APPEND_RODATA = "Dark Magician Girl";

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsDarkMagicianGirlMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == DARK_MAGICIAN_GIRL)
    return TRUE;

  return Duel_CardNameContains(cardId, sDarkMagicianGirlName);
}

static u8 ControlsDarkMagicianGirl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsDarkMagicianGirlMonster(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  return MonsterIsFaceUp(zone);
}

u8 CanActivateDARK_BURNING_ATTACK(void)
{
  return ControlsDarkMagicianGirl();
}

static void DARK_BURNING_ATTACK_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  enum DuelActionResult destroyResult;

  Duel_ShowEffectText(DARK_BURNING_ATTACK);

  if (IsDuelOver() == TRUE)
    return;

  if (!ControlsDarkMagicianGirl()) {
    if (spellZone != NULL && spellZone->id == DARK_BURNING_ATTACK)
      Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    else
      UpdateDuelGfxExceptField();
    return;
  }

  destroyResult = Duel_DestroyAllMonstersMatching(INACTIVE_DUELIST_MONSTER_ROW,
                                                   IsFaceUpMonsterZone, FALSE);
  if (destroyResult == DUEL_ACTION_DUEL_OVER)
    return;

  if (spellZone != NULL && spellZone->id == DARK_BURNING_ATTACK)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectDARK_BURNING_ATTACK(void)
{
  if (!CanActivateDARK_BURNING_ATTACK()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DARK_BURNING_ATTACK, DARK_BURNING_ATTACK_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
