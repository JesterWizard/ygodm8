#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"

void sub_8054AB0(u8, struct ScriptCtx *);
void sub_8054EC8(void);
void sub_8054F28(void);
void sub_8053F30(struct ScriptCtx *);
void sub_80540B0(struct ScriptCtx *);
void sub_8054150(struct ScriptCtx *);
void sub_80541F4(struct ScriptCtx *);
void sub_805429C(struct ScriptCtx *);
void sub_8054320(struct ScriptCtx *);
void sub_80543A4(struct ScriptCtx *);
void sub_805444C(struct ScriptCtx *);
void sub_80544F4(struct ScriptCtx *);
void sub_805459C(struct ScriptCtx *);
void sub_8054644(struct ScriptCtx *);
void sub_80547D0(struct ScriptCtx *);
void sub_8054878(struct ScriptCtx *);
void sub_8054920(struct ScriptCtx *);
void sub_80549E8(struct ScriptCtx *);
void sub_8055048(void);
void sub_80550C0(struct ScriptCtx *);
void sub_8055124(struct ScriptCtx *);
void sub_8054FB0(void);
void StartCutscene(u8);
void CreditsMain(void);
void CardPasswordMain(void);

LYN_REPLACE_CHECK(sub_8054AB0);
APPEND_TEXT void sub_8054AB0__Replacement(u8 arg0, struct ScriptCtx *script)
{
    switch (arg0)
    {
    case 0:
        sub_8054EC8();
        break;
    case 1:
        sub_8054F28();
        break;
    case 2:
        sub_8053F30(script);
        break;
    case 3:
        sub_80540B0(script);
        break;
    case 4:
        sub_8054150(script);
        break;
    case 5:
        sub_80541F4(script);
        break;
    case 6:
        sub_805429C(script);
        break;
    case 7:
        sub_8054320(script);
        break;
    case 8:
        sub_80543A4(script);
        break;
    case 9:
        sub_805444C(script);
        break;
    case 10:
        sub_80544F4(script);
        break;
    case 11:
        sub_805459C(script);
        break;
    case 12:
        sub_8054644(script);
        break;
    case 13:
        sub_80547D0(script);
        break;
    case 14:
        sub_8054878(script);
        break;
    case 15:
        StartCutscene(0);
        break;
    case 16:
        StartCutscene(1);
        break;
    case 17:
        CardShopBuyMain();
        OverworldLoadGraphics();
        sub_80533BC();
        break;
    case 18:
        CardShopSellMain();
        OverworldLoadGraphics();
        sub_80533BC();
        break;
    case 19:
        CardPasswordMain();
        OverworldLoadGraphics();
        break;
    case 20:
        CreditsMain();
        break;
    case 21:
        sub_8054FB0();
        break;
    case 22:
        sub_8054920(script);
        break;
    case 23:
        sub_80549E8(script);
        break;
    case 24:
        sub_8055048();
        break;
    case 25:
        sub_80550C0(script);
        break;
    case 32:
        sub_8055124(script);
        break;
    case 33:
        StartCutscene(8);
        break;
    case 34:
        StartCutscene(7);
        break;
    case 35:
        if (gRuntimeConfig.enable_password_terminal_feedback != TRUE)
            RemoveMoney(1000);
        break;
    }
}
