#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_steam_healer.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct ElementalHeroSteamHealerActionData {
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

extern struct ElementalHeroSteamHealerActionData sActionData;

void ClearElementalHeroSteamHealerPending(void) {
  gPendingElementalHeroSteamHealerDuelist = ELEMENTAL_HERO_STEAM_HEALER_PENDING_NONE;
  gPendingElementalHeroSteamHealerDestroyedAtk = 0;
}

static u8 IsMonsterBattleAction(u8 id) {
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u16 GetOriginalCardAtk(u16 cardId) {
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].atk;
}

static void MarkPendingGain(u8 duelist, u16 destroyedCardId) {
  u16 destroyedAtk = GetOriginalCardAtk(destroyedCardId);

  if (destroyedAtk == 0)
    return;

  gPendingElementalHeroSteamHealerDuelist = duelist;
  gPendingElementalHeroSteamHealerDestroyedAtk = destroyedAtk;
}

void ResolveElementalHeroSteamHealerBattleEffect(void) {
  u8 duelist;
  u16 destroyedAtk;

  duelist = gPendingElementalHeroSteamHealerDuelist;
  if (duelist == ELEMENTAL_HERO_STEAM_HEALER_PENDING_NONE)
    return;

  destroyedAtk = gPendingElementalHeroSteamHealerDestroyedAtk;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_STEAM_HEALER, 3);
  ClearElementalHeroSteamHealerPending();

  if (Duel_ChangeLp(duelist, destroyedAtk, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void ApplyElementalHeroSteamHealerBattleEffect(void) {
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == ELEMENTAL_HERO_STEAM_HEALER
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    MarkPendingGain(DUEL_PLAYER, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == ELEMENTAL_HERO_STEAM_HEALER
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    MarkPendingGain(DUEL_OPPONENT, sActionData.playerCardId);
  } else {
    return;
  }

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveElementalHeroSteamHealerBattleEffect();
}
