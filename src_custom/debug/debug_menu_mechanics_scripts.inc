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

/* ---------- Type Elements ---------- */

static const u8 sElem_Title[] APPEND_RODATA = "Type Elements";

static const u8 sElem_I1[] APPEND_RODATA =
    "Monsters have elements.#0In battle they work like#0rock-paper-scissors.#1";
static const u8 sElem_I2[] APPEND_RODATA =
    "If yours beats theirs,#0you destroy them even#0if your ATK is lower!#1";
static const u8 sElem_I3[] APPEND_RODATA =
    "Shadow beats Light.#0Attack Blue-Eyes with#0Kuriboh to see it in action.#1";
static const u8 sElem_I4[] APPEND_RODATA =
    "Then summon another monster and attack directly#1to win.";
static const u8 sElem_O1[] APPEND_RODATA =
    "That is the element#0system, matchups matter#0as much as raw ATK.#1";
static const u8 sElem_O2[] APPEND_RODATA =
    "Light beats Fiend.#0Fiend beats Dream.#0Dream beats Shadow.#1";
static const u8 sElem_O3[] APPEND_RODATA =
    "Fire beats Forest.#0Forest beats Wind.#0Wind beats Earth.#1";
static const u8 sElem_O4[] APPEND_RODATA =
    "Earth beats Thunder.#0Thunder beats Water.#0Water beats Fire.#1";
static const u8 sElem_O5[] APPEND_RODATA =
    "Divine is immune.#0Use the right elements#0to beat your opponent's monsters!#1";

static const struct MechanicsTutorialLine sElem_Intro[] APPEND_RODATA = {
  MT_LINE(PORTRAIT_YUGI, sElem_I1),
  MT_LINE(PORTRAIT_YUGI, sElem_I2),
  MT_LINE(PORTRAIT_YUGI, sElem_I3),
  MT_LINE(PORTRAIT_YUGI, sElem_I4),
  MT_END,
};

static const struct MechanicsTutorialLine sElem_Outro[] APPEND_RODATA = {
  MT_LINE(PORTRAIT_YUGI, sElem_O1),
  MT_LINE(PORTRAIT_YUGI, sElem_O2),
  MT_LINE(PORTRAIT_YUGI, sElem_O3),
  MT_LINE(PORTRAIT_YUGI, sElem_O4),
  MT_LINE(PORTRAIT_YUGI, sElem_O5),
  MT_END,
};
