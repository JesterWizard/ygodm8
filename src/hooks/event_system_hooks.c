#include "global.h"
#include "event_system.h"
#include "configs/runtime.h"

#include "generated/event_script_replacements.inc"

const struct Script *EventSystem_ResolveScript(const struct Script *script) {
  unsigned i;

  for (i = 0; i < gEventScriptReplacementCount; i++)
    if (gEventScriptReplacements[i].vanilla == script)
      return gEventScriptReplacements[i].replacement;

  return script;
}
