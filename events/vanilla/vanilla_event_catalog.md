# Vanilla Event Catalog

Source ROM: `baserom.gba`

## map_00_state_00

- map/state: `0/0`
- music: `4`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_00_state_01

- map/state: `0/1`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E349DC` R `0x08E349E8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E349DC`
  - portrait p16 expr0 pos8
  - dialogue: "The Egyptian God Cards are required to seal away the Dark Being. First, the Egyptian God Cards must "
  - fallthrough
- obj 1 R: `0x08E349E8`
  - portrait p16 expr0 pos8
  - dialogue: "Please. Hurry to the Egypt Exhibition. Reshef the Dark Being will soon engulf the world in darkness."
  - fallthrough

## map_00_state_02

- map/state: `0/2`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E349F4` R `0x08E34A00`
- obj 2: sprite `28` at `128,12` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `31` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `113` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E349F4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34A00`
  - check_flag
  - fallthrough

## map_00_state_03

- map/state: `0/3`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34A84` R `0x08E34A90`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34A84`
  - portrait p16 expr0 pos8
  - dialogue: "In order to imprison the Dark Being resurrected by Sol Chevalsky... We need the Egyptian God Cards. "
  - fallthrough
- obj 1 R: `0x08E34A90`
  - portrait p16 expr0 pos8
  - dialogue: "Please. Hurry to the cruise ship. Reshef the Dark Being will soon engulf the world."
  - fallthrough

## map_00_state_04

- map/state: `0/4`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34A9C` R `0x08E34AA8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34A9C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34AA8`
  - check_flag
  - fallthrough

## map_00_state_05

- map/state: `0/5`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34B14` R `0x08E34B20`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34B14`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34B20`
  - check_flag
  - fallthrough

## map_00_state_06

- map/state: `0/6`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34B50` R `0x08E34B50`
- obj 2: sprite `3` at `65528,52` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `55` at `65528,52` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `49` at `60,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `56` at `60,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34B50`
  - check_flag
  - fallthrough

## map_00_state_07

- map/state: `0/7`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34BBC` R `0x08E34BC8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34BBC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34BC8`
  - check_flag
  - fallthrough

## map_00_state_08

- map/state: `0/8`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34BF8` R `0x08E34C04`
- obj 2: sprite `57` at `60,128` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34BF8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34C04`
  - check_flag
  - fallthrough

## map_00_state_09

- map/state: `0/9`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34C34` R `0x08E34C40`
- obj 2: sprite `57` at `60,128` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34C34`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34C40`
  - check_flag
  - fallthrough

## map_00_state_10

- map/state: `0/10`
- music: `11`

### Initial Sprites
- obj 1: sprite `17` at `65520,53` A `0x08E34D6C` R `0x08E34D78`
- obj 2: sprite `34` at `76,15` A `0x08E34DCC` R `0x08E34DCC`
- obj 3: sprite `35` at `76,27` A `0x08E34DD8` R `0x08E34DD8`
- obj 4: sprite `128` at `86,21` A `0x08E34DE4` R `0x08E34DE4`
- obj 5: sprite `15` at `53,21` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `26` at `43,27` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `26` at `43,15` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E34CF4`
  - play_music
  - portrait p22 expr0 pos8
  - dialogue: "Exodia, obliterate!"
  - play_music
  - command_7c_8
  - delay
  - portrait p0 expr0 pos8
  - dialogue: "Waaaaah!"
  - play_music
  - slide_object
  - play_music
  - slide_object
  - play_music
  - slide_object
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 69, 'wander': 0}
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - delay
  - portrait p14 expr0 pos8
  - dialogue: "Are you all right?"
  - portrait p0 expr0 pos8
  - dialogue: "Big brother!"
  - portrait p22 expr0 pos8
  - dialogue: "Kukuku... Another victim arrives."
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - portrait p14 expr2 pos8
  - dialogue: "Nobody gets away with picking on my brothers!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p14 expr0 pos8
  - dialogue: "Hey! You guys are..."
  - hide_portrait
  - delay
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E34D6C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34D78`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E34DCC`
  - dialogue: "My big brother protects us from bullies!"
  - fallthrough
- obj 3 A: `0x08E34DD8`
  - dialogue: "Don't worry about the Neo Ghouls. Espa can beat them on his own."
  - fallthrough
- obj 4 A: `0x08E34DE4`
  - dialogue: "Espa is really good at dueling and can win without cheating."
  - fallthrough

## map_00_state_11

- map/state: `0/11`
- music: `11`

### Initial Sprites
- obj 1: sprite `17` at `76,21` A `0x08E34D6C` R `0x08E34D78`
- obj 2: sprite `34` at `86,15` A `0x08E34DCC` R `0x08E34DCC`
- obj 3: sprite `35` at `86,27` A `0x08E34DD8` R `0x08E34DD8`
- obj 4: sprite `128` at `96,21` A `0x08E34DE4` R `0x08E34DE4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34D6C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34D78`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E34DCC`
  - dialogue: "My big brother protects us from bullies!"
  - fallthrough
- obj 3 A: `0x08E34DD8`
  - dialogue: "Don't worry about the Neo Ghouls. Espa can beat them on his own."
  - fallthrough
- obj 4 A: `0x08E34DE4`
  - dialogue: "Espa is really good at dueling and can win without cheating."
  - fallthrough

## map_00_state_12

- map/state: `0/12`
- music: `9`

### Initial Sprites
- obj 1: sprite `17` at `53,24` A `0x08E34EA4` R `0x08E34EA4`
- obj 2: sprite `34` at `87,24` A `0x08E34DCC` R `0x08E34DCC`
- obj 3: sprite `35` at `97,18` A `0x08E34DD8` R `0x08E34DD8`
- obj 4: sprite `128` at `97,30` A `0x08E34DE4` R `0x08E34DE4`

### Scripts
- enter 0: `0x08E34E80`
  - play_music
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 4, 'wander': 0}
  - delay
  - dialogue: "Big brother, we can go too, right?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p14 expr0 pos8
  - dialogue: "No... I have a bad feeling about this."
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 4, 'wander': 0}
  - dialogue: "But the Neo Ghouls... They're almost gone."
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p14 expr0 pos8
  - dialogue: "Let's wait until {PLAYER} and his friends come back."
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 4, 'wander': 0}
  - delay
  - dialogue: "You never let us do anything!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 3, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p14 expr7 pos8
  - dialogue: "I'm only trying to keep you safe!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 4, 'wander': 0}
  - delay
  - dialogue: "I'm old enough to take care of myself! I mean, I need both my hands to count my age!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 3, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "C'mon, don't fight."
  - portrait p14 expr7 pos8
  - dialogue: "If that's what you want to do, fine."
  - portrait p14 expr0 pos8
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E34EA4`
  - portrait p14 expr0 pos8
  - dialogue: "Most of the Neo Ghouls have been routed from the Town of Domino. But there are still some lurking ar"
  - fallthrough
- obj 2 A: `0x08E34DCC`
  - dialogue: "My big brother protects us from bullies!"
  - fallthrough
- obj 3 A: `0x08E34DD8`
  - dialogue: "Don't worry about the Neo Ghouls. Espa can beat them on his own."
  - fallthrough
- obj 4 A: `0x08E34DE4`
  - dialogue: "Espa is really good at dueling and can win without cheating."
  - fallthrough

## map_00_state_13

- map/state: `0/13`
- music: `9`

### Initial Sprites
- obj 1: sprite `17` at `76,21` A `0x08E34EA4` R `0x08E34EA4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34EA4`
  - portrait p14 expr0 pos8
  - dialogue: "Most of the Neo Ghouls have been routed from the Town of Domino. But there are still some lurking ar"
  - fallthrough

## map_00_state_14

- map/state: `0/14`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34EC8` R `0x08E34EC8`
- obj 2: sprite `17` at `76,21` A `0x08E34DFC` R `0x08E34EB0`
- obj 3: sprite `34` at `86,15` A `0x08E34E5C` R `0x08E34E5C`
- obj 4: sprite `35` at `86,27` A `0x08E34E68` R `0x08E34E68`
- obj 5: sprite `128` at `96,21` A `0x08E34E74` R `0x08E34E74`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34EC8`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E34DFC`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E34EB0`
  - portrait p14 expr0 pos8
  - dialogue: "I'm exhausted. I need to rest."
  - fallthrough
- obj 3 A: `0x08E34E5C`
  - dialogue: "My big brother dueled great against the Neo Ghouls. He really showed them who's boss! He's the coole"
  - fallthrough
- obj 4 A: `0x08E34E68`
  - dialogue: "My big brother always says... A duelist becomes more powerful when he has friends supporting him."
  - fallthrough
- obj 5 A: `0x08E34E74`
  - dialogue: "I really like Espa! He's the best!"
  - fallthrough

## map_00_state_15

- map/state: `0/15`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E34DF0` R `0x08E34DF0`
- obj 2: sprite `17` at `76,21` A `0x08E34DFC` R `0x08E34EB0`
- obj 3: sprite `34` at `86,15` A `0x08E34E5C` R `0x08E34E5C`
- obj 4: sprite `35` at `86,27` A `0x08E34E68` R `0x08E34E68`
- obj 5: sprite `128` at `96,21` A `0x08E34E74` R `0x08E34E74`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34DF0`
  - portrait p16 expr0 pos8
  - dialogue: "We must make our way to Pegasus's island. We must thwart Reshef the Dark Being."
  - fallthrough
- obj 2 A: `0x08E34DFC`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E34EB0`
  - portrait p14 expr0 pos8
  - dialogue: "I'm exhausted. I need to rest."
  - fallthrough
- obj 3 A: `0x08E34E5C`
  - dialogue: "My big brother dueled great against the Neo Ghouls. He really showed them who's boss! He's the coole"
  - fallthrough
- obj 4 A: `0x08E34E68`
  - dialogue: "My big brother always says... A duelist becomes more powerful when he has friends supporting him."
  - fallthrough
- obj 5 A: `0x08E34E74`
  - dialogue: "I really like Espa! He's the best!"
  - fallthrough

## map_00_state_16

- map/state: `0/16`
- music: `4`

### Initial Sprites
- obj 1: sprite `17` at `76,21` A `0x08E34DFC` R `0x08E34EB0`
- obj 2: sprite `34` at `86,15` A `0x08E34E5C` R `0x08E34E5C`
- obj 3: sprite `35` at `86,27` A `0x08E34E68` R `0x08E34E68`
- obj 4: sprite `128` at `96,21` A `0x08E34E74` R `0x08E34E74`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34DFC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34EB0`
  - portrait p14 expr0 pos8
  - dialogue: "I'm exhausted. I need to rest."
  - fallthrough
- obj 2 A: `0x08E34E5C`
  - dialogue: "My big brother dueled great against the Neo Ghouls. He really showed them who's boss! He's the coole"
  - fallthrough
- obj 3 A: `0x08E34E68`
  - dialogue: "My big brother always says... A duelist becomes more powerful when he has friends supporting him."
  - fallthrough
- obj 4 A: `0x08E34E74`
  - dialogue: "I really like Espa! He's the best!"
  - fallthrough

## map_00_state_17

- map/state: `0/17`
- music: `4`

### Initial Sprites
- obj 1: sprite `17` at `76,21` A `0x08E34DFC` R `0x08E34E20`
- obj 2: sprite `34` at `86,15` A `0x08E34E5C` R `0x08E34E5C`
- obj 3: sprite `35` at `86,27` A `0x08E34E68` R `0x08E34E68`
- obj 4: sprite `128` at `96,21` A `0x08E34E74` R `0x08E34E74`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34DFC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34E20`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E34E5C`
  - dialogue: "My big brother dueled great against the Neo Ghouls. He really showed them who's boss! He's the coole"
  - fallthrough
- obj 3 A: `0x08E34E68`
  - dialogue: "My big brother always says... A duelist becomes more powerful when he has friends supporting him."
  - fallthrough
- obj 4 A: `0x08E34E74`
  - dialogue: "I really like Espa! He's the best!"
  - fallthrough

## map_00_state_18

- map/state: `0/18`
- music: `4`

### Initial Sprites
- obj 1: sprite `6` at `48,21` A `0x08E349F4` R `0x08E34A00`
- obj 2: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 13: sprite `1` at `54,39` A `0x08F04034` R `0x08F04034`
- obj 14: sprite `4` at `42,39` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- enter 3: `0x08E34A54`
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - hide_portrait
  - command_7c_2
  - delay
  - play_music
  - portrait p16 expr0 pos8
  - dialogue: "But we cannot worry about that now. Time is of the essence. The second Millennium Item must be found"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E349F4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34A00`
  - check_flag
  - fallthrough

## map_00_state_19

- map/state: `0/19`
- music: `4`

### Initial Sprites
- obj 1: sprite `17` at `44,34` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `34` at `44,50` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `35` at `36,42` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `128` at `52,42` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E34EBC`
  - portrait p14 expr9 pos1
  - dialogue: "Pipipi..."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "Big brother..."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "Are you worried?"
  - portrait p14 expr0 pos1
  - dialogue: "No... I'm not worried. I'm sure they'll get the job done."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "Yeah! They're stronger than the Big Bad Five! They won't lose to anyone!"
  - portrait p14 expr0 pos1
  - dialogue: "Hahahahaha! That's right! There's no way they'll lose!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "But they can't beat Kaibaman!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "Well, duh. Kaibaman's invincible! But {PLAYER}'s number one!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "So which one's stronger? A duelist who's invincible or a duelist who's number one?"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - play_music
  - portrait p14 expr0 pos1
  - dialogue: "Wh-what's that sound?"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_00_state_20

- map/state: `0/20`
- music: `9`

### Initial Sprites
- obj 1: sprite `17` at `76,21` A `0x08E34D6C` R `0x08E34D78`
- obj 2: sprite `34` at `86,15` A `0x08E34DCC` R `0x08E34DCC`
- obj 3: sprite `35` at `86,27` A `0x08E34DD8` R `0x08E34DD8`
- obj 4: sprite `128` at `96,21` A `0x08E34DE4` R `0x08E34DE4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E34D6C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E34D78`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E34DCC`
  - dialogue: "My big brother protects us from bullies!"
  - fallthrough
- obj 3 A: `0x08E34DD8`
  - dialogue: "Don't worry about the Neo Ghouls. Espa can beat them on his own."
  - fallthrough
- obj 4 A: `0x08E34DE4`
  - dialogue: "Espa is really good at dueling and can win without cheating."
  - fallthrough

## map_01_state_00

- map/state: `1/0`
- music: `4`

### Initial Sprites
- obj 1: sprite `10` at `8,32` A `0x08F04088` R `0x08F04094`
- obj 2: sprite `10` at `20,32` A `0x08F040A0` R `0x08F040AC`
- obj 3: sprite `10` at `32,32` A `0x08F040B8` R `0x08F040C4`
- obj 4: sprite `10` at `88,32` A `0x08F040D0` R `0x08F040DC`
- obj 5: sprite `10` at `100,32` A `0x08F040E8` R `0x08F040F4`
- obj 6: sprite `10` at `112,32` A `0x08F04100` R `0x08F0410C`
- obj 7: sprite `10` at `14,48` A `0x08F04118` R `0x08F04124`
- obj 8: sprite `10` at `26,48` A `0x08F04130` R `0x08F0413C`
- obj 9: sprite `10` at `94,48` A `0x08F04148` R `0x08F04154`
- obj 10: sprite `10` at `106,48` A `0x08F04160` R `0x08F0416C`
- obj 11: sprite `10` at `94,64` A `0x08F04178` R `0x08F04184`
- obj 12: sprite `10` at `106,64` A `0x08F04190` R `0x08F0419C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08F04088`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "The Phoenix Mode flag will"
  - newline
  - dialogue: "be activated."
  - page_break
  - fallthrough
- obj 1 R: `0x08F04094`
  - dialogue: "I'm activating the flag."
  - newline
  - dialogue: "Yah!"
  - page_break
  - set_flag
  - fallthrough
- obj 2 A: `0x08F040A0`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in front of Kaiba Corp."
  - page_break
  - fallthrough
- obj 2 R: `0x08F040AC`
  - dialogue: "Yah!"
  - fade_screen
  - warp: {'map_id': 12, 'state': 14, 'connection': 0}
  - fallthrough
- obj 3 A: `0x08F040B8`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "at the show stage."
  - page_break
  - fallthrough
- obj 3 R: `0x08F040C4`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 57, 'state': 3, 'connection': 0}
  - fallthrough
- obj 4 A: `0x08F040D0`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "on the cruise ship."
  - page_break
  - fallthrough
- obj 4 R: `0x08F040DC`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 28, 'state': 3, 'connection': 0}
  - fallthrough
- obj 5 A: `0x08F040E8`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in Italy."
  - page_break
  - fallthrough
- obj 5 R: `0x08F040F4`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 57, 'state': 3, 'connection': 0}
  - fallthrough
- obj 6 A: `0x08F04100`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in China."
  - page_break
  - fallthrough
- obj 6 R: `0x08F0410C`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 31, 'state': 8, 'connection': 0}
  - fallthrough
- obj 7 A: `0x08F04118`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in Canada."
  - page_break
  - fallthrough
- obj 7 R: `0x08F04124`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 34, 'state': 5, 'connection': 0}
  - fallthrough
- obj 8 A: `0x08F04130`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in Galapagos."
  - page_break
  - fallthrough
- obj 8 R: `0x08F0413C`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 37, 'state': 6, 'connection': 0}
  - fallthrough
- obj 9 A: `0x08F04148`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "outside grandpa's shop."
  - page_break
  - fallthrough
- obj 9 R: `0x08F04154`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 6, 'state': 14, 'connection': 0}
  - fallthrough
- obj 10 A: `0x08F04160`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in Clocktower Square A."
  - page_break
  - fallthrough
- obj 10 R: `0x08F0416C`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 0, 'state': 19, 'connection': 0}
  - fallthrough
- obj 11 A: `0x08F04178`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in Clocktower Square B."
  - page_break
  - fallthrough
- obj 11 R: `0x08F04184`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 1, 'state': 7, 'connection': 0}
  - fallthrough
- obj 12 A: `0x08F04190`
  - dialogue: "If you challenge me to"
  - newline
  - dialogue: "a duel..."
  - page_break
  - dialogue: "I'll warp you to the ending"
  - newline
  - dialogue: "in Pegasus's castle."
  - page_break
  - fallthrough
- obj 12 R: `0x08F0419C`
  - dialogue: "Yah!"
  - page_break
  - fade_screen
  - warp: {'map_id': 51, 'state': 10, 'connection': 0}
  - fallthrough

## map_01_state_01

- map/state: `1/1`
- music: `4`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E426E8` R `0x08E426F4`
- obj 2: sprite `59` at `96,32` A `0x08E42724` R `0x08E42730`
- obj 3: sprite `10` at `38,60` A `0x08E426DC` R `0x08E426DC`
- obj 4: sprite `6` at `26,14` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E42670`
  - play_music
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - portrait p7 expr0 pos1
  - dialogue: "{PLAYER}, what are you still doing here? Weren't the three of you taking the Duel Express?"
  - play_music
  - fade_screen
  - play_music
  - portrait p7 expr6 pos1
  - dialogue: "Whaaat? The Millennium Puzzle is gone? But how? How did that happen?"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - delay
  - portrait p16 expr0 pos1
  - dialogue: "Forgive me, but I overheard your conversation."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24585}
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p16 expr0 pos1
  - dialogue: "So it seems the Millennium Puzzle has also disappeared... What I have feared the most is coming to f"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 24585}
  - delay
  - portrait p16 expr0 pos1
  - dialogue: "I see you're puzzled, but that is only to be expected. Please bear with me and listen to my words ca"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E426E8`
  - dialogue: "I want to ride the Duel Express... But at my level, I'll get creamed in seconds."
  - fallthrough
- obj 1 R: `0x08E426F4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E42724`
  - dialogue: "Today's the day the Duel Express starts chugging! The best duelists have entered this tournament, an"
  - fallthrough
- obj 2 R: `0x08E42730`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E426DC`
  - portrait p7 expr0 pos1
  - dialogue: "You're going, {PLAYER}? The Egypt Exhibition is the last stop on the Duel Express. I don't think it'"
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 48, 'wander': 0}
  - set_flag
  - fallthrough

## map_01_state_02

- map/state: `1/2`
- music: `4`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E426E8` R `0x08E426F4`
- obj 2: sprite `59` at `96,32` A `0x08E42724` R `0x08E42730`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E426E8`
  - dialogue: "I want to ride the Duel Express... But at my level, I'll get creamed in seconds."
  - fallthrough
- obj 1 R: `0x08E426F4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E42724`
  - dialogue: "Today's the day the Duel Express starts chugging! The best duelists have entered this tournament, an"
  - fallthrough
- obj 2 R: `0x08E42730`
  - check_flag
  - fallthrough

## map_01_state_03

- map/state: `1/3`
- music: `11`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E42760` R `0x08E42760`
- obj 2: sprite `59` at `96,32` A `0x08E4276C` R `0x08E4276C`
- obj 3: sprite `26` at `37,40` A `0x08E42778` R `0x08E42778`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E42760`
  - dialogue: "I'm terrified of the Neo Ghouls. I'm never going to duel in the street again."
  - fallthrough
- obj 2 A: `0x08E4276C`
  - dialogue: "If you wear a Duel Disk, the Neo Ghouls will know that you're a duelist! They'll come after you!"
  - fallthrough
- obj 3 A: `0x08E42778`
  - portrait p49 expr0 pos8
  - dialogue: "You! You're a duelist! Fork over your rare cards!"
  - duel
  - fallthrough

## map_01_state_04

- map/state: `1/4`
- music: `11`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E427CC` R `0x08E427CC`
- obj 2: sprite `59` at `96,32` A `0x08E427D8` R `0x08E427D8`
- obj 3: sprite `18` at `37,40` A `0x08E427E4` R `0x08E42814`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E427CC`
  - dialogue: "You know that duelist with the weird laugh? He chased away the Neo Ghouls!"
  - fallthrough
- obj 2 A: `0x08E427D8`
  - dialogue: "That weird little kid with glasses saved us. But he's kind of arrogant and annoying, isn't he?"
  - fallthrough
- obj 3 A: `0x08E427E4`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E42814`
  - portrait p13 expr1 pos8
  - dialogue: "Hyohyohyo! You're wasting my time, you gruesome grub! You can't beat me in a duel!"
  - duel
  - fallthrough

## map_01_state_05

- map/state: `1/5`
- music: `4`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E4282C` R `0x08E42838`
- obj 2: sprite `59` at `96,32` A `0x08E42868` R `0x08E42874`
- obj 3: sprite `18` at `37,40` A `0x08E428A4` R `0x08E428A4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4282C`
  - dialogue: "The Neo Ghouls have left, but... Why do I still feel uneasy?"
  - fallthrough
- obj 1 R: `0x08E42838`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E42868`
  - dialogue: "There are evil duelists, like the Neo Ghouls... But it's still fun to duel."
  - fallthrough
- obj 2 R: `0x08E42874`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E428A4`
  - portrait p13 expr1 pos8
  - dialogue: "Hyohyohyohyo! The Neo Ghouls are gone, all thanks to me! You maggots better be grateful. Just to let"
  - walk_object_x
  - set_object_position
  - set_flag
  - set_map_music
  - fallthrough

## map_01_state_06

- map/state: `1/6`
- music: `4`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E4282C` R `0x08E42838`
- obj 2: sprite `59` at `96,32` A `0x08E42868` R `0x08E42874`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4282C`
  - dialogue: "The Neo Ghouls have left, but... Why do I still feel uneasy?"
  - fallthrough
- obj 1 R: `0x08E42838`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E42868`
  - dialogue: "There are evil duelists, like the Neo Ghouls... But it's still fun to duel."
  - fallthrough
- obj 2 R: `0x08E42874`
  - check_flag
  - fallthrough

## map_01_state_07

- map/state: `1/7`
- music: `4`

### Initial Sprites
- obj 1: sprite `7` at `28,40` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `17` at `44,24` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `34` at `36,16` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `35` at `52,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `128` at `36,32` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `10` at `28,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `49` at `12,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `54` at `20,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `56` at `36,96` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `3` at `128,64` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `55` at `128,56` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `6` at `20,13` A `0x08F04034` R `0x08F04034`
- obj 13: sprite `152` at `65520,40` A `0x08F04034` R `0x08F04034`
- obj 14: sprite `4` at `65520,56` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E42910`
  - play_music
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - delay
  - portrait p6 expr0 pos1
  - dialogue: "What's taking them so long?"
  - hide_portrait
  - delay
  - portrait p7 expr0 pos1
  - dialogue: "Mai! Everybody!"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - delay
  - portrait p6 expr0 pos1
  - dialogue: "Huh? What are you doing here? Are you better duelists now?"
  - portrait p9 expr0 pos1
  - dialogue: "You bet, Mai! Like ultra-strong!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 8, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p31 expr5 pos1
  - dialogue: "Ultra? Tristan..."
  - hide_portrait
  - delay
  - move_object: {'object_id': 8, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p14 expr0 pos1
  - dialogue: "Pipipi... And who might you be?"
  - hide_portrait
  - delay
  - walk_object_y
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_01_state_08

- map/state: `1/8`
- music: `4`

### Initial Sprites
- obj 1: sprite `10` at `36,48` A `0x08E428B0` R `0x08E428B0`
- obj 2: sprite `109` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `103` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `47` at `78,60` A `0x08E426E8` R `0x08E426F4`
- obj 5: sprite `59` at `96,32` A `0x08E42724` R `0x08E42730`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E428B0`
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 13, 'direction': 3, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 14, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p7 expr3 pos1
  - dialogue: "Sigh..."
  - portrait p1 expr0 pos1
  - dialogue: "What's wrong, Tea? Why the big sigh?"
  - portrait p7 expr3 pos8
  - dialogue: "Well... I had a famous fortuneteller do my reading."
  - portrait p1 expr0 pos1
  - dialogue: "You had your fortune told?"
  - portrait p7 expr3 pos1
  - dialogue: "Sigh... Yes, and... well..."
  - hide_portrait
  - delay
  - set_object_position
  - walk_object_y
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - delay
  - play_music
  - dialogue: "Hey good-lookin'! Why don't you mosey on over here to my arm?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 0, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 14, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p7 expr7 pos1
  - dialogue: "..."
- obj 4 A: `0x08E426E8`
  - dialogue: "I want to ride the Duel Express... But at my level, I'll get creamed in seconds."
  - fallthrough
- obj 4 R: `0x08E426F4`
  - check_flag
  - fallthrough
- obj 5 A: `0x08E42724`
  - dialogue: "Today's the day the Duel Express starts chugging! The best duelists have entered this tournament, an"
  - fallthrough
- obj 5 R: `0x08E42730`
  - check_flag
  - fallthrough

## map_01_state_09

- map/state: `1/9`
- music: `9`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E427CC` R `0x08E427CC`
- obj 2: sprite `59` at `96,32` A `0x08E427D8` R `0x08E427D8`
- obj 3: sprite `18` at `37,40` A `0x08E427E4` R `0x08E42814`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E427CC`
  - dialogue: "You know that duelist with the weird laugh? He chased away the Neo Ghouls!"
  - fallthrough
- obj 2 A: `0x08E427D8`
  - dialogue: "That weird little kid with glasses saved us. But he's kind of arrogant and annoying, isn't he?"
  - fallthrough
- obj 3 A: `0x08E427E4`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E42814`
  - portrait p13 expr1 pos8
  - dialogue: "Hyohyohyo! You're wasting my time, you gruesome grub! You can't beat me in a duel!"
  - duel
  - fallthrough

## map_01_state_10

- map/state: `1/10`
- music: `10`

### Initial Sprites
- obj 1: sprite `47` at `78,60` A `0x08E42760` R `0x08E42760`
- obj 2: sprite `59` at `96,32` A `0x08E4276C` R `0x08E4276C`
- obj 3: sprite `26` at `37,40` A `0x08E42778` R `0x08E42778`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E42760`
  - dialogue: "I'm terrified of the Neo Ghouls. I'm never going to duel in the street again."
  - fallthrough
- obj 2 A: `0x08E4276C`
  - dialogue: "If you wear a Duel Disk, the Neo Ghouls will know that you're a duelist! They'll come after you!"
  - fallthrough
- obj 3 A: `0x08E42778`
  - portrait p49 expr0 pos8
  - dialogue: "You! You're a duelist! Fork over your rare cards!"
  - duel
  - fallthrough

## map_02_state_00

- map/state: `2/0`
- music: `4`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_02_state_01

- map/state: `2/1`
- music: `4`

### Initial Sprites
- obj 1: sprite `62` at `40,45` A `0x08E477DC` R `0x08E477E8`
- obj 2: sprite `64` at `74,62` A `0x08E47818` R `0x08E47824`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E477DC`
  - dialogue: "Street duels are the hippest thing right now."
  - fallthrough
- obj 1 R: `0x08E477E8`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E47818`
  - dialogue: "KaibaCorp chartered an entire express train. For a duel tournament called Duel Express. It's amazing"
  - fallthrough
- obj 2 R: `0x08E47824`
  - check_flag
  - fallthrough

## map_02_state_02

- map/state: `2/2`
- music: `11`

### Initial Sprites
- obj 1: sprite `62` at `40,45` A `0x08E47854` R `0x08E47854`
- obj 2: sprite `64` at `52,40` A `0x08E47890` R `0x08E47890`
- obj 3: sprite `26` at `42,65520` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E47854`
  - dialogue: "This is not the time for a street duel! Can't anyone do anything about the Neo Ghouls?"
  - fallthrough
- obj 2 A: `0x08E47890`
  - dialogue: "Groan..."
  - hide_portrait
  - delay
  - show_object: {'object_id': 3, 'x': 52, 'y': 0, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You must be the brats who want to be heroes!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You should have stayed in the sandbox! I'm not as nice as the other guy!"
  - duel
  - fallthrough

## map_02_state_03

- map/state: `2/3`
- music: `11`

### Initial Sprites
- obj 1: sprite `62` at `40,45` A `0x08E478E4` R `0x08E478E4`
- obj 2: sprite `64` at `74,62` A `0x08E478F0` R `0x08E478F0`
- obj 3: sprite `7` at `63,23` A `0x08E478FC` R `0x08E4792C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E478E4`
  - dialogue: "Those Neo Ghouls! They'd better watch out or I'll pummel them next time!"
  - fallthrough
- obj 2 A: `0x08E478F0`
  - dialogue: "Zompire is the most awesomest ever! He's my hero! One day, I'm going to be strong, just like Zompire"
  - fallthrough
- obj 3 A: `0x08E478FC`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E4792C`
  - portrait p6 expr0 pos8
  - dialogue: "You want to duel me for practice before facing the Neo Ghouls? I hope I don't beat you so hard that "
  - duel
  - fallthrough

## map_02_state_04

- map/state: `2/4`
- music: `4`

### Initial Sprites
- obj 1: sprite `62` at `40,45` A `0x08E47944` R `0x08E47950`
- obj 2: sprite `64` at `74,62` A `0x08E47980` R `0x08E4798C`
- obj 3: sprite `7` at `63,23` A `0x08E479BC` R `0x08E479BC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E47944`
  - dialogue: "The Neo Ghouls weren't that scary, were they?"
  - fallthrough
- obj 1 R: `0x08E47950`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E47980`
  - dialogue: "Zompire is the awesomest!"
  - fallthrough
- obj 2 R: `0x08E4798C`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E479BC`
  - portrait p6 expr0 pos8
  - dialogue: "The Town of Domino is now safe. But you still have something to do, don't you? I'm going back to the"
  - walk_object_y
  - walk_object_x
  - set_object_position
  - set_flag
  - set_map_music
  - fallthrough

## map_02_state_05

- map/state: `2/5`
- music: `4`

### Initial Sprites
- obj 1: sprite `62` at `40,45` A `0x08E47944` R `0x08E47950`
- obj 2: sprite `64` at `74,62` A `0x08E47980` R `0x08E4798C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E47944`
  - dialogue: "The Neo Ghouls weren't that scary, were they?"
  - fallthrough
- obj 1 R: `0x08E47950`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E47980`
  - dialogue: "Zompire is the awesomest!"
  - fallthrough
- obj 2 R: `0x08E4798C`
  - check_flag
  - fallthrough

## map_02_state_06

- map/state: `2/6`
- music: `11`

### Initial Sprites
- obj 1: sprite `62` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `114` at `52,65520` A `0x08E47890` R `0x08E47890`
- obj 3: sprite `26` at `52,60` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- enter 1: `0x08E47860`
  - walk_object_y
  - dialogue: "S-stop picking on the weak!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8}
  - delay
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Wh-who are you?"
  - portrait p0 expr0 pos8
  - dialogue: "I-I'm t-the Greendale Zom... Y-you bad guys don't deserve to know my name!"
  - portrait p49 expr0 pos8
  - dialogue: "Little twerp! I'll make you regret facing me!"
  - hide_portrait
  - delay
  - walk_object_y
  - slide_object
  - play_music
  - portrait p49 expr0 pos8
  - dialogue: "Graaaaaaaaah!"
  - hide_portrait
  - delay
  - play_music
  - slide_object
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 4}
  - delay
  - dialogue: "Th-there! Th-that serves you right!"
  - portrait p49 expr0 pos8
  - dialogue: "...Come on, you didn't think that actually hurt me? Time to put this wannabe superhero to sleep!"
  - hide_portrait
  - delay
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Hand over your rare cards right now!"
  - hide_portrait
  - delay
  - slide_object
  - delay
  - dialogue: "I-I c-can't win... Maybe I should run away... ...No! A superhero never flies from danger!"
  - hide_portrait
  - delay
  - play_music
  - swap_object_sprite: {'object_id': 2, 'sprite_id': 64}
  - delay
  - portrait p0 expr0 pos8
- enter 2: `0x08E4786C`
  - walk_object_y
  - dialogue: "S-stop picking on the weak!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8}
  - delay
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Wh-who are you?"
  - portrait p0 expr0 pos8
  - dialogue: "I-I'm t-the Greendale Zom... Y-you bad guys don't deserve to know my name!"
  - portrait p49 expr0 pos8
  - dialogue: "Little twerp! I'll make you regret facing me!"
  - hide_portrait
  - delay
  - walk_object_y
  - slide_object
  - play_music
  - portrait p49 expr0 pos8
  - dialogue: "Graaaaaaaaah!"
  - hide_portrait
  - delay
  - play_music
  - slide_object
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 4}
  - delay
  - dialogue: "Th-there! Th-that serves you right!"
  - portrait p49 expr0 pos8
  - dialogue: "...Come on, you didn't think that actually hurt me? Time to put this wannabe superhero to sleep!"
  - hide_portrait
  - delay
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Hand over your rare cards right now!"
  - hide_portrait
  - delay
  - slide_object
  - delay
  - dialogue: "I-I c-can't win... Maybe I should run away... ...No! A superhero never flies from danger!"
  - hide_portrait
  - delay
  - play_music
  - swap_object_sprite: {'object_id': 2, 'sprite_id': 64}
  - delay
  - portrait p0 expr0 pos8
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 2 A: `0x08E47890`
  - dialogue: "Groan..."
  - hide_portrait
  - delay
  - show_object: {'object_id': 3, 'x': 52, 'y': 0, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You must be the brats who want to be heroes!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You should have stayed in the sandbox! I'm not as nice as the other guy!"
  - duel
  - fallthrough

## map_02_state_07

- map/state: `2/7`
- music: `11`

### Initial Sprites
- obj 1: sprite `20` at `52,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `99` at `46,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `99` at `58,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `99` at `46,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `99` at `58,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `18` at `65520,48` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E479C8`
  - delay
  - walk_object_y
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p12 expr1 pos1
  - dialogue: "Gahaha! All duelists swim in the same ocean! Hurry home!"
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos1
  - dialogue: "Ukkikki!"
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos0
  - dialogue: "Ukikkiki, kikiiki!!"
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos1
  - dialogue: "Ukikiiikiki!"
  - play_music
  - object_effect
  - play_music
  - object_effect
  - play_music
  - object_effect
  - play_music
  - object_effect
  - walk_object_x
  - delay
  - move_object: {'object_id': 6, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 6, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 6, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 6, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p13 expr0 pos1
  - dialogue: "I'm here to check on my card I gave away. So? Where are they?"
  - hide_portrait
  - delay
- exit 0: `0x08F04034`
  - fallthrough

## map_02_state_08

- map/state: `2/8`
- music: `9`

### Initial Sprites
- obj 1: sprite `62` at `40,45` A `0x08E478E4` R `0x08E478E4`
- obj 2: sprite `64` at `74,62` A `0x08E478F0` R `0x08E478F0`
- obj 3: sprite `7` at `63,23` A `0x08E478FC` R `0x08E4792C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E478E4`
  - dialogue: "Those Neo Ghouls! They'd better watch out or I'll pummel them next time!"
  - fallthrough
- obj 2 A: `0x08E478F0`
  - dialogue: "Zompire is the most awesomest ever! He's my hero! One day, I'm going to be strong, just like Zompire"
  - fallthrough
- obj 3 A: `0x08E478FC`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E4792C`
  - portrait p6 expr0 pos8
  - dialogue: "You want to duel me for practice before facing the Neo Ghouls? I hope I don't beat you so hard that "
  - duel
  - fallthrough

## map_02_state_09

- map/state: `2/9`
- music: `10`

