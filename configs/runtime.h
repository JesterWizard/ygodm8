#include "gba/types.h"
#include "gba/defines.h"

typedef struct {
    bool8 restore_life_points_after_duel;
} RuntimeConfig;

#define _maybe_unused __attribute__((unused))

#define LYN_REPLACE_CHECK(name) \
    extern void name(void); \
    static const void *const _maybe_unused lyn_exists_check_##name = &name

/*
 * Build-time PC port settings.
 * Toggle these before building to change default runtime behavior.
 */

extern const RuntimeConfig gRuntimeConfig;
