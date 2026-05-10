#include "gba/types.h"
#include "gba/defines.h"

typedef struct {
    bool8 restore_life_points_after_duel;
} RuntimeConfig;

/*
 * Build-time PC port settings.
 * Toggle these before building to change default runtime behavior.
 */

extern const RuntimeConfig gRuntimeConfig;
