#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "deck_menu.h"
#include "fusion_recipes.h"
#include "elemental_hero_electrum.h"
#include "gfx_reg_buffers.h"
#include "spell_effects.h"

void InitDeckData(void);
void ClearGraphicsBuffers(void);

/* ponytail: fusion mechanic. Recipe table lives in fusion_recipes.c. */

struct MonsterSource {
    struct DuelCard *zone;
};

static u8 CollectMonsters(struct MonsterSource *out, u8 maxOut)
{
    u8 count = 0;
    u8 i;

    /* Hand first — hand cards have priority for sacrifice. */
    for (i = 0; i < MAX_ZONES_IN_ROW && count < maxOut; i++) {
        struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];
        if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
            out[count++].zone = zone;
    }

    for (i = 0; i < MAX_ZONES_IN_ROW && count < maxOut; i++) {
        struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
        if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
            out[count++].zone = zone;
    }

    return count;
}

static u8 RecipeIsFeasible(const struct FusionRecipe *recipe,
                           struct MonsterSource *monsters, u8 monsterCount)
{
    u8 found1 = 0, found2 = 0;
    u8 usedMask = 0;
    u8 i;

    if (recipe->result == CARD_NONE)
        return FALSE;

    if (recipe->material1 == FUSION_RECIPE_WILDCARD) {
        found1 = 1;
    } else {
        for (i = 0; i < monsterCount; i++) {
            if (!(usedMask & (1 << i)) && monsters[i].zone->id == recipe->material1) {
                found1 = 1;
                usedMask |= (1 << i);
                break;
            }
        }
    }
    if (!found1) return FALSE;

    if (recipe->material2 == FUSION_RECIPE_WILDCARD) {
        for (i = 0; i < monsterCount; i++) {
            if (!(usedMask & (1 << i))) { found2 = 1; break; }
        }
    } else {
        for (i = 0; i < monsterCount; i++) {
            if (!(usedMask & (1 << i)) && monsters[i].zone->id == recipe->material2)
                { found2 = 1; break; }
        }
    }
    return found2;
}

static u8 SelectMaterials(const struct FusionRecipe *recipe,
                          struct MonsterSource *monsters, u8 monsterCount,
                          struct DuelCard **mat1, struct DuelCard **mat2)
{
    u8 usedMask = 0;
    u8 i;

    *mat1 = NULL; *mat2 = NULL;

    /* Material slots are ordered: hand-first list means hand cards match first. */
    if (recipe->material1 != FUSION_RECIPE_WILDCARD) {
        for (i = 0; i < monsterCount; i++) {
            if (monsters[i].zone->id == recipe->material1) {
                *mat1 = monsters[i].zone; usedMask |= (1 << i); break;
            }
        }
    }
    if (recipe->material2 != FUSION_RECIPE_WILDCARD) {
        for (i = 0; i < monsterCount; i++) {
            if (!(usedMask & (1 << i)) && monsters[i].zone->id == recipe->material2)
                { *mat2 = monsters[i].zone; usedMask |= (1 << i); break; }
        }
    }
    /* Wildcards fill from earliest (hand-priority) not yet used. */
    if (*mat1 == NULL && recipe->material1 == FUSION_RECIPE_WILDCARD) {
        for (i = 0; i < monsterCount; i++) {
            if (!(usedMask & (1 << i)))
                { *mat1 = monsters[i].zone; usedMask |= (1 << i); break; }
        }
    }
    if (*mat2 == NULL && recipe->material2 == FUSION_RECIPE_WILDCARD) {
        for (i = 0; i < monsterCount; i++) {
            if (!(usedMask & (1 << i)))
                { *mat2 = monsters[i].zone; break; }
        }
    }
    return (*mat1 != NULL && *mat2 != NULL) ? 2 : 0;
}

static void ExecuteFusionByRecipe(const struct FusionRecipe *recipe)
{
    struct MonsterSource monsters[10];
    u8 monsterCount;
    struct DuelCard *mat1 = NULL, *mat2 = NULL;
    s8 emptyZone;
    struct DuelSummonOpts opts;

    monsterCount = CollectMonsters(monsters, 10);
    if (monsterCount < 2) return;

    if (SelectMaterials(recipe, monsters, monsterCount, &mat1, &mat2) < 2) return;

    emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
    if (emptyZone < 0) return;

    Duel_ShowEffectText(POLYMERIZATION);
    if (IsDuelOver() == TRUE) return;

    /* Send materials to the GY. ClearZoneAndSendMonToGraveyard works for
       hand zones (reads id, clears slot, sets GY top-card). */
    ClearZoneAndSendMonToGraveyard(mat1, ACTIVE_DUELIST);
    ClearZoneAndSendMonToGraveyard(mat2, ACTIVE_DUELIST);

    /* Destroy the Polymerization spell on the field. */
    ClearZoneAndSendMonToGraveyard(
        gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

    /* Place the fusion monster on the field. */
    opts = Duel_DefaultSpecialSummonOpts(FALSE);
    opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
    Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, recipe->result, opts);

    if (recipe->result == ELEMENTAL_HERO_ELECTRUM)
      ElementalHeroElectrum_OnFusionSummoned();

    /* ponytail: fusion summoned face-down in attack position */
    {
        u8 i;
        for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
            struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
            if (zone->id == recipe->result && zone->isFaceUp) {
                FlipCardFaceDown(zone);
                break;
            }
        }
    }
}

