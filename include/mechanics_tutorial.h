#ifndef GUARD_MECHANICS_TUTORIAL_H
#define GUARD_MECHANICS_TUTORIAL_H

#include "gba/types.h"
#include "timed_duel.h"
#include "overworld.h"

/* One textbox line. portraitId = PORTRAIT_* (or PORTRAIT_NONE). text NULL ends a list. */
struct MechanicsTutorialLine {
  u8 portraitId;
  const u8 *text;
};

struct MechanicsTutorialEntry {
  u8 opponentId;
  const u8 *title;
  const struct TimedDuelLayout *layout;
  const struct MechanicsTutorialLine *intro; /* MT_END-terminated; may be NULL */
  const struct MechanicsTutorialLine *outro; /* MT_END-terminated; may be NULL */
  u16 winOnSummonCardId; /* CARD_NONE = no auto-complete on summon anim */
};

#define MT_LINE(portrait, textPtr) { (portrait), (textPtr) }
#define MT_END                     { PORTRAIT_NONE, NULL }

extern u8 gMechanicsTutorialActiveId;
extern u8 gMechanicsTutorialIntroDone;
extern u16 gMechanicsTutorialPendingCardId;

u8 MechanicsTutorial_GetCount(void);
const struct MechanicsTutorialEntry *MechanicsTutorial_GetEntry(u8 index);
const struct MechanicsTutorialEntry *MechanicsTutorial_GetActiveEntry(void);
const struct TimedDuelLayout *MechanicsTutorial_GetActiveLayout(void);
void MechanicsTutorial_FormatMenuTitle(u8 index, u8 *out);

u8 MechanicsTutorial_IsActive(void);
void MechanicsTutorial_ApplySetupIfActive(void);
void MechanicsTutorial_ApplyLifePointsIfActive(void);
u8 MechanicsTutorial_ShouldSkipDrawPhase(u8 turnDuelist);
void MechanicsTutorial_TryShowIntro(void);
void MechanicsTutorial_NoteSummonAnim(u16 cardId);
void MechanicsTutorial_OnSummonAnimFinished(void);
void MechanicsTutorial_HandleWin(void);
void MechanicsTutorial_OnDuelEnd(void);
void MechanicsTutorial_RunAtIndex(u8 index);

#endif // GUARD_MECHANICS_TUTORIAL_H