### Initial Sprites
- obj 1: sprite `62` at `40,45` A `0x08E47854` R `0x08E47854`
- obj 2: sprite `64` at `52,40` A `0x08E47890` R `0x08E47890`
- obj 3: sprite `26` at `42,65520` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E47854`
  - dialogue: "This is not the time for a street duel! Can't anyone do anything about the Neo Ghouls?"
  - fallthrough
- obj 2 A: `0x08E47890`
  - dialogue: "Groan..."
  - hide_portrait
  - delay
  - show_object: {'object_id': 3, 'x': 52, 'y': 0, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You must be the brats who want to be heroes!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You should have stayed in the sandbox! I'm not as nice as the other guy!"
  - duel
  - fallthrough

## map_02_state_10

- map/state: `2/10`
- music: `10`

### Initial Sprites
- obj 1: sprite `62` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `114` at `52,65520` A `0x08E47890` R `0x08E47890`
- obj 3: sprite `26` at `52,60` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- enter 1: `0x08E47860`
  - walk_object_y
  - dialogue: "S-stop picking on the weak!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8}
  - delay
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Wh-who are you?"
  - portrait p0 expr0 pos8
  - dialogue: "I-I'm t-the Greendale Zom... Y-you bad guys don't deserve to know my name!"
  - portrait p49 expr0 pos8
  - dialogue: "Little twerp! I'll make you regret facing me!"
  - hide_portrait
  - delay
  - walk_object_y
  - slide_object
  - play_music
  - portrait p49 expr0 pos8
  - dialogue: "Graaaaaaaaah!"
  - hide_portrait
  - delay
  - play_music
  - slide_object
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 4}
  - delay
  - dialogue: "Th-there! Th-that serves you right!"
  - portrait p49 expr0 pos8
  - dialogue: "...Come on, you didn't think that actually hurt me? Time to put this wannabe superhero to sleep!"
  - hide_portrait
  - delay
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Hand over your rare cards right now!"
  - hide_portrait
  - delay
  - slide_object
  - delay
  - dialogue: "I-I c-can't win... Maybe I should run away... ...No! A superhero never flies from danger!"
  - hide_portrait
  - delay
  - play_music
  - swap_object_sprite: {'object_id': 2, 'sprite_id': 64}
  - delay
  - portrait p0 expr0 pos8
- enter 2: `0x08E4786C`
  - walk_object_y
  - dialogue: "S-stop picking on the weak!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8}
  - delay
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Wh-who are you?"
  - portrait p0 expr0 pos8
  - dialogue: "I-I'm t-the Greendale Zom... Y-you bad guys don't deserve to know my name!"
  - portrait p49 expr0 pos8
  - dialogue: "Little twerp! I'll make you regret facing me!"
  - hide_portrait
  - delay
  - walk_object_y
  - slide_object
  - play_music
  - portrait p49 expr0 pos8
  - dialogue: "Graaaaaaaaah!"
  - hide_portrait
  - delay
  - play_music
  - slide_object
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 4}
  - delay
  - dialogue: "Th-there! Th-that serves you right!"
  - portrait p49 expr0 pos8
  - dialogue: "...Come on, you didn't think that actually hurt me? Time to put this wannabe superhero to sleep!"
  - hide_portrait
  - delay
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Hand over your rare cards right now!"
  - hide_portrait
  - delay
  - slide_object
  - delay
  - dialogue: "I-I c-can't win... Maybe I should run away... ...No! A superhero never flies from danger!"
  - hide_portrait
  - delay
  - play_music
  - swap_object_sprite: {'object_id': 2, 'sprite_id': 64}
  - delay
  - portrait p0 expr0 pos8
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 2 A: `0x08E47890`
  - dialogue: "Groan..."
  - hide_portrait
  - delay
  - show_object: {'object_id': 3, 'x': 52, 'y': 0, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You must be the brats who want to be heroes!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You should have stayed in the sandbox! I'm not as nice as the other guy!"
  - duel
  - fallthrough

## map_03_state_00

- map/state: `3/0`
- music: `4`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_03_state_01

- map/state: `3/1`
- music: `4`

### Initial Sprites
- obj 1: sprite `65` at `40,32` A `0x08E4A8A4` R `0x08E4A8B0`
- obj 2: sprite `67` at `79,53` A `0x08E4A8E0` R `0x08E4A8EC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4A8A4`
  - dialogue: "I'm a huge fan of Mr. Seto Kaiba. I wonder if Kaiba Corporation would hire me?"
  - fallthrough
- obj 1 R: `0x08E4A8B0`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E4A8E0`
  - dialogue: "Dueling is only fun if you don't cheat. You should always choose ante cards before dueling. That way"
  - fallthrough
- obj 2 R: `0x08E4A8EC`
  - check_flag
  - fallthrough

## map_03_state_02

- map/state: `3/2`
- music: `10`

### Initial Sprites
- obj 1: sprite `65` at `72,32` A `0x08E4A928` R `0x08E4A940`
- obj 2: sprite `67` at `79,53` A `0x08E4A958` R `0x08E4A970`
- obj 3: sprite `26` at `65520,32` A `0x08E4A988` R `0x08E4A994`
- obj 4: sprite `26` at `91,53` A `0x08E4A9D0` R `0x08E4A9DC`

### Scripts
- enter 0: `0x08E4A91C`
  - play_music
  - dialogue: "Help me!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24577}
  - delay
  - walk_object_x
  - walk_object_x
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Silence! Hand over your rare cards right now!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "I never said I was putting up my rare cards as ante in this duel!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 8, 'wander': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Well, you thought wrong! Give me your rare cards!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - dialogue: "N-Neo Ghouls... You horrible stinking thugs..."
  - portrait p49 expr0 pos8
  - dialogue: "Ha ha ha! Flattery will get you nowhere! All the world's rare cards belong to the Neo Ghouls!"
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4A928`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E4A940`
  - dialogue: "Please, no! No more duels!"
  - fallthrough
- obj 2 A: `0x08E4A958`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E4A970`
  - dialogue: "Duel... Please, I'm too scared...."
  - fallthrough
- obj 3 A: `0x08E4A988`
  - portrait p49 expr0 pos8
  - dialogue: "I'll take your rare cards, too!"
  - duel
  - fallthrough
- obj 3 R: `0x08E4A994`
  - portrait p49 expr0 pos8
  - dialogue: "This is your first, and last, mistake!"
  - duel
  - fallthrough
- obj 4 A: `0x08E4A9D0`
  - portrait p49 expr0 pos8
  - dialogue: "You have some rare cards that I want."
  - duel
  - fallthrough
- obj 4 R: `0x08E4A9DC`
  - portrait p49 expr0 pos8
  - dialogue: "You fool! You dare challenge me?"
  - duel
  - fallthrough

## map_03_state_03

- map/state: `3/3`
- music: `11`

### Initial Sprites
- obj 1: sprite `65` at `40,32` A `0x08E4A928` R `0x08E4A940`
- obj 2: sprite `67` at `71,53` A `0x08E4A958` R `0x08E4A970`
- obj 3: sprite `26` at `28,32` A `0x08E4A988` R `0x08E4A994`
- obj 4: sprite `26` at `83,53` A `0x08E4A9D0` R `0x08E4A9DC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4A928`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E4A940`
  - dialogue: "Please, no! No more duels!"
  - fallthrough
- obj 2 A: `0x08E4A958`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E4A970`
  - dialogue: "Duel... Please, I'm too scared...."
  - fallthrough
- obj 3 A: `0x08E4A988`
  - portrait p49 expr0 pos8
  - dialogue: "I'll take your rare cards, too!"
  - duel
  - fallthrough
- obj 3 R: `0x08E4A994`
  - portrait p49 expr0 pos8
  - dialogue: "This is your first, and last, mistake!"
  - duel
  - fallthrough
- obj 4 A: `0x08E4A9D0`
  - portrait p49 expr0 pos8
  - dialogue: "You have some rare cards that I want."
  - duel
  - fallthrough
- obj 4 R: `0x08E4A9DC`
  - portrait p49 expr0 pos8
  - dialogue: "You fool! You dare challenge me?"
  - duel
  - fallthrough

## map_03_state_04

- map/state: `3/4`
- music: `11`

### Initial Sprites
- obj 1: sprite `65` at `40,32` A `0x08E4AA30` R `0x08E4AA30`
- obj 2: sprite `67` at `71,53` A `0x08E4AA3C` R `0x08E4AA3C`
- obj 3: sprite `19` at `28,32` A `0x08E4AA48` R `0x08E4AA78`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4AA30`
  - dialogue: "I was hoping that Kaiba would save us... But surprisingly, Rex Raptor came to our rescue."
  - fallthrough
- obj 2 A: `0x08E4AA3C`
  - dialogue: "The Neo Ghouls are robbing everyone's rare cards. Somebody has to stop them!"
  - fallthrough
- obj 3 A: `0x08E4AA48`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E4AA78`
  - portrait p11 expr0 pos8
  - dialogue: "You wanna duel me? You really want to become extinct? All right! Let's duel!"
  - duel
  - fallthrough

## map_03_state_05

- map/state: `3/5`
- music: `4`

### Initial Sprites
- obj 1: sprite `65` at `40,32` A `0x08E4AA90` R `0x08E4AA9C`
- obj 2: sprite `67` at `71,53` A `0x08E4AAA8` R `0x08E4AAB4`
- obj 3: sprite `19` at `28,32` A `0x08E4AAE4` R `0x08E4AAE4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4AA90`
  - dialogue: "Kaiba Corporation is up ahead. Is something going on there?"
  - fallthrough
- obj 1 R: `0x08E4AA9C`
  - dialogue: "I'm too worried about Mr. Kaiba to duel."
  - fallthrough
- obj 2 A: `0x08E4AAA8`
  - dialogue: "The Town of Domino has become peaceful since the Neo Ghouls left."
  - fallthrough
- obj 2 R: `0x08E4AAB4`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E4AAE4`
  - portrait p11 expr0 pos8
  - dialogue: "Things are now as cool as the Ice Age. I'm outta here. Back to boning up my deck among the fossils."
  - walk_object_x
  - set_object_position
  - set_flag
  - set_map_music
  - fallthrough

## map_03_state_06

- map/state: `3/6`
- music: `4`

### Initial Sprites
- obj 1: sprite `65` at `40,32` A `0x08E4AA90` R `0x08E4AA9C`
- obj 2: sprite `67` at `71,53` A `0x08E4AAA8` R `0x08E4AAB4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4AA90`
  - dialogue: "Kaiba Corporation is up ahead. Is something going on there?"
  - fallthrough
- obj 1 R: `0x08E4AA9C`
  - dialogue: "I'm too worried about Mr. Kaiba to duel."
  - fallthrough
- obj 2 A: `0x08E4AAA8`
  - dialogue: "The Town of Domino has become peaceful since the Neo Ghouls left."
  - fallthrough
- obj 2 R: `0x08E4AAB4`
  - check_flag
  - fallthrough

## map_03_state_07

- map/state: `3/7`
- music: `9`

### Initial Sprites
- obj 1: sprite `65` at `40,32` A `0x08E4AA30` R `0x08E4AA30`
- obj 2: sprite `67` at `71,53` A `0x08E4AA3C` R `0x08E4AA3C`
- obj 3: sprite `19` at `28,32` A `0x08E4AA48` R `0x08E4AA78`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4AA30`
  - dialogue: "I was hoping that Kaiba would save us... But surprisingly, Rex Raptor came to our rescue."
  - fallthrough
- obj 2 A: `0x08E4AA3C`
  - dialogue: "The Neo Ghouls are robbing everyone's rare cards. Somebody has to stop them!"
  - fallthrough
- obj 3 A: `0x08E4AA48`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E4AA78`
  - portrait p11 expr0 pos8
  - dialogue: "You wanna duel me? You really want to become extinct? All right! Let's duel!"
  - duel
  - fallthrough

## map_03_state_08

- map/state: `3/8`
- music: `10`

### Initial Sprites
- obj 1: sprite `65` at `40,32` A `0x08E4A928` R `0x08E4A940`
- obj 2: sprite `67` at `71,53` A `0x08E4A958` R `0x08E4A970`
- obj 3: sprite `26` at `28,32` A `0x08E4A988` R `0x08E4A994`
- obj 4: sprite `26` at `83,53` A `0x08E4A9D0` R `0x08E4A9DC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E4A928`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E4A940`
  - dialogue: "Please, no! No more duels!"
  - fallthrough
- obj 2 A: `0x08E4A958`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E4A970`
  - dialogue: "Duel... Please, I'm too scared...."
  - fallthrough
- obj 3 A: `0x08E4A988`
  - portrait p49 expr0 pos8
  - dialogue: "I'll take your rare cards, too!"
  - duel
  - fallthrough
- obj 3 R: `0x08E4A994`
  - portrait p49 expr0 pos8
  - dialogue: "This is your first, and last, mistake!"
  - duel
  - fallthrough
- obj 4 A: `0x08E4A9D0`
  - portrait p49 expr0 pos8
  - dialogue: "You have some rare cards that I want."
  - duel
  - fallthrough
- obj 4 R: `0x08E4A9DC`
  - portrait p49 expr0 pos8
  - dialogue: "You fool! You dare challenge me?"
  - duel
  - fallthrough

## map_04_state_00

- map/state: `4/0`
- music: `4`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_04_state_01

- map/state: `4/1`
- music: `4`

### Initial Sprites
- obj 1: sprite `68` at `27,20` A `0x08E4D03C` R `0x08E4D048`
- obj 2: sprite `69` at `102,38` A `0x08E4D054` R `0x08E4D060`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E4D03C`
  - dialogue: "You say you're a true duelist, but you're just an amateur that likes playing games. You're all talk!"
  - fallthrough
- obj 1 R: `0x08E4D048`
  - dialogue: "No way, I don't duel."
  - fallthrough
- obj 2 A: `0x08E4D054`
  - dialogue: "You're a duelist, aren't you? I can tell from your Duel Disk. Boy, there sure are a lot of duelists "
  - fallthrough
- obj 2 R: `0x08E4D060`
  - check_flag
  - fallthrough

## map_04_state_02

- map/state: `4/2`
- music: `11`

### Initial Sprites
- obj 1: sprite `68` at `27,20` A `0x08E4D090` R `0x08E4D090`
- obj 2: sprite `69` at `102,38` A `0x08E4D0B4` R `0x08E4D0B4`
- obj 3: sprite `26` at `90,28` A `0x08E4D0C0` R `0x08E4D0C0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E4D090`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E4D0B4`
  - dialogue: "I should've never come to the Town of Domino."
  - fallthrough
- obj 3 A: `0x08E4D0C0`
  - portrait p49 expr0 pos8
  - dialogue: "Like all other cities, this town will also fall to the Neo Ghouls."
  - duel
  - fallthrough

## map_04_state_03

- map/state: `4/3`
- music: `11`

### Initial Sprites
- obj 1: sprite `68` at `27,20` A `0x08E4D114` R `0x08E4D114`
- obj 2: sprite `69` at `102,38` A `0x08E4D120` R `0x08E4D120`
- obj 3: sprite `21` at `90,28` A `0x08E4D12C` R `0x08E4D15C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E4D114`
  - dialogue: "A few duelists are nice. He looks pretty scary, but he's actually a good guy."
  - fallthrough
- obj 2 A: `0x08E4D120`
  - dialogue: "The Neo Ghouls took one look at his face and ran."
  - fallthrough
- obj 3 A: `0x08E4D12C`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E4D15C`
  - portrait p15 expr0 pos8
  - dialogue: "My Neo Ghost deck will haunt you..."
  - duel
  - fallthrough

## map_04_state_04

- map/state: `4/4`
- music: `4`

### Initial Sprites
- obj 1: sprite `68` at `27,20` A `0x08E4D174` R `0x08E4D198`
- obj 2: sprite `69` at `102,38` A `0x08E4D1A4` R `0x08E4D1B0`
- obj 3: sprite `21` at `90,28` A `0x08E4D1BC` R `0x08E4D1BC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E4D174`
  - dialogue: "Do all duelists want rare cards? {CARD_1}Yes No{CARD_2}"
  - fallthrough
- obj 1 R: `0x08E4D198`
  - dialogue: "Oh, no. I'm not a duelist."
  - fallthrough
- obj 2 A: `0x08E4D1A4`
  - dialogue: "You're... Not with the Neo Ghouls. Whew."
  - fallthrough
- obj 2 R: `0x08E4D1B0`
  - dialogue: "No, I've had enough duels to last me a lifetime."
  - fallthrough
- obj 3 A: `0x08E4D1BC`
  - portrait p15 expr0 pos8
  - dialogue: "It's a little too bright out here. I'll make my way back to the graveyard. Home sweet home."
  - hide_portrait
  - delay
  - walk_object_y
  - set_object_position
  - set_flag
  - set_map_music
  - fallthrough

## map_04_state_05

- map/state: `4/5`
- music: `4`

### Initial Sprites
- obj 1: sprite `68` at `27,20` A `0x08E4D174` R `0x08E4D198`
- obj 2: sprite `69` at `102,38` A `0x08E4D1A4` R `0x08E4D1B0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E4D174`
  - dialogue: "Do all duelists want rare cards? {CARD_1}Yes No{CARD_2}"
  - fallthrough
- obj 1 R: `0x08E4D198`
  - dialogue: "Oh, no. I'm not a duelist."
  - fallthrough
- obj 2 A: `0x08E4D1A4`
  - dialogue: "You're... Not with the Neo Ghouls. Whew."
  - fallthrough
- obj 2 R: `0x08E4D1B0`
  - dialogue: "No, I've had enough duels to last me a lifetime."
  - fallthrough

## map_04_state_06

- map/state: `4/6`
- music: `4`

### Initial Sprites
- obj 1: sprite `150` at `48,16` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `151` at `64,16` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E4D1C8`
  - delay
  - play_music
  - object_effect
  - dialogue: "Let's duel!"
  - play_music
  - object_effect
  - dialogue: "Okay."
  - fade_screen
  - warp: {'map_id': 5, 'state': 6, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_04_state_07

- map/state: `4/7`
- music: `4`

### Initial Sprites
- obj 1: sprite `19` at `128,16` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `21` at `65520,16` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E4D1D4`
  - delay
  - walk_object_x
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p11 expr0 pos0
  - dialogue: "I'm sure they're supposed to be around here somewhere. Huh? They're not here yet?"
  - hide_portrait
  - delay
  - walk_object_x
  - portrait p15 expr0 pos0
  - dialogue: "My cosmic powers tell me this is the place. I hope they come back safely."
  - command_7c_2
  - fade_screen
  - warp: {'map_id': 1, 'state': 7, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_04_state_08

- map/state: `4/8`
- music: `9`

### Initial Sprites
- obj 1: sprite `68` at `27,20` A `0x08E4D114` R `0x08E4D114`
- obj 2: sprite `69` at `102,38` A `0x08E4D120` R `0x08E4D120`
- obj 3: sprite `21` at `90,28` A `0x08E4D12C` R `0x08E4D15C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E4D114`
  - dialogue: "A few duelists are nice. He looks pretty scary, but he's actually a good guy."
  - fallthrough
- obj 2 A: `0x08E4D120`
  - dialogue: "The Neo Ghouls took one look at his face and ran."
  - fallthrough
- obj 3 A: `0x08E4D12C`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E4D15C`
  - portrait p15 expr0 pos8
  - dialogue: "My Neo Ghost deck will haunt you..."
  - duel
  - fallthrough

## map_04_state_09

- map/state: `4/9`
- music: `10`

### Initial Sprites
- obj 1: sprite `68` at `27,20` A `0x08E4D090` R `0x08E4D090`
- obj 2: sprite `69` at `102,38` A `0x08E4D0B4` R `0x08E4D0B4`
- obj 3: sprite `26` at `90,28` A `0x08E4D0C0` R `0x08E4D0C0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E4D090`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E4D0B4`
  - dialogue: "I should've never come to the Town of Domino."
  - fallthrough
- obj 3 A: `0x08E4D0C0`
  - portrait p49 expr0 pos8
  - dialogue: "Like all other cities, this town will also fall to the Neo Ghouls."
  - duel
  - fallthrough

## map_05_state_00

- map/state: `5/0`
- music: `4`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_05_state_01

- map/state: `5/1`
- music: `4`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E50EA8` R `0x08E50EB4`
- obj 2: sprite `71` at `90,32` A `0x08E50EE4` R `0x08E50EF0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E50EA8`
  - dialogue: "I won't be riding the Duel Express... But that doesn't mean my duelist level is low!"
  - fallthrough
- obj 1 R: `0x08E50EB4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E50EE4`
  - dialogue: "Did you hear about the Duel Express? Any duelist can get on board. Maybe I should go, too."
  - fallthrough
- obj 2 R: `0x08E50EF0`
  - check_flag
  - fallthrough

## map_05_state_02

- map/state: `5/2`
- music: `11`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E50F20` R `0x08E50F20`
- obj 2: sprite `71` at `90,32` A `0x08E50F2C` R `0x08E50F2C`
- obj 3: sprite `26` at `45,28` A `0x08E50F38` R `0x08E50F38`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E50F20`
  - dialogue: "No, no, no... My Hyozanryu... The Neo Ghouls ripped it off. They couldn't care less about having a f"
  - fallthrough
- obj 2 A: `0x08E50F2C`
  - dialogue: "How do you expect me to duel without my rare cards?"
  - fallthrough
- obj 3 A: `0x08E50F38`
  - portrait p49 expr0 pos8
  - dialogue: "Domino duelists are spineless wimps! No one's shown the least bit of resistance!"
  - duel
  - fallthrough

## map_05_state_03

- map/state: `5/3`
- music: `11`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E50F8C` R `0x08E50F8C`
- obj 2: sprite `71` at `90,32` A `0x08E50FB0` R `0x08E50FB0`
- obj 3: sprite `20` at `45,28` A `0x08E50FBC` R `0x08E50FEC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E50F8C`
  - dialogue: "I'm the greatest! I sent the Neo Ghouls running! Witnesses may say that the funky fisherman guy scar"
  - fallthrough
- obj 2 A: `0x08E50FB0`
  - dialogue: "There sure are some really good duelists out there. One duelist crushed the Neo Ghouls in a sec. He "
  - fallthrough
- obj 3 A: `0x08E50FBC`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E50FEC`
  - portrait p12 expr0 pos8
  - dialogue: "Excellent! I was getting bored of the Neo Ghouls! Prepare to be swamped!"
  - duel
  - fallthrough

## map_05_state_04

- map/state: `5/4`
- music: `4`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E51004` R `0x08E51010`
- obj 2: sprite `71` at `90,32` A `0x08E51040` R `0x08E5104C`
- obj 3: sprite `20` at `45,28` A `0x08E5107C` R `0x08E5107C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E51004`
  - dialogue: "Let's see... Who might have rare cards... Who looks weak enough for me to beat... There have to be s"
  - fallthrough
- obj 1 R: `0x08E51010`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E51040`
  - dialogue: "I'll never forget Mako Tsunami. He's one of the duelists who saved the Town of Domino."
  - fallthrough
- obj 2 R: `0x08E5104C`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E5107C`
  - portrait p12 expr0 pos8
  - dialogue: "Sigh... I miss the sea! I'm going back home among the waves!"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - set_object_position
  - set_flag
  - set_map_music
  - fallthrough

## map_05_state_05

- map/state: `5/5`
- music: `4`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E51004` R `0x08E51010`
- obj 2: sprite `71` at `90,32` A `0x08E51040` R `0x08E5104C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E51004`
  - dialogue: "Let's see... Who might have rare cards... Who looks weak enough for me to beat... There have to be s"
  - fallthrough
- obj 1 R: `0x08E51010`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E51040`
  - dialogue: "I'll never forget Mako Tsunami. He's one of the duelists who saved the Town of Domino."
  - fallthrough
- obj 2 R: `0x08E5104C`
  - check_flag
  - fallthrough

## map_05_state_06

- map/state: `5/6`
- music: `4`

### Initial Sprites
- obj 1: sprite `111` at `48,48` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `112` at `64,48` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E51088`
  - delay
  - play_music
  - object_effect
  - dialogue: "Oh no! I lost again."
  - play_music
  - object_effect
  - dialogue: "Hahah, I did it! Try harder next time!"
  - play_music
  - object_effect
  - dialogue: "Yeah, I'm not going to lose again!"
  - fade_screen
  - warp: {'map_id': 6, 'state': 15, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_05_state_07

- map/state: `5/7`
- music: `4`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E50EA8` R `0x08E50EB4`
- obj 2: sprite `71` at `90,32` A `0x08E50EE4` R `0x08E50EF0`

### Scripts
- enter 0: `0x08E51094`
  - play_music
  - portrait p4 expr0 pos8
  - dialogue: "I can't believe Tristan made us go all the way around the world just because his stomach was growlin"
  - portrait p1 expr0 pos8
  - dialogue: "It wasn't Tristan's fault. It was just a misunderstanding. Anyway, we have more important things to "
  - portrait p4 expr0 pos8
  - dialogue: "Oh yeah! Maybe Ishizu has good news. She may have found a way to restore the Egyptian God Cards."
  - portrait p1 expr0 pos8
  - dialogue: "Yes, I hope so. {PLAYER}, Joey, let's meet up with Ishizu."
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E50EA8`
  - dialogue: "I won't be riding the Duel Express... But that doesn't mean my duelist level is low!"
  - fallthrough
- obj 1 R: `0x08E50EB4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E50EE4`
  - dialogue: "Did you hear about the Duel Express? Any duelist can get on board. Maybe I should go, too."
  - fallthrough
- obj 2 R: `0x08E50EF0`
  - check_flag
  - fallthrough

## map_05_state_08

- map/state: `5/8`
- music: `9`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E50F8C` R `0x08E50F8C`
- obj 2: sprite `71` at `90,32` A `0x08E50FB0` R `0x08E50FB0`
- obj 3: sprite `20` at `45,28` A `0x08E50FBC` R `0x08E50FEC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E50F8C`
  - dialogue: "I'm the greatest! I sent the Neo Ghouls running! Witnesses may say that the funky fisherman guy scar"
  - fallthrough
- obj 2 A: `0x08E50FB0`
  - dialogue: "There sure are some really good duelists out there. One duelist crushed the Neo Ghouls in a sec. He "
  - fallthrough
- obj 3 A: `0x08E50FBC`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E50FEC`
  - portrait p12 expr0 pos8
  - dialogue: "Excellent! I was getting bored of the Neo Ghouls! Prepare to be swamped!"
  - duel
  - fallthrough

## map_05_state_09

- map/state: `5/9`
- music: `10`

### Initial Sprites
- obj 1: sprite `70` at `40,57` A `0x08E50F20` R `0x08E50F20`
- obj 2: sprite `71` at `90,32` A `0x08E50F2C` R `0x08E50F2C`
- obj 3: sprite `26` at `45,28` A `0x08E50F38` R `0x08E50F38`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E50F20`
  - dialogue: "No, no, no... My Hyozanryu... The Neo Ghouls ripped it off. They couldn't care less about having a f"
  - fallthrough
- obj 2 A: `0x08E50F2C`
  - dialogue: "How do you expect me to duel without my rare cards?"
  - fallthrough
- obj 3 A: `0x08E50F38`
  - portrait p49 expr0 pos8
  - dialogue: "Domino duelists are spineless wimps! No one's shown the least bit of resistance!"
  - duel
  - fallthrough

## map_06_state_00

- map/state: `6/0`
- music: `6`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_06_state_01

- map/state: `6/1`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `80,56` A `0x08E5CBB8` R `0x08E5CBC4`
- obj 2: sprite `54` at `32,48` A `0x08E5CBDC` R `0x08E5CBE8`
- obj 3: sprite `57` at `36,40` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CBB8`
  - portrait p9 expr0 pos8
  - dialogue: "Yo, {PLAYER}! I heard from Tea. I know you can win!"
  - fallthrough
- obj 1 R: `0x08E5CBC4`
  - portrait p9 expr0 pos8
  - dialogue: "You want to duel me? Sure thing! Let's duel!"
  - duel
  - fallthrough
- obj 2 A: `0x08E5CBDC`
  - portrait p31 expr0 pos8
  - dialogue: "Hi, {PLAYER}. Tea told me what's up.. You'll do awesome."
  - fallthrough
- obj 2 R: `0x08E5CBE8`
  - portrait p31 expr0 pos8
  - dialogue: "I don't really consider myself a duelist... But I can duel better than that loser Tristan."
  - duel
  - fallthrough
- obj 3 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_06_state_02

- map/state: `6/2`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `44,40` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `54` at `44,56` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `57` at `36,40` A `0x08E5CDD4` R `0x08E5CDD4`
- obj 4: sprite `1` at `144,56` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `56` at `144,48` A `0x08E5CC54` R `0x08E5CC60`

### Scripts
- enter 0: `0x08E5CC00`
  - play_music
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 3 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough
- obj 5 A: `0x08E5CC54`
  - portrait p32 expr0 pos8
  - dialogue: "{PLAYER}, please keep an eye on Joey."
  - fallthrough
- obj 5 R: `0x08E5CC60`
  - portrait p32 expr0 pos8
  - dialogue: "I'm no match for you, {PLAYER}. If you want to duel, I think my big brother would be a finer opponen"
  - fallthrough

## map_06_state_03

- map/state: `6/3`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `144,40` A `0x08E5CC90` R `0x08E5CC9C`
- obj 2: sprite `54` at `144,56` A `0x08E5CCB4` R `0x08E5CBE8`
- obj 3: sprite `57` at `36,40` A `0x08E5CDD4` R `0x08E5CDD4`
- obj 4: sprite `1` at `128,96` A `0x08E5CC6C` R `0x08E5CC6C`
- obj 5: sprite `56` at `44,48` A `0x08E5CC84` R `0x08E5CC60`

### Scripts
- enter 0: `0x08E5CC78`
  - play_music
  - delay
  - move_object: {'object_id': 5, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p32 expr0 pos8
  - dialogue: "Oh,"
  - delay
  - dialogue: "big brother! Is your work for Ishizu going smoothly?"
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 16384}
  - portrait p32 expr0 pos8
  - dialogue: "Joey,"
  - delay
  - dialogue: "what's wrong?"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - delay
  - portrait p4 expr3 pos8
  - dialogue: "Serenity,"
  - delay
  - dialogue: "uh..."
  - delay
  - dialogue: "Er, um..."
  - delay
  - dialogue: "Tell me da truth. Is there"
  - delay
  - dialogue: "anybody that you like?"
  - portrait p32 expr0 pos8
  - dialogue: "Yeah."
  - delay
  - dialogue: "There sure is."
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 16384}
  - portrait p4 expr2 pos8
  - dialogue: "S-"
  - delay
  - dialogue: "Serenity!"
  - delay
  - dialogue: "Are you serious? Do I know this guy?"
  - portrait p32 expr0 pos8
  - dialogue: "Yup."
  - delay
  - dialogue: "Tristan..."
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 16384}
  - hide_portrait
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CC90`
  - portrait p9 expr0 pos8
  - dialogue: "{PLAYER},"
  - delay
  - dialogue: "I know you can win. You have to fight for me, too!"
  - fallthrough
- obj 1 R: `0x08E5CC9C`
  - portrait p9 expr0 pos8
  - dialogue: "I don't really feel like it, but I'll do anything for you, buddy!"
  - duel
  - fallthrough
- obj 2 A: `0x08E5CCB4`
  - portrait p31 expr0 pos8
  - dialogue: "{PLAYER},"
  - delay
  - dialogue: "leave it to me! I'll keep an eye on Tristan. ...Especially to make sure that he doesn't hit on Seren"
  - fallthrough
- obj 2 R: `0x08E5CBE8`
  - portrait p31 expr0 pos8
  - dialogue: "I don't really consider myself a duelist... But I can duel better than that loser Tristan."
  - duel
  - fallthrough
- obj 3 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough
- obj 4 A: `0x08E5CC6C`
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 16}
  - fallthrough
- obj 5 A: `0x08E5CC84`
  - portrait p32 expr0 pos8
  - dialogue: "Wouldn't it be great if we could stay friends forever?"
  - fallthrough
- obj 5 R: `0x08E5CC60`
  - portrait p32 expr0 pos8
  - dialogue: "I'm no match for you, {PLAYER}. If you want to duel, I think my big brother would be a finer opponen"
  - fallthrough

## map_06_state_04

- map/state: `6/4`
- music: `6`

### Initial Sprites
- obj 1: sprite `56` at `44,48` A `0x08E5CC54` R `0x08E5CC60`
- obj 2: sprite `57` at `36,40` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CC54`
  - portrait p32 expr0 pos8
  - dialogue: "{PLAYER}, please keep an eye on Joey."
  - fallthrough
- obj 1 R: `0x08E5CC60`
  - portrait p32 expr0 pos8
  - dialogue: "I'm no match for you, {PLAYER}. If you want to duel, I think my big brother would be a finer opponen"
  - fallthrough
- obj 2 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_06_state_05

- map/state: `6/5`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `80,56` A `0x08E5CC90` R `0x08E5CC9C`
- obj 2: sprite `54` at `28,34` A `0x08E5CCB4` R `0x08E5CBE8`
- obj 3: sprite `56` at `44,48` A `0x08E5CC84` R `0x08E5CC60`
- obj 4: sprite `57` at `36,40` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CC90`
  - portrait p9 expr0 pos8
  - dialogue: "{PLAYER},"
  - delay
  - dialogue: "I know you can win. You have to fight for me, too!"
  - fallthrough
- obj 1 R: `0x08E5CC9C`
  - portrait p9 expr0 pos8
  - dialogue: "I don't really feel like it, but I'll do anything for you, buddy!"
  - duel
  - fallthrough
- obj 2 A: `0x08E5CCB4`
  - portrait p31 expr0 pos8
  - dialogue: "{PLAYER},"
  - delay
  - dialogue: "leave it to me! I'll keep an eye on Tristan. ...Especially to make sure that he doesn't hit on Seren"
  - fallthrough
- obj 2 R: `0x08E5CBE8`
  - portrait p31 expr0 pos8
  - dialogue: "I don't really consider myself a duelist... But I can duel better than that loser Tristan."
  - duel
  - fallthrough
- obj 3 A: `0x08E5CC84`
  - portrait p32 expr0 pos8
  - dialogue: "Wouldn't it be great if we could stay friends forever?"
  - fallthrough
- obj 3 R: `0x08E5CC60`
  - portrait p32 expr0 pos8
  - dialogue: "I'm no match for you, {PLAYER}. If you want to duel, I think my big brother would be a finer opponen"
  - fallthrough
- obj 4 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_06_state_06

- map/state: `6/6`
- music: `31`

### Initial Sprites
- obj 1: sprite `49` at `36,40` A `0x08E5CCCC` R `0x08E5CCD8`
- obj 2: sprite `54` at `36,56` A `0x08E5CCE4` R `0x08E5CCF0`
- obj 3: sprite `56` at `44,48` A `0x08E5CCFC` R `0x08E5CCFC`
- obj 4: sprite `26` at `72,48` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `57` at `28,48` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08E5CCC0`
  - play_music
  - delay
  - walk_object_x
  - delay
  - portrait p32 expr6 pos1
  - dialogue: "Eeek!"
  - portrait p9 expr2 pos1
  - dialogue: "Hey! What do you think you're doing to Serenity?"
  - portrait p31 expr0 pos1
  - dialogue: "I'll protect you, Serenity!"
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 0, 'wander': 0}
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - delay
  - portrait p49 expr0 pos1
  - dialogue: "Tsk..."
  - hide_portrait
  - delay
  - walk_object_x
  - play_music
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p9 expr0 pos1
  - dialogue: "Are you okay, Serenity?"
  - portrait p32 expr0 pos1
  - dialogue: "Yes, I'm fine, Tristan. And Duke, thank you too."
  - portrait p31 expr0 pos1
  - dialogue: "You can count on me, Serenity. I won't let the Neo Ghouls lay a finger on you."
  - portrait p9 expr0 pos1
  - dialogue: "That goes double for me!"
  - portrait p31 expr0 pos1
  - dialogue: "It's okay Tristan. Serenity's safe in my arms. She doesn't need you."
  - portrait p9 expr5 pos1
  - dialogue: "Devlin, you..."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8}
  - delay
  - portrait p32 expr0 pos1
  - dialogue: "Oh, hi {PLAYER}."
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CCCC`
  - portrait p9 expr0 pos8
  - dialogue: "{PLAYER}, Serenity's safe with me. I can't say the same about loverboy over there... The Neo Ghouls "
  - fallthrough
- obj 1 R: `0x08E5CCD8`
  - portrait p9 expr0 pos8
  - dialogue: "What? You don't have the time to duel me!"
  - fallthrough
- obj 2 A: `0x08E5CCE4`
  - portrait p31 expr0 pos8
  - dialogue: "{PLAYER}, let's drive the Neo Ghouls out of town!"
  - fallthrough
- obj 2 R: `0x08E5CCF0`
  - portrait p31 expr0 pos8
  - dialogue: "I don't think we have any time to spare."
  - fallthrough
- obj 3 A: `0x08E5CCFC`
  - portrait p32 expr0 pos8
  - dialogue: "{PLAYER}, I'm fine. Please don't worry about me."
  - fallthrough
- obj 5 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_06_state_07

- map/state: `6/7`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `36,40` A `0x08E5CCCC` R `0x08E5CCD8`
- obj 2: sprite `54` at `36,56` A `0x08E5CCE4` R `0x08E5CCF0`
- obj 3: sprite `56` at `44,48` A `0x08E5CCFC` R `0x08E5CCFC`
- obj 4: sprite `57` at `28,48` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CCCC`
  - portrait p9 expr0 pos8
  - dialogue: "{PLAYER}, Serenity's safe with me. I can't say the same about loverboy over there... The Neo Ghouls "
  - fallthrough
