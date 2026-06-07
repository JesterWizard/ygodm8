#ifndef EVENT_OBJECT_SLOTS_H
#define EVENT_OBJECT_SLOTS_H

/* Per-map object slot aliases (local IDs).
 *
 * The player always occupies slot 0. For maps with repeated sprites
 * (Neo Ghouls, Chevaliers, guards, etc.), define LOCALID_* at the top
 * of the map script after the includes:
 *
 *   #define LOCALID_CHEVALIER_BACK_L  2
 *   #define LOCALID_CHEVALIER_BACK_R  3
 *
 *   LOAD_SPRITE(LOCALID_CHEVALIER_BACK_L, SPRITE_CHEVALIER)
 *   WALK_OBJECT_Y(LOCALID_CHEVALIER_FRONT_R, 96)
 *   OBJECT_EFFECT(OBJECT_LOCALID(LOCALID_CHEVALIER_BACK_L), OBJECT_EFFECT_JUMPING)
 *
 * Unique characters can still use SPRITE_* when bound to one slot via
 * LOAD_SPRITE. SPRITE_* names in object commands fail when the same
 * sprite appears on multiple slots.
 *
 * REACTION and OBJECT_EFFECT take bitmasks. Wrap a local ID with
 * OBJECT_LOCALID(), or combine with |.
 */

#define SLOT_PLAYER 0
#define OBJECT_LOCALID(local_id) (1 << (local_id))

#endif
