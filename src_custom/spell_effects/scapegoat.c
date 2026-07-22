#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define SCAPEGOAT_TOKEN_COUNT 4

/* Ceiling: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in.
 * Ceiling: wrong Type/Attribute (Fairy/LIGHT vs Beast/EARTH); upgrade: add
 * SHEEP_TOKEN card data + art, then swap this define. */
#define SCAPEGOAT_TOKEN_ID MOON_TOKEN

void LockMonsterCardsInRow(unsigned char turnRow);
void UpdateDuelGfxExceptField(void);

static u8 CanSpecialSummonSheepTokens(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) > 0;
}

static void SpecialSummonSheepTokens(void)
{
  u8 i;
  u8 empty;
  u8 summonCount;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  empty = (u8)NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  summonCount = empty;
  if (summonCount > SCAPEGOAT_TOKEN_COUNT)
    summonCount = SCAPEGOAT_TOKEN_COUNT;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  /* lockMonster → isLocked; many tribute validators skip locked zones. */
  opts.lockMonster = TRUE;
  opts.markSpecialSummon = FALSE;

  for (i = 0; i < summonCount; i++) {
    if (i + 1 == summonCount)
      opts.updateGfx = TRUE;

    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, SCAPEGOAT_TOKEN_ID, opts)
        != DUEL_ACTION_OK)
      break;
  }
}

static void SCAPEGOAT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(SCAPEGOAT);

  if (IsDuelOver() == TRUE)
    return;

  if (!CanSpecialSummonSheepTokens())
    return;

  SpecialSummonSheepTokens();

  if (IsDuelOver() == TRUE)
    return;

  /* Block further Normal Summons this turn (vanilla summoningBlocked path). */
  BlockTurnSummoning(ACTIVE_DUELIST);
  LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);

  /* Ceiling: LockMonsterCardsInRow also blocks Normal Set of monsters.
   * Ceiling: cannot allow Set while blocking Summon without a menu hook that
   * distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly. */
  /* Ceiling: token tribute-lock is only via isLocked — not all tribute paths
   * honor it, and Tokens can still be used for non-Tribute costs.
   * Ceiling: best-effort lockMonster; upgrade: tribute validator excludes
   * SCAPEGOAT_TOKEN_ID / token flag. */

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectSCAPEGOAT(void)
{
  if (Duel_TryResolveSpellThroughTraps(SCAPEGOAT, SCAPEGOAT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