- obj 1 R: `0x08E5CCD8`
  - portrait p9 expr0 pos8
  - dialogue: "What? You don't have the time to duel me!"
  - fallthrough
- obj 2 A: `0x08E5CCE4`
  - portrait p31 expr0 pos8
  - dialogue: "{PLAYER}, let's drive the Neo Ghouls out of town!"
  - fallthrough
- obj 2 R: `0x08E5CCF0`
  - portrait p31 expr0 pos8
  - dialogue: "I don't think we have any time to spare."
  - fallthrough
- obj 3 A: `0x08E5CCFC`
  - portrait p32 expr0 pos8
  - dialogue: "{PLAYER}, I'm fine. Please don't worry about me."
  - fallthrough
- obj 4 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_06_state_08

- map/state: `6/8`
- music: `6`

### Initial Sprites
- obj 1: sprite `57` at `44,48` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `54` at `36,48` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `56` at `44,40` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E5CD68`
  - play_music
  - delay
  - play_music
  - dialogue: "Arf arf arf arf arf!"
  - portrait p32 expr0 pos8
  - dialogue: "Lucky, what's wrong?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - delay
  - portrait p32 expr0 pos8
  - dialogue: "Hey Joey!"
  - portrait p31 expr0 pos8
  - dialogue: "{PLAYER}! Yugi and Joey!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 14, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos8
  - dialogue: "Is Tristan around? I don't see him..."
  - portrait p32 expr3 pos8
  - dialogue: "H-he..."
  - portrait p31 expr3 pos8
  - dialogue: "T-Tristan..."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24577}
  - delay
  - portrait p1 expr6 pos8
  - dialogue: "Is something wrong?"
  - portrait p4 expr2 pos8
  - dialogue: "What? Did somethin' happen to Tristan?"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 12}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_06_state_09

- map/state: `6/9`
- music: `6`

### Initial Sprites
- obj 1: sprite `57` at `128,48` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `54` at `44,40` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `56` at `44,48` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `99` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E5CD74`
  - play_music
  - delay
  - set_object_position
  - delay
  - walk_object_y
  - delay
  - play_music
  - portrait p38 expr2 pos8
  - dialogue: "Ukkiii!"
  - portrait p32 expr6 pos8
  - dialogue: "Oh! This monkey..."
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Uki, uki. uki."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 2, 'object_mask': 16}
  - walk_object_x
  - delay
  - play_music
  - dialogue: "Arf arf arf!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 3, 'distance': 0, 'wander': 0}
  - walk_object_x
  - delay
  - walk_object_x
  - delay
  - play_music
  - dialogue: "Arf."
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Uki!"
  - portrait p0 expr0 pos8
  - play_music
  - dialogue: "Arf arf!"
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Uki uki."
  - portrait p32 expr0 pos8
  - dialogue: "I read that monkeys and dogs don't get along... But this monkey and Lucky seem like best friends."
  - portrait p31 expr0 pos8
  - dialogue: "It can't be... This monkey robot... Could it be Tristan?"
  - hide_portrait
  - delay
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_06_state_10

- map/state: `6/10`
- music: `6`

### Initial Sprites
- obj 1: sprite `57` at `44,48` A `0x08E5CDD4` R `0x08E5CDD4`
- obj 2: sprite `54` at `36,48` A `0x08E5CD98` R `0x08E5CBE8`
- obj 3: sprite `56` at `44,40` A `0x08E5CD8C` R `0x08E5CC60`
- obj 4: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 13: sprite `1` at `63,42` A `0x08F04034` R `0x08F04034`
- obj 14: sprite `4` at `52,40` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E5CD80`
  - portrait p31 expr5 pos8
  - dialogue: "...And that's what happened."
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 24577}
  - portrait p32 expr3 pos8
  - dialogue: "Big brother... I saw this look on Tristan's face... It was as if he was saying that he didn't want a"
  - portrait p4 expr2 pos8
  - dialogue: "Don't worry about a thing, Serenity. Tristan's our friend. There's no way we'll abandon him! We'll l"
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough
- obj 2 A: `0x08E5CD98`
  - portrait p31 expr0 pos8
  - dialogue: "I bet Tristan ran off on purpose! That's the only way Serenity would pay attention to him instead of"
  - fallthrough
- obj 2 R: `0x08E5CBE8`
  - portrait p31 expr0 pos8
  - dialogue: "I don't really consider myself a duelist... But I can duel better than that loser Tristan."
  - duel
  - fallthrough
- obj 3 A: `0x08E5CD8C`
  - portrait p32 expr3 pos8
  - dialogue: "Where could Tristan have gone?"
  - fallthrough
- obj 3 R: `0x08E5CC60`
  - portrait p32 expr0 pos8
  - dialogue: "I'm no match for you, {PLAYER}. If you want to duel, I think my big brother would be a finer opponen"
  - fallthrough

## map_06_state_11

- map/state: `6/11`
- music: `6`

### Initial Sprites
- obj 1: sprite `57` at `44,48` A `0x08E5CDD4` R `0x08E5CDD4`
- obj 2: sprite `54` at `36,48` A `0x08E5CD98` R `0x08E5CBE8`
- obj 3: sprite `56` at `44,40` A `0x08E5CD8C` R `0x08E5CC60`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough
- obj 2 A: `0x08E5CD98`
  - portrait p31 expr0 pos8
  - dialogue: "I bet Tristan ran off on purpose! That's the only way Serenity would pay attention to him instead of"
  - fallthrough
- obj 2 R: `0x08E5CBE8`
  - portrait p31 expr0 pos8
  - dialogue: "I don't really consider myself a duelist... But I can duel better than that loser Tristan."
  - duel
  - fallthrough
- obj 3 A: `0x08E5CD8C`
  - portrait p32 expr3 pos8
  - dialogue: "Where could Tristan have gone?"
  - fallthrough
- obj 3 R: `0x08E5CC60`
  - portrait p32 expr0 pos8
  - dialogue: "I'm no match for you, {PLAYER}. If you want to duel, I think my big brother would be a finer opponen"
  - fallthrough

## map_06_state_12

- map/state: `6/12`
- music: `6`

### Initial Sprites
- obj 1: sprite `99` at `104,40` A `0x08E5CDC8` R `0x08F04034`
- obj 2: sprite `54` at `36,48` A `0x08E5CDBC` R `0x08E5CDBC`
- obj 3: sprite `56` at `36,40` A `0x08E5CDB0` R `0x08E5CDB0`
- obj 4: sprite `49` at `128,40` A `0x08E5CDC8` R `0x08E5CDC8`
- obj 5: sprite `11` at `128,128` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `57` at `28,40` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08E5CDA4`
  - play_music
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 12}
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_x
  - portrait p32 expr6 pos1
  - dialogue: "Tristan!"
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - play_music
  - portrait p38 expr5 pos1
  - dialogue: "Ukiiii!"
  - portrait p32 expr0 pos1
  - dialogue: "I'm so glad you found him!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - delay
  - play_music
  - reaction: {'reaction': 5, 'object_mask': 16384}
  - delay
  - portrait p4 expr2 pos8
  - dialogue: "Hey, Tristan! That's enough! Get away from Serenity."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 2}
  - delay
  - portrait p4 expr2 pos8
  - dialogue: "Why, you..."
  - hide_portrait
  - delay
  - walk_object_x
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_x
  - delay
  - portrait p32 expr2 pos1
  - dialogue: "Stop Joey! Hasn't Tristan suffer enough already?"
  - portrait p4 expr7 pos8
  - dialogue: "Yeah, but..."
  - hide_portrait
  - delay
  - play_music
- exit 0: `0x08E5CE10`
  - set_flag
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 2: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5CDC8`
  - portrait p9 expr0 pos8
  - dialogue: "I'm glad you guys care so much..."
  - portrait p9 expr2 pos8
  - dialogue: "But come on! You've got to be kidding! I don't look anything like that monkey robot!"
  - fallthrough
- obj 2 A: `0x08E5CDBC`
  - portrait p31 expr0 pos8
  - dialogue: "I totally thought that the monkey robot was Tristan. You have to admit, there is a strong resemblanc"
  - fallthrough
- obj 3 A: `0x08E5CDB0`
  - portrait p32 expr0 pos8
  - dialogue: "I wasn't trying to be funny..."
  - fallthrough
- obj 6 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_06_state_13

- map/state: `6/13`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `36,40` A `0x08E5CD08` R `0x08E5CD14`
- obj 2: sprite `54` at `36,56` A `0x08E5CD2C` R `0x08E5CD38`
- obj 3: sprite `56` at `44,48` A `0x08E5CD50` R `0x08E5CD5C`
- obj 4: sprite `57` at `28,48` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CD08`
  - portrait p9 expr0 pos8
  - dialogue: "You did it, {PLAYER}. You got rid of the Neo Ghouls... Awesome! But... Your battle isn't over yet, i"
  - fallthrough
- obj 1 R: `0x08E5CD14`
  - portrait p9 expr0 pos8
  - dialogue: "Sure! If you think you can learn something from me, I'll duel you!"
  - duel
  - fallthrough
- obj 2 A: `0x08E5CD2C`
  - portrait p31 expr0 pos8
  - dialogue: "We'll look after things while you're gone, {PLAYER}."
  - fallthrough
- obj 2 R: `0x08E5CD38`
  - portrait p31 expr0 pos8
  - dialogue: "No problem! I'll duel if you want me to."
  - duel
  - fallthrough
- obj 3 A: `0x08E5CD50`
  - portrait p32 expr0 pos8
  - dialogue: "{PLAYER}, good luck. I hope Joey doesn't get in the way..."
  - fallthrough
- obj 3 R: `0x08E5CD5C`
  - portrait p32 expr0 pos8
  - dialogue: "I wouldn't be much of a challenge, {PLAYER}."
  - fallthrough
- obj 4 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_06_state_14

- map/state: `6/14`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `36,40` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `54` at `36,56` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `56` at `44,48` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `57` at `28,48` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `10` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `11` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E5CDE0`
  - play_music
  - delay
  - show_object: {'object_id': 5, 'x': 75, 'y': 39, 'frame': 0, 'mode': 0}
  - delay
  - walk_object_y
  - walk_object_x
  - portrait p7 expr3 pos1
  - dialogue: "I can't stand waiting anymore! I'm going to find and help Yugi, Joey, and {PLAYER}!"
  - portrait p9 expr2 pos1
  - dialogue: "And just how are you going to help them?"
  - portrait p31 expr0 pos1
  - dialogue: "Tristan's right, Tea."
  - portrait p32 expr3 pos1
  - dialogue: "Tea... Please, you have to believe in my brother... And have faith in them."
  - portrait p7 expr3 pos1
  - dialogue: "I believe... I believe in them, but... I can't stand waiting around."
  - hide_portrait
  - delay
  - show_object: {'object_id': 6, 'x': 75, 'y': 39, 'frame': 0, 'mode': 0}
  - delay
  - walk_object_y
  - move_object: {'object_id': 6, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 5, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p8 expr0 pos0
  - dialogue: "Tea... They'll be fine. Can't you tell? Can't you feel it?"
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 32}
  - fade_screen
  - warp: {'map_id': 4, 'state': 6, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_06_state_15

- map/state: `6/15`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `36,40` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `54` at `36,56` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `56` at `44,48` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `57` at `28,48` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `10` at `64,48` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `11` at `75,48` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `111` at `128,44` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `112` at `128,52` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E5CDEC`
  - portrait p8 expr0 pos0
  - dialogue: "The happy expressions on the children's faces... Those are the faces of the Town of Domino at peace."
  - portrait p0 expr0 pos0
  - walk_object_x
  - walk_object_x
  - delay
  - play_music
  - object_effect
  - dialogue: "Hi! Can I see your cards?"
  - play_music
  - object_effect
  - dialogue: "Do you have any new cards?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 6, 'direction': 3, 'distance': 0, 'wander': 0}
  - portrait p8 expr0 pos0
  - dialogue: "As a matter of fact, some rare cards have come in."
  - portrait p0 expr0 pos0
  - play_music
  - object_effect
  - dialogue: "Yeah! I'll buy some!"
  - play_music
  - object_effect
  - dialogue: "Hey, no fair! They're mine!"
  - portrait p8 expr0 pos0
  - dialogue: "There's no need to fight. I have two of each, so you both can get one."
  - portrait p0 expr0 pos0
  - play_music
  - object_effect
  - dialogue: "Okay!"
  - play_music
  - object_effect
  - dialogue: "Sure!"
  - portrait p8 expr0 pos0
  - dialogue: "Fine, let's head inside."
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - show_object: {'object_id': 7, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - show_object: {'object_id': 8, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - hide_portrait
  - delay
  - move_object: {'object_id': 6, 'direction': 1, 'distance': 0, 'wander': 0}
  - portrait p8 expr0 pos0
  - dialogue: "The boys will be back soon. There's no doubt. Isn't that right, Tea?"
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_06_state_16

- map/state: `6/16`
- music: `6`

### Initial Sprites
- obj 1: sprite `49` at `80,56` A `0x08E5CDF8` R `0x08E5CBC4`
- obj 2: sprite `54` at `32,48` A `0x08E5CE04` R `0x08E5CBE8`
- obj 3: sprite `57` at `36,40` A `0x08E5CDD4` R `0x08E5CDD4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E5CDF8`
  - portrait p9 expr0 pos8
  - dialogue: "Have fun with Serenity."
  - fallthrough
- obj 1 R: `0x08E5CBC4`
  - portrait p9 expr0 pos8
  - dialogue: "You want to duel me? Sure thing! Let's duel!"
  - duel
  - fallthrough
- obj 2 A: `0x08E5CE04`
  - portrait p31 expr0 pos8
  - dialogue: "Huh? Aren't you supposed to be with Serenity? You have to catch the Kaibaman show."
  - fallthrough
- obj 2 R: `0x08E5CBE8`
  - portrait p31 expr0 pos8
  - dialogue: "I don't really consider myself a duelist... But I can duel better than that loser Tristan."
  - duel
  - fallthrough
- obj 3 A: `0x08E5CDD4`
  - play_music
  - dialogue: "Arf arf!"
  - fallthrough

## map_07_state_00

- map/state: `7/0`
- music: `6`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_07_state_01

- map/state: `7/1`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F828` R `0x08E5F834`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `52,96` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `68,96` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08E5F840`
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 32, 'wander': 1}
  - portrait p1 expr0 pos0
  - dialogue: "Grandpa, I'm home."
  - portrait p0 expr0 pos0
  - move_object: {'object_id': 4, 'direction': 2, 'distance': 32, 'wander': 0}
  - portrait p4 expr0 pos0
  - dialogue: "Hmm... Did any new rare cards come in?"
  - portrait p0 expr0 pos0
  - walk_object_y
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F828`
  - portrait p7 expr0 pos0
  - dialogue: "{PLAYER}, be careful."
  - fallthrough
- obj 1 R: `0x08E5F834`
  - portrait p7 expr0 pos0
  - dialogue: "Duel? Against me? If you have that kind of time, go help Ishizu."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_02

- map/state: `7/2`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F894` R `0x08E5F834`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F894`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F834`
  - portrait p7 expr0 pos0
  - dialogue: "Duel? Against me? If you have that kind of time, go help Ishizu."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_03

- map/state: `7/3`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8F4` R `0x08E5F90C`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08E5F8E8`
  - portrait p1 expr6 pos8
  - dialogue: "Grandpa! We're in trouble! Tristan turned into a monkey robot and ran away!"
  - portrait p8 expr0 pos8
  - dialogue: "Monkey robot? Like the ones made by KaibaCorp?"
  - portrait p4 expr2 pos8
  - dialogue: "I knew it was that dirty rat Kaiba's fault! Only a psycho like him would make a monkey out of my fri"
  - portrait p8 expr0 pos8
  - dialogue: "The robot looked harmless to me..."
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8F4`
  - portrait p7 expr0 pos8
  - dialogue: "Why would Kaiba turn Tristan into a robot...? Well, we have more important things to worry about. If"
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F90C`
  - portrait p7 expr0 pos8
  - dialogue: "Don't you have to find Tristan first?"
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_04

- map/state: `7/4`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8F4` R `0x08E5F90C`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8F4`
  - portrait p7 expr0 pos8
  - dialogue: "Why would Kaiba turn Tristan into a robot...? Well, we have more important things to worry about. If"
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F90C`
  - portrait p7 expr0 pos8
  - dialogue: "Don't you have to find Tristan first?"
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_05

- map/state: `7/5`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8B8` R `0x08E5F8DC`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8B8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F8DC`
  - portrait p7 expr0 pos8
  - dialogue: "What's the point of dueling me? Pegasus is the one you really want, {PLAYER}."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_06

- map/state: `7/6`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F828` R `0x08E5F834`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F828`
  - portrait p7 expr0 pos0
  - dialogue: "{PLAYER}, be careful."
  - fallthrough
- obj 1 R: `0x08E5F834`
  - portrait p7 expr0 pos0
  - dialogue: "Duel? Against me? If you have that kind of time, go help Ishizu."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_07

- map/state: `7/7`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F894` R `0x08E5F834`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `99` at `76,44` A `0x08E5F984` R `0x08E5F990`
- obj 6: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 7: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F894`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F834`
  - portrait p7 expr0 pos0
  - dialogue: "Duel? Against me? If you have that kind of time, go help Ishizu."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F984`
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Ukki!"
  - fallthrough
- obj 5 R: `0x08E5F990`
  - play_music
  - portrait p38 expr2 pos8
  - dialogue: "Ukki! Ukikki!"
  - duel
  - fallthrough
- obj 6 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_08

- map/state: `7/8`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8B8` R `0x08E5F8DC`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `99` at `76,44` A `0x08E5F984` R `0x08E5F990`
- obj 6: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 7: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8B8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F8DC`
  - portrait p7 expr0 pos8
  - dialogue: "What's the point of dueling me? Pegasus is the one you really want, {PLAYER}."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F984`
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Ukki!"
  - fallthrough
- obj 5 R: `0x08E5F990`
  - play_music
  - portrait p38 expr2 pos8
  - dialogue: "Ukki! Ukikki!"
  - duel
  - fallthrough
- obj 6 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_09

- map/state: `7/9`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F828` R `0x08E5F834`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `99` at `76,44` A `0x08E5F984` R `0x08E5F990`
- obj 6: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 7: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F828`
  - portrait p7 expr0 pos0
  - dialogue: "{PLAYER}, be careful."
  - fallthrough
- obj 1 R: `0x08E5F834`
  - portrait p7 expr0 pos0
  - dialogue: "Duel? Against me? If you have that kind of time, go help Ishizu."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F984`
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Ukki!"
  - fallthrough
- obj 5 R: `0x08E5F990`
  - play_music
  - portrait p38 expr2 pos8
  - dialogue: "Ukki! Ukikki!"
  - duel
  - fallthrough
- obj 6 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_10

- map/state: `7/10`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8B8` R `0x08E5F8DC`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `128,96` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `128,96` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8B8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F8DC`
  - portrait p7 expr0 pos8
  - dialogue: "What's the point of dueling me? Pegasus is the one you really want, {PLAYER}."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_11

- map/state: `7/11`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8B8` R `0x08E5F8DC`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `128,96` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8B8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F8DC`
  - portrait p7 expr0 pos8
  - dialogue: "What's the point of dueling me? Pegasus is the one you really want, {PLAYER}."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_12

- map/state: `7/12`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8B8` R `0x08E5F8DC`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `128,96` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `128,96` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `99` at `76,44` A `0x08E5F984` R `0x08E5F990`
- obj 6: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 7: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8B8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F8DC`
  - portrait p7 expr0 pos8
  - dialogue: "What's the point of dueling me? Pegasus is the one you really want, {PLAYER}."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F984`
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Ukki!"
  - fallthrough
- obj 5 R: `0x08E5F990`
  - play_music
  - portrait p38 expr2 pos8
  - dialogue: "Ukki! Ukikki!"
  - duel
  - fallthrough
- obj 6 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_13

- map/state: `7/13`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `47,52` A `0x08E5F8B8` R `0x08E5F8DC`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `128,96` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `99` at `76,44` A `0x08E5F984` R `0x08E5F990`
- obj 6: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 7: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F8B8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E5F8DC`
  - portrait p7 expr0 pos8
  - dialogue: "What's the point of dueling me? Pegasus is the one you really want, {PLAYER}."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F984`
  - play_music
  - portrait p38 expr0 pos8
  - dialogue: "Ukki!"
  - fallthrough
- obj 5 R: `0x08E5F990`
  - play_music
  - portrait p38 expr2 pos8
  - dialogue: "Ukki! Ukikki!"
  - duel
  - fallthrough
- obj 6 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_07_state_14

- map/state: `7/14`
- music: `6`

### Initial Sprites
- obj 1: sprite `10` at `128,96` A `0x08E5F828` R `0x08E5F834`
- obj 2: sprite `11` at `59,28` A `0x08E5F918` R `0x08E5F918`
- obj 3: sprite `1` at `68,64` A `0x08E5F84C` R `0x08E5F858`
- obj 4: sprite `4` at `52,64` A `0x08E5F870` R `0x08E5F87C`
- obj 5: sprite `41` at `84,32` A `0x08E5F948` R `0x08E5F948`
- obj 6: sprite `41` at `59,29` A `0x08E5F918` R `0x08E5F918`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E5F828`
  - portrait p7 expr0 pos0
  - dialogue: "{PLAYER}, be careful."
  - fallthrough
- obj 1 R: `0x08E5F834`
  - portrait p7 expr0 pos0
  - dialogue: "Duel? Against me? If you have that kind of time, go help Ishizu."
  - fallthrough
- obj 2 A: `0x08E5F918`
  - portrait p8 expr0 pos8
  - dialogue: "Hello! Good to see you! I have some excellent cards. {CARD_1}Buy cards Sell cards{CARD_2}"
  - fallthrough
- obj 3 A: `0x08E5F84C`
  - portrait p1 expr0 pos0
  - dialogue: "We should buy some cards and strengthen our decks."
  - fallthrough
- obj 3 R: `0x08E5F858`
  - portrait p1 expr0 pos0
  - dialogue: "Sure, let's check how our decks are shaping up!"
  - duel
  - fallthrough
- obj 4 A: `0x08E5F870`
  - portrait p4 expr0 pos0
  - dialogue: "I wish Yugi's grandpa would give us a discount on cards."
  - fallthrough
- obj 4 R: `0x08E5F87C`
  - portrait p4 expr0 pos0
  - dialogue: "Yeah, sure! I'll take ya on!"
  - duel
  - fallthrough
- obj 5 A: `0x08E5F948`
  - dialogue: "Hello. I am the Password Terminal. You can enter a password for {BYTE_8250}{BYTE_824F}{BYTE_824F}{BY"
  - fallthrough

## map_08_state_00

- map/state: `8/0`
- music: `5`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_08_state_01

- map/state: `8/1`
- music: `5`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_09_state_00

- map/state: `9/0`
- music: `5`

### Initial Sprites
- obj 1: sprite `41` at `56,32` A `0x08E621E4` R `0x08E621E4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E621E4`
  - play_music
  - special
  - restore_life_points
  - dialogue: "Your Life Points {BYTE_8169}LP{BYTE_816A} have been restored. Would you like to save? {CARD_1}Yes No"
  - fallthrough

## map_09_state_01

- map/state: `9/1`
- music: `12`

### Initial Sprites
- obj 1: sprite `41` at `56,32` A `0x08E621E4` R `0x08E621E4`
- obj 2: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 13: sprite `1` at `50,96` A `0x08F04034` R `0x08F04034`
- obj 14: sprite `4` at `80,62` A `0x08E62154` R `0x08E62154`

### Scripts
- enter 0: `0x08E62160`
  - play_music
  - set_flag
  - delay
  - portrait p4 expr0 pos0
  - dialogue: "Now I put dis Monsta Card in here, like so... And voila! I'm good to go!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos0
  - dialogue: "{PLAYER}, how's adjustin' your deck comin' along?"
  - portrait p0 expr0 pos0
  - dialogue: "{CARD_1}Perfect Lousy{CARD_2}"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08E621D8`
  - command_7c_2
  - fade_screen
  - warp: {'map_id': 1, 'state': 1, 'connection': 4}
  - fallthrough
- obj 1 A: `0x08E621E4`
  - play_music
  - special
  - restore_life_points
  - dialogue: "Your Life Points {BYTE_8169}LP{BYTE_816A} have been restored. Would you like to save? {CARD_1}Yes No"
  - fallthrough
- obj 14 A: `0x08E62154`
  - play_music
  - cutscene 8 INTRO_CUTSCENE
  - warp: {'map_id': 9, 'state': 2, 'connection': 0}
  - fallthrough

## map_09_state_02

- map/state: `9/2`
- music: `12`

### Initial Sprites
- obj 1: sprite `41` at `56,32` A `0x08E621E4` R `0x08E621E4`
- obj 2: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `0` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 13: sprite `1` at `50,96` A `0x08F04034` R `0x08F04034`
- obj 14: sprite `4` at `80,62` A `0x08E62154` R `0x08E62154`

### Scripts
- enter 0: `0x08E62160`
  - play_music
  - set_flag
  - delay
  - portrait p4 expr0 pos0
  - dialogue: "Now I put dis Monsta Card in here, like so... And voila! I'm good to go!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos0
  - dialogue: "{PLAYER}, how's adjustin' your deck comin' along?"
  - portrait p0 expr0 pos0
  - dialogue: "{CARD_1}Perfect Lousy{CARD_2}"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08E621D8`
  - command_7c_2
  - fade_screen
  - warp: {'map_id': 1, 'state': 1, 'connection': 4}
  - fallthrough
- obj 1 A: `0x08E621E4`
  - play_music
  - special
  - restore_life_points
  - dialogue: "Your Life Points {BYTE_8169}LP{BYTE_816A} have been restored. Would you like to save? {CARD_1}Yes No"
  - fallthrough
- obj 14 A: `0x08E62154`
  - play_music
  - cutscene 8 INTRO_CUTSCENE
  - warp: {'map_id': 9, 'state': 2, 'connection': 0}
  - fallthrough

## map_10_state_00

- map/state: `10/0`
- music: `7`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_10_state_01

- map/state: `10/1`
- music: `7`

### Initial Sprites
- obj 1: sprite `72` at `51,28` A `0x08E63218` R `0x08E63224`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E63218`
  - dialogue: "I want to get on the Duel Express... But I'm lost. I can't find Domino Station."
  - fallthrough
- obj 1 R: `0x08E63224`
  - check_flag
  - fallthrough

## map_10_state_02

- map/state: `10/2`
- music: `7`

### Initial Sprites
- obj 1: sprite `72` at `51,28` A `0x08E63254` R `0x08E63254`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E63254`
  - check_flag
  - fallthrough

## map_10_state_03

- map/state: `10/3`
- music: `7`

### Initial Sprites
- obj 1: sprite `72` at `51,28` A `0x08E63278` R `0x08E63284`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E63278`
  - dialogue: "The Neo Ghouls are gone, but... Something doesn't feel right. I hope nothing terrible happens."
  - fallthrough
- obj 1 R: `0x08E63284`
  - check_flag
  - fallthrough

## map_11_state_00

- map/state: `11/0`
- music: `7`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_11_state_01

- map/state: `11/1`
- music: `7`

### Initial Sprites
- obj 1: sprite `73` at `73,32` A `0x08E642EC` R `0x08E642F8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E642EC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E642F8`
  - check_flag
  - fallthrough

## map_11_state_02

- map/state: `11/2`
- music: `7`

### Initial Sprites
- obj 1: sprite `73` at `73,32` A `0x08E64334` R `0x08E64334`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E64334`
  - check_flag
  - fallthrough

## map_11_state_03

- map/state: `11/3`
- music: `7`

### Initial Sprites
- obj 1: sprite `73` at `73,32` A `0x08E64358` R `0x08E64364`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E64358`
  - dialogue: "I managed to hide my rare cards from the Neo Ghouls."
  - fallthrough
- obj 1 R: `0x08E64364`
  - check_flag
  - fallthrough

## map_12_state_00

- map/state: `12/0`
- music: `12`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_12_state_01

- map/state: `12/1`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6EF64` R `0x08E6EF70`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6EF64`
  - portrait p30 expr0 pos8
  - dialogue: "This is Kaiba Corporation. This is not a place for civilians."
  - fallthrough
- obj 1 R: `0x08E6EF70`
  - check_flag
  - fallthrough

## map_12_state_02

- map/state: `12/2`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6EF64` R `0x08E6EF70`
- obj 2: sprite `55` at `36,21` A `0x08E6EFA0` R `0x08E6EFC4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6EF64`
  - portrait p30 expr0 pos8
  - dialogue: "This is Kaiba Corporation. This is not a place for civilians."
  - fallthrough
- obj 1 R: `0x08E6EF70`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E6EFA0`
  - portrait p10 expr0 pos8
  - dialogue: "My big brother isn't here. He's investigating the Millennium Items."
  - check_flag
  - fallthrough
- obj 2 R: `0x08E6EFC4`
  - check_flag
  - fallthrough

## map_12_state_03

- map/state: `12/3`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6F000` R `0x08E6EF70`
- obj 2: sprite `55` at `128,44` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `49` at `73,52` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `54` at `73,60` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E6EFF4`
  - play_music
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - delay
  - portrait p30 expr0 pos0
  - dialogue: "I told you! No!"
  - portrait p9 expr5 pos0
  - dialogue: "Oh, come on, please?"
  - portrait p31 expr0 pos0
  - dialogue: "Yeah, we're Kaiba's best friends."
  - portrait p30 expr0 pos0
  - dialogue: "I've never heard of you two before."
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 24}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - portrait p10 expr0 pos0
  - dialogue: "What's going on?"
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - portrait p30 expr0 pos0
  - dialogue: "Master Mokuba..."
  - portrait p9 expr6 pos0
  - dialogue: "M-Mokuba! We're friends, right?"
  - portrait p31 expr0 pos0
  - dialogue: "Tristan, that's not what we're here for."
  - portrait p9 expr0 pos0
  - dialogue: "Whoops, that's right."
  - portrait p10 expr0 pos0
  - dialogue: "...Will somebody tell me what's going on?"
  - portrait p30 expr0 pos0
  - dialogue: "These two are demanding that..."
  - portrait p9 expr0 pos0
  - dialogue: "Let us use your Duel Machine!"
  - walk_object_x
  - walk_object_x
  - portrait p10 expr0 pos0
  - dialogue: "The Duel Machine? Why do you want it?"
  - slide_object
  - portrait p9 expr1 pos0
  - dialogue: "So Serenity will go out with me..."
  - play_music
  - slide_object
  - slide_object
  - portrait p31 expr0 pos0
  - dialogue: "N-no! That's not it! We want to improve our duel levels."
  - slide_object
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F000`
  - portrait p30 expr0 pos8
  - dialogue: "This is the first time Master Mokuba invited his friends to visit him at work... But are those two r"
  - fallthrough
- obj 1 R: `0x08E6EF70`
  - check_flag
  - fallthrough

## map_12_state_04

- map/state: `12/4`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6F000` R `0x08E6EF70`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F000`
  - portrait p30 expr0 pos8
  - dialogue: "This is the first time Master Mokuba invited his friends to visit him at work... But are those two r"
  - fallthrough
- obj 1 R: `0x08E6EF70`
  - check_flag
  - fallthrough

## map_12_state_05

- map/state: `12/5`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6F000` R `0x08E6EF70`
- obj 2: sprite `55` at `36,21` A `0x08E6F00C` R `0x08E6EFC4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F000`
  - portrait p30 expr0 pos8
  - dialogue: "This is the first time Master Mokuba invited his friends to visit him at work... But are those two r"
  - fallthrough
