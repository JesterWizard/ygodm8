#ifndef GUARD_EVENT_SYSTEM_H
#define GUARD_EVENT_SYSTEM_H

#include "overworld.h"

typedef struct {
  const struct Script *vanilla;
  const struct Script *replacement;
} EventScriptReplacement;

extern const EventScriptReplacement gEventScriptReplacements[];
extern const unsigned gEventScriptReplacementCount;

const struct Script *EventSystem_ResolveScript(const struct Script *script);

#endif
