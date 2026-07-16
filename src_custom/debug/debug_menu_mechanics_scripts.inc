/* Mechanics tutorial scripts — author text + portraits here.
 *
 * Add a tutorial:
 *  1. Layout in debug_menu_mechanics_layouts.c (+ header extern).
 *  2. Title / lines below (PORTRAIT_* from overworld.h; text uses #0 newline, #1 wait).
 *  3. One MECHANICS_TUTORIAL_ENTRY in debug_menu_mechanics_table.inc.
 *
 * winOnSummonCardId: after that card's summon cut-in, play outro then end the duel.
 */

/* ---------- Boss Cut-Ins ---------- */

static const u8 sBoss_Title[] APPEND_RODATA = "Boss Cut-Ins";

static const u8 sBoss_I1[] APPEND_RODATA =
    "Some boss monsters#0show a full-art cut-in#0when you summon them.#1";
static const u8 sBoss_I2[] APPEND_RODATA =
    "Tribute Summon#0Yubel from your hand#0and watch it play!#1";
static const u8 sBoss_O1[] APPEND_RODATA =
    "That was the cut-in.#0Any boss with one will#0do the same on summon.#1";

static const struct MechanicsTutorialLine sBoss_Intro[] APPEND_RODATA = {
  MT_LINE(PORTRAIT_YUGI, sBoss_I1),
  MT_LINE(PORTRAIT_YUGI, sBoss_I2),
  MT_END,
};

static const struct MechanicsTutorialLine sBoss_Outro[] APPEND_RODATA = {
  MT_LINE(PORTRAIT_YUGI, sBoss_O1),
  MT_END,
};