- obj 1 R: `0x08E6EF70`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E6F00C`
  - portrait p10 expr0 pos8
  - dialogue: "Tristan and Duke are training inside."
  - fallthrough
- obj 2 R: `0x08E6EFC4`
  - check_flag
  - fallthrough

## map_12_state_06

- map/state: `12/6`
- music: `405`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6F024` R `0x08E6F030`
- obj 2: sprite `55` at `36,21` A `0x08E6F084` R `0x08E6F09C`
- obj 3: sprite `3` at `24,21` A `0x08E6F0C0` R `0x08E6F0C0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F024`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E6F030`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E6F084`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E6F09C`
  - portrait p10 expr0 pos8
  - dialogue: "I'm too busy to play with you."
  - fallthrough
- obj 3 A: `0x08E6F0C0`
  - play_music
  - portrait p3 expr0 pos8
  - dialogue: "I figured you'd come. You're here to see about Obelisk the Tormentor. You want to know if it's turne"
  - portrait p0 expr0 pos8
  - dialogue: "{CARD_1}Yes No{CARD_2}"
  - fallthrough

## map_12_state_07

- map/state: `12/7`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6F024` R `0x08E6F030`
- obj 2: sprite `55` at `36,21` A `0x08E6F084` R `0x08E6F09C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F024`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E6F030`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E6F084`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E6F09C`
  - portrait p10 expr0 pos8
  - dialogue: "I'm too busy to play with you."
  - fallthrough

## map_12_state_08

- map/state: `12/8`
- music: `12`

### Initial Sprites
- obj 1: sprite `15` at `80,56` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E6F180`
  - play_music
  - portrait p22 expr0 pos0
  - dialogue: "Kukuku... Fresh new prey to hunt..."
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - portrait p1 expr0 pos1
  - dialogue: "There he is! It's him, {PLAYER}!"
  - portrait p4 expr0 pos1
  - dialogue: "He must be one of da remaining Neo Ghouls. He's who Espa Roba was talking about. I can't believe we "
  - portrait p1 expr0 pos1
  - dialogue: "Let's go!"
  - fade_screen
  - warp: {'map_id': 57, 'state': 2, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_12_state_09

- map/state: `12/9`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6EF64` R `0x08E6EF70`
- obj 2: sprite `55` at `36,21` A `0x08E6F114` R `0x08E6F114`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6EF64`
  - portrait p30 expr0 pos8
  - dialogue: "This is Kaiba Corporation. This is not a place for civilians."
  - fallthrough
- obj 1 R: `0x08E6EF70`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E6F114`
  - check_flag
  - fallthrough

## map_12_state_10

- map/state: `12/10`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6F0F0` R `0x08E6F0F0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F0F0`
  - check_flag
  - fallthrough

## map_12_state_11

- map/state: `12/11`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `55` at `36,21` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `129` at `24,32` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `129` at `36,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `129` at `48,32` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `129` at `30,40` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `129` at `42,40` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E6F168`
  - play_music
  - dialogue: "M-master Mokuba... Please, please give us one more chance."
  - portrait p10 expr2 pos8
  - dialogue: "After all the horrible things you've done to us?"
  - portrait p0 expr0 pos8
  - dialogue: "I know we were wrong. But... Times are tough. No one has any money! We want to work, but no one's hi"
  - portrait p10 expr0 pos8
  - dialogue: "Well... I guess I have something for you..."
  - portrait p0 expr0 pos8
  - dialogue: "R-really? Oh, thank you!"
  - portrait p10 expr0 pos8
  - dialogue: "All right. Quick, get changed."
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 248}
  - portrait p4 expr0 pos8
  - dialogue: "Where's Serenity?"
  - fade_screen
  - warp: {'map_id': 57, 'state': 1, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_12_state_12

- map/state: `12/12`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08E6F1C8` R `0x08E6EF70`
- obj 2: sprite `55` at `36,21` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `3` at `24,21` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `100` at `30,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `130` at `38,32` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E6F138`
  - play_music
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 3, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 14, 'direction': 3, 'distance': 8, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - delay
  - portrait p39 expr5 pos8
  - dialogue: "You're Seto Kaiba, aren't you?"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 24577}
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8192}
  - delay
  - portrait p10 expr2 pos8
  - dialogue: "Who are you? You're not very polite."
  - portrait p39 expr0 pos8
  - dialogue: "I'm Rebecca. And this is my friend Teddy."
  - hide_portrait
  - portrait p40 expr0 pos8
  - delay
  - portrait p10 expr0 pos8
  - dialogue: "A stuffed animal is your friend?"
  - portrait p39 expr5 pos8
  - dialogue: "Be quiet! Teddy's not a stuffed animal! Teddy is the best bear in the galaxy! Growl! And we know a s"
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 5, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p40 expr0 pos8
  - delay
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 5, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p39 expr5 pos8
  - dialogue: "You're the one who tore up Solomon Muto's card. You tore up his Blue-Eyes White Dragon."
  - hide_portrait
  - delay
  - play_music
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F1C8`
  - portrait p30 expr0 pos8
  - dialogue: "That girl is no match for Master Seto, but in ten years, she will be ready to take on the world."
  - fallthrough
- obj 1 R: `0x08E6EF70`
  - check_flag
  - fallthrough

## map_12_state_13

- map/state: `12/13`
- music: `31`

### Initial Sprites
- obj 1: sprite `33` at `26,21` A `0x08E6F1B0` R `0x08E6F1BC`
- obj 2: sprite `55` at `36,21` A `0x08E6F198` R `0x08E6F1A4`
- obj 3: sprite `129` at `24,32` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `129` at `36,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `129` at `48,32` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `129` at `30,40` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `129` at `42,40` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `56` at `12,66` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E6F174`
  - play_music
  - portrait p10 expr0 pos8
  - dialogue: "Roland, you played a good Kaibaman."
  - portrait p30 expr0 pos8
  - dialogue: "Thank you, Master Mokuba."
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p10 expr0 pos8
  - dialogue: "Everyone, good work! I'm counting on you again for the next show!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 248}
  - delay
  - move_object: {'object_id': 3, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Men, he did give us a job..."
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "But we were once The Big Five..."
  - hide_portrait
  - delay
  - move_object: {'object_id': 5, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Is this a job fit for the former KaibaCorp Board of Directors?"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 248}
  - delay
  - dialogue: "No! It's not! I don't want a job entertaining runts!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_x
  - move_object: {'object_id': 6, 'direction': 1, 'distance': 16, 'wander': 0}
  - delay
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 0, 'wander': 0}
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E6F1B0`
  - portrait p30 expr0 pos8
  - dialogue: "I was the one wearing the Kaibaman costume. But that's top secret!"
  - fallthrough
- obj 1 R: `0x08E6F1BC`
  - portrait p30 expr0 pos8
  - dialogue: "There's no way you can beat Kaibaman. You shouldn't even try."
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 1}
  - fallthrough
- obj 2 A: `0x08E6F198`
  - portrait p10 expr0 pos8
  - dialogue: "The Kaibaman show is really popular."
  - fallthrough
- obj 2 R: `0x08E6F1A4`
  - portrait p10 expr0 pos8
  - dialogue: "I bet you think you're a better duelist because you saw the show. But you're really not, so you shou"
  - fallthrough

## map_12_state_14

- map/state: `12/14`
- music: `12`

### Initial Sprites
- obj 1: sprite `33` at `80,56` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E6F18C`
  - play_music
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 8, 'wander': 0}
  - delay
  - portrait p30 expr0 pos0
  - dialogue: "Master Mokuba... Master Seto..."
  - hide_portrait
  - delay
  - portrait p30 expr0 pos0
  - dialogue: "There's no point standing around. There must be something that I can do... I know!"
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - fade_screen
  - warp: {'map_id': 57, 'state': 3, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_13_state_00

- map/state: `13/0`
- music: `12`

### Initial Sprites
- obj 1: sprite `41` at `76,53` A `0x08E716DC` R `0x08E716E8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E716DC`
  - play_music
  - dialogue: "BEEP PIPPI... I AM... KAIBA CORPORATION'S LATEST DUEL MACHINE KC-{BYTE_8250}{BYTE_824F}{BYTE_824F}{B"
  - fallthrough
- obj 1 R: `0x08E716E8`
  - play_music
  - dialogue: "CHALLENGE CONFIRMED. ENTER DESIRED DUEL LEVEL. {CARD_1}Novice Standard and above{CARD_2}"
  - fallthrough

## map_13_state_01

- map/state: `13/1`
- music: `12`

### Initial Sprites
- obj 1: sprite `55` at `62,40` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `49` at `46,48` A `0x08E716AC` R `0x08E716B8`
- obj 3: sprite `54` at `46,56` A `0x08E716C4` R `0x08E716D0`
- obj 4: sprite `41` at `76,53` A `0x08E71760` R `0x08E7176C`

### Scripts
- enter 0: `0x08E716A0`
  - play_music
  - portrait p9 expr0 pos8
  - dialogue: "Mokuba, crank it up to the max duelist level!"
  - portrait p10 expr0 pos8
  - dialogue: "No way! The computer will totally pummel you! Start at level {BYTE_8251}. If you can't win at that l"
  - portrait p9 expr0 pos8
  - dialogue: "Oh, fine. I guess that'll have to do."
  - portrait p31 expr0 pos8
  - dialogue: "Set me up at the same level!"
  - portrait p10 expr0 pos8
  - dialogue: "Okay, start the Duel Machine!"
  - play_music
  - fade_screen
  - portrait p9 expr4 pos8
  - dialogue: "Gwaaaaaaah!"
  - portrait p31 expr0 pos8
  - dialogue: "I... I barely won."
  - portrait p0 expr0 pos8
  - play_music
  - dialogue: "ASSESSING DUELIST LEVEL... ASSESSING DUELIST LEVEL... ASSESSMENT COMPLETE. BOTH IDIOTS. BOTH IDIOTS."
  - portrait p9 expr5 pos8
  - dialogue: "Are you serious?"
  - portrait p31 expr5 pos8
  - dialogue: "But I won!"
  - portrait p10 expr0 pos8
  - dialogue: "Simply winning doesn't impress the Duel Machine. It also checks for spell and trap combos. Judging b"
  - portrait p0 expr0 pos8
  - dialogue: "Oh yeah? One more time!"
  - portrait p10 expr0 pos8
  - dialogue: "Go right ahead. But I think you're wasting your time."
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - set_object_position
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 2 A: `0x08E716AC`
  - portrait p9 expr5 pos8
  - dialogue: "I'm training! Don't distract me!"
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08E716B8`
  - portrait p9 expr5 pos8
  - dialogue: "Can't you see I'm dueling?"
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 A: `0x08E716C4`
  - portrait p31 expr5 pos8
  - dialogue: "I can't lose to Tristan."
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 R: `0x08E716D0`
  - portrait p31 expr5 pos8
  - dialogue: "Please don't bug me while I'm training."
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 4 A: `0x08E71760`
  - play_music
  - dialogue: "OPERATING AT DUELIST LEVEL {BYTE_8251}. SYSTEM IN OPERATION."
  - fallthrough
- obj 4 R: `0x08E7176C`
  - play_music
  - dialogue: "OPERATING AT DUELIST LEVEL FOR IDIOTS. SYSTEM IN OPERATION. WAIT FOR YOUR TURN BEFORE STARTING."
  - fallthrough

## map_13_state_02

- map/state: `13/2`
- music: `12`

### Initial Sprites
- obj 1: sprite `49` at `46,48` A `0x08E716AC` R `0x08E716B8`
- obj 2: sprite `54` at `46,56` A `0x08E716C4` R `0x08E716D0`
- obj 3: sprite `41` at `76,53` A `0x08E71760` R `0x08E7176C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E716AC`
  - portrait p9 expr5 pos8
  - dialogue: "I'm training! Don't distract me!"
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 1 R: `0x08E716B8`
  - portrait p9 expr5 pos8
  - dialogue: "Can't you see I'm dueling?"
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 A: `0x08E716C4`
  - portrait p31 expr5 pos8
  - dialogue: "I can't lose to Tristan."
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08E716D0`
  - portrait p31 expr5 pos8
  - dialogue: "Please don't bug me while I'm training."
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 A: `0x08E71760`
  - play_music
  - dialogue: "OPERATING AT DUELIST LEVEL {BYTE_8251}. SYSTEM IN OPERATION."
  - fallthrough
- obj 3 R: `0x08E7176C`
  - play_music
  - dialogue: "OPERATING AT DUELIST LEVEL FOR IDIOTS. SYSTEM IN OPERATION. WAIT FOR YOUR TURN BEFORE STARTING."
  - fallthrough

## map_13_state_03

- map/state: `13/3`
- music: `12`

### Initial Sprites
- obj 1: sprite `41` at `76,53` A `0x08E716DC` R `0x08E716E8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E716DC`
  - play_music
  - dialogue: "BEEP PIPPI... I AM... KAIBA CORPORATION'S LATEST DUEL MACHINE KC-{BYTE_8250}{BYTE_824F}{BYTE_824F}{B"
  - fallthrough
- obj 1 R: `0x08E716E8`
  - play_music
  - dialogue: "CHALLENGE CONFIRMED. ENTER DESIRED DUEL LEVEL. {CARD_1}Novice Standard and above{CARD_2}"
  - fallthrough

## map_14_state_00

- map/state: `14/0`
- music: `230`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_14_state_01

- map/state: `14/1`
- music: `230`

### Initial Sprites
- obj 1: sprite `52` at `31,26` A `0x08E773E4` R `0x08E773E4`
- obj 2: sprite `52` at `43,26` A `0x08E77564` R `0x08E77564`
- obj 3: sprite `52` at `56,26` A `0x08E77570` R `0x08E77570`
- obj 4: sprite `40` at `112,60` A `0x08E7736C` R `0x08E77378`
- obj 5: sprite `51` at `12,50` A `0x08E773A8` R `0x08E773B4`
- obj 6: sprite `29` at `56,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E774EC`
  - check_flag
  - fallthrough
- exit 0: `0x08E774E0`
  - check_flag
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E773E4`
  - dialogue: "KaibaCorp is amazing. They chartered an entire express train just for a duel tournament..."
  - fallthrough
- obj 2 A: `0x08E77564`
  - dialogue: "All aboard! Duel Express will soon depart! The next and only stop is the Egypt Exhibition!"
  - fallthrough
- obj 3 A: `0x08E77570`
  - dialogue: "The Duel Express is only running for duelists today. Non-duelists are not allowed to ride."
  - fallthrough
- obj 4 A: `0x08E7736C`
  - dialogue: "If you win this tournament, you get a lot of ante cards! With these high stakes, it's more exciting "
  - fallthrough
- obj 4 R: `0x08E77378`
  - check_flag
  - fallthrough
- obj 5 A: `0x08E773A8`
  - dialogue: "Dueling is stupid. Haven't you heard? There are a bunch of bad guys who rip off rare cards in duels."
  - fallthrough
- obj 5 R: `0x08E773B4`
  - dialogue: "No way! Forget it! I don't even want to look at any cards!"
  - fallthrough

## map_14_state_02

- map/state: `14/2`
- music: `230`

### Initial Sprites
- obj 1: sprite `52` at `31,26` A `0x08E773E4` R `0x08E773E4`
- obj 2: sprite `52` at `43,26` A `0x08E77564` R `0x08E77564`
- obj 3: sprite `52` at `68,32` A `0x08E77570` R `0x08E77570`
- obj 4: sprite `40` at `112,60` A `0x08E7736C` R `0x08E77378`
- obj 5: sprite `51` at `12,50` A `0x08E773A8` R `0x08E773B4`
- obj 6: sprite `29` at `56,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08E774E0`
  - check_flag
  - fallthrough
- obj 1 A: `0x08E773E4`
  - dialogue: "KaibaCorp is amazing. They chartered an entire express train just for a duel tournament..."
  - fallthrough
- obj 2 A: `0x08E77564`
  - dialogue: "All aboard! Duel Express will soon depart! The next and only stop is the Egypt Exhibition!"
  - fallthrough
- obj 3 A: `0x08E77570`
  - dialogue: "The Duel Express is only running for duelists today. Non-duelists are not allowed to ride."
  - fallthrough
- obj 4 A: `0x08E7736C`
  - dialogue: "If you win this tournament, you get a lot of ante cards! With these high stakes, it's more exciting "
  - fallthrough
- obj 4 R: `0x08E77378`
  - check_flag
  - fallthrough
- obj 5 A: `0x08E773A8`
  - dialogue: "Dueling is stupid. Haven't you heard? There are a bunch of bad guys who rip off rare cards in duels."
  - fallthrough
- obj 5 R: `0x08E773B4`
  - dialogue: "No way! Forget it! I don't even want to look at any cards!"
  - fallthrough

## map_14_state_03

- map/state: `14/3`
- music: `230`

### Initial Sprites
- obj 1: sprite `52` at `31,26` A `0x08E773E4` R `0x08E773E4`
- obj 2: sprite `52` at `43,26` A `0x08E773E4` R `0x08E773E4`
- obj 3: sprite `52` at `68,32` A `0x08E773E4` R `0x08E773E4`
- obj 4: sprite `74` at `80,48` A `0x08E77414` R `0x08E77420`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E773E4`
  - dialogue: "KaibaCorp is amazing. They chartered an entire express train just for a duel tournament..."
  - fallthrough
- obj 4 A: `0x08E77414`
  - dialogue: "First class costs too much. An economy seat will do."
  - fallthrough
- obj 4 R: `0x08E77420`
  - dialogue: "This is where they punch your ticket. Go shuffle your deck somewhere else."
  - fallthrough

## map_14_state_04

- map/state: `14/4`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `56,26` A `0x08E77444` R `0x08E77450`
- obj 2: sprite `26` at `43,26` A `0x08E77438` R `0x08E77438`
- obj 3: sprite `26` at `31,26` A `0x08E77438` R `0x08E77438`
- obj 4: sprite `74` at `80,48` A `0x08E77474` R `0x08E77480`
- obj 5: sprite `52` at `48,64` A `0x08E774A4` R `0x08E774B0`

### Scripts
- enter 0: `0x08E7742C`
  - clear_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E77444`
  - portrait p49 expr0 pos8
  - dialogue: "This is Neo Ghouls' turf! Get lost!"
  - fallthrough
- obj 1 R: `0x08E77450`
  - portrait p49 expr0 pos8
  - dialogue: "Do you think you can beat the Neo Ghouls?"
  - duel
  - fallthrough
- obj 2 A: `0x08E77438`
  - portrait p49 expr0 pos8
  - dialogue: "This is Neo Ghouls' turf! Get lost!"
  - fallthrough
- obj 4 A: `0x08E77474`
  - dialogue: "You want to know what's going on? I'll tell you what's going on! Those weird guys won't let us up to"
  - fallthrough
- obj 4 R: `0x08E77480`
  - dialogue: "This is hardly the time for that!"
  - fallthrough
- obj 5 A: `0x08E774A4`
  - dialogue: "Oh my, what to do, what to do. What on earth are those people up to? Those Neo Ghouls are horrible d"
  - fallthrough
- obj 5 R: `0x08E774B0`
  - dialogue: "Do I look like a duelist to you?"
  - fallthrough

## map_14_state_05

- map/state: `14/5`
- music: `230`

### Initial Sprites
- obj 1: sprite `74` at `80,48` A `0x08E7748C` R `0x08E77498`
- obj 2: sprite `52` at `48,64` A `0x08E774BC` R `0x08E774B0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E7748C`
  - dialogue: "Those Neo Ghoul weirdoes are finally gone."
  - fallthrough
- obj 1 R: `0x08E77498`
  - dialogue: "Sorry, I don't have time for fun and games."
  - fallthrough
- obj 2 A: `0x08E774BC`
  - dialogue: "The Neo Ghouls at the turnstiles may have left... But unfortunately, there are still more on the tra"
  - fallthrough
- obj 2 R: `0x08E774B0`
  - dialogue: "Do I look like a duelist to you?"
  - fallthrough

## map_14_state_06

- map/state: `14/6`
- music: `230`

### Initial Sprites
- obj 1: sprite `74` at `80,48` A `0x08E7748C` R `0x08E77498`
- obj 2: sprite `52` at `48,64` A `0x08E774C8` R `0x08E774D4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E7748C`
  - dialogue: "Those Neo Ghoul weirdoes are finally gone."
  - fallthrough
- obj 1 R: `0x08E77498`
  - dialogue: "Sorry, I don't have time for fun and games."
  - fallthrough
- obj 2 A: `0x08E774C8`
  - dialogue: "The next stop is the Egypt Exhibition."
  - fallthrough
- obj 2 R: `0x08E774D4`
  - dialogue: "Sorry, I'm working."
  - fallthrough

## map_14_state_07

- map/state: `14/7`
- music: `230`

### Initial Sprites
- obj 1: sprite `1` at `49,54` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `4` at `56,44` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `52` at `31,26` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `52` at `43,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `52` at `56,32` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `40` at `112,60` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `51` at `12,50` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E77588`
  - play_music
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos1
  - dialogue: "What took ya so long, {PLAYER}! If you're having trouble against these guys... Well, I'd hate to thi"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 1}
  - delay
  - command_7c_2
  - fade_screen
  - clear_flag
  - check_flag
  - fallthrough
- exit 0: `0x08E774E0`
  - check_flag
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_14_state_08

- map/state: `14/8`
- music: `230`

### Initial Sprites
- obj 1: sprite `1` at `62,54` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `4` at `43,44` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `52` at `31,26` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `52` at `43,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `52` at `56,32` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `40` at `112,60` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `51` at `12,50` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E77594`
  - play_music
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos1
  - dialogue: "What took ya so long, {PLAYER}! If you're having trouble against these guys... Well, I'd hate to thi"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 1}
  - delay
  - command_7c_2
  - fade_screen
  - clear_flag
  - check_flag
  - fallthrough
- exit 0: `0x08E774E0`
  - check_flag
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_14_state_09

- map/state: `14/9`
- music: `230`

### Initial Sprites
- obj 1: sprite `1` at `56,44` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `4` at `37,54` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `52` at `31,26` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `52` at `43,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `52` at `56,32` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `40` at `112,60` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `51` at `12,50` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E775B8`
  - play_music
  - hide_portrait
  - delay
  - portrait p4 expr0 pos1
  - dialogue: "Gotta hand it to you, Yugi. That duel lasted barely a second! On the other hand..."
  - portrait p4 expr7 pos1
  - dialogue: "{PLAYER}, you had me worried!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 1}
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p1 expr0 pos1
  - dialogue: "I... I couldn't afford to waste any time. I have to find the spirit right away! But {PLAYER}'s duel "
  - hide_portrait
  - delay
  - command_7c_2
  - fade_screen
  - clear_flag
  - check_flag
  - fallthrough
- exit 0: `0x08E774E0`
  - check_flag
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_14_state_10

- map/state: `14/10`
- music: `230`

### Initial Sprites
- obj 1: sprite `1` at `43,44` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `4` at `50,54` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `52` at `31,26` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `52` at `43,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `52` at `56,32` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `40` at `112,60` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `51` at `12,50` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E775C4`
  - play_music
  - hide_portrait
  - delay
  - portrait p4 expr0 pos8
  - dialogue: "Gotta hand it to you, Yugi. That duel lasted barely a second! On the other hand..."
  - portrait p4 expr7 pos1
  - dialogue: "{PLAYER}, you had me worried!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 1}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p1 expr0 pos8
  - dialogue: "I... I couldn't afford to waste any time. I have to find the spirit right away! But {PLAYER}'s duel "
  - hide_portrait
  - delay
  - command_7c_2
  - fade_screen
  - clear_flag
  - check_flag
  - fallthrough
- exit 0: `0x08E774E0`
  - check_flag
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_15_state_00

- map/state: `15/0`
- music: `231`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04064`
  - set_flag
  - fallthrough

## map_15_state_01

- map/state: `15/1`
- music: `231`

### Initial Sprites
- obj 1: sprite `75` at `31,60` A `0x08E7A47C` R `0x08E7A488`
- obj 2: sprite `76` at `34,32` A `0x08E7A4C4` R `0x08E7A4D0`
- obj 3: sprite `77` at `69,24` A `0x08E7A50C` R `0x08E7A500`
- obj 4: sprite `78` at `76,46` A `0x08E7A53C` R `0x08E7A548`
- obj 5: sprite `79` at `101,33` A `0x08E7A578` R `0x08E7A584`

### Scripts
- enter 0: `0x08E7A458`
  - play_music
  - portrait p4 expr0 pos0
  - dialogue: "The Duel Express is reserved for duelists only... I'm raring to go!"
  - portrait p0 expr0 pos0
  - dialogue: "{CARD_1}Our objective is... I won't lose!{CARD_2}"
  - fallthrough
- exit 0: `0x08F04064`
  - set_flag
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E7A47C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E7A488`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E7A4C4`
  - dialogue: "What a motley crew of pathetic duelists."
  - fallthrough
- obj 2 R: `0x08E7A4D0`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E7A50C`
  - dialogue: "Everyone looks so tough. I'm not sure if I can last until the end."
  - fallthrough
- obj 3 R: `0x08E7A500`
  - check_flag
  - fallthrough
- obj 4 A: `0x08E7A53C`
  - dialogue: "KaibaCorp sure knows how to throw an event. They're letting us ride a chartered express train for fr"
  - fallthrough
- obj 4 R: `0x08E7A548`
  - check_flag
  - fallthrough
- obj 5 A: `0x08E7A578`
  - dialogue: "The Duel Express is bound for the Egypt Exhibition. The station is very crowded due to the duel tour"
  - fallthrough
- obj 5 R: `0x08E7A584`
  - check_flag
  - fallthrough

## map_15_state_02

- map/state: `15/2`
- music: `231`

### Initial Sprites
- obj 1: sprite `75` at `31,60` A `0x08E7A47C` R `0x08E7A488`
- obj 2: sprite `76` at `34,32` A `0x08E7A4C4` R `0x08E7A4D0`
- obj 3: sprite `77` at `69,24` A `0x08E7A50C` R `0x08E7A500`
- obj 4: sprite `78` at `76,46` A `0x08E7A53C` R `0x08E7A548`
- obj 5: sprite `79` at `101,33` A `0x08E7A578` R `0x08E7A584`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04064`
  - set_flag
  - fallthrough
- obj 1 A: `0x08E7A47C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E7A488`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E7A4C4`
  - dialogue: "What a motley crew of pathetic duelists."
  - fallthrough
- obj 2 R: `0x08E7A4D0`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E7A50C`
  - dialogue: "Everyone looks so tough. I'm not sure if I can last until the end."
  - fallthrough
- obj 3 R: `0x08E7A500`
  - check_flag
  - fallthrough
- obj 4 A: `0x08E7A53C`
  - dialogue: "KaibaCorp sure knows how to throw an event. They're letting us ride a chartered express train for fr"
  - fallthrough
- obj 4 R: `0x08E7A548`
  - check_flag
  - fallthrough
- obj 5 A: `0x08E7A578`
  - dialogue: "The Duel Express is bound for the Egypt Exhibition. The station is very crowded due to the duel tour"
  - fallthrough
- obj 5 R: `0x08E7A584`
  - check_flag
  - fallthrough

## map_15_state_03

- map/state: `15/3`
- music: `231`

### Initial Sprites
- obj 1: sprite `80` at `69,24` A `0x08E7A5B4` R `0x08E7A5C0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04064`
  - set_flag
  - fallthrough
- obj 1 A: `0x08E7A5B4`
  - dialogue: "I heard a most remarkable thing today. An express train was chartered solely for dueling! Some peopl"
  - fallthrough
- obj 1 R: `0x08E7A5C0`
  - check_flag
  - fallthrough

## map_15_state_04

- map/state: `15/4`
- music: `231`

### Initial Sprites
- obj 1: sprite `80` at `69,24` A `0x08E7A5F0` R `0x08E7A5F0`
- obj 2: sprite `79` at `101,33` A `0x08E7A5FC` R `0x08E7A608`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04064`
  - set_flag
  - fallthrough
- obj 1 A: `0x08E7A5F0`
  - dialogue: "The Neo Ghouls robbed me of all my rare cards. I can't duel anymore."
  - fallthrough
- obj 2 A: `0x08E7A5FC`
  - dialogue: "The next stop is the Egypt Exhibition... But the Neo Ghouls have taken over the train."
  - fallthrough
- obj 2 R: `0x08E7A608`
  - dialogue: "Please don't joke at a time like this."
  - fallthrough

## map_15_state_05

- map/state: `15/5`
- music: `231`

### Initial Sprites
- obj 1: sprite `80` at `69,24` A `0x08E7A614` R `0x08E7A614`
- obj 2: sprite `79` at `101,33` A `0x08E7A620` R `0x08E7A620`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04064`
  - set_flag
  - fallthrough
- obj 1 A: `0x08E7A614`
  - dialogue: "Take this train if you want to go to the Egypt Exhibition."
  - fallthrough
- obj 2 A: `0x08E7A620`
  - dialogue: "This train will be departing shortly. Please wait on board."
  - fallthrough

## map_16_state_00

- map/state: `16/0`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_16_state_01

- map/state: `16/1`
- music: `232`

### Initial Sprites
- obj 1: sprite `46` at `8,52` A `0x08E7DDF8` R `0x08E7DE34`
- obj 2: sprite `53` at `64,48` A `0x08E7DCD8` R `0x08E7DD14`
- obj 3: sprite `58` at `48,48` A `0x08E7DD68` R `0x08E7DDA4`
- obj 4: sprite `46` at `88,56` A `0x08E7DEB8` R `0x08E7DEB8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E7DDF8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E7DE34`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E7DCD8`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E7DD14`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E7DD68`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E7DDA4`
  - check_flag
  - fallthrough
- obj 4 A: `0x08E7DEB8`
  - check_flag
  - fallthrough

## map_16_state_02

- map/state: `16/2`
- music: `232`

### Initial Sprites
- obj 1: sprite `46` at `8,44` A `0x08E7DE7C` R `0x08E7DE34`
- obj 2: sprite `53` at `128,96` A `0x08E7DCD8` R `0x08E7DD14`
- obj 3: sprite `58` at `128,96` A `0x08E7DD68` R `0x08E7DDA4`
- obj 4: sprite `46` at `88,56` A `0x08E7DE7C` R `0x08E7DE34`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08E7E02C`
  - check_flag
  - fallthrough
- obj 1 A: `0x08E7DE7C`
  - dialogue: "A giant man, you say? He disembarked and headed to the Egypt Exhibition."
  - fallthrough
- obj 1 R: `0x08E7DE34`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E7DCD8`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E7DD14`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E7DD68`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E7DDA4`
  - check_flag
  - fallthrough

## map_16_state_03

- map/state: `16/3`
- music: `232`

### Initial Sprites
- obj 1: sprite `46` at `8,52` A `0x08E7DEDC` R `0x08E7DEDC`
- obj 2: sprite `53` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `58` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `46` at `88,56` A `0x08E7DF78` R `0x08E7DEE8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08E7E02C`
  - check_flag
  - fallthrough
- obj 1 A: `0x08E7DEDC`
  - dialogue: "Thank you for riding with us."
  - fallthrough
- obj 4 A: `0x08E7DF78`
  - check_flag
  - fallthrough
- obj 4 R: `0x08E7DEE8`
  - check_flag
  - fallthrough

## map_16_state_04

- map/state: `16/4`
- music: `232`

### Initial Sprites
- obj 1: sprite `46` at `8,44` A `0x08E7DE7C` R `0x08E7DE34`
- obj 2: sprite `53` at `128,96` A `0x08E7DCD8` R `0x08E7DD14`
- obj 3: sprite `58` at `128,96` A `0x08E7DD68` R `0x08E7DDA4`
- obj 4: sprite `46` at `108,56` A `0x08E7DF78` R `0x08E7DEE8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08E7E02C`
  - check_flag
  - fallthrough
- obj 1 A: `0x08E7DE7C`
  - dialogue: "A giant man, you say? He disembarked and headed to the Egypt Exhibition."
  - fallthrough
- obj 1 R: `0x08E7DE34`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E7DCD8`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E7DD14`
  - check_flag
  - fallthrough
- obj 3 A: `0x08E7DD68`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E7DDA4`
  - check_flag
  - fallthrough
- obj 4 A: `0x08E7DF78`
  - check_flag
  - fallthrough
- obj 4 R: `0x08E7DEE8`
  - check_flag
  - fallthrough

## map_16_state_05

- map/state: `16/5`
- music: `236`

### Initial Sprites
- obj 1: sprite `46` at `9,44` A `0x08E7DEDC` R `0x08E7DEDC`
- obj 2: sprite `53` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `58` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `46` at `108,56` A `0x08E7DF78` R `0x08E7DEE8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08E7E02C`
  - check_flag
  - fallthrough
- obj 1 A: `0x08E7DEDC`
  - dialogue: "Thank you for riding with us."
  - fallthrough
- obj 4 A: `0x08E7DF78`
  - check_flag
  - fallthrough
- obj 4 R: `0x08E7DEE8`
  - check_flag
  - fallthrough

## map_16_state_06

- map/state: `16/6`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `8,52` A `0x08E7DFB4` R `0x08E7DFC0`
- obj 2: sprite `46` at `88,56` A `0x08E7DFF0` R `0x08E7DFF0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E7DFB4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E7DFC0`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E7DFF0`
  - check_flag
  - fallthrough

## map_16_state_07

- map/state: `16/7`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `128,96` A `0x08E7DFE4` R `0x08E7DFE4`
- obj 2: sprite `46` at `108,56` A `0x08E7DFF0` R `0x08E7DFF0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E7DFE4`
  - portrait p49 expr0 pos8
  - dialogue: "..."
  - fallthrough
- obj 2 A: `0x08E7DFF0`
  - check_flag
  - fallthrough

## map_16_state_08

- map/state: `16/8`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_16_state_09

- map/state: `16/9`
- music: `232`

### Initial Sprites
- obj 1: sprite `46` at `8,52` A `0x08E7DEDC` R `0x08E7DEDC`
- obj 2: sprite `53` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `58` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `46` at `88,56` A `0x08E7DF78` R `0x08E7DEE8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08E7E02C`
  - check_flag
  - fallthrough
- obj 1 A: `0x08E7DEDC`
  - dialogue: "Thank you for riding with us."
  - fallthrough
- obj 4 A: `0x08E7DF78`
  - check_flag
  - fallthrough
- obj 4 R: `0x08E7DEE8`
  - check_flag
  - fallthrough

## map_16_state_10

- map/state: `16/10`
- music: `236`

### Initial Sprites
- obj 1: sprite `46` at `9,44` A `0x08E7DEDC` R `0x08E7DEDC`
- obj 2: sprite `53` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `58` at `65528,65528` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `46` at `108,56` A `0x08E7DF78` R `0x08E7DEE8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08E7E02C`
  - check_flag
  - fallthrough
- obj 1 A: `0x08E7DEDC`
  - dialogue: "Thank you for riding with us."
  - fallthrough
- obj 4 A: `0x08E7DF78`
  - check_flag
  - fallthrough
- obj 4 R: `0x08E7DEE8`
  - check_flag
  - fallthrough

## map_16_state_11

- map/state: `16/11`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_17_state_00

- map/state: `17/0`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_17_state_01

- map/state: `17/1`
- music: `232`

### Initial Sprites
- obj 1: sprite `29` at `65528,52` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E7F10C`
  - walk_object_x
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 13, 'direction': 1, 'distance': 0, 'wander': 0}
  - walk_object_x
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_17_state_02

- map/state: `17/2`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_17_state_03

- map/state: `17/3`
- music: `236`

### Initial Sprites
- obj 1: sprite `74` at `58,45` A `0x08E7F148` R `0x08E7F154`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E7F148`
  - dialogue: "I should've taken first class..."
  - fallthrough
- obj 1 R: `0x08E7F154`
  - dialogue: "This is the train's deck! Don't confuse it with a duel deck!"
  - fallthrough

## map_17_state_04

- map/state: `17/4`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `8,56` A `0x08E7F160` R `0x08E7F16C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E7F160`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E7F16C`
  - check_flag
  - fallthrough

## map_17_state_05

- map/state: `17/5`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `128,96` A `0x08E7F19C` R `0x08E7F19C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E7F19C`
  - portrait p49 expr0 pos8
  - dialogue: "..."
  - fallthrough

## map_17_state_06

- map/state: `17/6`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_17_state_07

- map/state: `17/7`
- music: `232`

### Initial Sprites
- obj 1: sprite `29` at `80,52` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `46` at `128,52` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- enter 2: `0x08E7F124`
  - play_music
  - play_music
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24577}
  - portrait p19 expr0 pos0
  - dialogue: "Ha ha ha! Looks like we've entered a tunnel! And darkness gives me power! It's time to duel!"
  - clear_flag
  - duel
  - fallthrough

## map_17_state_08

- map/state: `17/8`
- music: `236`

### Initial Sprites
- obj 1: sprite `74` at `58,45` A `0x08E7F1A8` R `0x08E7F1B4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E7F1A8`
  - dialogue: "The train is the best way to travel. How else can you see the beautiful scenery? It's too bad I'm ge"
  - fallthrough
- obj 1 R: `0x08E7F1B4`
  - dialogue: "I'm taking a vacation by train. Please let me enjoy this time alone."
  - fallthrough

## map_18_state_00

- map/state: `18/0`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_18_state_01

- map/state: `18/1`
- music: `232`

### Initial Sprites
- obj 1: sprite `43` at `10,51` A `0x08E80A6C` R `0x08E80A78`
- obj 2: sprite `44` at `28,40` A `0x08E80AC0` R `0x08E80ACC`
- obj 3: sprite `45` at `80,56` A `0x08E80A18` R `0x08E80A24`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E80A6C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E80A78`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E80AC0`
  - dialogue: "I only came for the Egypt Exhibition. I had no clue that dueling was my husband's hobby. I wouldn't "
  - fallthrough
- obj 2 R: `0x08E80ACC`
  - dialogue: "Duel? Most certainly not. How uncouth!"
  - fallthrough
- obj 3 A: `0x08E80A18`
  - check_flag
  - fallthrough
- obj 3 R: `0x08E80A24`
  - check_flag
  - fallthrough

## map_18_state_02

- map/state: `18/2`
- music: `236`

### Initial Sprites
- obj 1: sprite `80` at `32,56` A `0x08E80AD8` R `0x08E80AE4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E80AD8`
  - dialogue: "A journey by train has its charms."
  - fallthrough
- obj 1 R: `0x08E80AE4`
  - check_flag
  - fallthrough

## map_18_state_03

- map/state: `18/3`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `16,55` A `0x08E80B2C` R `0x08E80B2C`
- obj 2: sprite `46` at `128,52` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E80B2C`
  - portrait p49 expr0 pos8
  - dialogue: "You must be pretty good to get this far! But I'm warning you, I'm much tougher than the other guys!"
  - duel
  - fallthrough

## map_18_state_04

- map/state: `18/4`
- music: `232`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_18_state_05

- map/state: `18/5`
- music: `236`

### Initial Sprites
- obj 1: sprite `80` at `32,56` A `0x08E80B50` R `0x08E80B5C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E80B50`
  - dialogue: "Sigh... I feel so empty... Oh, if only my rare cards were safe..."
  - fallthrough
- obj 1 R: `0x08E80B5C`
  - dialogue: "I can't duel without my cards."
  - fallthrough

## map_19_state_00

- map/state: `19/0`
- music: `16`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_19_state_01

- map/state: `19/1`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `96,52` A `0x08E83A84` R `0x08E83A90`
- obj 2: sprite `1` at `128,52` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `4` at `128,68` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `63` at `65528,64` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `16` at `65528,64` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `14` at `65528,58` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `15` at `65528,70` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E83A84`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E83A90`
  - check_flag
  - fallthrough

## map_19_state_02

- map/state: `19/2`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `96,52` A `0x08E83A84` R `0x08E83A90`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E83A84`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E83A90`
  - check_flag
  - fallthrough

## map_19_state_03

- map/state: `19/3`
- music: `16`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_20_state_00

- map/state: `20/0`
- music: `231`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_20_state_01

- map/state: `20/1`
- music: `231`

### Initial Sprites
- obj 1: sprite `81` at `72,48` A `0x08E84F30` R `0x08E84F3C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E84F30`
  - dialogue: "A big guy took off running up the stairs."
  - fallthrough
- obj 1 R: `0x08E84F3C`
  - dialogue: "This is where I lost. I have no more ante cards."
  - fallthrough

## map_20_state_02

- map/state: `20/2`
- music: `231`

### Initial Sprites
- obj 1: sprite `82` at `72,48` A `0x08E84F48` R `0x08E84F54`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E84F48`
  - dialogue: "Grovel before me like the dog that you are! I'm trying to imitate Kaiba. Pretty good, right? Huh? He"
  - fallthrough
- obj 1 R: `0x08E84F54`
  - check_flag
  - fallthrough

## map_20_state_03

- map/state: `20/3`
- music: `11`

### Initial Sprites
- obj 1: sprite `82` at `72,48` A `0x08E84FA8` R `0x08E84FB4`
- obj 2: sprite `26` at `18,37` A `0x08E84F84` R `0x08E84F84`
- obj 3: sprite `26` at `14,43` A `0x08E84F84` R `0x08E84F84`
- obj 4: sprite `26` at `14,31` A `0x08E84F84` R `0x08E84F84`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E84FA8`
  - dialogue: "The Egypt Exhibition is overflowing with Neo Ghouls!"
  - fallthrough
- obj 1 R: `0x08E84FB4`
  - dialogue: "I don't want the Neo Ghouls to find out that I'm a duelist!"
  - fallthrough
- obj 2 A: `0x08E84F84`
  - portrait p49 expr0 pos8
  - dialogue: "You're not taking another step!"
  - duel
  - fallthrough

## map_20_state_04

- map/state: `20/4`
- music: `231`

### Initial Sprites
- obj 1: sprite `82` at `72,48` A `0x08E84FA8` R `0x08E84FB4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E84FA8`
  - dialogue: "The Egypt Exhibition is overflowing with Neo Ghouls!"
  - fallthrough
- obj 1 R: `0x08E84FB4`
  - dialogue: "I don't want the Neo Ghouls to find out that I'm a duelist!"
  - fallthrough

## map_20_state_05

- map/state: `20/5`
- music: `231`

### Initial Sprites
- obj 1: sprite `82` at `72,48` A `0x08E84FC0` R `0x08E84FCC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E84FC0`
  - dialogue: "Heart of the cards, guide me! ...No matter how hard I try, I can't draw the card I want... Huh? You "
  - fallthrough
- obj 1 R: `0x08E84FCC`
  - check_flag
  - fallthrough

## map_21_state_00

- map/state: `21/0`
- music: `230`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_21_state_01

- map/state: `21/1`
- music: `230`

### Initial Sprites
- obj 1: sprite `83` at `40,56` A `0x08E86330` R `0x08E86354`
- obj 2: sprite `83` at `24,56` A `0x08E86378` R `0x08E8639C`
- obj 3: sprite `29` at `40,72` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E86324`
  - play_music
  - play_music
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p19 expr0 pos8
  - dialogue: "Tsk! The runt chased after me!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - walk_object_y
  - delay
  - play_music
  - slide_object
  - delay
  - walk_object_y
  - walk_object_x
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E86330`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E86354`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E86378`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E8639C`
  - dialogue: "No, I don't duel. You should find someone else."
  - fallthrough

