#ifndef GUARD_CONSTANTS_DUEL_FIELDS_H
#define GUARD_CONSTANTS_DUEL_FIELDS_H

//TODO: FIELD -> DUEL_FIELD
enum {
  FIELD_ARENA,
  FIELD_FOREST,
  FIELD_WASTELAND,
  FIELD_MOUNTAIN,
  FIELD_SOGEN,
  FIELD_UMI,
  FIELD_YAMI,
  NUM_VANILLA_FIELDS
};

#include "constants/custom_fields_generated.h"

#define IsCustomField(field) ((field) >= FIRST_CUSTOM_FIELD && (field) < NUM_FIELDS)

#endif // GUARD_CONSTANTS_DUEL_FIELDS_H
