#include "global.h"
#include "common-chax.h"
#include "debug_save_anywhere.h"
#include "overworld.h"

void sub_8053404(void);
void sub_804DF5C(int objectId);
void sub_804F1F4(void);

LYN_REPLACE_CHECK(sub_8053D50);
void sub_8053D50__Replacement(u8 obj, u8 arg1, struct ScriptCtx *script) {
  (void)obj;
  (void)arg1;

  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;

  script->unk86 = 0;
  sub_8053404();
  gOverworld.objects[obj].spriteId = arg1;
  sub_804DF5C(obj);
  sub_804F1F4();
}