## map_21_state_02

- map/state: `21/2`
- music: `230`

### Initial Sprites
- obj 1: sprite `83` at `58,64` A `0x08E86330` R `0x08E86354`
- obj 2: sprite `83` at `24,56` A `0x08E86378` R `0x08E8639C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E86330`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E86354`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E86378`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E8639C`
  - dialogue: "No, I don't duel. You should find someone else."
  - fallthrough

## map_21_state_03

- map/state: `21/3`
- music: `230`

### Initial Sprites
- obj 1: sprite `83` at `56,63` A `0x08E86330` R `0x08E86354`
- obj 2: sprite `83` at `24,56` A `0x08E86378` R `0x08E8639C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E86330`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E86354`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E86378`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E8639C`
  - dialogue: "No, I don't duel. You should find someone else."
  - fallthrough

## map_21_state_04

- map/state: `21/4`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `32,22` A `0x08E863FC` R `0x08E863FC`
- obj 2: sprite `26` at `32,31` A `0x08E863FC` R `0x08E863FC`
- obj 3: sprite `26` at `32,40` A `0x08E863FC` R `0x08E863FC`
- obj 4: sprite `26` at `22,48` A `0x08E863FC` R `0x08E863FC`
- obj 5: sprite `26` at `40,50` A `0x08E863A8` R `0x08E863A8`
- obj 6: sprite `83` at `94,58` A `0x08E863CC` R `0x08E863D8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E863FC`
  - portrait p49 expr0 pos8
  - dialogue: "You will proceed no further!"
  - fallthrough
- obj 5 A: `0x08E863A8`
  - portrait p49 expr0 pos8
  - dialogue: "You will proceed no further!"
  - duel
  - fallthrough
- obj 6 A: `0x08E863CC`
  - dialogue: "This is total chaos! Please do something about the Neo Ghouls!"
  - fallthrough
- obj 6 R: `0x08E863D8`
  - dialogue: "At a time like this? You have to be joking!"
  - fallthrough

## map_21_state_05

- map/state: `21/5`
- music: `230`

### Initial Sprites
- obj 1: sprite `26` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `26` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `26` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `26` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `83` at `94,58` A `0x08E863CC` R `0x08E863D8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 5 A: `0x08E863CC`
  - dialogue: "This is total chaos! Please do something about the Neo Ghouls!"
  - fallthrough
- obj 5 R: `0x08E863D8`
  - dialogue: "At a time like this? You have to be joking!"
  - fallthrough

## map_21_state_06

- map/state: `21/6`
- music: `230`

### Initial Sprites
- obj 1: sprite `83` at `56,63` A `0x08E863E4` R `0x08E863F0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E863E4`
  - dialogue: "It was chaotic before, but things have quieted down. The Egypt Exhibition is open for admission."
  - fallthrough
- obj 1 R: `0x08E863F0`
  - dialogue: "I'm sorry, but I'm not a duelist. May I suggest you find someone else to duel?"
  - fallthrough

## map_21_state_07

- map/state: `21/7`
- music: `11`

### Initial Sprites
- obj 1: sprite `26` at `128,96` A `0x08E863FC` R `0x08E863FC`
- obj 2: sprite `26` at `128,96` A `0x08E863FC` R `0x08E863FC`
- obj 3: sprite `26` at `128,96` A `0x08E863FC` R `0x08E863FC`
- obj 4: sprite `26` at `22,48` A `0x08E863FC` R `0x08E863FC`
- obj 5: sprite `26` at `40,50` A `0x08E863A8` R `0x08E863A8`
- obj 6: sprite `83` at `94,58` A `0x08E863CC` R `0x08E863D8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E863FC`
  - portrait p49 expr0 pos8
  - dialogue: "You will proceed no further!"
  - fallthrough
- obj 5 A: `0x08E863A8`
  - portrait p49 expr0 pos8
  - dialogue: "You will proceed no further!"
  - duel
  - fallthrough
- obj 6 A: `0x08E863CC`
  - dialogue: "This is total chaos! Please do something about the Neo Ghouls!"
  - fallthrough
- obj 6 R: `0x08E863D8`
  - dialogue: "At a time like this? You have to be joking!"
  - fallthrough

## map_22_state_00

- map/state: `22/0`
- music: `230`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_22_state_01

- map/state: `22/1`
- music: `230`

### Initial Sprites
- obj 1: sprite `58` at `52,40` A `0x08E8CAB0` R `0x08E8CABC`
- obj 2: sprite `42` at `96,18` A `0x08E8CAEC` R `0x08E8CB10`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E8CAB0`
  - dialogue: "Here sleeps the power of ancient pharaohs. I know that ancient power will make me stronger! I will b"
  - fallthrough
- obj 1 R: `0x08E8CABC`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E8CAEC`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E8CB10`
  - dialogue: "No, I don't duel. You should find someone else."
  - fallthrough

## map_22_state_02

- map/state: `22/2`
- music: `230`

### Initial Sprites
- obj 1: sprite `58` at `52,40` A `0x08E8CAB0` R `0x08E8CABC`
- obj 2: sprite `42` at `80,18` A `0x08E8CAEC` R `0x08E8CB10`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E8CAB0`
  - dialogue: "Here sleeps the power of ancient pharaohs. I know that ancient power will make me stronger! I will b"
  - fallthrough
- obj 1 R: `0x08E8CABC`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E8CAEC`
  - check_flag
  - fallthrough
- obj 2 R: `0x08E8CB10`
  - dialogue: "No, I don't duel. You should find someone else."
  - fallthrough

## map_22_state_03

- map/state: `22/3`
- music: `230`

### Initial Sprites
- obj 1: sprite `84` at `76,61` A `0x08E8CB1C` R `0x08E8CB28`
- obj 2: sprite `3` at `48,26` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `55` at `44,33` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E8CB34`
  - play_music
  - delay
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 8, 'wander': 0}
  - delay
  - portrait p3 expr0 pos8
  - dialogue: "Humph. So the merry band of losers finally have a clue about what's really going on."
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 8, 'wander': 0}
  - delay
  - portrait p10 expr0 pos8
  - dialogue: "Ishizu visited my big brother. She wanted him to get the Egyptian God Cards back."
  - portrait p3 expr0 pos8
  - dialogue: "Mokuba, keep quiet. The title as champion And the strongest cards... Only the most powerful duelist "
  - portrait p10 expr0 pos8
  - dialogue: "I bet you guys are happy that my big bro's gonna help you out, huh?"
  - portrait p3 expr2 pos8
  - dialogue: "Mokuba!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p10 expr6 pos8
  - dialogue: "W-what is it, Seto?"
  - portrait p3 expr0 pos8
  - dialogue: "I have no intention of teaming up with these clowns!"
  - portrait p10 expr3 pos8
  - dialogue: "Big brother..."
  - portrait p3 expr2 pos8
  - dialogue: "Listen up, you fools! A real duelist doesn't need help from a bunch of cheerleaders! All you should "
  - portrait p3 expr1 pos8
  - dialogue: "Wahahahahaha!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 72, 'wander': 0}
  - delay
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 68, 'wander': 0}
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 1}
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E8CB1C`
  - dialogue: "This is the Egypt Exhibition."
  - fallthrough
- obj 1 R: `0x08E8CB28`
  - dialogue: "No way, I'm not a duelist. I came here for the exhibition."
  - fallthrough

## map_22_state_04

- map/state: `22/4`
- music: `230`

### Initial Sprites
- obj 1: sprite `84` at `76,61` A `0x08E8CB1C` R `0x08E8CB28`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E8CB1C`
  - dialogue: "This is the Egypt Exhibition."
  - fallthrough
- obj 1 R: `0x08E8CB28`
  - dialogue: "No way, I'm not a duelist. I came here for the exhibition."
  - fallthrough

## map_22_state_05

- map/state: `22/5`
- music: `11`

### Initial Sprites
- obj 1: sprite `3` at `64,20` A `0x08E8CB58` R `0x08E8CB64`
- obj 2: sprite `26` at `64,40` A `0x08E8CB94` R `0x08E8CB94`
- obj 3: sprite `26` at `52,40` A `0x08E8CB94` R `0x08E8CB94`
- obj 4: sprite `26` at `76,24` A `0x08E8CB94` R `0x08E8CB94`
- obj 5: sprite `26` at `88,32` A `0x08E8CB94` R `0x08E8CB94`
- obj 6: sprite `26` at `76,40` A `0x08E8CB94` R `0x08E8CB94`
- obj 7: sprite `26` at `84,44` A `0x08E8CB94` R `0x08E8CB94`
- obj 8: sprite `26` at `84,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 9: sprite `26` at `44,44` A `0x08E8CB94` R `0x08E8CB94`
- obj 10: sprite `26` at `44,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 11: sprite `84` at `19,58` A `0x08E8CBA0` R `0x08E8CBAC`

### Scripts
- enter 0: `0x08E8CB40`
  - check_flag
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E8CB58`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E8CB64`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E8CB94`
  - portrait p49 expr0 pos8
  - dialogue: "If I take down Kaiba, I'll be promoted! Hihihi..."
  - fallthrough
- obj 11 A: `0x08E8CBA0`
  - dialogue: "I was enjoying the Egypt Exhibition... Until all chaos broke out."
  - fallthrough
- obj 11 R: `0x08E8CBAC`
  - dialogue: "I'm not a duelist. That's why they left me alone."
  - fallthrough

## map_22_state_06

- map/state: `22/6`
- music: `11`

### Initial Sprites
- obj 1: sprite `3` at `64,20` A `0x08E8CB58` R `0x08E8CB64`
- obj 2: sprite `26` at `64,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 3: sprite `26` at `64,40` A `0x08E8CB94` R `0x08E8CB94`
- obj 4: sprite `26` at `76,24` A `0x08E8CB94` R `0x08E8CB94`
- obj 5: sprite `26` at `88,32` A `0x08E8CB94` R `0x08E8CB94`
- obj 6: sprite `26` at `76,40` A `0x08E8CB94` R `0x08E8CB94`
- obj 7: sprite `26` at `84,44` A `0x08E8CB94` R `0x08E8CB94`
- obj 8: sprite `26` at `84,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 9: sprite `26` at `44,44` A `0x08E8CB94` R `0x08E8CB94`
- obj 10: sprite `26` at `44,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 11: sprite `84` at `19,58` A `0x08E8CBA0` R `0x08E8CBAC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E8CB58`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E8CB64`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E8CB94`
  - portrait p49 expr0 pos8
  - dialogue: "If I take down Kaiba, I'll be promoted! Hihihi..."
  - fallthrough
- obj 11 A: `0x08E8CBA0`
  - dialogue: "I was enjoying the Egypt Exhibition... Until all chaos broke out."
  - fallthrough
- obj 11 R: `0x08E8CBAC`
  - dialogue: "I'm not a duelist. That's why they left me alone."
  - fallthrough

## map_22_state_07

- map/state: `22/7`
- music: `11`

### Initial Sprites
- obj 1: sprite `3` at `64,24` A `0x08E8CB58` R `0x08E8CB64`
- obj 2: sprite `26` at `64,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 3: sprite `26` at `64,36` A `0x08E8CB94` R `0x08E8CB94`
- obj 4: sprite `26` at `76,24` A `0x08E8CB94` R `0x08E8CB94`
- obj 5: sprite `26` at `88,32` A `0x08E8CB94` R `0x08E8CB94`
- obj 6: sprite `26` at `76,40` A `0x08E8CB94` R `0x08E8CB94`
- obj 7: sprite `26` at `84,44` A `0x08E8CB94` R `0x08E8CB94`
- obj 8: sprite `26` at `84,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 9: sprite `26` at `44,44` A `0x08E8CB94` R `0x08E8CB94`
- obj 10: sprite `26` at `44,64` A `0x08E8CB94` R `0x08E8CB94`
- obj 11: sprite `84` at `19,58` A `0x08E8CBA0` R `0x08E8CBAC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E8CB58`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E8CB64`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E8CB94`
  - portrait p49 expr0 pos8
  - dialogue: "If I take down Kaiba, I'll be promoted! Hihihi..."
  - fallthrough
- obj 11 A: `0x08E8CBA0`
  - dialogue: "I was enjoying the Egypt Exhibition... Until all chaos broke out."
  - fallthrough
- obj 11 R: `0x08E8CBAC`
  - dialogue: "I'm not a duelist. That's why they left me alone."
  - fallthrough

## map_22_state_08

- map/state: `22/8`
- music: `402`

### Initial Sprites
- obj 1: sprite `3` at `64,24` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `55` at `65520,24` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `23` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `123` at `65520,24` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `6` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `30` at `65520,24` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E8CBB8`
  - play_music
  - delay
  - walk_object_x
  - delay
  - portrait p10 expr0 pos0
  - dialogue: "Big brother! Most of the Neo Ghouls have left the Town of Domino."
  - portrait p3 expr0 pos1
  - dialogue: "Good."
  - portrait p10 expr0 pos0
  - dialogue: "I protected KaibaCorp, just like you told me. So you don't have to worry about a thing."
  - portrait p3 expr0 pos1
  - dialogue: "Good work, Mokuba."
  - portrait p10 expr0 pos0
  - dialogue: "Heheh, thanks. You know I'll do anything for you. So, anything new with your Egyptian God Card?"
  - portrait p3 expr0 pos1
  - dialogue: "Somehow, it's back to normal."
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p3 expr0 pos0
  - dialogue: "I don't know what they did, but..."
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 2: `0x08F04034`
  - fallthrough

## map_22_state_09

- map/state: `22/9`
- music: `230`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_23_state_00

- map/state: `23/0`
- music: `233`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_23_state_01

- map/state: `23/1`
- music: `233`

### Initial Sprites
- obj 1: sprite `30` at `52,26` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `29` at `64,26` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `115` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E95294`
  - play_music
  - delay
  - portrait p19 expr4 pos8
  - dialogue: "Giyaaaaah!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 1}
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - move_object: {'object_id': 13, 'direction': 2, 'distance': 0, 'wander': 0}
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_y
  - delay
  - portrait p46 expr0 pos8
  - dialogue: "You've come for the Millennium Necklace?"
  - portrait p0 expr0 pos8
  - dialogue: "{CARD_1}Yes No{CARD_2}"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_23_state_02

- map/state: `23/2`
- music: `233`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_23_state_03

- map/state: `23/3`
- music: `233`

### Initial Sprites
- obj 1: sprite `63` at `62,22` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `6` at `50,22` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `2` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `115` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `116` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `117` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `118` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `119` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `120` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `121` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E95318`
  - play_music
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24577}
  - walk_object_x
  - walk_object_y
  - walk_object_y
  - walk_object_x
  - move_object: {'object_id': 13, 'direction': 2, 'distance': 0, 'wander': 0}
  - walk_object_y
  - walk_object_x
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_y
  - delay
  - portrait p20 expr0 pos8
  - dialogue: "Kukuku... What took you so long? You've kept us waiting. But that gave me time to talk to this woman"
  - portrait p16 expr0 pos8
  - dialogue: "Then you should understand what I'm asking. We need your help to defeat the Dark Being..."
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p20 expr0 pos8
  - dialogue: "Idiot! All I care about is defeating Pegasus! I don't give half a brain about the Dark Being or anyo"
  - hide_portrait
  - delay
  - walk_object_y
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p20 expr0 pos8
  - dialogue: "C'mon, I'm done talking! Hand over the Millennium Items."
  - portrait p0 expr0 pos0
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_23_state_04

- map/state: `23/4`
- music: `233`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_23_state_05

- map/state: `23/5`
- music: `233`

