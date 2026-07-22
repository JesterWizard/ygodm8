#include "global.h"
#include "common-chax.h"
#include "arcana_force_coin.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void sub_8041C94(u8 *text, u16 cardId, u16 cardId2, u16 a, u16 b);
void ResetCardEffectTextData(void);
void SetCardInfo(u16 cardId);

static const u8 sCoinHeadsText[] APPEND_RODATA = "#2#0Coin result: Heads!#1";
static const u8 sCoinTailsText[] APPEND_RODATA = "#2#0Coin result: Tails!#1";

void ArcanaForce_AnnounceCoinResult(u16 cardId, u8 heads)
{
  if (gHideEffectText || cardId == CARD_NONE)
    return;

  ResetCardEffectTextData();
  gCardEffectTextData.cardId = cardId;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94((u8 *)(heads ? sCoinHeadsText : sCoinTailsText), cardId, 0, 0, 0);
  SetCardInfo(cardId);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
}

void ArcanaForce_SetCoin(struct DuelCard *zone, u8 heads)
{
  if (zone == NULL)
    return;

  zone->unk4 = heads ? ARCANA_FORCE_COIN_HEADS : ARCANA_FORCE_COIN_TAILS;
  ArcanaForce_AnnounceCoinResult(zone->id, heads);
}

unsigned char ShouldActivateARCANA_FORCE_0_THE_FOOL(void);
void ActivateARCANA_FORCE_0_THE_FOOL(void);
unsigned char ShouldActivateARCANA_FORCE_EX_THE_DARK_RULER(void);
void ActivateARCANA_FORCE_EX_THE_DARK_RULER(void);
unsigned char ShouldActivateARCANA_FORCE_EX_THE_LIGHT_RULER(void);
void ActivateARCANA_FORCE_EX_THE_LIGHT_RULER(void);
unsigned char ShouldActivateARCANA_FORCE_I_THE_MAGICIAN(void);
void ActivateARCANA_FORCE_I_THE_MAGICIAN(void);
unsigned char ShouldActivateARCANA_FORCE_III_THE_EMPRESS(void);
void ActivateARCANA_FORCE_III_THE_EMPRESS(void);
unsigned char ShouldActivateARCANA_FORCE_IV_THE_EMPEROR(void);
void ActivateARCANA_FORCE_IV_THE_EMPEROR(void);
unsigned char ShouldActivateARCANA_FORCE_THE_CHAOS_RULER(void);
void ActivateARCANA_FORCE_THE_CHAOS_RULER(void);
unsigned char ShouldActivateARCANA_FORCE_VI_THE_LOVERS(void);
void ActivateARCANA_FORCE_VI_THE_LOVERS(void);
unsigned char ShouldActivateARCANA_FORCE_VII_THE_CHARIOT(void);
void ActivateARCANA_FORCE_VII_THE_CHARIOT(void);
unsigned char ShouldActivateARCANA_FORCE_VIII_THE_STRENGTH(void);
void ActivateARCANA_FORCE_VIII_THE_STRENGTH(void);
unsigned char ShouldActivateARCANA_FORCE_XIV_TEMPERANCE(void);
void ActivateARCANA_FORCE_XIV_TEMPERANCE(void);
unsigned char ShouldActivateARCANA_FORCE_XVIII_THE_MOON(void);
void ActivateARCANA_FORCE_XVIII_THE_MOON(void);
unsigned char ShouldActivateARCANA_FORCE_XXI_THE_WORLD(void);
void ActivateARCANA_FORCE_XXI_THE_WORLD(void);

void ArcanaForce_RunSummonCoinIfPending(struct DuelCard *zone, u16 cardId,
                                        void (*activate)(void))
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || activate == NULL || zone->id != cardId)
    return;
  if (!ArcanaForce_CoinPending(zone))
    return;
  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  gActiveEffect.cardId = cardId;
  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = col;
  activate();
}

void TryArcanaForceOnSummonCoinHooks(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  switch (zone->id) {
  case ARCANA_FORCE_0_THE_FOOL:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_0_THE_FOOL,
                                       ActivateARCANA_FORCE_0_THE_FOOL);
    break;
  case ARCANA_FORCE_EX_THE_DARK_RULER:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_EX_THE_DARK_RULER,
                                       ActivateARCANA_FORCE_EX_THE_DARK_RULER);
    break;
  case ARCANA_FORCE_EX_THE_LIGHT_RULER:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_EX_THE_LIGHT_RULER,
                                       ActivateARCANA_FORCE_EX_THE_LIGHT_RULER);
    break;
  case ARCANA_FORCE_I_THE_MAGICIAN:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_I_THE_MAGICIAN,
                                       ActivateARCANA_FORCE_I_THE_MAGICIAN);
    break;
  case ARCANA_FORCE_III_THE_EMPRESS:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_III_THE_EMPRESS,
                                       ActivateARCANA_FORCE_III_THE_EMPRESS);
    break;
  case ARCANA_FORCE_IV_THE_EMPEROR:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_IV_THE_EMPEROR,
                                       ActivateARCANA_FORCE_IV_THE_EMPEROR);
    break;
  case ARCANA_FORCE_THE_CHAOS_RULER:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_THE_CHAOS_RULER,
                                       ActivateARCANA_FORCE_THE_CHAOS_RULER);
    break;
  case ARCANA_FORCE_VI_THE_LOVERS:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_VI_THE_LOVERS,
                                       ActivateARCANA_FORCE_VI_THE_LOVERS);
    break;
  case ARCANA_FORCE_VII_THE_CHARIOT:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_VII_THE_CHARIOT,
                                       ActivateARCANA_FORCE_VII_THE_CHARIOT);
    break;
  case ARCANA_FORCE_VIII_THE_STRENGTH:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_VIII_THE_STRENGTH,
                                       ActivateARCANA_FORCE_VIII_THE_STRENGTH);
    break;
  case ARCANA_FORCE_XIV_TEMPERANCE:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_XIV_TEMPERANCE,
                                       ActivateARCANA_FORCE_XIV_TEMPERANCE);
    break;
  case ARCANA_FORCE_XVIII_THE_MOON:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_XVIII_THE_MOON,
                                       ActivateARCANA_FORCE_XVIII_THE_MOON);
    break;
  case ARCANA_FORCE_XXI_THE_WORLD:
    ArcanaForce_RunSummonCoinIfPending(zone, ARCANA_FORCE_XXI_THE_WORLD,
                                       ActivateARCANA_FORCE_XXI_THE_WORLD);
    break;
  default:
    break;
  }
}