static void ShowFusionPicker(void)
{
    struct MonsterSource monsters[10];
    u8 monsterCount;
    u8 feasibleRecipeIndices[16];
    u8 feasibleCount = 0;
    u8 i;

    monsterCount = CollectMonsters(monsters, 10);
    if (monsterCount < 2) return;

    for (i = 0; i < FusionRecipe_Count(); i++) {
        if (RecipeIsFeasible(&gFusionRecipes[i], monsters, monsterCount))
            feasibleRecipeIndices[feasibleCount++] = i;
    }

    if (feasibleCount == 0) return;
    if (feasibleCount == 1) {
        ExecuteFusionByRecipe(&gFusionRecipes[feasibleRecipeIndices[0]]);
        return;
    }

    /* Multiple fusions possible — let the player pick. */
    {
        u8 savedDeckMenu[sizeof(gDeckMenu)];
        u8 j;

        for (j = 0; j < sizeof(gDeckMenu); j++)
            ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

        for (j = 0; j < feasibleCount; j++)
            gDeckMenu.cards[j] = gFusionRecipes[feasibleRecipeIndices[j]].result;
        gDeckMenu.cardCount = feasibleCount;
        gDeckMenu.currentPos = 0;

        ClearGraphicsBuffers();
        LoadOam();
        LoadPalettes();

        DisableDisplay();
        InitDeckData();
        DeckMenuMainReadOnly();

        /* Determine which card was selected. */
        {
            u16 chosenId;
            u8 chosenRecipeIdx = 0xFF;

            chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
            for (j = 0; j < feasibleCount; j++) {
                if (gFusionRecipes[feasibleRecipeIndices[j]].result == chosenId) {
                    chosenRecipeIdx = feasibleRecipeIndices[j];
                    break;
                }
            }

            for (j = 0; j < sizeof(gDeckMenu); j++)
                ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

            /* Re-init deck state from saved backup. */
            ClearGraphicsBuffers();
            LoadOam();
            LoadPalettes();

            if (chosenRecipeIdx != 0xFF)
                ExecuteFusionByRecipe(&gFusionRecipes[chosenRecipeIdx]);
        }
    }
}

APPEND_TEXT void EffectPolymerization(void)
{
    if (WhoseTurn() != DUEL_PLAYER) {
        /* AI path: pick first feasible fusion (highest ATK if multiple). */
        struct MonsterSource monsters[10];
        u8 monsterCount = CollectMonsters(monsters, 10);
        u8 i;
        u16 bestAtk = 0;
        s8 bestRecipeIdx = -1;

        if (monsterCount < 2) {
            if (!gHideEffectText) PlayMusic(SFX_FORBIDDEN);
            return;
        }

        for (i = 0; i < FusionRecipe_Count(); i++) {
            if (!RecipeIsFeasible(&gFusionRecipes[i], monsters, monsterCount))
                continue;
            SetCardInfo(gFusionRecipes[i].result);
            if (bestRecipeIdx < 0 || gCardInfo.atk > bestAtk) {
                bestRecipeIdx = (s8)i;
                bestAtk = gCardInfo.atk;
            }
        }

        if (bestRecipeIdx < 0) {
            if (!gHideEffectText) PlayMusic(SFX_FORBIDDEN);
            return;
        }

        ExecuteFusionByRecipe(&gFusionRecipes[bestRecipeIdx]);
        return;
    }

    /* Player path: check feasibility then show picker (or auto-execute). */
    {
        struct MonsterSource monsters[10];
        u8 monsterCount = CollectMonsters(monsters, 10);
        u8 hasAny = 0;
        u8 i;

        if (monsterCount < 2) {
            if (!gHideEffectText) PlayMusic(SFX_FORBIDDEN);
            return;
        }

        for (i = 0; i < FusionRecipe_Count(); i++) {
            if (RecipeIsFeasible(&gFusionRecipes[i], monsters, monsterCount)) {
                hasAny = 1;
                break;
            }
        }

        if (!hasAny) {
            if (!gHideEffectText) PlayMusic(SFX_FORBIDDEN);
            return;
        }

        ShowFusionPicker();
    }
}