### Initial Sprites
- obj 1: sprite `63` at `62,40` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `6` at `54,30` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `2` at `62,50` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `113` at `54,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `4` at `46,50` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E95480`
  - play_music
  - delay
  - portrait p2 expr1 pos8
  - dialogue: "I know exactly how hard {PLAYER} has worked to get this far."
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p2 expr1 pos8
  - dialogue: "{PLAYER} is worthy of having the Egyptian God Cards."
  - hide_portrait
  - delay
  - fade_screen
  - clear_flag
  - warp: {'map_id': 48, 'state': 3, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_23_state_06

- map/state: `23/6`
- music: `233`

### Initial Sprites
- obj 1: sprite `63` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `6` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `2` at `62,48` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `1` at `62,56` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `3` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E9548C`
  - play_music
  - delay
  - portrait p2 expr1 pos1
  - dialogue: "Never forget that no matter what, we're always together."
  - portrait p1 expr1 pos0
  - dialogue: "Right!"
  - hide_portrait
  - delay
  - fade_screen
  - clear_flag
  - clear_flag
  - warp: {'map_id': 48, 'state': 4, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_23_state_07

- map/state: `23/7`
- music: `233`

### Initial Sprites
- obj 1: sprite `63` at `62,96` A `0x08E95474` R `0x08E95474`
- obj 2: sprite `6` at `60,96` A `0x08E95468` R `0x08E95468`
- obj 3: sprite `2` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E953A8`
  - show_object: {'object_id': 13, 'x': 68, 'y': 58, 'frame': 0, 'mode': 0}
  - play_music
  - show_object: {'object_id': 3, 'x': 68, 'y': 50, 'frame': 0, 'mode': 1}
  - delay
  - play_music
  - portrait p2 expr1 pos1
  - dialogue: "It's been a long time, partner."
  - portrait p1 expr1 pos0
  - dialogue: "My other self... I... I thought I'd never see you again."
  - portrait p2 expr1 pos1
  - dialogue: "Never forget that no matter what, we're always together."
  - portrait p1 expr1 pos0
  - dialogue: "Right!"
  - portrait p2 expr1 pos1
  - dialogue: "Okay, partner! Let's get the Egyptian God Card back!"
  - hide_portrait
  - delay
  - play_music
  - walk_object_y
  - show_object: {'object_id': 3, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - fade_screen
  - clear_flag
  - warp: {'map_id': 23, 'state': 9, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E95474`
  - dialogue: "..."
  - fallthrough
- obj 2 A: `0x08E95468`
  - portrait p16 expr0 pos8
  - dialogue: "I'm sorry about this... Let's exit."
  - fallthrough

## map_23_state_08

- map/state: `23/8`
- music: `233`

### Initial Sprites
- obj 1: sprite `30` at `52,28` A `0x08E952F4` R `0x08E95300`
- obj 2: sprite `29` at `64,26` A `0x08E9530C` R `0x08E9530C`

### Scripts
- enter 0: `0x08E952C4`
  - play_music
  - portrait p1 expr6 pos8
  - dialogue: "That image I just saw..."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 1}
  - delay
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8192}
  - delay
  - portrait p1 expr6 pos8
  - dialogue: "{PLAYER}, you saw it too, didn't you?"
  - portrait p0 expr0 pos0
  - dialogue: "{CARD_1}Yes No{CARD_2}"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E952F4`
  - portrait p46 expr0 pos8
  - dialogue: "We have secretly guarded over the Millennium Items. Millennium Items are believed to attract each ot"
  - fallthrough
- obj 1 R: `0x08E95300`
  - portrait p46 expr0 pos8
  - dialogue: "You are only allowed to duel me once. Did you not have to leave immediately?"
  - fallthrough
- obj 2 A: `0x08E9530C`
  - dialogue: "..."
  - fallthrough

## map_23_state_09

- map/state: `23/9`
- music: `233`

### Initial Sprites
- obj 1: sprite `63` at `62,40` A `0x08E95474` R `0x08E95474`
- obj 2: sprite `6` at `50,22` A `0x08E95468` R `0x08E95468`
- obj 3: sprite `2` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `23` at `20,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `113` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `117` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `134` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `136` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `135` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `135` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E953B4`
  - delay
  - move_object: {'object_id': 13, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - swap_object_sprite: {'object_id': 13, 'sprite_id': 2}
  - delay
  - walk_object_y
  - delay
  - portrait p2 expr2 pos8
  - dialogue: "You'll pay for how you treated my partner, Bandit Keith!"
  - portrait p20 expr0 pos8
  - dialogue: "Huh? What are you talking about? Just fork over your Egyptian God Card!"
  - portrait p0 expr0 pos0
  - dialogue: "{CARD_1}No! There's no other choice...{CARD_2}"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E95474`
  - dialogue: "..."
  - fallthrough
- obj 2 A: `0x08E95468`
  - portrait p16 expr0 pos8
  - dialogue: "I'm sorry about this... Let's exit."
  - fallthrough

## map_23_state_10

- map/state: `23/10`
- music: `233`

### Initial Sprites
- obj 1: sprite `63` at `62,40` A `0x08E95474` R `0x08E95474`
- obj 2: sprite `6` at `50,22` A `0x08E95468` R `0x08E95468`
- obj 3: sprite `2` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `23` at `20,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `113` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `117` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `134` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `136` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `135` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `135` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `0` at `192,192` A `0x08F04034` R `0x08F04034`
- obj 13: sprite `2` at `68,50` A `0x08F04034` R `0x08F04034`
- obj 14: sprite `4` at `56,58` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E95498`
  - play_music
  - delay
  - play_music
  - command_7c_8
  - portrait p20 expr6 pos8
  - dialogue: "Wh-what's this?!"
  - portrait p2 expr2 pos8
  - dialogue: "It's Ra's judgment... Actually, it's more than that. Feel the wrath for angering the Egyptian Gods!"
  - play_music
  - command_7c_8
  - command_7c_8
  - play_music
  - command_7c_8
  - play_music
  - portrait p20 expr4 pos8
  - dialogue: "Gwaaah!"
  - hide_portrait
  - delay
  - play_music
  - show_object: {'object_id': 5, 'x': 58, 'y': 38, 'frame': 0, 'mode': 0}
  - delay
  - play_music
  - object_effect
  - delay
  - command_7c_2
  - fade_screen
  - clear_flag
  - warp: {'map_id': 60, 'state': 4, 'connection': 0}
  - fallthrough
- enter 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E95474`
  - dialogue: "..."
  - fallthrough
- obj 2 A: `0x08E95468`
  - portrait p16 expr0 pos8
  - dialogue: "I'm sorry about this... Let's exit."
  - fallthrough

## map_24_state_00

- map/state: `24/0`
- music: `239`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_24_state_01

- map/state: `24/1`
- music: `239`

### Initial Sprites
- obj 1: sprite `42` at `44,32` A `0x08E981BC` R `0x08E981C8`
- obj 2: sprite `48` at `52,32` A `0x08E9815C` R `0x08E98168`

### Scripts
- enter 0: `0x08E98144`
  - play_music
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Takeshi, is it really okay to be onboard this luxury liner? It looks, like, really expensive."
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Don't you worry about a thing, babe. All I have to do is win some duels. Piece of cake! Really? Take"
  - delay
  - dialogue: "."
  - delay
  - dialogue: "."
  - delay
  - dialogue: "Okay, I admit it! I am smart! My cranium's bursting with brains!"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E981BC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E981C8`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E9815C`
  - dialogue: "Don't bug us! Go away, creep!"
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08E98168`
  - dialogue: "What's your problem? You are, like, so uncool!"
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough

## map_24_state_02

- map/state: `24/2`
- music: `239`

### Initial Sprites
- obj 1: sprite `42` at `44,32` A `0x08E981BC` R `0x08E981C8`
- obj 2: sprite `48` at `52,32` A `0x08E9815C` R `0x08E98168`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E981BC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E981C8`
  - check_flag
  - fallthrough
- obj 2 A: `0x08E9815C`
  - dialogue: "Don't bug us! Go away, creep!"
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08E98168`
  - dialogue: "What's your problem? You are, like, so uncool!"
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough

## map_24_state_03

- map/state: `24/3`
- music: `239`

### Initial Sprites
- obj 1: sprite `42` at `44,32` A `0x08E981E0` R `0x08E98204`
- obj 2: sprite `48` at `52,32` A `0x08E98210` R `0x08E98210`
- obj 3: sprite `26` at `44,46` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `113` at `44,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08E981D4`
  - play_music
  - delay
  - dialogue: "I'm sorry, I'm sorry. Here are my rare cards."
  - hide_portrait
  - delay
  - play_music
  - show_object: {'object_id': 4, 'x': 44, 'y': 36, 'frame': 0, 'mode': 0}
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 8}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "Humph, these cards are garbage."
  - hide_portrait
  - delay
  - play_music
  - show_object: {'object_id': 4, 'x': 44, 'y': 96, 'frame': 0, 'mode': 0}
  - delay
  - dialogue: "Oh... Uh, then how about this one?"
  - hide_portrait
  - delay
  - play_music
  - show_object: {'object_id': 4, 'x': 44, 'y': 36, 'frame': 0, 'mode': 0}
  - delay
  - play_music
  - show_object: {'object_id': 4, 'x': 44, 'y': 96, 'frame': 0, 'mode': 0}
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "That better be all of them."
  - portrait p0 expr0 pos0
  - dialogue: "That's all I have, I swear."
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Takeshi... Are you, like, sure about this?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Y-yeah, I'm positive."
  - portrait p49 expr0 pos8
  - dialogue: "What? You have a problem?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "No no no no no no no no no. I don't want any trouble."
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E981E0`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E98204`
  - dialogue: "How am I supposed to duel when they took my cards? Duh!"
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 A: `0x08E98210`
  - dialogue: "Like, what's your problem! Why can't you be, like, brave, like my man Takeshi?"
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough

## map_24_state_04

- map/state: `24/4`
- music: `239`

### Initial Sprites
- obj 1: sprite `42` at `44,32` A `0x08E981E0` R `0x08E98204`
- obj 2: sprite `48` at `52,32` A `0x08E98210` R `0x08E98210`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E981E0`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E98204`
  - dialogue: "How am I supposed to duel when they took my cards? Duh!"
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 A: `0x08E98210`
  - dialogue: "Like, what's your problem! Why can't you be, like, brave, like my man Takeshi?"
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough

## map_24_state_05

- map/state: `24/5`
- music: `239`

### Initial Sprites
- obj 1: sprite `42` at `44,32` A `0x08E9821C` R `0x08E98228`
- obj 2: sprite `48` at `52,32` A `0x08E98234` R `0x08E98240`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08E9821C`
  - dialogue: "It's so awesome that the Neo Ghouls are gone."
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 1 R: `0x08E98228`
  - dialogue: "Get lost! Stop making fun of me! How am I supposed to duel without any cards? The Neo Ghouls stole e"
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 A: `0x08E98234`
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - dialogue: "Takeshi, like, I don't care if you can't duel. I love you!"
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08E98240`
  - dialogue: "What are you, like some kind of dueling fanatic? You're, like, totally bugging me! Go away."
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - fallthrough

## map_25_state_00

- map/state: `25/0`
- music: `15`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_25_state_01

- map/state: `25/1`
- music: `15`

### Initial Sprites
- obj 1: sprite `50` at `50,17` A `0x08E99588` R `0x08E99594`
- obj 2: sprite `85` at `64,68` A `0x08E995A0` R `0x08E995AC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E99588`
  - dialogue: "Welcome! I hope you enjoy yourselves!"
  - fallthrough
- obj 1 R: `0x08E99594`
  - dialogue: "We have a duel specialist on board. The specialist is on the floor in the next section. Please chall"
  - fallthrough
- obj 2 A: `0x08E995A0`
  - dialogue: "That dealer... I think he's cheating."
  - fallthrough
- obj 2 R: `0x08E995AC`
  - dialogue: "A duel? What's that? Can I win money? There's no money involved? Then what's the point? How can you "
  - fallthrough

## map_25_state_02

- map/state: `25/2`
- music: `15`

### Initial Sprites
- obj 1: sprite `50` at `50,17` A `0x08E995B8` R `0x08E995DC`
- obj 2: sprite `85` at `64,68` A `0x08E995E8` R `0x08E995F4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E995B8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08E995DC`
  - dialogue: "Hahaha, sorry, but I am not a duelist."
  - fallthrough
- obj 2 A: `0x08E995E8`
  - dialogue: "That dealer over there... All he did was hide from the Neo Ghouls."
  - fallthrough
- obj 2 R: `0x08E995F4`
  - dialogue: "No, I'll pass."
  - fallthrough

## map_25_state_03

- map/state: `25/3`
- music: `15`

### Initial Sprites
- obj 1: sprite `50` at `50,17` A `0x08E99600` R `0x08E99600`
- obj 2: sprite `85` at `64,68` A `0x08E9960C` R `0x08E99618`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08E99600`
  - dialogue: "I bet you're duelists. No, I'm not psychic. It's obvious because you're wearing Duel Disks. Unfortun"
  - fallthrough
- obj 2 A: `0x08E9960C`
  - dialogue: "I hear that dealer dislikes duelists."
  - fallthrough
- obj 2 R: `0x08E99618`
  - dialogue: "No thanks. I don't duel."
  - fallthrough

## map_26_state_00

- map/state: `26/0`
- music: `15`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_26_state_01

- map/state: `26/1`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `96,24` A `0x08EA3BA8` R `0x08EA3BB4`
- obj 2: sprite `66` at `80,24` A `0x08EA3C14` R `0x08EA3C20`
- obj 3: sprite `86` at `112,52` A `0x08EA3C98` R `0x08EA3CA4`
- obj 4: sprite `87` at `112,61` A `0x08EA3CB0` R `0x08EA3CBC`

### Scripts
- enter 0: `0x08EA3B90`
  - play_music
  - delay
  - portrait p29 expr0 pos0
  - dialogue: "Mai, my darling! Please marry me! Be mine, Mai Valentine!"
  - portrait p6 expr2 pos0
  - dialogue: "Stop following me! I already told you, I'll only marry if you beat me in a duel."
  - portrait p29 expr0 pos0
  - dialogue: "Okay! Then today's the day you'll be marching with me to the chapel!"
  - fade_screen
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3BA8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EA3BB4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EA3C14`
  - portrait p29 expr0 pos8
  - dialogue: "I already hear wedding bells!!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08EA3C20`
  - portrait p29 expr0 pos8
  - dialogue: "I don't think so! This is not the time! Can't you see that I'm trying to propose?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 A: `0x08EA3C98`
  - dialogue: "This ship's lady duelist is beautiful, no?"
  - fallthrough
- obj 3 R: `0x08EA3CA4`
  - dialogue: "Sorry, chap. I prefer to watch."
  - fallthrough
- obj 4 A: `0x08EA3CB0`
  - dialogue: "My husband has a thing for female duelists."
  - fallthrough
- obj 4 R: `0x08EA3CBC`
  - check_flag
  - fallthrough

## map_26_state_02

- map/state: `26/2`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `8,74` A `0x08EA3B84` R `0x08EA3B84`
- obj 2: sprite `49` at `24,52` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `54` at `98,70` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EA3B78`
  - play_music
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - portrait p6 expr2 pos0
  - dialogue: "C'mon, boys! Work harder, you two! At this rate, you'll never become real duelists. It'll take you a"
  - portrait p9 expr5 pos0
  - dialogue: "Wh-why are we working for Mai?"
  - portrait p31 expr5 pos0
  - dialogue: "What'd we do to deserve this?"
  - portrait p0 expr0 pos0
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - portrait p6 expr0 pos0
  - dialogue: "Oh, hi Joey! Do you want me to train you too?"
  - portrait p4 expr5 pos0
  - dialogue: "Why would I need training?"
  - portrait p6 expr0 pos0
  - dialogue: "Ahahaha, I'm only joking. Minion One and Minion Two, stop slacking off!"
  - portrait p9 expr5 pos0
  - dialogue: "M-Minion One?"
  - portrait p31 expr5 pos0
  - dialogue: "Two?!"
  - portrait p0 expr0 pos0
  - dialogue: "This sucks..."
  - portrait p6 expr7 pos0
  - dialogue: "Wipe those frowns off your faces. If you really want to improve your dueling skills, you should hit "
  - portrait p31 expr0 pos0
  - dialogue: "A training quest?"
  - portrait p9 expr1 pos0
  - dialogue: "I'm going! I am soooo going! Anything beats getting worked like a mule. I would rather be anywhere e"
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - portrait p31 expr0 pos0
  - dialogue: "S-sure. Wait for me, Tristan."
  - walk_object_x
  - walk_object_y
  - portrait p6 expr7 pos0
  - dialogue: "Those two... I was only kidding. I mean, what's a training quest anyway? Sigh... Now that my minions"
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3B84`
  - portrait p6 expr0 pos0
  - dialogue: "Tristan and Duke left on a training quest. But what are they training for?"
  - fallthrough

## map_26_state_03

- map/state: `26/3`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `96,24` A `0x08EA3BA8` R `0x08EA3BB4`
- obj 2: sprite `66` at `80,24` A `0x08EA3C14` R `0x08EA3C20`
- obj 3: sprite `86` at `112,52` A `0x08EA3C98` R `0x08EA3CA4`
- obj 4: sprite `87` at `112,61` A `0x08EA3CB0` R `0x08EA3CBC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3BA8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EA3BB4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EA3C14`
  - portrait p29 expr0 pos8
  - dialogue: "I already hear wedding bells!!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08EA3C20`
  - portrait p29 expr0 pos8
  - dialogue: "I don't think so! This is not the time! Can't you see that I'm trying to propose?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 A: `0x08EA3C98`
  - dialogue: "This ship's lady duelist is beautiful, no?"
  - fallthrough
- obj 3 R: `0x08EA3CA4`
  - dialogue: "Sorry, chap. I prefer to watch."
  - fallthrough
- obj 4 A: `0x08EA3CB0`
  - dialogue: "My husband has a thing for female duelists."
  - fallthrough
- obj 4 R: `0x08EA3CBC`
  - check_flag
  - fallthrough

## map_26_state_04

- map/state: `26/4`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `96,24` A `0x08EA3BA8` R `0x08EA3BB4`
- obj 2: sprite `66` at `80,24` A `0x08EA3C14` R `0x08EA3C20`
- obj 3: sprite `86` at `80,72` A `0x08EA3C98` R `0x08EA3CA4`
- obj 4: sprite `87` at `96,64` A `0x08EA3CB0` R `0x08EA3CBC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3BA8`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EA3BB4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EA3C14`
  - portrait p29 expr0 pos8
  - dialogue: "I already hear wedding bells!!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08EA3C20`
  - portrait p29 expr0 pos8
  - dialogue: "I don't think so! This is not the time! Can't you see that I'm trying to propose?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 A: `0x08EA3C98`
  - dialogue: "This ship's lady duelist is beautiful, no?"
  - fallthrough
- obj 3 R: `0x08EA3CA4`
  - dialogue: "Sorry, chap. I prefer to watch."
  - fallthrough
- obj 4 A: `0x08EA3CB0`
  - dialogue: "My husband has a thing for female duelists."
  - fallthrough
- obj 4 R: `0x08EA3CBC`
  - check_flag
  - fallthrough

## map_26_state_05

- map/state: `26/5`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `96,24` A `0x08EA3C74` R `0x08EA3C44`
- obj 2: sprite `66` at `80,24` A `0x08EA3C80` R `0x08EA3C8C`
- obj 3: sprite `86` at `80,72` A `0x08EA3C98` R `0x08EA3CA4`
- obj 4: sprite `87` at `96,64` A `0x08EA3CB0` R `0x08EA3CBC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3C74`
  - portrait p6 expr0 pos8
  - dialogue: "It seems you found what you were looking for."
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 1 R: `0x08EA3C44`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EA3C80`
  - portrait p29 expr3 pos8
  - dialogue: "I'm the Hollywood heartthrob Jean Claude Magnum, the biggest action hero in the world. But Mai Valen"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08EA3C8C`
  - portrait p29 expr0 pos8
  - dialogue: "Without Mai's hand in marriage on the line... There's no point in dueling."
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 A: `0x08EA3C98`
  - dialogue: "This ship's lady duelist is beautiful, no?"
  - fallthrough
- obj 3 R: `0x08EA3CA4`
  - dialogue: "Sorry, chap. I prefer to watch."
  - fallthrough
- obj 4 A: `0x08EA3CB0`
  - dialogue: "My husband has a thing for female duelists."
  - fallthrough
- obj 4 R: `0x08EA3CBC`
  - check_flag
  - fallthrough

## map_26_state_06

- map/state: `26/6`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `96,24` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `16` at `72,32` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `26` at `84,24` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `26` at `84,32` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `86` at `80,72` A `0x08EA3D58` R `0x08EA3D64`
- obj 6: sprite `87` at `96,64` A `0x08EA3D70` R `0x08EA3D7C`

### Scripts
- enter 0: `0x08EA3CEC`
  - play_music
  - delay
  - portrait p6 expr2 pos0
  - dialogue: "Harpie Lady!"
  - play_music
  - command_7c_8
  - delay
  - portrait p6 expr2 pos0
  - dialogue: "Harpies' Triangle Ecstasy!"
  - play_music
  - command_7c_8
  - delay
  - play_music
  - slide_object
  - play_music
  - object_effect
  - show_object: {'object_id': 3, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - delay
  - portrait p23 expr0 pos0
  - dialogue: "Hyahahahaha! Nice attack... But how much longer can you keep this up? Go!"
  - hide_portrait
  - delay
  - walk_object_y
  - move_object: {'object_id': 4, 'direction': 3, 'distance': 0, 'wander': 0}
  - set_object_position
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - delay
  - portrait p6 expr2 pos0
  - dialogue: "Grr... There's too many of them..."
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 4}
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 5 A: `0x08EA3D58`
  - dialogue: "The Neo Ghouls are frightening individuals indeed. If it weren't for Mai, my rare cards would be gon"
  - fallthrough
- obj 5 R: `0x08EA3D64`
  - dialogue: "Oh, no. No more duels for me, thank you kindly."
  - fallthrough
- obj 6 A: `0x08EA3D70`
  - dialogue: "How could we be attacked by the Neo Ghouls? Dear me, this ship's security is not up to snuff."
  - fallthrough
- obj 6 R: `0x08EA3D7C`
  - dialogue: "I'm sorry, the idea doesn't enthuse me."
  - fallthrough

## map_26_state_07

- map/state: `26/7`
- music: `15`

### Initial Sprites
- obj 1: sprite `86` at `80,72` A `0x08EA3D58` R `0x08EA3D64`
- obj 2: sprite `87` at `96,64` A `0x08EA3D70` R `0x08EA3D7C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3D58`
  - dialogue: "The Neo Ghouls are frightening individuals indeed. If it weren't for Mai, my rare cards would be gon"
  - fallthrough
- obj 1 R: `0x08EA3D64`
  - dialogue: "Oh, no. No more duels for me, thank you kindly."
  - fallthrough
- obj 2 A: `0x08EA3D70`
  - dialogue: "How could we be attacked by the Neo Ghouls? Dear me, this ship's security is not up to snuff."
  - fallthrough
- obj 2 R: `0x08EA3D7C`
  - dialogue: "I'm sorry, the idea doesn't enthuse me."
  - fallthrough

## map_26_state_08

- map/state: `26/8`
- music: `15`

### Initial Sprites
- obj 1: sprite `86` at `80,72` A `0x08EA3DE8` R `0x08EA3DF4`
- obj 2: sprite `87` at `96,64` A `0x08EA3E24` R `0x08EA3E30`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3DE8`
  - dialogue: "Roulette, poker, slot machines... There are many kinds of games I enjoy. But the best of all is Duel"
  - fallthrough
- obj 1 R: `0x08EA3DF4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EA3E24`
  - dialogue: "My husband is engrossed in dueling. It's funny, he wasn't interested at all before."
  - fallthrough
- obj 2 R: `0x08EA3E30`
  - check_flag
  - fallthrough

## map_26_state_09

- map/state: `26/9`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `96,24` A `0x08EA3D88` R `0x08EA3DAC`
- obj 2: sprite `86` at `80,72` A `0x08EA3DE8` R `0x08EA3DF4`
- obj 3: sprite `87` at `96,64` A `0x08EA3E24` R `0x08EA3E30`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3D88`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EA3DAC`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EA3DE8`
  - dialogue: "Roulette, poker, slot machines... There are many kinds of games I enjoy. But the best of all is Duel"
  - fallthrough
- obj 2 R: `0x08EA3DF4`
  - check_flag
  - fallthrough
- obj 3 A: `0x08EA3E24`
  - dialogue: "My husband is engrossed in dueling. It's funny, he wasn't interested at all before."
  - fallthrough
- obj 3 R: `0x08EA3E30`
  - check_flag
  - fallthrough

## map_26_state_10

- map/state: `26/10`
- music: `24`

### Initial Sprites
- obj 1: sprite `7` at `102,32` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `66` at `86,32` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EA3E60`
  - play_music
  - delay
  - play_music
  - object_effect
  - delay
  - portrait p29 expr0 pos0
  - dialogue: "Mai Valentine, be mine! Marry me! Please!"
  - portrait p6 expr2 pos0
  - dialogue: "Would you quit already? You're annoying me."
  - portrait p29 expr0 pos0
  - dialogue: "But if you marry me, I won't annoy you anymore."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 2}
  - delay
  - portrait p29 expr0 pos0
  - dialogue: "I'm a Hollywood star. I have my pride. I'm not leaving until you say yes."
  - portrait p6 expr7 pos0
  - dialogue: "Listen to me, Romeo. I already have someone special."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 4}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p6 expr0 pos0
  - dialogue: "So you can give up now, Jean Claude."
  - portrait p29 expr0 pos0
  - dialogue: "Wh-who is he?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - portrait p6 expr2 pos0
  - dialogue: "That's none of your business."
  - portrait p29 expr0 pos0
  - dialogue: "You're lying, aren't you? You're just trying to make me leave."
  - portrait p6 expr7 pos0
  - dialogue: "Er, um..."
  - portrait p29 expr0 pos0
  - dialogue: "See! There really isn't anyone special!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 4, 'wander': 0}
  - delay
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_26_state_11

- map/state: `26/11`
- music: `15`

### Initial Sprites
- obj 1: sprite `7` at `96,24` A `0x08EA3C74` R `0x08EA3C44`
- obj 2: sprite `66` at `128,96` A `0x08EA3C80` R `0x08EA3C8C`
- obj 3: sprite `86` at `80,72` A `0x08EA3C98` R `0x08EA3CA4`
- obj 4: sprite `87` at `96,64` A `0x08EA3CB0` R `0x08EA3CBC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EA3C74`
  - portrait p6 expr0 pos8
  - dialogue: "It seems you found what you were looking for."
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 1 R: `0x08EA3C44`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EA3C80`
  - portrait p29 expr3 pos8
  - dialogue: "I'm the Hollywood heartthrob Jean Claude Magnum, the biggest action hero in the world. But Mai Valen"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 2 R: `0x08EA3C8C`
  - portrait p29 expr0 pos8
  - dialogue: "Without Mai's hand in marriage on the line... There's no point in dueling."
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- obj 3 A: `0x08EA3C98`
  - dialogue: "This ship's lady duelist is beautiful, no?"
  - fallthrough
- obj 3 R: `0x08EA3CA4`
  - dialogue: "Sorry, chap. I prefer to watch."
  - fallthrough
- obj 4 A: `0x08EA3CB0`
  - dialogue: "My husband has a thing for female duelists."
  - fallthrough
- obj 4 R: `0x08EA3CBC`
  - check_flag
  - fallthrough

## map_27_state_00

- map/state: `27/0`
- music: `240`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_27_state_01

- map/state: `27/1`
- music: `240`

### Initial Sprites
- obj 1: sprite `30` at `96,56` A `0x08EA4F1C` R `0x08EA4F28`
- obj 2: sprite `32` at `128,56` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `118` at `128,56` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EA4F1C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EA4F28`
  - check_flag
  - fallthrough

## map_27_state_02

- map/state: `27/2`
- music: `240`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_28_state_00

- map/state: `28/0`
- music: `16`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_28_state_01

- map/state: `28/1`
- music: `16`

### Initial Sprites
- obj 1: sprite `101` at `56,62` A `0x08EA69D4` R `0x08EA69E0`
- obj 2: sprite `102` at `64,62` A `0x08EA69EC` R `0x08EA69F8`

### Scripts
- enter 0: `0x08EA69C8`
  - play_music
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Now this is rare."
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "It certainly is."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "This is a community cemetery from long ago."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "I know. It's called the Catacombs."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - dialogue: "That's right! You've done your homework."
  - hide_portrait
  - delay
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EA69D4`
  - dialogue: "This is a community cemetery from long ago."
  - fallthrough
- obj 1 R: `0x08EA69E0`
  - dialogue: "Duo? What do you mean? Do you want me to be your partner? Do you want to perform a duo and sing with"
  - fallthrough
- obj 2 A: `0x08EA69EC`
  - dialogue: "It's called the Catacombs. For some reason, this place makes me feel calm."
  - fallthrough
- obj 2 R: `0x08EA69F8`
  - dialogue: "Jewel? You'll buy one for me?"
  - fallthrough

## map_28_state_02

- map/state: `28/2`
- music: `16`

### Initial Sprites
- obj 1: sprite `101` at `56,56` A `0x08EA69A4` R `0x08EA69A4`
- obj 2: sprite `102` at `63,56` A `0x08EA69B0` R `0x08EA69B0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EA69A4`
  - dialogue: "I heard there's a good fortuneteller around these parts. Where might he be?"
  - fallthrough
- obj 2 A: `0x08EA69B0`
  - dialogue: "I'm on a date with my man. My heart is pounding like a jackhammer!"
  - fallthrough

## map_28_state_03

- map/state: `28/3`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `128,54` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `101` at `56,62` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `102` at `64,62` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EA69BC`
  - play_music
  - play_music
  - object_effect
  - delay
  - dialogue: "I want the fortuneteller to tell me if me and my snookums are made for each other!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "I'll get him to look into my past life. Isn't it exciting, sugarmuffin? It certainly is, kissylips!"
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 12}
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 2}
  - delay
  - dialogue: "L-look... There he is... I... I know. Okay! Let's have him tell our fortunes! Urgh!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Wh-what's the matter, lovebucket? My back... Ow, ow, ow..."
  - hide_portrait
  - delay
  - walk_object_x
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p15 expr0 pos1
  - dialogue: "Are you okay? The elderly should take it easy."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 12}
  - delay
  - dialogue: "I had him do a reading about my health... Oh... What a waste..."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 2}
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p15 expr0 pos1
- exit 0: `0x08F04034`
  - fallthrough

## map_28_state_04

- map/state: `28/4`
- music: `16`

### Initial Sprites
- obj 1: sprite `101` at `56,62` A `0x08EA69D4` R `0x08EA69E0`
- obj 2: sprite `102` at `64,62` A `0x08EA69EC` R `0x08EA69F8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EA69D4`
  - dialogue: "This is a community cemetery from long ago."
  - fallthrough
- obj 1 R: `0x08EA69E0`
  - dialogue: "Duo? What do you mean? Do you want me to be your partner? Do you want to perform a duo and sing with"
  - fallthrough
- obj 2 A: `0x08EA69EC`
  - dialogue: "It's called the Catacombs. For some reason, this place makes me feel calm."
  - fallthrough
- obj 2 R: `0x08EA69F8`
  - dialogue: "Jewel? You'll buy one for me?"
  - fallthrough

## map_29_state_00

- map/state: `29/0`
- music: `16`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_29_state_01

- map/state: `29/1`
- music: `16`

### Initial Sprites

### Scripts
- enter 0: `0x08EAC864`
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 16, 'wander': 0}
  - delay
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 1}
  - walk_object_x
  - check_flag
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_29_state_02

- map/state: `29/2`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `100,44` A `0x08EAC888` R `0x08EAC8C4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EAC888`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EAC8C4`
  - portrait p15 expr0 pos0
  - dialogue: "I'll duel you again when I make my deck stronger."
  - fallthrough

## map_29_state_03

- map/state: `29/3`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `80,56` A `0x08EAC8A0` R `0x08EAC8C4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EAC8A0`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EAC8C4`
  - portrait p15 expr0 pos0
  - dialogue: "I'll duel you again when I make my deck stronger."
  - fallthrough

## map_29_state_04

- map/state: `29/4`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `60,44` A `0x08EAC984` R `0x08EAC99C`
- obj 2: sprite `131` at `60,45` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EAC984`
  - portrait p15 expr0 pos8
  - dialogue: "Do you want your fortune told?"
  - portrait p0 expr0 pos8
  - dialogue: "{CARD_1}Yes No{CARD_2}"
  - fallthrough
- obj 1 R: `0x08EAC99C`
  - portrait p15 expr0 pos8
  - dialogue: "My fortunetelling tells me that I can't win. So I won't duel right now.."
  - fallthrough

## map_29_state_05

- map/state: `29/5`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `72,42` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `26` at `72,54` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EAC8D0`
  - play_music
  - portrait p49 expr0 pos1
  - dialogue: "You're defying Master Keith's orders? After he was willing to let you join him, just like old times!"
  - portrait p15 expr0 pos1
  - dialogue: "He never treated me with respect! I don't trust him!"
  - portrait p49 expr0 pos1
  - dialogue: "You fool! Pledge your allegiance to Bandit Keith! If you do, he's willing to let you use all the rar"
  - portrait p15 expr0 pos1
  - dialogue: "I'm not afraid of him anymore!"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 4}
  - delay
  - portrait p49 expr0 pos1
  - dialogue: "Tsk, the cavalry arrives! I'll take care of them first!"
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - duel
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_29_state_06

- map/state: `29/6`
- music: `16`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_29_state_07

- map/state: `29/7`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `72,42` A `0x08EAC90C` R `0x08EAC930`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EAC90C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EAC930`
  - check_flag
  - fallthrough

## map_29_state_08

- map/state: `29/8`
- music: `16`

### Initial Sprites
- obj 1: sprite `21` at `60,44` A `0x08EAC984` R `0x08EAC99C`
- obj 2: sprite `66` at `44,54` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `131` at `60,45` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EAC96C`
  - play_music
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p29 expr0 pos8
  - dialogue: "Oh! Fantastic! This is where we'll film my new movie!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - walk_object_x
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p29 expr0 pos8
  - dialogue: "Hey! You!"
  - portrait p15 expr0 pos8
  - dialogue: "Are you talking to me?"
  - portrait p29 expr0 pos8
  - dialogue: "I'm Hollywood superstar Jean Claude Magnum, but I'm sure you already knew that. I'm shooting my next"
  - portrait p15 expr0 pos8
  - dialogue: "..."
  - portrait p29 expr0 pos8
  - dialogue: "What are you doing here?"
  - portrait p15 expr0 pos8
  - dialogue: "I'm a tour guide, plus I read fortunes."
  - portrait p29 expr0 pos8
  - dialogue: "Fortunetelling! How absolutely spectacular! I want you to read the future regarding my marriage prop"
  - portrait p15 expr0 pos8
  - dialogue: "No problem."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 8, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 16, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 8, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EAC984`
  - portrait p15 expr0 pos8
  - dialogue: "Do you want your fortune told?"
  - portrait p0 expr0 pos8
  - dialogue: "{CARD_1}Yes No{CARD_2}"
  - fallthrough
- obj 1 R: `0x08EAC99C`
  - portrait p15 expr0 pos8
  - dialogue: "My fortunetelling tells me that I can't win. So I won't duel right now.."
  - fallthrough

## map_30_state_00

- map/state: `30/0`
- music: `241`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_30_state_01

- map/state: `30/1`
- music: `241`

### Initial Sprites
- obj 1: sprite `30` at `60,28` A `0x08EAD9EC` R `0x08EAD9F8`
- obj 2: sprite `22` at `60,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `120` at `60,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EAD9EC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EAD9F8`
  - check_flag
  - fallthrough

## map_30_state_02

- map/state: `30/2`
- music: `241`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_31_state_00

- map/state: `31/0`
- music: `242`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_31_state_01

- map/state: `31/1`
- music: `242`

### Initial Sprites
- obj 1: sprite `23` at `54,36` A `0x08EB4264` R `0x08EB4270`

### Scripts
- enter 0: `0x08EB4264`
  - check_flag
  - fallthrough
- enter 4: `0x08EB4258`
  - play_music
  - play_music
  - walk_object_y
  - show_object: {'object_id': 13, 'x': 78, 'y': 88, 'frame': 0, 'mode': 0}
  - walk_object_y
  - show_object: {'object_id': 14, 'x': 66, 'y': 88, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_x
  - walk_object_y
  - delay
  - dialogue: "Hiyah! This is a special dish for all, found only at the Great Wall! It's my Great Wall noodle soup!"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 R: `0x08EB4270`
  - check_flag
  - fallthrough

## map_31_state_02

- map/state: `31/2`
- music: `242`

### Initial Sprites
- obj 1: sprite `23` at `68,38` A `0x08EB4288` R `0x08EB42A0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EB4288`
  - dialogue: "I'm very busy making noodles, okay?"
  - fallthrough
- obj 1 R: `0x08EB42A0`
  - dialogue: "Hiyah! You want to duel? I'm too busy making noodles and gruel. I have no time to duel."
  - fallthrough

## map_31_state_03

- map/state: `31/3`
- music: `242`

### Initial Sprites
- obj 1: sprite `23` at `68,38` A `0x08EB4288` R `0x08EB42D0`
- obj 2: sprite `123` at `128,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `1` at `52,65528` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `4` at `92,65528` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `3` at `68,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `55` at `76,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EB42AC`
  - set_flag
  - walk_object_x
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr7 pos0
  - dialogue: "There's somethin' fishy about those guys. Really fishy. {PLAYER}, you think so too, right?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p0 expr0 pos0
  - dialogue: "{CARD_1}Yup Nope{CARD_2}"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EB4288`
  - dialogue: "I'm very busy making noodles, okay?"
  - fallthrough
- obj 1 R: `0x08EB42D0`
  - play_music
  - play_music
  - portrait p24 expr0 pos0
  - dialogue: "Grrr! How cleverly you surmise to see through our disguise!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 13, 'direction': 3, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p24 expr0 pos0
  - dialogue: "Very well! You leave us with no choice! I challenge you in Master Sol Chevalsky's place! We shall du"
  - duel
  - fallthrough

## map_31_state_04

- map/state: `31/4`
- music: `242`

### Initial Sprites
- obj 1: sprite `23` at `68,38` A `0x08EB4288` R `0x08EB42D0`
- obj 2: sprite `123` at `128,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `1` at `52,65528` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `4` at `92,65528` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `3` at `68,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `55` at `76,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EB4288`
  - dialogue: "I'm very busy making noodles, okay?"
  - fallthrough
- obj 1 R: `0x08EB42D0`
  - play_music
  - play_music
  - portrait p24 expr0 pos0
  - dialogue: "Grrr! How cleverly you surmise to see through our disguise!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 13, 'direction': 3, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p24 expr0 pos0
  - dialogue: "Very well! You leave us with no choice! I challenge you in Master Sol Chevalsky's place! We shall du"
  - duel
  - fallthrough

## map_31_state_05

- map/state: `31/5`
- music: `242`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_31_state_06

- map/state: `31/6`
- music: `242`

### Initial Sprites
- obj 1: sprite `97` at `128,96` A `0x08EB43B4` R `0x08EB43B4`

### Scripts
- enter 0: `0x08EB43C0`
  - play_music
  - delay
  - play_music
  - show_object: {'object_id': 1, 'x': 72, 'y': 44, 'frame': 0, 'mode': 1}
  - delay
  - portrait p35 expr0 pos8
  - dialogue: "The Winged Dragon of Ra has awakened, I see."
  - portrait p4 expr0 pos8
  - dialogue: "We did exactly what you said, pops. Now come on, where's Pegasus hiding?"
  - portrait p35 expr0 pos8
  - dialogue: "Be patient. I've been living in the mountains for generations, and I've become bored. I feel like pl"
  - hide_portrait
  - delay
  - walk_object_x
  - hide_portrait
  - command_7c_2
  - delay
  - play_music
  - portrait p4 expr0 pos8
  - dialogue: "What's up with dat guy..."
  - portrait p1 expr0 pos8
  - dialogue: "Who knows... Let's go catch him!"
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EB43B4`
  - portrait p35 expr0 pos8
  - dialogue: "You must restore Ra's power. There must be someone who knows how to wake it..."
  - fallthrough

## map_31_state_07

- map/state: `31/7`
- music: `242`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_31_state_08

- map/state: `31/8`
- music: `380`

### Initial Sprites
- obj 1: sprite `18` at `48,38` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `149` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EB43CC`
  - play_music
  - play_music
  - show_object: {'object_id': 2, 'x': 64, 'y': 96, 'frame': 0, 'mode': 0}
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 32, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 6, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 12, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 6, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 6, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 10, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 10, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 4, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 6, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 4, 'wander': 0}
  - walk_object_y
  - walk_object_x
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_31_state_09

- map/state: `31/9`
- music: `242`

### Initial Sprites
- obj 1: sprite `97` at `128,96` A `0x08EB43B4` R `0x08EB43B4`

### Scripts
- enter 0: `0x08EB43A8`
  - play_music
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24577}
  - delay
  - play_music
  - show_object: {'object_id': 1, 'x': 72, 'y': 44, 'frame': 0, 'mode': 1}
  - delay
  - portrait p35 expr0 pos8
  - dialogue: "I am Paradox. I am the sage of all duelists. I have heard many things about you."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 2}
  - delay
  - portrait p35 expr0 pos8
  - dialogue: "However, there's something different about you. You're not who I expected..."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - portrait p4 expr2 pos8
  - dialogue: "Enough with the weird introductions! Let's cut to the chase. Where's Pegasus?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 0, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 8193}
  - delay
  - portrait p35 expr0 pos8
  - dialogue: "Why do you want to know?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p1 expr0 pos8
  - dialogue: "We have to stop the Dark Being at all costs!"
  - portrait p35 expr0 pos8
  - dialogue: "Reshef the Dark Being... If the three Egyptian God Cards regained their power... It may be possible "
  - portrait p4 expr0 pos8
  - dialogue: "Yeah, so tell us where he's at..."
  - portrait p35 expr0 pos8
  - dialogue: "Patience, young one. Patience. {PLAYER}, The Winged Dragon of Ra that you hold..."
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EB43B4`
  - portrait p35 expr0 pos8
  - dialogue: "You must restore Ra's power. There must be someone who knows how to wake it..."
  - fallthrough

## map_31_state_10

- map/state: `31/10`
- music: `242`

### Initial Sprites
- obj 1: sprite `97` at `72,44` A `0x08EB43B4` R `0x08EB43B4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EB43B4`
  - portrait p35 expr0 pos8
  - dialogue: "You must restore Ra's power. There must be someone who knows how to wake it..."
  - fallthrough

## map_32_state_00

- map/state: `32/0`
- music: `242`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_32_state_01

- map/state: `32/1`
- music: `242`

### Initial Sprites
- obj 1: sprite `24` at `59,46` A `0x08EB8FC4` R `0x08EB8FD0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EB8FC4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EB8FD0`
  - check_flag
  - fallthrough

## map_32_state_02

- map/state: `32/2`
- music: `242`

### Initial Sprites
- obj 1: sprite `24` at `59,46` A `0x08EB8FDC` R `0x08EB8FF4`
- obj 2: sprite `122` at `65528,36` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `1` at `128,32` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `4` at `128,52` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `3` at `65528,40` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `55` at `65528,48` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EB8FDC`
  - dialogue: "Aiyah! This is the Great Wall of China. It is one of China's treasures. There's nothing finer."
  - set_flag
  - fallthrough
- obj 1 R: `0x08EB8FF4`
  - dialogue: "Aiyah! I do not know how to duel."
  - fallthrough

## map_32_state_03

- map/state: `32/3`
- music: `242`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_32_state_04

- map/state: `32/4`
- music: `242`

### Initial Sprites
- obj 1: sprite `30` at `59,46` A `0x08EB90D8` R `0x08EB90D8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08EB915C`
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - fallthrough
- obj 1 A: `0x08EB90D8`
  - portrait p46 expr0 pos8
  - dialogue: "You'll proceed no further without defeating me!"
  - duel
  - fallthrough

## map_32_state_05

- map/state: `32/5`
- music: `242`

### Initial Sprites
- obj 1: sprite `30` at `59,46` A `0x08EB90FC` R `0x08EB90FC`

### Scripts
- enter 0: `0x08EB90F0`
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 1}
  - portrait p4 expr0 pos8
  - dialogue: "Huh? Where are we?"
  - portrait p1 expr0 pos8
  - dialogue: "We went into that tall building, but..."
  - portrait p4 expr0 pos8
  - dialogue: "A-anyway, let's keep movin'."
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08EB915C`
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - fallthrough
- obj 1 A: `0x08EB90FC`
  - portrait p46 expr0 pos8
  - dialogue: "You'll proceed no further without defeating me!"
  - duel
  - fallthrough

## map_32_state_06

- map/state: `32/6`
- music: `242`

### Initial Sprites
- obj 1: sprite `30` at `59,46` A `0x08EB90FC` R `0x08EB90FC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08EB915C`
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - fallthrough
- obj 1 A: `0x08EB90FC`
  - portrait p46 expr0 pos8
  - dialogue: "You'll proceed no further without defeating me!"
  - duel
  - fallthrough

## map_32_state_07

- map/state: `32/7`
- music: `242`

### Initial Sprites
- obj 1: sprite `30` at `59,46` A `0x08EB9114` R `0x08EB9114`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08EB915C`
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - fallthrough
- obj 1 A: `0x08EB9114`
  - portrait p46 expr0 pos8
  - dialogue: "You'll proceed no further without defeating me!"
  - duel
  - fallthrough

## map_32_state_08

- map/state: `32/8`
- music: `242`

### Initial Sprites
- obj 1: sprite `30` at `59,46` A `0x08EB912C` R `0x08EB912C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08EB915C`
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - fallthrough
- obj 1 A: `0x08EB912C`
  - portrait p46 expr0 pos8
  - dialogue: "You'll proceed no further without defeating me!"
  - duel
  - fallthrough

## map_32_state_09

- map/state: `32/9`
- music: `242`

### Initial Sprites
- obj 1: sprite `30` at `59,46` A `0x08EB9144` R `0x08EB9144`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 3: `0x08EB915C`
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - clear_flag
  - fallthrough
- obj 1 A: `0x08EB9144`
  - portrait p46 expr0 pos8
  - dialogue: "You'll proceed no further without defeating me!"
  - duel
  - fallthrough

## map_32_state_10

- map/state: `32/10`
- music: `242`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 1: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_33_state_00

- map/state: `33/0`
- music: `243`

### Initial Sprites
- obj 1: sprite `97` at `60,38` A `0x08EBEC58` R `0x08EBEC58`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EBEC58`
  - warp: {'map_id': 53, 'state': 2, 'connection': 0}
  - fallthrough

## map_33_state_01

- map/state: `33/1`
- music: `243`

### Initial Sprites
- obj 1: sprite `30` at `60,38` A `0x08EBEACC` R `0x08EBEAD8`
- obj 2: sprite `31` at `60,65528` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `119` at `60,65528` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EBEACC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EBEAD8`
  - check_flag
  - fallthrough

## map_33_state_02

- map/state: `33/2`
- music: `243`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_33_state_03

- map/state: `33/3`
- music: `243`

### Initial Sprites
- obj 1: sprite `18` at `72,46` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `12` at `88,40` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `13` at `88,52` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EBEB38`
  - play_music
  - portrait p27 expr0 pos0
  - dialogue: "You listen to us..."
  - portrait p26 expr0 pos0
  - dialogue: "You're going to join us as a Neo Ghoul."
  - portrait p13 expr0 pos0
  - dialogue: "You're smart as a spider to recruit me."
  - portrait p27 expr0 pos0
  - dialogue: "You'll join us?"
  - portrait p13 expr1 pos0
  - dialogue: "Hyohyohyo! Okay!"
  - portrait p0 expr0 pos0
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_33_state_04

- map/state: `33/4`
- music: `243`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_33_state_05

- map/state: `33/5`
- music: `243`

### Initial Sprites
- obj 1: sprite `97` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EBEBE0`
  - play_music
  - delay
  - play_music
  - show_object: {'object_id': 1, 'x': 60, 'y': 68, 'frame': 0, 'mode': 1}
  - delay
  - portrait p35 expr0 pos8
  - dialogue: "What took you so long? However, you've passed the challenges so far. Along the way, you have been gi"
  - portrait p0 expr0 pos8
  - dialogue: "{CARD_1}Yes No{CARD_2}"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_33_state_06

- map/state: `33/6`
- music: `243`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_34_state_00

- map/state: `34/0`
- music: `244`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_34_state_01

- map/state: `34/1`
- music: `244`

### Initial Sprites
- obj 1: sprite `88` at `65,43` A `0x08EC253C` R `0x08EC2548`
- obj 2: sprite `93` at `92,40` A `0x08EC2578` R `0x08EC25C0`
- obj 3: sprite `94` at `20,50` A `0x08EC25CC` R `0x08EC25D8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- enter 4: `0x08EC2524`
  - check_flag
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC253C`
  - dialogue: "You can find a ton of dinosaur fossils here."
  - fallthrough
- obj 1 R: `0x08EC2548`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EC2578`
  - check_flag
  - fallthrough
- obj 2 R: `0x08EC25C0`
  - dialogue: "I'm no duelist. So no dueling for me, buddy."
  - fallthrough
- obj 3 A: `0x08EC25CC`
  - dialogue: "I'm hoping for a big discovery, eh? Then I'll be famous!"
  - fallthrough
- obj 3 R: `0x08EC25D8`
  - check_flag
  - fallthrough

## map_34_state_02

- map/state: `34/2`
- music: `244`

### Initial Sprites
- obj 1: sprite `88` at `82,55` A `0x08EC2614` R `0x08EC2620`
- obj 2: sprite `93` at `88,40` A `0x08EC262C` R `0x08EC2638`
- obj 3: sprite `94` at `46,66` A `0x08EC2644` R `0x08EC2650`
- obj 4: sprite `26` at `92,49` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `26` at `92,61` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EC2608`
  - play_music
  - delay
  - walk_object_x
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "There's a duelist here, I know it!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - portrait p49 expr0 pos8
  - dialogue: "You better not cross the Neo Ghouls or we'll punish you hard! Be a good boy and tell us!"
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - walk_object_x
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "H-he's in the cave..."
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 5, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_x
  - walk_object_y
  - set_object_position
  - walk_object_x
  - walk_object_y
  - set_object_position
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - set_flag
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EC2614`
  - dialogue: "I can't believe the Neo Ghouls are here, eh?"
  - fallthrough
- obj 1 R: `0x08EC2620`
  - dialogue: "I'm in no mood for dueling, buddy."
  - fallthrough
- obj 2 A: `0x08EC262C`
  - dialogue: "I hope the duelist in the cave's all right, eh?"
  - fallthrough
- obj 2 R: `0x08EC2638`
  - dialogue: "I'm no duelist, buddy. So I don't duel."
  - fallthrough
- obj 3 A: `0x08EC2644`
  - dialogue: "What do you suppose brought the Neo Ghouls out here?"
  - fallthrough
- obj 3 R: `0x08EC2650`
  - dialogue: "Sorry, pal, I dedicated my life to fossils. No more dueling for me."
  - fallthrough

## map_34_state_03

- map/state: `34/3`
- music: `244`

### Initial Sprites
- obj 1: sprite `88` at `78,55` A `0x08EC2614` R `0x08EC2620`
- obj 2: sprite `93` at `88,40` A `0x08EC262C` R `0x08EC2638`
- obj 3: sprite `94` at `46,66` A `0x08EC2644` R `0x08EC2650`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC2614`
  - dialogue: "I can't believe the Neo Ghouls are here, eh?"
  - fallthrough
- obj 1 R: `0x08EC2620`
  - dialogue: "I'm in no mood for dueling, buddy."
  - fallthrough
- obj 2 A: `0x08EC262C`
  - dialogue: "I hope the duelist in the cave's all right, eh?"
  - fallthrough
- obj 2 R: `0x08EC2638`
  - dialogue: "I'm no duelist, buddy. So I don't duel."
  - fallthrough
- obj 3 A: `0x08EC2644`
  - dialogue: "What do you suppose brought the Neo Ghouls out here?"
  - fallthrough
- obj 3 R: `0x08EC2650`
  - dialogue: "Sorry, pal, I dedicated my life to fossils. No more dueling for me."
  - fallthrough

## map_34_state_04

- map/state: `34/4`
- music: `244`

### Initial Sprites
- obj 1: sprite `88` at `78,55` A `0x08EC265C` R `0x08EC2668`
- obj 2: sprite `93` at `92,40` A `0x08EC2698` R `0x08EC26A4`
- obj 3: sprite `94` at `20,50` A `0x08EC26B0` R `0x08EC26BC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC265C`
  - dialogue: "A long time ago, we were on a dig in Egypt where we unearthed a stone tablet. Legend says the Egypti"
  - fallthrough
