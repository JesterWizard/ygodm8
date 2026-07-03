#ifndef GUARD_CARD_EFFECT_TEXTS_H
#define GUARD_CARD_EFFECT_TEXTS_H

/* Generated from manifest effect_texts — do not edit. */

enum CardEffectTextId {
  CARD_EFFECT_TEXT_NONE = 0,
  CARD_EFFECT_TEXT_ELEMENTAL_HERO_CORE_POPUP_1,
  CARD_EFFECT_TEXT_ELEMENTAL_HERO_CORE_POPUP_2,
  NUM_CARD_EFFECT_TEXTS
};

const u8 *GetCardEffectText(u16 effectTextId);

#endif /* GUARD_CARD_EFFECT_TEXTS_H */
