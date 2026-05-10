#include "runtime.h"

const RuntimeConfig gRuntimeConfig __attribute__((section(".runtime_config"))) = {
    .restore_life_points_after_duel = TRUE,
};