- obj 1 R: `0x08EC2668`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EC2698`
  - dialogue: "I hear Duel Monsters are based on stone tablets. Weren't those tablets found in Egypt? We only dig f"
  - fallthrough
- obj 2 R: `0x08EC26A4`
  - dialogue: "Nah, I'm focused on my work. I don't duel at all."
  - fallthrough
- obj 3 A: `0x08EC26B0`
  - dialogue: "I wish I could unearth some rare fossils. Actually, I'd like to find anything, as long as it's rare."
  - fallthrough
- obj 3 R: `0x08EC26BC`
  - dialogue: "No, I'll get in trouble if I goof off too much. Sorry, next time."
  - fallthrough

## map_34_state_05

- map/state: `34/5`
- music: `381`

### Initial Sprites
- obj 1: sprite `88` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `93` at `92,40` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `94` at `20,50` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EC26C8`
  - play_music
  - play_music
  - show_object: {'object_id': 1, 'x': 106, 'y': 32, 'frame': 0, 'mode': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 4, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "This is a huge discovery, eh!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 12}
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 4, 'wander': 0}
  - show_object: {'object_id': 1, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "We ought to hurry too."
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - show_object: {'object_id': 2, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - delay
  - walk_object_x
  - walk_object_y
  - delay
  - move_object: {'object_id': 3, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "Maybe our find will really make us famous!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 2, 'object_mask': 8}
  - walk_object_y
  - show_object: {'object_id': 3, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - command_7c_2
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_35_state_00

- map/state: `35/0`
- music: `245`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_35_state_01

- map/state: `35/1`
- music: `245`

### Initial Sprites
- obj 1: sprite `19` at `94,50` A `0x08EC62CC` R `0x08EC62E4`
- obj 2: sprite `95` at `94,41` A `0x08EC62B4` R `0x08EC62B4`
- obj 3: sprite `96` at `94,59` A `0x08EC62C0` R `0x08EC62C0`

### Scripts
- enter 0: `0x08EC62A8`
  - play_music
  - command_7c_7
  - delay
  - play_music
  - portrait p4 expr0 pos8
  - dialogue: "What... It's an earthquake!"
  - portrait p1 expr0 pos8
  - dialogue: "Is Reshef's resurrection causing the tremors?"
  - portrait p4 expr5 pos8
  - dialogue: "Whatever it is, stay on your toes. We better keep moving, guys."
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC62CC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EC62E4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EC62B4`
  - dialogue: "That quake was off the Richter scale!"
  - fallthrough
- obj 3 A: `0x08EC62C0`
  - dialogue: "We don't often get quakes around these parts. I hope nothing bad is going to happen."
  - fallthrough

## map_35_state_02

- map/state: `35/2`
- music: `245`

### Initial Sprites
- obj 1: sprite `19` at `94,50` A `0x08EC62CC` R `0x08EC62E4`
- obj 2: sprite `95` at `94,41` A `0x08EC62B4` R `0x08EC62B4`
- obj 3: sprite `96` at `94,59` A `0x08EC62C0` R `0x08EC62C0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC62CC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EC62E4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EC62B4`
  - dialogue: "That quake was off the Richter scale!"
  - fallthrough
- obj 3 A: `0x08EC62C0`
  - dialogue: "We don't often get quakes around these parts. I hope nothing bad is going to happen."
  - fallthrough

## map_35_state_03

- map/state: `35/3`
- music: `245`

### Initial Sprites
- obj 1: sprite `19` at `85,59` A `0x08EC62CC` R `0x08EC62E4`
- obj 2: sprite `95` at `94,41` A `0x08EC62B4` R `0x08EC62B4`
- obj 3: sprite `96` at `94,59` A `0x08EC62C0` R `0x08EC62C0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC62CC`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EC62E4`
  - check_flag
  - fallthrough
- obj 2 A: `0x08EC62B4`
  - dialogue: "That quake was off the Richter scale!"
  - fallthrough
- obj 3 A: `0x08EC62C0`
  - dialogue: "We don't often get quakes around these parts. I hope nothing bad is going to happen."
  - fallthrough

## map_35_state_04

- map/state: `35/4`
- music: `245`

### Initial Sprites
- obj 1: sprite `19` at `90,56` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `26` at `96,40` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `26` at `84,40` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `95` at `63,68` A `0x08EC63BC` R `0x08EC63C8`
- obj 5: sprite `96` at `49,63` A `0x08EC63D4` R `0x08EC63D4`

### Scripts
- enter 0: `0x08EC6344`
  - play_music
  - portrait p11 expr2 pos0
  - dialogue: "Two on one's not fair, you dorkasaurus!"
  - portrait p49 expr0 pos0
  - dialogue: "Fair? We don't know the meaning of the word fair!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 4, 'object_mask': 2}
  - delay
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p11 expr6 pos8
  - dialogue: "You scavengers..."
  - portrait p49 expr0 pos0
  - dialogue: "Tsk! Our boy has friends! We'll wipe the floor with all of you!"
  - portrait p11 expr0 pos8
  - dialogue: "With {PLAYER} at my side, you guys are as scary as baby birds! I won't lose to any Neo Ghouls! {PLAY"
  - portrait p0 expr0 pos0
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 4 A: `0x08EC63BC`
  - dialogue: "Good to see you safe and sound, eh?"
  - fallthrough
- obj 4 R: `0x08EC63C8`
  - dialogue: "I believe you have more important things to do.. I think you should get moving, eh?"
  - fallthrough
- obj 5 A: `0x08EC63D4`
  - dialogue: "I tell you, excavating fossils is slow and laborious. Even though it's hard work, I never take short"
  - fallthrough

## map_35_state_05

- map/state: `35/5`
- music: `245`

### Initial Sprites
- obj 1: sprite `95` at `63,68` A `0x08EC63BC` R `0x08EC63C8`
- obj 2: sprite `96` at `49,63` A `0x08EC63D4` R `0x08EC63D4`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC63BC`
  - dialogue: "Good to see you safe and sound, eh?"
  - fallthrough
- obj 1 R: `0x08EC63C8`
  - dialogue: "I believe you have more important things to do.. I think you should get moving, eh?"
  - fallthrough
- obj 2 A: `0x08EC63D4`
  - dialogue: "I tell you, excavating fossils is slow and laborious. Even though it's hard work, I never take short"
  - fallthrough

## map_35_state_06

- map/state: `35/6`
- music: `245`

### Initial Sprites
- obj 1: sprite `95` at `63,68` A `0x08EC63E0` R `0x08EC63E0`
- obj 2: sprite `96` at `49,63` A `0x08EC63EC` R `0x08EC63EC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EC63E0`
  - dialogue: "Fossils are the remains of prehistoric life forms. Over millions of years, they were preserved in st"
  - fallthrough
- obj 2 A: `0x08EC63EC`
  - dialogue: "Remnants of living creatures preserved in stone... That makes fossils sound creppy, eh? Come to thin"
  - fallthrough

## map_36_state_00

- map/state: `36/0`
- music: `245`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_36_state_01

- map/state: `36/1`
- music: `245`

### Initial Sprites
- obj 1: sprite `30` at `86,56` A `0x08EC9C0C` R `0x08EC9C18`
- obj 2: sprite `5` at `144,112` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `116` at `128,56` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EC9C0C`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EC9C18`
  - check_flag
  - fallthrough

## map_36_state_02

- map/state: `36/2`
- music: `245`

### Initial Sprites
- obj 1: sprite `19` at `86,56` A `0x08EC9C54` R `0x08EC9C78`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EC9C54`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EC9C78`
  - check_flag
  - fallthrough

## map_36_state_03

- map/state: `36/3`
- music: `382`

### Initial Sprites
- obj 1: sprite `19` at `56,54` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `88` at `84,32` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `93` at `67,36` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `94` at `51,35` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `95` at `70,56` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `96` at `88,48` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EC9CB4`
  - play_music
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "Whoa, this is a huge discovery, eh."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "Yeah, I agree with you there."
  - portrait p11 expr0 pos8
  - dialogue: "It is awesome."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "M-maybe we're the first in the world to find this?"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 126}
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "That's a distinct possibility, eh."
  - hide_portrait
  - delay
  - move_object: {'object_id': 4, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 4, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 4, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "This is going to make us famous!"
  - hide_portrait
- exit 0: `0x08F04034`
  - fallthrough

## map_37_state_00

- map/state: `37/0`
- music: `246`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_37_state_01

- map/state: `37/1`
- music: `246`

### Initial Sprites
- obj 1: sprite `20` at `56,64` A `0x08ECD7E4` R `0x08ECD7F0`

### Scripts
- enter 0: `0x08ECD7D8`
  - play_music
  - play_music
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 8, 'wander': 0}
  - delay
  - portrait p12 expr0 pos8
  - dialogue: "I can hear the sea raging... It's shouting as if nature is out of balance."
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ECD7E4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08ECD7F0`
  - check_flag
  - fallthrough

## map_37_state_02

- map/state: `37/2`
- music: `246`

### Initial Sprites
- obj 1: sprite `20` at `56,72` A `0x08ECD7E4` R `0x08ECD7F0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ECD7E4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08ECD7F0`
  - check_flag
  - fallthrough

## map_37_state_03

- map/state: `37/3`
- music: `246`

### Initial Sprites
- obj 1: sprite `20` at `56,72` A `0x08ECD8A4` R `0x08ECD8B0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ECD8A4`
  - portrait p12 expr0 pos8
  - dialogue: "There's a cartload of monkeys around.. They're in the rainforest."
  - fallthrough
- obj 1 R: `0x08ECD8B0`
  - portrait p12 expr0 pos8
  - dialogue: "These days, monkeys are so smart that they can duel. If you have time to burn, go into the rainfores"
  - fallthrough

## map_37_state_04

- map/state: `37/4`
- music: `246`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_37_state_05

- map/state: `37/5`
- music: `249`

### Initial Sprites
- obj 1: sprite `20` at `56,72` A `0x08ECD844` R `0x08ECD868`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ECD844`
  - check_flag
  - fallthrough
- obj 1 R: `0x08ECD868`
  - check_flag
  - fallthrough

## map_37_state_06

- map/state: `37/6`
- music: `383`

### Initial Sprites
- obj 1: sprite `20` at `56,74` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `99` at `42,48` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `99` at `42,56` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `99` at `62,40` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `99` at `70,56` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `145` at `50,48` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `146` at `50,56` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `147` at `62,48` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `148` at `62,56` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ECD8BC`
  - play_music
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p12 expr7 pos1
  - dialogue: "Hey! Wait! Wait up!"
  - play_music
  - portrait p38 expr0 pos1
  - dialogue: "Ukki! Ukikki!"
  - hide_portrait
  - delay
  - show_object: {'object_id': 6, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 7, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 8, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 9, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - play_music
  - slide_object
  - show_object: {'object_id': 2, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - move_object: {'object_id': 3, 'direction': 1, 'distance': 0, 'wander': 0}
  - play_music
  - slide_object
  - show_object: {'object_id': 3, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - move_object: {'object_id': 4, 'direction': 2, 'distance': 0, 'wander': 0}
  - play_music
  - slide_object
  - show_object: {'object_id': 4, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - move_object: {'object_id': 5, 'direction': 2, 'distance': 0, 'wander': 0}
  - play_music
  - slide_object
  - show_object: {'object_id': 5, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 8, 'wander': 0}
  - delay
  - portrait p12 expr7 pos1
  - dialogue: "Tsk, these annoying little monkeys..."
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p12 expr1 pos1
  - dialogue: "Oh well. I'll just catch more fish. The sea is plentiful with her bounty."
  - hide_portrait
  - delay
  - play_music
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_37_state_07

- map/state: `37/7`
- music: `383`

### Initial Sprites
- obj 1: sprite `20` at `60,76` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `99` at `56,64` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `99` at `64,64` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `99` at `60,58` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `99` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `132` at `60,75` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ECD8C8`
  - play_music
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p12 expr0 pos1
  - dialogue: "We're setting sail!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos1
  - dialogue: "Ukiii!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos1
  - dialogue: "Ukikiiii!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p12 expr1 pos1
  - dialogue: "Wait for me! I'm returning back to the Town of Domino right now!"
  - fade_screen
  - show_object: {'object_id': 1, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 2, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 3, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 4, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 6, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 5, 'x': 60, 'y': 0, 'frame': 0, 'mode': 0}
  - play_music
  - slide_object
  - play_music
  - portrait p38 expr6 pos1
  - dialogue: "Ukiii!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr5 pos1
  - dialogue: "Ukikikikiiii!"
  - hide_portrait
  - delay
- exit 0: `0x08F04034`
  - fallthrough
- exit 3: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_38_state_00

- map/state: `38/0`
- music: `247`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_38_state_01

- map/state: `38/1`
- music: `247`

### Initial Sprites
- obj 1: sprite `18` at `88,56` A `0x08ED164C` R `0x08ED1658`

### Scripts
- enter 0: `0x08ED1640`
  - play_music
  - delay
  - walk_object_x
  - delay
  - walk_object_y
  - delay
  - walk_object_x
  - delay
  - walk_object_y
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p13 expr1 pos8
  - dialogue: "Hyohyohyohyohyo! This island is a treasure trove of rare insects!"
  - set_flag
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 2: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08ED164C`
  - portrait p13 expr0 pos8
  - dialogue: "Hyo? You're trying to steal my beautiful bugs, aren't you? I'm not sharing any of them with you!"
  - fallthrough
- obj 1 R: `0x08ED1658`
  - check_flag
  - fallthrough

## map_38_state_02

- map/state: `38/2`
- music: `247`

### Initial Sprites
- obj 1: sprite `18` at `56,40` A `0x08ED164C` R `0x08ED1658`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ED164C`
  - portrait p13 expr0 pos8
  - dialogue: "Hyo? You're trying to steal my beautiful bugs, aren't you? I'm not sharing any of them with you!"
  - fallthrough
- obj 1 R: `0x08ED1658`
  - check_flag
  - fallthrough

## map_38_state_03

- map/state: `38/3`
- music: `247`

### Initial Sprites
- obj 1: sprite `99` at `84,52` A `0x08ED1718` R `0x08ED1718`
- obj 2: sprite `99` at `68,40` A `0x08ED1724` R `0x08ED1724`
- obj 3: sprite `99` at `52,48` A `0x08ED1748` R `0x08ED1748`
- obj 4: sprite `99` at `40,36` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `133` at `64,26` A `0x08ED1784` R `0x08ED1790`
- obj 6: sprite `133` at `66,28` A `0x08ED1784` R `0x08ED1790`
- obj 7: sprite `133` at `62,30` A `0x08ED1784` R `0x08ED1790`

### Scripts
- enter 0: `0x08ED16E8`
  - play_music
  - delay
  - walk_object_y
  - walk_object_x
  - delay
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos0
  - dialogue: "Uki!"
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos0
  - dialogue: "Uki!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - delay
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos0
  - dialogue: "Ukiki!"
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr0 pos0
  - dialogue: "Ukiki!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - delay
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr2 pos0
  - dialogue: "Uki uki ukikki!"
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr5 pos0
  - dialogue: "Ukiiiii!"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - walk_object_x
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 2: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08ED1718`
  - play_music
  - play_music
  - portrait p38 expr5 pos8
  - dialogue: "Ukiii..."
  - portrait p4 expr0 pos8
  - dialogue: "This one's too strong to be Tristan. It's not him."
  - fallthrough
- obj 2 A: `0x08ED1724`
  - check_flag
  - fallthrough
- obj 3 A: `0x08ED1748`
  - check_flag
  - fallthrough
- obj 5 A: `0x08ED1784`
  - dialogue: "This is a banana!"
  - fallthrough
- obj 5 R: `0x08ED1790`
  - dialogue: "Sorry, you can't duel a banana!"
  - fallthrough

## map_38_state_04

- map/state: `38/4`
- music: `247`

### Initial Sprites
- obj 1: sprite `99` at `84,52` A `0x08ED1718` R `0x08ED1718`
- obj 2: sprite `99` at `70,36` A `0x08ED1724` R `0x08ED1724`
- obj 3: sprite `99` at `58,36` A `0x08ED1748` R `0x08ED1748`
- obj 4: sprite `133` at `64,26` A `0x08ED1784` R `0x08ED1790`
- obj 5: sprite `133` at `66,28` A `0x08ED1784` R `0x08ED1790`
- obj 6: sprite `133` at `62,30` A `0x08ED1784` R `0x08ED1790`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ED1718`
  - play_music
  - play_music
  - portrait p38 expr5 pos8
  - dialogue: "Ukiii..."
  - portrait p4 expr0 pos8
  - dialogue: "This one's too strong to be Tristan. It's not him."
  - fallthrough
- obj 2 A: `0x08ED1724`
  - check_flag
  - fallthrough
- obj 3 A: `0x08ED1748`
  - check_flag
  - fallthrough
- obj 4 A: `0x08ED1784`
  - dialogue: "This is a banana!"
  - fallthrough
- obj 4 R: `0x08ED1790`
  - dialogue: "Sorry, you can't duel a banana!"
  - fallthrough

## map_38_state_05

- map/state: `38/5`
- music: `250`

### Initial Sprites
- obj 1: sprite `18` at `56,40` A `0x08ED1688` R `0x08ED16AC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ED1688`
  - check_flag
  - fallthrough
- obj 1 R: `0x08ED16AC`
  - check_flag
  - fallthrough

## map_38_state_06

- map/state: `38/6`
- music: `384`

### Initial Sprites
- obj 1: sprite `20` at `104,52` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `99` at `90,40` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `99` at `90,48` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `99` at `90,56` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `99` at `90,64` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `137` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `138` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `137` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `138` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED176C`
  - play_music
  - portrait p12 expr7 pos0
  - dialogue: "How many chances do you want! You're driving me bananas! I'm taking you down!"
  - hide_portrait
  - delay
  - slide_object
  - slide_object
  - slide_object
  - slide_object
  - delay
  - play_music
  - portrait p38 expr0 pos0
  - dialogue: "Ukiiii!"
  - fade_screen
  - show_object: {'object_id': 2, 'x': 0, 'y': 50, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 3, 'x': 80, 'y': 80, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 4, 'x': 44, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 5, 'x': 96, 'y': 96, 'frame': 0, 'mode': 0}
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - delay
  - show_object: {'object_id': 6, 'x': 56, 'y': 42, 'frame': 0, 'mode': 0}
  - play_music
  - slide_object
  - delay
  - walk_object_y
  - walk_object_y
  - walk_object_x
  - delay
  - show_object: {'object_id': 7, 'x': 72, 'y': 46, 'frame': 0, 'mode': 0}
  - play_music
  - slide_object
  - delay
  - walk_object_x
  - show_object: {'object_id': 4, 'x': 44, 'y': 0, 'frame': 0, 'mode': 0}
  - walk_object_y
  - walk_object_x
  - delay
  - show_object: {'object_id': 8, 'x': 56, 'y': 48, 'frame': 0, 'mode': 0}
  - play_music
  - slide_object
  - delay
  - walk_object_y
  - show_object: {'object_id': 4, 'x': 44, 'y': 96, 'frame': 0, 'mode': 0}
  - show_object: {'object_id': 5, 'x': 96, 'y': 0, 'frame': 0, 'mode': 0}
  - walk_object_y
  - walk_object_x
  - delay
  - show_object: {'object_id': 9, 'x': 72, 'y': 44, 'frame': 0, 'mode': 0}
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 2: `0x08F04034`
  - fallthrough

## map_38_state_07

- map/state: `38/7`
- music: `384`

### Initial Sprites
- obj 1: sprite `20` at `104,52` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `99` at `54,40` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `99` at `60,54` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `99` at `68,34` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `99` at `74,48` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `132` at `64,46` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED1778`
  - play_music
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 3, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 5, 'direction': 2, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 5, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 4, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p12 expr0 pos0
  - dialogue: "Keep working! There's no time to rest!"
  - play_music
  - portrait p38 expr0 pos0
  - dialogue: "U-ukiii..."
  - fade_screen
  - warp: {'map_id': 37, 'state': 7, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 2: `0x08F04034`
  - fallthrough

## map_39_state_00

- map/state: `39/0`
- music: `248`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_39_state_01

- map/state: `39/1`
- music: `248`

### Initial Sprites
- obj 1: sprite `2` at `55,54` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `32` at `144,112` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `121` at `55,46` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED4A80`
  - play_music
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24577}
  - delay
  - portrait p1 expr6 pos8
  - dialogue: "L-look!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 4, 'wander': 0}
  - delay
  - play_music
  - show_object: {'object_id': 3, 'x': 144, 'y': 112, 'frame': 0, 'mode': 0}
  - delay
  - walk_object_y
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p2 expr0 pos8
  - dialogue: "It's been a long time, partner."
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 13, 'direction': 1, 'distance': 0, 'wander': 0}
  - walk_object_x
  - delay
  - portrait p2 expr0 pos8
  - dialogue: "I've already snatched the Millennium Item here. Including the ones you have, that makes six. Ishizu "
  - portrait p0 expr0 pos8
  - dialogue: "{CARD_1}Yes No{CARD_2}"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_39_state_02

- map/state: `39/2`
- music: `248`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_39_state_03

- map/state: `39/3`
- music: `407`

### Initial Sprites
- obj 1: sprite `20` at `56,56` A `0x08ED4AD4` R `0x08ED4AD4`
- obj 2: sprite `14` at `56,40` A `0x08ED4AC8` R `0x08ED4AC8`

### Scripts
- enter 0: `0x08ED4ABC`
  - play_music
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 8, 'wander': 0}
  - delay
  - portrait p12 expr7 pos8
  - dialogue: "S-say something!"
  - portrait p21 expr0 pos8
  - dialogue: "..."
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 8, 'wander': 0}
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p12 expr7 pos8
  - dialogue: "W-what a strange individual! I've never felt so uncomfortable..."
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ED4AD4`
  - portrait p12 expr1 pos8
  - dialogue: "Hey, you've come just at the right time. Can you do something about this person? I lack the skill to"
  - portrait p0 expr0 pos0
  - fallthrough
- obj 2 A: `0x08ED4AC8`
  - portrait p21 expr0 pos8
  - dialogue: "..."
  - fallthrough

## map_39_state_04

- map/state: `39/4`
- music: `407`

### Initial Sprites
- obj 1: sprite `20` at `56,56` A `0x08ED4AD4` R `0x08ED4AD4`
- obj 2: sprite `14` at `56,40` A `0x08ED4AC8` R `0x08ED4AC8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ED4AD4`
  - portrait p12 expr1 pos8
  - dialogue: "Hey, you've come just at the right time. Can you do something about this person? I lack the skill to"
  - portrait p0 expr0 pos0
  - fallthrough
- obj 2 A: `0x08ED4AC8`
  - portrait p21 expr0 pos8
  - dialogue: "..."
  - fallthrough

## map_39_state_05

- map/state: `39/5`
- music: `248`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_39_state_06

- map/state: `39/6`
- music: `248`

### Initial Sprites
- obj 1: sprite `99` at `76,69` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED4B40`
  - play_music
  - delay
  - walk_object_x
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - delay
  - walk_object_x
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr6 pos8
  - dialogue: "Ukki?"
  - portrait p1 expr0 pos8
  - dialogue: "Why are you running? Are you Tristan?"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - play_music
  - portrait p38 expr5 pos8
  - dialogue: "Ukiiii..."
  - portrait p4 expr0 pos8
  - dialogue: "We'll know for sure after we duel!"
  - walk_object_x
  - walk_object_x
  - move_object: {'object_id': 13, 'direction': 0, 'distance': 0, 'wander': 0}
  - walk_object_x
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - duel
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_39_state_07

- map/state: `39/7`
- music: `248`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_39_state_08

- map/state: `39/8`
- music: `251`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_40_state_00

- map/state: `40/0`
- music: `252`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_40_state_01

- map/state: `40/1`
- music: `252`

### Initial Sprites
- obj 1: sprite `6` at `128,72` A `0x08ED55FC` R `0x08ED55FC`

### Scripts
- enter 0: `0x08ED55F0`
  - play_music
  - delay
  - walk_object_x
  - delay
  - walk_object_x
  - walk_object_x
  - walk_object_x
  - delay
  - portrait p16 expr0 pos8
  - dialogue: "So... This is Pegasus's island. Seto Kaiba has probably already gone ahead."
  - portrait p0 expr0 pos0
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p16 expr0 pos8
  - dialogue: "I do not know what Pegasus is planning. But we cannot ignore Reshef the Dark Being. Harsh battles aw"
  - set_flag
  - fallthrough
- exit 0: `0x08ED5608`
  - set_flag
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08ED55FC`
  - portrait p16 expr0 pos8
  - dialogue: "The Duelist Kingdom Tournament was once held here. However, the island has been transformed since th"
  - fallthrough

## map_40_state_02

- map/state: `40/2`
- music: `252`

### Initial Sprites
- obj 1: sprite `6` at `32,72` A `0x08ED55FC` R `0x08ED55FC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08ED5608`
  - set_flag
  - fallthrough
- obj 1 A: `0x08ED55FC`
  - portrait p16 expr0 pos8
  - dialogue: "The Duelist Kingdom Tournament was once held here. However, the island has been transformed since th"
  - fallthrough

## map_40_state_03

- map/state: `40/3`
- music: `252`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08ED5608`
  - set_flag
  - fallthrough

## map_41_state_00

- map/state: `41/0`
- music: `253`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_41_state_01

- map/state: `41/1`
- music: `253`

### Initial Sprites
- obj 1: sprite `39` at `128,96` A `0x08ED7C0C` R `0x08ED7C0C`
- obj 2: sprite `39` at `128,96` A `0x08ED7C24` R `0x08ED7C24`
- obj 3: sprite `39` at `128,96` A `0x08ED7C3C` R `0x08ED7C3C`

### Scripts
- enter 0: `0x08ED7BDC`
  - play_music
  - delay
  - show_object: {'object_id': 0, 'x': 58, 'y': 62, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - show_object: {'object_id': 13, 'x': 66, 'y': 62, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - show_object: {'object_id': 14, 'x': 50, 'y': 62, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - play_music
  - set_flag
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 16384}
  - delay
  - portrait p4 expr3 pos8
  - dialogue: "That Pegasus... What drove him to do this?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 13, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 0, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - dialogue: "{CARD_1}I don't know We'll know if we go{CARD_2}"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08ED7C0C`
  - play_music
  - object_effect
  - delay
  - portrait p50 expr0 pos1
  - dialogue: "Gawry nida! Gawry nida! You'll go no further! Gawry!"
  - portrait p4 expr2 pos8
  - dialogue: "Wha... Who are you?"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p50 expr0 pos1
  - dialogue: "I am one of many! Gawry! Master Chevalsky turned us into duelists! Gawry! We no longer have no names"
  - portrait p4 expr2 pos8
  - dialogue: "That Pegasus... He's really annoyin' me now! {PLAYER}, it's time to lay down the law!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - delay
  - play_music
  - duel
  - fallthrough
- obj 2 A: `0x08ED7C24`
  - delay
  - play_music
  - object_effect
  - portrait p50 expr0 pos0
  - dialogue: "Gawry nida! Gawry nida! You'll go no further! Gawry!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - duel
  - fallthrough
- obj 3 A: `0x08ED7C3C`
  - delay
  - play_music
  - object_effect
  - portrait p50 expr0 pos1
  - dialogue: "Gawry nida! Gawry nida! You'll go no further! Gawry!"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - duel
  - fallthrough

## map_41_state_02

- map/state: `41/2`
- music: `253`

### Initial Sprites
- obj 1: sprite `39` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `39` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `39` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED7C54`
  - play_music
  - delay
  - play_music
  - set_flag
  - delay
  - play_music
  - play_music
  - command_7c_7
  - delay
  - play_music
  - show_object: {'object_id': 1, 'x': 40, 'y': 54, 'frame': 0, 'mode': 2}
  - move_object: {'object_id': 0, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - object_effect
  - portrait p50 expr0 pos1
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_x
  - delay
  - duel
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_42_state_00

- map/state: `42/0`
- music: `254`

### Initial Sprites
- obj 1: sprite `29` at `10,60` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_42_state_01

- map/state: `42/1`
- music: `254`

### Initial Sprites
- obj 1: sprite `29` at `128,64` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `4` at `62,58` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `27` at `128,74` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED9D70`
  - play_music
  - delay
  - walk_object_x
  - delay
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - portrait p19 expr0 pos0
  - dialogue: "Nihihi... I commend you on coming this far."
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - portrait p18 expr0 pos0
  - dialogue: "Gehehehehe... But you're not going any farther. We won't let you!"
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - portrait p4 expr2 pos0
  - dialogue: "Hah! In your dreams! We'll take you on!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos0
  - dialogue: "{PLAYER}, pick who you want to duel!"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- exit 4: `0x08ED9E60`
  - set_flag
  - fallthrough

## map_42_state_02

- map/state: `42/2`
- music: `254`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 4: `0x08ED9E60`
  - set_flag
  - fallthrough

## map_42_state_03

- map/state: `42/3`
- music: `254`

### Initial Sprites
- obj 1: sprite `29` at `98,64` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `4` at `88,74` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `27` at `98,74` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED9E48`
  - play_music
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos0
  - dialogue: "I didn't realize until now that you've gotten really strong, {PLAYER}."
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- exit 4: `0x08ED9E60`
  - set_flag
  - fallthrough

## map_42_state_04

- map/state: `42/4`
- music: `254`

### Initial Sprites
- obj 1: sprite `29` at `98,64` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `4` at `88,64` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `27` at `98,74` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08ED9E54`
  - play_music
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p4 expr0 pos0
  - dialogue: "I didn't realize until now that you've gotten really strong, {PLAYER}."
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- exit 4: `0x08ED9E60`
  - set_flag
  - fallthrough

## map_43_state_00

- map/state: `43/0`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_43_state_01

- map/state: `43/1`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `128,37` A `0x08EDA650` R `0x08EDA650`
- obj 2: sprite `39` at `65520,35` A `0x08EDA668` R `0x08EDA668`

### Scripts
- enter 0: `0x08EDA638`
  - play_music
  - portrait p1 expr0 pos8
  - dialogue: "We can't betray Joey's trust, {PLAYER}. We have to go as quickly as possible."
  - warp: {'map_id': 55, 'state': 3, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EDA650`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough
- obj 2 A: `0x08EDA668`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough

## map_43_state_02

- map/state: `43/2`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `96,38` A `0x08EDA650` R `0x08EDA650`
- obj 2: sprite `39` at `24,40` A `0x08EDA668` R `0x08EDA668`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EDA650`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough
- obj 2 A: `0x08EDA668`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough

## map_43_state_03

- map/state: `43/3`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `128,37` A `0x08EDA650` R `0x08EDA650`
- obj 2: sprite `39` at `65520,35` A `0x08EDA668` R `0x08EDA668`

### Scripts
- enter 0: `0x08EDA644`
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 8193}
  - delay
  - walk_object_x
  - delay
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida!"
  - hide_portrait
  - delay
  - walk_object_x
  - delay
  - portrait p50 expr0 pos1
  - dialogue: "Gawry nida!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - portrait p50 expr0 pos8
  - dialogue: "You'll go no further!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - portrait p50 expr0 pos1
  - dialogue: "Gawry!"
  - set_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EDA650`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough
- obj 2 A: `0x08EDA668`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough

## map_44_state_00

- map/state: `44/0`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_44_state_01

- map/state: `44/1`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `56,33` A `0x08EDA8AC` R `0x08EDA8AC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EDA8AC`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough

## map_45_state_00

- map/state: `45/0`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_45_state_01

- map/state: `45/1`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `62,41` A `0x08EDAAF0` R `0x08EDAAF0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EDAAF0`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough

## map_46_state_00

- map/state: `46/0`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_46_state_01

- map/state: `46/1`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `51,36` A `0x08EDAD34` R `0x08EDAD34`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EDAD34`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough

## map_47_state_00

- map/state: `47/0`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_47_state_01

- map/state: `47/1`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `40,20` A `0x08EDB06C` R `0x08EDB06C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EDB06C`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! We win all duels! Gawry!"
  - duel
  - fallthrough

## map_47_state_02

- map/state: `47/2`
- music: `17`

### Initial Sprites
- obj 1: sprite `6` at `56,39` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `3` at `49,30` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `2` at `33,19` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `4` at `40,16` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `55` at `128,51` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EDB084`
  - set_object_position
  - walk_object_x
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 63}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 4, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - command_7c_8
  - delay
  - portrait p10 expr0 pos0
  - dialogue: "Hey! Everyone! Over here!"
  - portrait p0 expr0 pos8
  - hide_portrait
  - delay
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_48_state_00

- map/state: `48/0`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_48_state_01

- map/state: `48/1`
- music: `17`

### Initial Sprites
- obj 1: sprite `1` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `122` at `65528,68` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `123` at `128,68` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EDE89C`
  - set_object_position
  - walk_object_x
  - move_object: {'object_id': 0, 'direction': 1, 'distance': 0, 'wander': 0}
  - set_object_position
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - fallthrough
- enter 1: `0x08EDE8A8`
  - set_object_position
  - walk_object_x
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 0, 'wander': 0}
  - set_object_position
  - walk_object_x
  - walk_object_y
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - fallthrough
- enter 2: `0x08EDE8B4`
  - portrait p1 expr0 pos8
  - dialogue: "We should reach Pegasus's castle soon. {PLAYER}, do you think you can beat Pegasus?"
  - portrait p0 expr0 pos0
  - dialogue: "{CARD_1}I don't know. Of course!{CARD_2}"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_48_state_02

- map/state: `48/2`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_48_state_03

- map/state: `48/3`
- music: `17`

### Initial Sprites
- obj 1: sprite `1` at `60,60` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `122` at `65528,68` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `123` at `128,68` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EDE8CC`
  - play_music
  - portrait p1 expr0 pos8
  - dialogue: "I'm also going to give everything I've got. I have to get the spirit of the Puzzle back..."
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_48_state_04

- map/state: `48/4`
- music: `17`

### Initial Sprites
- obj 1: sprite `1` at `60,60` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `122` at `65528,68` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `123` at `128,68` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EDE8E4`
  - play_music
  - portrait p1 expr0 pos8
  - dialogue: "I also have to get the spirit of the Puzzle back. That's why I have to keep up with your skills, {PL"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_48_state_05

- map/state: `48/5`
- music: `17`

### Initial Sprites
- obj 1: sprite `1` at `68,44` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `23` at `52,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `24` at `68,38` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EDE980`
  - play_music
  - portrait p1 expr0 pos8
  - dialogue: "That's why I can't waste any time. I won't be stopped!"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_48_state_06

- map/state: `48/6`
- music: `17`

### Initial Sprites
- obj 1: sprite `1` at `52,44` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `23` at `52,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `24` at `68,38` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EDE980`
  - play_music
  - portrait p1 expr0 pos8
  - dialogue: "That's why I can't waste any time. I won't be stopped!"
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_49_state_00

- map/state: `49/0`
- music: `17`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_49_state_01

- map/state: `49/1`
- music: `17`

### Initial Sprites
- obj 1: sprite `39` at `60,48` A `0x08EDEBD8` R `0x08EDEBD8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 4: `0x08EDEBF0`
  - set_flag
  - fallthrough
- obj 1 A: `0x08EDEBD8`
  - portrait p50 expr0 pos8
  - dialogue: "Gawry nida! Gawry nida! You'll go no further! Gawry!"
  - duel
  - fallthrough

## map_50_state_00

- map/state: `50/0`
- music: `18`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_50_state_01

- map/state: `50/1`
- music: `410`

### Initial Sprites
- obj 1: sprite `97` at `128,96` A `0x08EE04C4` R `0x08EE0524`

### Scripts
- enter 0: `0x08EE04B8`
  - play_music
  - delay
  - walk_object_y
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 1}
  - delay
  - play_music
  - show_object: {'object_id': 1, 'x': 60, 'y': 52, 'frame': 0, 'mode': 1}
  - delay
  - portrait p35 expr0 pos8
  - dialogue: "Excellent. You've done well to get this far. However, in order to proceed, you must conquer this lab"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 1}
  - delay
  - portrait p35 expr0 pos8
  - dialogue: "Yes... You must light your way with spirit cards. The cards that embody the spirits of your fellow d"
  - set_flag
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EE04C4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EE0524`
  - portrait p35 expr0 pos8
  - dialogue: "Duelists do not communicate with words. Duels unite your spirits. With your hearts as one, your wish"
  - fallthrough

## map_50_state_02

- map/state: `50/2`
- music: `18`

### Initial Sprites
- obj 1: sprite `97` at `60,52` A `0x08EE04C4` R `0x08EE0524`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EE04C4`
  - check_flag
  - fallthrough
- obj 1 R: `0x08EE0524`
  - portrait p35 expr0 pos8
  - dialogue: "Duelists do not communicate with words. Duels unite your spirits. With your hearts as one, your wish"
  - fallthrough

## map_50_state_03

- map/state: `50/3`
- music: `23`

### Initial Sprites
- obj 1: sprite `6` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `3` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `2` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `4` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE0530`
  - play_music
  - set_object_position
  - walk_object_y
  - set_object_position
  - walk_object_y
  - set_object_position
  - walk_object_y
  - stop_music
  - warp: {'map_id': 47, 'state': 2, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_51_state_00

- map/state: `51/0`
- music: `18`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_51_state_01

- map/state: `51/1`
- music: `18`

### Initial Sprites

### Scripts
- enter 0: `0x08EE4028`
  - check_flag
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE3FC8`
  - clear_flag
  - fallthrough

## map_51_state_02

- map/state: `51/2`
- music: `18`

### Initial Sprites
- obj 1: sprite `21` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE3CB0`
  - check_flag
  - fallthrough
- enter 1: `0x08EE3CBC`
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- enter 3: `0x08EE3CC8`
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE3FD4`
  - clear_flag
  - warp: {'map_id': 51, 'state': 1, 'connection': 0}
  - fallthrough

## map_51_state_03

- map/state: `51/3`
- music: `18`

### Initial Sprites
- obj 1: sprite `19` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE3D34`
  - check_flag
  - fallthrough
- enter 1: `0x08EE3D40`
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- enter 3: `0x08EE3D4C`
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE3FE0`
  - clear_flag
  - warp: {'map_id': 51, 'state': 2, 'connection': 0}
  - fallthrough

## map_51_state_04

- map/state: `51/4`
- music: `18`

### Initial Sprites
- obj 1: sprite `18` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE3DB8`
  - check_flag
  - fallthrough
- enter 1: `0x08EE3DC4`
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- enter 3: `0x08EE3DD0`
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE3FEC`
  - clear_flag
  - warp: {'map_id': 51, 'state': 3, 'connection': 0}
  - fallthrough

## map_51_state_05

- map/state: `51/5`
- music: `18`

### Initial Sprites
- obj 1: sprite `20` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE3E3C`
  - check_flag
  - fallthrough
- enter 1: `0x08EE3E48`
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- enter 3: `0x08EE3E54`
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE3FF8`
  - clear_flag
  - warp: {'map_id': 51, 'state': 4, 'connection': 0}
  - fallthrough

## map_51_state_06

- map/state: `51/6`
- music: `18`

### Initial Sprites
- obj 1: sprite `17` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE3EC0`
  - check_flag
  - fallthrough
- enter 1: `0x08EE3ECC`
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- enter 3: `0x08EE3ED8`
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE4004`
  - clear_flag
  - warp: {'map_id': 51, 'state': 5, 'connection': 0}
  - fallthrough

## map_51_state_07

- map/state: `51/7`
- music: `18`

### Initial Sprites
- obj 1: sprite `7` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE3F44`
  - check_flag
  - fallthrough
- enter 1: `0x08EE3F50`
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- enter 3: `0x08EE3F5C`
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE4010`
  - clear_flag
  - warp: {'map_id': 51, 'state': 6, 'connection': 0}
  - fallthrough

## map_51_state_08

- map/state: `51/8`
- music: `18`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_51_state_09

- map/state: `51/9`
- music: `23`

### Initial Sprites
- obj 1: sprite `6` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `3` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `2` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `4` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE404C`
  - play_music
  - show_object: {'object_id': 1, 'x': 56, 'y': 32, 'frame': 0, 'mode': 0}
  - walk_object_y
  - play_music
  - object_effect
  - show_object: {'object_id': 2, 'x': 64, 'y': 32, 'frame': 0, 'mode': 0}
  - walk_object_y
  - delay
  - move_object: {'object_id': 2, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - show_object: {'object_id': 1, 'x': 56, 'y': 60, 'frame': 0, 'mode': 3}
  - delay
  - walk_object_y
  - walk_object_y
  - delay
  - fade_screen
  - warp: {'map_id': 50, 'state': 3, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_51_state_10

- map/state: `51/10`
- music: `18`

### Initial Sprites
- obj 1: sprite `124` at `74,40` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `125` at `43,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `126` at `19,54` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `124` at `54,54` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `125` at `110,61` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `126` at `44,76` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `124` at `105,52` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `125` at `12,62` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `126` at `78,61` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `124` at `64,70` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `125` at `78,72` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE4058`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough

## map_52_state_00

- map/state: `52/0`
- music: `18`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_52_state_01

- map/state: `52/1`
- music: `18`

### Initial Sprites
- obj 1: sprite `41` at `60,26` A `0x08EE62A0` R `0x08EE62A0`
- obj 2: sprite `32` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EE62A0`
  - check_flag
  - fallthrough

## map_53_state_00

- map/state: `53/0`
- music: `18`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_53_state_01

- map/state: `53/1`
- music: `18`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_53_state_02

- map/state: `53/2`
- music: `18`

### Initial Sprites
- obj 1: sprite `124` at `31,34` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `125` at `43,36` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `126` at `88,44` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `124` at `46,76` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `125` at `76,20` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `126` at `102,69` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `124` at `98,36` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `125` at `17,41` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `126` at `18,72` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `124` at `61,55` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `125` at `86,72` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `31` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE62E8`
  - delay
  - fade_screen
  - cutscene 7 PEGASUS_BEFORE_CREDITS
  - fallthrough
- enter 1: `0x08F04034`
  - fallthrough

## map_54_state_00

- map/state: `54/0`
- music: `19`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_54_state_01

- map/state: `54/1`
- music: `19`

### Initial Sprites
- obj 1: sprite `3` at `60,63` A `0x08EE9C60` R `0x08EE9C60`
- obj 2: sprite `6` at `46,96` A `0x08EE9C78` R `0x08EE9C78`
- obj 3: sprite `55` at `60,65520` A `0x08EE9C6C` R `0x08EE9C6C`
- obj 4: sprite `39` at `60,42` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `113` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE9C24`
  - play_music
  - delay
  - portrait p3 expr2 pos8
  - dialogue: "Go, Blue-Eyes White Dragon!"
  - play_music
  - command_7c_8
  - delay
  - portrait p3 expr2 pos8
  - dialogue: "White Lightning Attack!"
  - play_music
  - command_7c_8
  - delay
  - play_music
  - slide_object
  - play_music
  - object_effect
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p3 expr0 pos8
  - dialogue: "Humph. So you finally showed up. But you're too late. That Pegasus... I will crush him myself!"
  - hide_portrait
  - delay
  - walk_object_y
  - delay
  - portrait p16 expr0 pos8
  - dialogue: "Kaiba... You cannot win alone... One Egyptian God Card isn't enough. You have no chance. Not against"
  - portrait p3 expr1 pos8
  - dialogue: "My deck is perfect! Whoever the opponent may be, defeat isn't in the cards!"
  - hide_portrait
  - delay
  - show_object: {'object_id': 3, 'x': 60, 'y': 18, 'frame': 0, 'mode': 0}
  - walk_object_y
  - move_object: {'object_id': 0, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 7}
  - delay
  - portrait p10 expr8 pos8
  - dialogue: "Then duel me, big brother, with your perfect deck."
  - portrait p3 expr6 pos8
  - dialogue: "Wh-what? Mokuba? Wh-what are you saying?"
  - portrait p10 expr8 pos8
  - dialogue: "Reshef is going to rule this world anyway. It's better to quit fighting and accept fate."
  - portrait p16 expr0 pos8
  - dialogue: "Mokuba's spirit is under control..."
  - portrait p3 expr5 pos8
  - dialogue: "Pegasus! How dare you!"
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EE9C60`
  - portrait p3 expr0 pos8
  - dialogue: "Hurry up and beat Pegasus."
  - fallthrough
- obj 2 A: `0x08EE9C78`
  - portrait p16 expr0 pos8
  - dialogue: "Come, {PLAYER}, we must go. The time has come to seal Reshef the Dark Being."
  - fallthrough
- obj 3 A: `0x08EE9C6C`
  - portrait p10 expr3 pos8
  - dialogue: "..."
  - fallthrough

## map_54_state_02

- map/state: `54/2`
- music: `19`

### Initial Sprites
- obj 1: sprite `3` at `60,42` A `0x08EE9C60` R `0x08EE9C60`
- obj 2: sprite `6` at `46,72` A `0x08EE9C78` R `0x08EE9C78`
- obj 3: sprite `55` at `68,37` A `0x08EE9C6C` R `0x08EE9C6C`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EE9C60`
  - portrait p3 expr0 pos8
  - dialogue: "Hurry up and beat Pegasus."
  - fallthrough
- obj 2 A: `0x08EE9C78`
  - portrait p16 expr0 pos8
  - dialogue: "Come, {PLAYER}, we must go. The time has come to seal Reshef the Dark Being."
  - fallthrough
- obj 3 A: `0x08EE9C6C`
  - portrait p10 expr3 pos8
  - dialogue: "..."
  - fallthrough

## map_54_state_03

- map/state: `54/3`
- music: `19`

### Initial Sprites
- obj 1: sprite `124` at `58,24` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `125` at `43,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `126` at `35,72` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `124` at `67,72` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `125` at `72,36` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `126` at `96,64` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `124` at `95,36` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `125` at `16,70` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `126` at `21,51` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `124` at `63,53` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `125` at `86,72` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EE9C84`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- exit 2: `0x08EE9C90`
  - delay
  - fade_screen
  - warp: {'map_id': 53, 'state': 2, 'connection': 0}
  - fallthrough

## map_55_state_00

- map/state: `55/0`
- music: `20`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_55_state_01

- map/state: `55/1`
- music: `20`

### Initial Sprites
- obj 1: sprite `31` at `60,46` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `6` at `52,96` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `3` at `72,96` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `1` at `60,96` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `4` at `50,96` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `135` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `124` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `125` at `128,96` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `126` at `128,96` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EF04D4`
  - play_music
  - walk_object_y
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 1}
  - walk_object_y
  - delay
  - portrait p5 expr1 pos8
  - dialogue: "Congratulations for passing my test! So, {PLAYER}, it is you who survived until the end... Fufufu, I"
  - hide_portrait
  - delay
  - walk_object_y
  - portrait p16 expr0 pos8
  - dialogue: "Pegasus, stop this nonsense at once."
  - portrait p5 expr0 pos8
  - dialogue: "My past means nothing to me. I am no longer Pegasus. I am Sol Chevalsky!"
  - portrait p16 expr0 pos8
  - dialogue: "Why are you acting like this? It's not too late. Return Reshef the Dark Being to its prison."
  - portrait p5 expr1 pos8
  - dialogue: "What? Why should I do that? When Reshef gains full power, it would create a wonderful world! Why can"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 1}
  - delay
  - portrait p16 expr0 pos8
  - dialogue: "He is under the spell of the Dark Being..."
  - portrait p5 expr0 pos8
  - dialogue: "To complete the resurrection of Reshef the Dark Being... There is no greater sacrifice... Than the s"
  - hide_portrait
  - delay
  - play_music
  - set_object_position
  - delay
  - portrait p5 expr1 pos8
  - dialogue: "I have his power right here. Fufufu... There are no duelists left who can beat me. Therefore, you wi"
  - portrait p16 expr0 pos8
  - dialogue: "He has the pieces of the Millennium Puzzle..."
  - hide_portrait
  - delay
  - play_music
  - set_object_position
  - delay
  - portrait p5 expr1 pos8
  - dialogue: "Come, the preparations have been made. We will duel, and you will taste defeat!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - portrait p16 expr0 pos8
  - dialogue: "There is no choice. Please, {PLAYER}. You must free Pegasus's spirit from Reshef."
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_55_state_02

- map/state: `55/2`
- music: `20`

### Initial Sprites
- obj 1: sprite `124` at `27,50` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `125` at `50,42` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `126` at `102,64` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `124` at `67,62` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `125` at `74,38` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `126` at `39,69` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `124` at `95,36` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `125` at `16,70` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `126` at `13,42` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `124` at `59,50` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `125` at `86,72` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EF0570`
  - delay
  - fade_screen
  - warp: {'map_id': 54, 'state': 3, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_55_state_03

- map/state: `55/3`
- music: `20`

### Initial Sprites
- obj 1: sprite `31` at `60,46` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `39` at `56,60` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `39` at `64,60` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `39` at `56,68` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `39` at `64,68` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EF057C`
  - portrait p5 expr0 pos8
  - dialogue: "Fufufu... You've finally arrived. Duelists of pure hearts and spirits, I was hoping you would come. "
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p5 expr0 pos8
  - dialogue: "Now! Go, my disciples! Go forth and defeat them!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - portrait p50 expr0 pos1
  - dialogue: "Gawry nida!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - portrait p50 expr0 pos0
  - dialogue: "Gawry nida!"
  - hide_portrait
  - delay
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - walk_object_y
  - portrait p5 expr0 pos8
  - dialogue: "Reshef the Dark Being created my disciples. These duelists have neither emotion nor mercy. Crush the"
  - portrait p5 expr1 pos8
  - dialogue: "Ahahahahaha!"
  - fade_screen
  - warp: {'map_id': 43, 'state': 3, 'connection': 4}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_55_state_04

- map/state: `55/4`
- music: `20`

### Initial Sprites
- obj 1: sprite `31` at `60,46` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EF0588`
  - portrait p5 expr0 pos8
  - dialogue: "The path you are on is neverending! I have taken the miserable spirits of the duelists you defeated."
  - portrait p5 expr1 pos8
  - dialogue: "Ahahahahaha!"
  - set_flag
  - fade_screen
  - warp: {'map_id': 51, 'state': 1, 'connection': 2}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_56_state_00

- map/state: `56/0`
- music: `25`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_56_state_01

- map/state: `56/1`
- music: `25`

### Initial Sprites
- obj 1: sprite `98` at `11,64` A `0x08EF2F84` R `0x08EF2F90`
- obj 2: sprite `5` at `25,77` A `0x08EF2FA8` R `0x08EF2FB4`
- obj 3: sprite `22` at `94,77` A `0x08EF2FCC` R `0x08EF2FD8`
- obj 4: sprite `2` at `60,77` A `0x08EF2FF0` R `0x08EF2FFC`
- obj 5: sprite `4` at `107,65` A `0x08EF3014` R `0x08EF3020`
- obj 6: sprite `3` at `98,41` A `0x08EF3038` R `0x08EF3044`
- obj 7: sprite `31` at `76,26` A `0x08EF305C` R `0x08EF3068`
- obj 8: sprite `97` at `37,26` A `0x08EF3080` R `0x08EF308C`
- obj 9: sprite `32` at `20,41` A `0x08EF30A4` R `0x08EF30B0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EF2F84`
  - portrait p36 expr0 pos8
  - dialogue: "My name is Noah. Shall I make you a permanent citizen of my virtual world?"
  - fallthrough
- obj 1 R: `0x08EF2F90`
  - portrait p36 expr0 pos8
  - dialogue: "Heh. You want me to duel you? I admire your courage, but your stupidity will be your downfall! Savor"
  - duel
  - fallthrough
- obj 2 A: `0x08EF2FA8`
  - portrait p33 expr0 pos8
  - dialogue: "Hahahahahahaha! I'll destroy you and plunge the world into darkness!"
  - fallthrough
- obj 2 R: `0x08EF2FB4`
  - portrait p33 expr0 pos8
  - dialogue: "I'll annihilate you quick. In fact, I'll beat you in one turn! Fuhahahahaha!"
  - duel
  - fallthrough
- obj 3 A: `0x08EF2FCC`
  - portrait p34 expr0 pos8
  - dialogue: "Hahahahaha! I don't think it's wise for you to get to know me!"
  - fallthrough
- obj 3 R: `0x08EF2FD8`
  - portrait p34 expr0 pos8
  - dialogue: "My occult deck will banish you into the shadows!"
  - duel
  - fallthrough
- obj 4 A: `0x08EF2FF0`
  - portrait p2 expr0 pos8
  - dialogue: "{PLAYER}, what can be seen and not seen at the same time?"
  - fallthrough
- obj 4 R: `0x08EF2FFC`
  - portrait p2 expr0 pos8
  - dialogue: "I accept your challenge!"
  - duel
  - fallthrough
- obj 5 A: `0x08EF3014`
  - portrait p37 expr0 pos8
  - dialogue: "{PLAYER}... You're goin' down..."
  - fallthrough
- obj 5 R: `0x08EF3020`
  - portrait p37 expr0 pos8
  - dialogue: "Even your family won't recognize you after I finish pummeling ya!"
  - duel
  - fallthrough
- obj 6 A: `0x08EF3038`
  - portrait p3 expr0 pos8
  - dialogue: "You want to know who my strongest rival is? Heh. One thing's for certain. It's not you."
  - fallthrough
- obj 6 R: `0x08EF3044`
  - portrait p3 expr0 pos8
  - dialogue: "A duel can start anyplace and anytime two duelists meet. I accept your duel!"
  - duel
  - fallthrough
- obj 7 A: `0x08EF305C`
  - portrait p5 expr0 pos8
  - dialogue: "The finest drink, The tastiest Gorgonzola cheese... The funniest comic book in the world... What mor"
  - fallthrough
- obj 7 R: `0x08EF3068`
  - portrait p5 expr0 pos8
  - dialogue: "I've scanned your mind. I can read your strategies as if it were an open book! I hate to say this, b"
  - duel
  - fallthrough
- obj 8 A: `0x08EF3080`
  - portrait p35 expr0 pos8
  - dialogue: "I am Paradox. I am the sage for all duelists."
  - fallthrough
- obj 8 R: `0x08EF308C`
  - portrait p35 expr0 pos8
  - dialogue: "You're challenging me? Either you're brave... Or you underestimate me..."
  - duel
  - fallthrough
- obj 9 A: `0x08EF30A4`
  - portrait p17 expr0 pos8
  - dialogue: "My name is Shadi... You have a room in your soul... Which I will disassemble!"
  - fallthrough
- obj 9 R: `0x08EF30B0`
  - portrait p17 expr0 pos8
  - dialogue: "This duel has been foretold millenniums ago... Can you overcome my test?"
  - duel
  - fallthrough

## map_56_state_02

- map/state: `56/2`
- music: `25`

### Initial Sprites
- obj 1: sprite `98` at `11,64` A `0x08EF2F84` R `0x08EF2F90`
- obj 2: sprite `5` at `128,96` A `0x08EF2FA8` R `0x08EF2FB4`
- obj 3: sprite `22` at `94,77` A `0x08EF2FCC` R `0x08EF2FD8`
- obj 4: sprite `2` at `60,77` A `0x08EF2FF0` R `0x08EF2FFC`
- obj 5: sprite `4` at `107,65` A `0x08EF3014` R `0x08EF3020`
- obj 6: sprite `3` at `98,41` A `0x08EF3038` R `0x08EF3044`
- obj 7: sprite `31` at `76,26` A `0x08EF305C` R `0x08EF3068`
- obj 8: sprite `97` at `37,26` A `0x08EF3080` R `0x08EF308C`
- obj 9: sprite `32` at `20,41` A `0x08EF30A4` R `0x08EF30B0`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EF2F84`
  - portrait p36 expr0 pos8
  - dialogue: "My name is Noah. Shall I make you a permanent citizen of my virtual world?"
  - fallthrough
- obj 1 R: `0x08EF2F90`
  - portrait p36 expr0 pos8
  - dialogue: "Heh. You want me to duel you? I admire your courage, but your stupidity will be your downfall! Savor"
  - duel
  - fallthrough
- obj 2 A: `0x08EF2FA8`
  - portrait p33 expr0 pos8
  - dialogue: "Hahahahahahaha! I'll destroy you and plunge the world into darkness!"
  - fallthrough
- obj 2 R: `0x08EF2FB4`
  - portrait p33 expr0 pos8
  - dialogue: "I'll annihilate you quick. In fact, I'll beat you in one turn! Fuhahahahaha!"
  - duel
  - fallthrough
- obj 3 A: `0x08EF2FCC`
  - portrait p34 expr0 pos8
  - dialogue: "Hahahahaha! I don't think it's wise for you to get to know me!"
  - fallthrough
- obj 3 R: `0x08EF2FD8`
  - portrait p34 expr0 pos8
  - dialogue: "My occult deck will banish you into the shadows!"
  - duel
  - fallthrough
- obj 4 A: `0x08EF2FF0`
  - portrait p2 expr0 pos8
  - dialogue: "{PLAYER}, what can be seen and not seen at the same time?"
  - fallthrough
- obj 4 R: `0x08EF2FFC`
  - portrait p2 expr0 pos8
  - dialogue: "I accept your challenge!"
  - duel
  - fallthrough
- obj 5 A: `0x08EF3014`
  - portrait p37 expr0 pos8
  - dialogue: "{PLAYER}... You're goin' down..."
  - fallthrough
- obj 5 R: `0x08EF3020`
  - portrait p37 expr0 pos8
  - dialogue: "Even your family won't recognize you after I finish pummeling ya!"
  - duel
  - fallthrough
- obj 6 A: `0x08EF3038`
  - portrait p3 expr0 pos8
  - dialogue: "You want to know who my strongest rival is? Heh. One thing's for certain. It's not you."
  - fallthrough
- obj 6 R: `0x08EF3044`
  - portrait p3 expr0 pos8
  - dialogue: "A duel can start anyplace and anytime two duelists meet. I accept your duel!"
  - duel
  - fallthrough
- obj 7 A: `0x08EF305C`
  - portrait p5 expr0 pos8
  - dialogue: "The finest drink, The tastiest Gorgonzola cheese... The funniest comic book in the world... What mor"
  - fallthrough
- obj 7 R: `0x08EF3068`
  - portrait p5 expr0 pos8
  - dialogue: "I've scanned your mind. I can read your strategies as if it were an open book! I hate to say this, b"
  - duel
  - fallthrough
- obj 8 A: `0x08EF3080`
  - portrait p35 expr0 pos8
  - dialogue: "I am Paradox. I am the sage for all duelists."
  - fallthrough
- obj 8 R: `0x08EF308C`
  - portrait p35 expr0 pos8
  - dialogue: "You're challenging me? Either you're brave... Or you underestimate me..."
  - duel
  - fallthrough
- obj 9 A: `0x08EF30A4`
  - portrait p17 expr0 pos8
  - dialogue: "My name is Shadi... You have a room in your soul... Which I will disassemble!"
  - fallthrough
- obj 9 R: `0x08EF30B0`
  - portrait p17 expr0 pos8
  - dialogue: "This duel has been foretold millenniums ago... Can you overcome my test?"
  - duel
  - fallthrough

## map_57_state_00

- map/state: `57/0`
- music: `13`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_57_state_01

- map/state: `57/1`
- music: `13`

### Initial Sprites
- obj 1: sprite `108` at `128,70` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `55` at `74,68` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `56` at `128,70` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `104` at `128,70` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `103` at `128,70` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `106` at `128,70` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `105` at `128,70` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `107` at `128,70` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `111` at `37,26` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `112` at `36,52` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `33` at `81,73` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EFB3F0`
  - play_music
  - walk_object_x
  - delay
  - move_object: {'object_id': 14, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 14, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - move_object: {'object_id': 14, 'direction': 3, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 16384}
  - walk_object_x
  - walk_object_x
  - delay
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - walk_object_y
  - walk_object_x
  - play_music
  - move_object: {'object_id': 13, 'direction': 3, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - play_music
  - move_object: {'object_id': 14, 'direction': 3, 'distance': 0, 'wander': 0}
  - walk_object_x
  - walk_object_y
  - walk_object_x
  - play_music
  - move_object: {'object_id': 0, 'direction': 3, 'distance': 0, 'wander': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_57_state_02

- map/state: `57/2`
- music: `13`

### Initial Sprites
- obj 1: sprite `108` at `88,56` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `55` at `74,68` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `15` at `65520,72` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `104` at `76,38` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `103` at `82,28` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `106` at `100,38` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `105` at `94,28` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `107` at `88,38` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `34` at `28,32` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `35` at `44,24` A `0x08F04034` R `0x08F04034`
- obj 11: sprite `128` at `40,32` A `0x08F04034` R `0x08F04034`
- obj 12: sprite `17` at `65520,72` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EFB42C`
  - play_music
  - delay
  - play_music
  - object_effect
  - dialogue: "Yeah, do it, Kaibaman!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "Bash the Big Bad Five!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p47 expr0 pos0
  - dialogue: "Thanks, everyone!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p47 expr0 pos0
  - dialogue: "Prepare for final justice, Big Bad Five! Prepare to feel Kaibaman's ultimate finisher, Final Card Fl"
  - play_music
  - special
  - play_music
  - slide_object
  - play_music
  - slide_object
  - play_music
  - slide_object
  - play_music
  - slide_object
  - play_music
  - slide_object
  - portrait p42 expr0 pos0
  - dialogue: "Graaah! We're done for!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - portrait p47 expr0 pos0
  - dialogue: "Justice just rules! I am victorious in victory!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p10 expr0 pos0
  - dialogue: "Uh... That's the weirdest catchphrase I've ever heard, but I guess it's cool."
  - hide_portrait
- exit 0: `0x08F04034`
  - fallthrough

## map_57_state_03

- map/state: `57/3`
- music: `13`

### Initial Sprites
- obj 1: sprite `33` at `88,56` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `129` at `76,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `129` at `82,28` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `129` at `100,38` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `129` at `94,28` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `129` at `88,38` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EFB444`
  - portrait p30 expr0 pos0
  - dialogue: "All right, crew! Everyone ready?"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "Yes, I understand. But..."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "We're missing two of our members..."
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - dialogue: "What's the point of doing a children's show?"
  - portrait p30 expr0 pos0
  - dialogue: "You fools!"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 124}
  - delay
  - portrait p30 expr0 pos0
  - dialogue: "The children are afraid! The Neo Ghouls stole their rare cards. Kaibaman represents hope to the kids"
  - hide_portrait
  - delay
  - move_object: {'object_id': 2, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 3, 'direction': 3, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 4, 'direction': 1, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 5, 'direction': 1, 'distance': 0, 'wander': 0}
  - move_object: {'object_id': 6, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - portrait p30 expr0 pos0
  - dialogue: "As a bonus, I'll speak to Master Kaiba about giving you better jobs."
  - hide_portrait
  - delay
  - play_music
  - swap_object_sprite: {'object_id': 1, 'sprite_id': 108}
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 124}
  - delay
  - move_object: {'object_id': 5, 'direction': 0, 'distance': 0, 'wander': 0}
  - play_music
  - object_effect
  - play_music
  - swap_object_sprite: {'object_id': 5, 'sprite_id': 105}
  - portrait p43 expr0 pos0
- exit 0: `0x08F04034`
  - fallthrough

## map_57_state_04

- map/state: `57/4`
- music: `13`

### Initial Sprites
- obj 1: sprite `108` at `88,56` A `0x08F04034` R `0x08F04034`
- obj 2: sprite `104` at `76,38` A `0x08F04034` R `0x08F04034`
- obj 3: sprite `103` at `82,28` A `0x08F04034` R `0x08F04034`
- obj 4: sprite `106` at `100,38` A `0x08F04034` R `0x08F04034`
- obj 5: sprite `105` at `94,28` A `0x08F04034` R `0x08F04034`
- obj 6: sprite `107` at `88,38` A `0x08F04034` R `0x08F04034`
- obj 7: sprite `111` at `36,32` A `0x08F04034` R `0x08F04034`
- obj 8: sprite `112` at `36,52` A `0x08F04034` R `0x08F04034`
- obj 9: sprite `150` at `23,56` A `0x08F04034` R `0x08F04034`
- obj 10: sprite `151` at `24,33` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08EFB450`
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "Go for it, Kaibaman!"
  - hide_portrait
  - delay
  - play_music
  - object_effect
  - delay
  - dialogue: "Don't give up, Kaibaman!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 1, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - portrait p47 expr0 pos0
  - dialogue: "Justice just rules! I am victorious in victory!"
  - hide_portrait
  - delay
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - play_music
  - command_7c_8
  - delay
  - portrait p47 expr0 pos0
  - dialogue: "Dragon Sabre Blast!"
  - play_music
  - command_7c_8
  - delay
  - command_7c_2
  - fade_screen
  - warp: {'map_id': 26, 'state': 10, 'connection': 0}
  - fallthrough
- exit 0: `0x08F04034`
  - fallthrough

## map_58_state_00

- map/state: `58/0`
- music: `0`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough

## map_59_state_00

- map/state: `59/0`
- music: `26`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_59_state_01

- map/state: `59/1`
- music: `26`

### Initial Sprites
- obj 1: sprite `139` at `56,48` A `0x08F04034` R `0x08F04034`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- enter 4: `0x08EFDA58`
  - play_music
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 16, 'wander': 0}
  - move_object: {'object_id': 0, 'direction': 1, 'distance': 16, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 1, 'distance': 16, 'wander': 0}
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 16, 'wander': 0}
  - portrait p51 expr0 pos8
  - dialogue: "Ah! It has been too long! Greetings, Pharaoh! Welcome, powerful duelists!"
  - portrait p4 expr0 pos8
  - dialogue: "Heheh, powerful duelists, huh? I love hearin' that every time! Odion, how are ya?"
  - portrait p51 expr0 pos8
  - dialogue: "I am well, as you can see."
  - portrait p4 expr0 pos8
  - dialogue: "Hahaha! Yeah, you're lookin' good."
  - portrait p51 expr0 pos8
  - dialogue: "My friends, what brings you here?"
  - portrait p1 expr0 pos8
  - dialogue: "We're here to see Marik. We have to talk to him."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 2}
  - delay
  - portrait p51 expr0 pos8
  - dialogue: "It is most unfortunate, but... I cannot permit you to see him."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 24577}
  - delay
  - portrait p4 expr0 pos8
  - dialogue: "That isn't the answer we're lookin' for. {PLAYER}, that's not cool, right?"
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_59_state_02

- map/state: `59/2`
- music: `26`

### Initial Sprites
- obj 1: sprite `139` at `128,96` A `0x08EFDAAC` R `0x08EFDAB8`

### Scripts
- enter 0: `0x08EFDAA0`
  - play_music
  - show_object: {'object_id': 1, 'x': 61, 'y': 30, 'frame': 0, 'mode': 0}
  - walk_object_y
  - move_object: {'object_id': 1, 'direction': 2, 'distance': 0, 'wander': 0}
  - delay
  - portrait p51 expr0 pos8
  - dialogue: "Master Marik will decipher the hieroglyphics. But he will need time. It is best if you continue your"
  - set_flag
  - fallthrough
- enter 1: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EFDAAC`
  - portrait p51 expr0 pos8
  - dialogue: "Since you arrived, Master Marik has been chanting devoutly. He is chanting to atone for his past sin"
  - fallthrough
- obj 1 R: `0x08EFDAB8`
  - portrait p51 expr0 pos8
  - dialogue: "You dare enter my haven of traps? Fine! We shall duel!"
  - duel
  - fallthrough

## map_59_state_03

- map/state: `59/3`
- music: `26`

### Initial Sprites
- obj 1: sprite `139` at `56,48` A `0x08EFDAAC` R `0x08EFDAB8`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08EFDAAC`
  - portrait p51 expr0 pos8
  - dialogue: "Since you arrived, Master Marik has been chanting devoutly. He is chanting to atone for his past sin"
  - fallthrough
- obj 1 R: `0x08EFDAB8`
  - portrait p51 expr0 pos8
  - dialogue: "You dare enter my haven of traps? Fine! We shall duel!"
  - duel
  - fallthrough

## map_59_state_04

- map/state: `59/4`
- music: `26`

### Initial Sprites
- obj 1: sprite `139` at `56,48` A `0x08EFDAAC` R `0x08EFDAB8`

### Scripts
- enter 0: `0x08EFDAD0`
  - play_music
  - delay
  - play_music
  - reaction: {'reaction': 1, 'object_mask': 2}
  - delay
  - move_object: {'object_id': 1, 'direction': 3, 'distance': 16, 'wander': 0}
  - move_object: {'object_id': 0, 'direction': 1, 'distance': 16, 'wander': 0}
  - move_object: {'object_id': 13, 'direction': 1, 'distance': 16, 'wander': 0}
  - move_object: {'object_id': 14, 'direction': 1, 'distance': 16, 'wander': 0}
  - portrait p51 expr0 pos8
  - dialogue: "What is the matter, {PLAYER}?"
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 2}
  - delay
  - portrait p51 expr0 pos8
  - dialogue: "I-Impossible! You obtained the secret of the Phoenix Mode? We must see Master Marik right away!"
  - hide_portrait
  - delay
  - walk_object_x
  - walk_object_y
  - show_object: {'object_id': 1, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - walk_object_x
  - walk_object_y
  - show_object: {'object_id': 0, 'x': 128, 'y': 96, 'frame': 0, 'mode': 0}
  - check_flag
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- exit 1: `0x08F04034`
  - fallthrough
- obj 1 A: `0x08EFDAAC`
  - portrait p51 expr0 pos8
  - dialogue: "Since you arrived, Master Marik has been chanting devoutly. He is chanting to atone for his past sin"
  - fallthrough
- obj 1 R: `0x08EFDAB8`
  - portrait p51 expr0 pos8
  - dialogue: "You dare enter my haven of traps? Fine! We shall duel!"
  - duel
  - fallthrough

## map_59_state_05

- map/state: `59/5`
- music: `26`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 0: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_60_state_00

- map/state: `60/0`
- music: `27`

### Initial Sprites

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough

## map_60_state_01

- map/state: `60/1`
- music: `27`

### Initial Sprites
- obj 1: sprite `5` at `60,44` A `0x08F03A38` R `0x08F03A44`
- obj 2: sprite `139` at `68,64` A `0x08F03A08` R `0x08F03A14`

### Scripts
- enter 0: `0x08F039CC`
  - play_music
  - portrait p48 expr0 pos8
  - dialogue: "Father, Mother... And all those people I harmed... I hope that the sun shines upon your spirits."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 24577}
  - delay
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p48 expr0 pos8
  - dialogue: "Hello. It has been a long time."
  - portrait p51 expr0 pos8
  - dialogue: "Master Marik, forgive us for disturbing your rituals."
  - portrait p48 expr0 pos8
  - dialogue: "It does not matter. They are always welcome. Even my departed Father would have welcomed them."
  - portrait p1 expr0 pos8
  - dialogue: "Marik, we need your help. We have to awaken {PLAYER}'s The Winged Dragon of Ra."
  - portrait p48 expr0 pos8
  - dialogue: "...Tell me more."
  - hide_portrait
  - play_music
  - fade_screen
  - portrait p48 expr0 pos8
  - dialogue: "So... That explains why my sister left in a hurry. It makes sense now..."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 3, 'object_mask': 2}
  - delay
  - portrait p48 expr0 pos8
  - dialogue: "I understand what you seek."
  - portrait p4 expr0 pos8
  - dialogue: "Great! Then how about getting on it right away?"
  - portrait p48 expr0 pos8
  - dialogue: "I will not awaken Ra so easily."
  - portrait p4 expr2 pos8
  - dialogue: "What?!"
  - portrait p48 expr0 pos8
  - dialogue: "I believe you know why. Ra is the most powerful of the Egyptian God Cards. You felt its mystical str"
  - hide_portrait
  - delay
  - play_music
  - command_7c_2
  - fade_screen
  - set_flag
  - warp: {'map_id': 23, 'state': 10, 'connection': 0}
  - fallthrough
- enter 1: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08F03A38`
  - portrait p48 expr0 pos8
  - dialogue: "There must be a secret in the hieroglyphics. A secret method for awakening the Phoenix Mode."
  - fallthrough
- obj 1 R: `0x08F03A44`
  - portrait p48 expr0 pos8
  - dialogue: "Fine. I have been freed of my obligations as a gravekeeper. When I duel, I duel for myself and will "
  - duel
  - fallthrough
- obj 2 A: `0x08F03A08`
  - portrait p51 expr0 pos8
  - dialogue: "Since you arrived, Master Marik has been chanting devoutly. He is chanting to atone for his past sin"
  - fallthrough
- obj 2 R: `0x08F03A14`
  - portrait p51 expr0 pos8
  - dialogue: "You dare enter my haven of traps? Fine! We shall duel!"
  - duel
  - fallthrough

## map_60_state_02

- map/state: `60/2`
- music: `27`

### Initial Sprites
- obj 1: sprite `5` at `60,44` A `0x08F03A38` R `0x08F03A44`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08F03A38`
  - portrait p48 expr0 pos8
  - dialogue: "There must be a secret in the hieroglyphics. A secret method for awakening the Phoenix Mode."
  - fallthrough
- obj 1 R: `0x08F03A44`
  - portrait p48 expr0 pos8
  - dialogue: "Fine. I have been freed of my obligations as a gravekeeper. When I duel, I duel for myself and will "
  - duel
  - fallthrough

## map_60_state_03

- map/state: `60/3`
- music: `27`

### Initial Sprites
- obj 1: sprite `5` at `60,44` A `0x08F03A68` R `0x08F03A74`
- obj 2: sprite `139` at `68,64` A `0x08F03AB0` R `0x08F03ABC`

### Scripts
- enter 0: `0x08F04034`
  - fallthrough
- exit 2: `0x08F03AD4`
  - command_7c_2
  - fade_screen
  - clear_flag
  - fallthrough
- obj 1 A: `0x08F03A68`
  - portrait p48 expr0 pos8
  - dialogue: "The Winged Dragon of Ra has been fully awakened. {PLAYER}! Imprison Reshef with the power of Ra!"
  - fallthrough
- obj 1 R: `0x08F03A74`
  - portrait p48 expr0 pos8
  - dialogue: "You wish to test Ra's full power on me? Fine. I accept. I will not hold anything back!"
  - duel
  - fallthrough
- obj 2 A: `0x08F03AB0`
  - portrait p51 expr0 pos8
  - dialogue: "Reshef toys with the spirits of duelists... It dominates through deception and terror. But before th"
  - fallthrough
- obj 2 R: `0x08F03ABC`
  - portrait p51 expr0 pos8
  - dialogue: "{PLAYER}, you have obtained the power of the Egyptian God Phoenix. I have little idea how I will far"
  - duel
  - fallthrough

## map_60_state_04

- map/state: `60/4`
- music: `27`

### Initial Sprites
- obj 1: sprite `5` at `60,44` A `0x08F03A38` R `0x08F03A44`
- obj 2: sprite `139` at `68,64` A `0x08F03A08` R `0x08F03A14`

### Scripts
- enter 0: `0x08F039D8`
  - play_music
  - portrait p4 expr5 pos8
  - dialogue: "Urk... Yeah, you're right. Ra is seriously scary."
  - portrait p48 expr0 pos8
  - dialogue: "So, I have a proposal, {PLAYER}."
  - hide_portrait
  - delay
  - play_music
  - reaction: {'reaction': 0, 'object_mask': 1}
  - delay
  - portrait p48 expr0 pos8
  - dialogue: "I will test you. I will determine if you are worthy of using Ra. If you fail to defeat me in a duel."
  - duel
  - fallthrough
- enter 1: `0x08F04034`
  - fallthrough
- exit 2: `0x08F04244`
  - command_7c_2
  - fade_screen
  - fallthrough
- obj 1 A: `0x08F03A38`
  - portrait p48 expr0 pos8
  - dialogue: "There must be a secret in the hieroglyphics. A secret method for awakening the Phoenix Mode."
  - fallthrough
- obj 1 R: `0x08F03A44`
  - portrait p48 expr0 pos8
  - dialogue: "Fine. I have been freed of my obligations as a gravekeeper. When I duel, I duel for myself and will "
  - duel
  - fallthrough
- obj 2 A: `0x08F03A08`
  - portrait p51 expr0 pos8
  - dialogue: "Since you arrived, Master Marik has been chanting devoutly. He is chanting to atone for his past sin"
  - fallthrough
- obj 2 R: `0x08F03A14`
  - portrait p51 expr0 pos8
  - dialogue: "You dare enter my haven of traps? Fine! We shall duel!"
  - duel
  - fallthrough

## map_60_state_05

- map/state: `60/5`
- music: `27`

### Initial Sprites
- obj 1: sprite `5` at `60,44` A `0x08F03A68` R `0x08F03A74`
- obj 2: sprite `139` at `68,64` A `0x08F03AB0` R `0x08F03ABC`

### Scripts
- enter 0: `0x08F03A8C`
  - play_music
  - portrait p48 expr0 pos8
  - dialogue: "{PLAYER}, you've finally succeeded. You have obtained the secret behind the Phoenix Mode."
  - portrait p51 expr0 pos8
  - dialogue: "Master Marik..."
  - portrait p48 expr0 pos8
  - dialogue: "Yes, I know, Odion. I am going to awaken {PLAYER}'s The Winged Dragon of Ra so that he can use the P"
  - hide_portrait
  - delay
  - walk_object_y
  - delay
  - portrait p48 expr0 pos8
  - dialogue: "I'll need to see The Winged Dragon of Ra."
  - hide_portrait
  - delay
  - play_music
  - delay
  - walk_object_y
  - delay
  - portrait p48 expr0 pos8
  - dialogue: "Awaken! Phoenix Mode!"
  - play_music
  - command_7c_8
  - play_music
  - command_7c_8
  - command_7c_8
  - play_music
  - command_7c_8
  - command_7c_8
  - set_flag
  - portrait p48 expr0 pos8
  - dialogue: "Phoenix! Be calm! Your enemy is the one who weakened the Egyptian God Cards. With {PLAYER}, you must"
  - portrait p51 expr0 pos8
  - dialogue: "What terrifying power..."
  - hide_portrait
  - delay
  - walk_object_y
  - delay
  - play_music
  - remove_card
  - add_card
  - delay
  - walk_object_y
  - move_object: {'object_id': 1, 'direction': 0, 'distance': 0, 'wander': 0}
  - delay
  - portrait p0 expr0 pos0
  - dialogue: "Received The Winged Dragon of Ra {BYTE_8169}Phoenix Mode{BYTE_816A}! The deck adjustment menu will b"
  - page_break
  - start_menu
  - fallthrough
- enter 1: `0x08F04034`
  - fallthrough
- exit 2: `0x08F03AD4`
  - command_7c_2
  - fade_screen
  - clear_flag
  - fallthrough
- obj 1 A: `0x08F03A68`
  - portrait p48 expr0 pos8
  - dialogue: "The Winged Dragon of Ra has been fully awakened. {PLAYER}! Imprison Reshef with the power of Ra!"
  - fallthrough
- obj 1 R: `0x08F03A74`
  - portrait p48 expr0 pos8
  - dialogue: "You wish to test Ra's full power on me? Fine. I accept. I will not hold anything back!"
  - duel
  - fallthrough
- obj 2 A: `0x08F03AB0`
  - portrait p51 expr0 pos8
  - dialogue: "Reshef toys with the spirits of duelists... It dominates through deception and terror. But before th"
  - fallthrough
- obj 2 R: `0x08F03ABC`
  - portrait p51 expr0 pos8
  - dialogue: "{PLAYER}, you have obtained the power of the Egyptian God Phoenix. I have little idea how I will far"
  - duel
  - fallthrough
