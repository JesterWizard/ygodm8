#ifndef GUARD_OVERWORLD_H
#define GUARD_OVERWORLD_H

#define OVERWORLD_FLAG_EXIT_OVERWORLD 1
#define OVERWORLD_FLAG_MAP_TRANSITION 2
#define OVERWORLD_FLAG_WORLD_MAP_TRANSITION 4

//TODO: ObjectDirection?
enum Direction {
  DIRECTION_DOWN,
  DIRECTION_LEFT,
  DIRECTION_UP,
  DIRECTION_RIGHT
};

enum OverworldLocation {
  LOCATION_CLOCK_TOWER_SQUARE_NORTHWEST,
  LOCATION_CLOCK_TOWER_SQUARE_NORTH,
  LOCATION_CLOCK_TOWER_SQUARE_NORTHEAST,
  LOCATION_CLOCK_TOWER_SQUARE_SOUTHEAST,
  LOCATION_CLOCK_TOWER_SQUARE_SOUTH,
  LOCATION_CLOCK_TOWER_SQUARE_SOUTHWEST,
  LOCATION_CARD_SHOP_OUTSIDE,
  LOCATION_CARD_SHOP_INSIDE,
  LOCATION_PLAYER_HOUSE_OUTSIDE,
  LOCATION_PLAYER_HOUSE_INSIDE,
  LOCATION_CLOCK_TOWER_SQUARE_BACK_ALLEY_NORTH,
  LOCATION_CLOCK_TOWER_SQUARE_BACK_ALLEY_NORTH_EAST,
  LOCATION_KAIBACORP,
  LOCATION_DUEL_MACHINE,
  LOCATION_DOMINO_STATION_TURNSTILES,
  LOCATION_DOMINO_STATION_TRAIN_STATION,
  LOCATION_DUEL_EXPRESS_CARRIAGE_RIGHT,
  LOCATION_DUEL_EXPRESS_CARRIAGE_MIDDLE,
  LOCATION_DUEL_EXPRESS_CARRIAGE_LEFT,
  LOCATION_ITALY_CATACOMBS_MIDDLE,
  LOCATION_EGYPT_EXHIBITION_TRAIN_STATION,
  LOCATION_EGYPT_EXHIBITION_TURNSTILES,
  LOCATION_EGYPT_EXHIBITION_ARTWORK,
  LOCATION_EGYPT_EXHIBITION_MILLENNIUM_GUARDIAN,
  LOCATION_DOMINO_PIER_DOCKS,
  LOCATION_DOMINO_PIER_CASINO_LEFT_ROOM,
  LOCATION_DOMINO_PIER_CASINO_MAIN_ROOM,
  LOCATION_DOMINO_PIER_MILLENNIUM_GUARDIAN,
  LOCATION_ITALY_CATACOMBS_LEFT,
  LOCATION_ITALY_CATACOMBS_RIGHT,
  LOCATION_ITALY_MILLENNIUM_GUARDIAN,
  LOCATION_CHINA_GREAT_WALL_ENTRANCE,
  LOCATION_CHINA_GREAT_WALL,
  LOCATION_CHINA_GREAT_WALL_MILLENNIUM_GUARDIAN,
  LOCATION_CANADA_RUINS_OUTSIDE,
  LOCATION_CANADA_RUINS_INSIDE,
  LOCATION_CANADA_RUINS_MILLENNIUM_GUARDIAN,
  LOCATION_GALAPAGOS_BEACH,
  LOCATION_GALAPAGOS_FOREST,
  LOCATION_GALAPAGOS_TEMPLE,
  LOCATION_PEGASUS_ISLAND_CABLE_CAR_BOTTOM_OUTSIDE,
  LOCATION_PEGASUS_ISLAND_CABLE_CAR_INSIDE,
  LOCATION_PEGASUS_ISLAND_CABLE_CAR_TOP_OUTSIDE,
  LOCATION_PEGASUS_ISLAND_DUNGEON_ENTRANCE,
  LOCATION_PEGASUS_ISLAND_DUNGEON_LAVA_ROOM_SOUTH,
  LOCATION_PEGASUS_ISLAND_DUNGEON_CLIFF,
  LOCATION_PEGASUS_ISLAND_DUNGEON_LAVA_ROOM_NORTH,
  LOCATION_PEGASUS_ISLAND_DUNGEON_BRIDGE,
  LOCATION_PEGASUS_ISLAND_DUNGEON_STAIRCASE,
  LOCATION_PEGASUS_ISLAND_DUNGEON_RUINS,
  LOCATION_PEGASUS_CASTLE_OUTSIDE,
  LOCATION_PEGASUS_CASTLE_HALLWAY,
  LOCATION_PEGASUS_CASTLE_LEFT_ROOM,
  LOCATION_PEGASUS_CASTLE_RIGHT_ROOM,
  LOCATION_PEGASUS_CASTLE_DUEL_ROOM,
  LOCATION_PEGASUS_CASTLE_RESHEF_TABLET_ROOM,
  LOCATION_HALL_OF_ETERNITY,
  LOCATION_KAIBA_LAND,
  LOCATION_CLOCK_TOWER_SQUARE_NORTH_WEST2_TODO,
  LOCATION_EGYPT,
  LOCATION_EGYPT_MARIK_ROOM
};

// TODO: OVERWORLD_ENTITY_SPRITE?
enum OverworldEntitySprite {
  SPRITE_NONE = -1,
  SPRITE_YUGI_UNUSED,
  SPRITE_YUGI,
  SPRITE_ATEM,
  SPRITE_SETO,
  SPRITE_JOEY,
  SPRITE_MARIK,
  SPRITE_ISHIZU,
  SPRITE_MAI,
  SPRITE_SOLOMON_UNUSED_TODO,
  SPRITE_JOEY_UNUSED_TODO,
  SPRITE_TEA,
  SPRITE_SOLOMON,
  SPRITE_LUMIS,
  SPRITE_UMBRA,
  SPRITE_STRINGS,
  SPRITE_SEEKER,
  SPRITE_ARKANA,
  SPRITE_ESPA,
  SPRITE_WEEVIL,
  SPRITE_REX,
  SPRITE_MAKO,
  SPRITE_BONZ,
  SPRITE_BAKURA,
  SPRITE_PARA,
  SPRITE_DOX,
  SPRITE_PLAYER,
  SPRITE_NEO_GHOUL,
  SPRITE_MIMIC_OF_DOOM,
  SPRITE_PUPPETEER_OF_DOOM,
  SPRITE_PANIK,
  SPRITE_MILLENNIUM_GUARDIAN,
  SPRITE_PEGASUS,
  SPRITE_SHADI,
  SPRITE_ROLAND,
  SPRITE_ESPA_BIGGER_BROTHER_TODO,
  SPRITE_ESPA_LITTLE_BROTHER_TODO,
  SPRITE_BLUE_EYES_UNUSED_TODO,
  SPRITE_SLIFER_TODO,
  SPRITE_RA_TODO,
  SPRITE_CHEVALIER,
  SPRITE_40,
  SPRITE_INVISIBLE,
  SPRITE_TAKESHI,
  SPRITE_43,
  SPRITE_44,
  SPRITE_45,
  SPRITE_DUEL_EXPRESS_CONDUCTOR,
  SPRITE_47,
  SPRITE_48,
  SPRITE_TRISTAN,
  SPRITE_50,
  SPRITE_51,
  SPRITE_52,
  SPRITE_53,
  SPRITE_DUKE,
  SPRITE_MOKUBA,
  SPRITE_SERENITY,
  SPRITE_LUCKY,
  SPRITE_58,
  SPRITE_59,
  SPRITE_60,
  SPRITE_61,
  SPRITE_62,
  SPRITE_BANDIT_KEITH,
  SPRITE_64,
  SPRITE_65,
  SPRITE_JEAN_CLAUDE_MAGNUM,
  SPRITE_67,
  SPRITE_68,
  SPRITE_69,
  SPRITE_70,
  SPRITE_71, //Mohawk red hair guy
  SPRITE_72,
  SPRITE_73,
  SPRITE_74,
  SPRITE_75,
  SPRITE_76,
  SPRITE_77,
  SPRITE_78,
  SPRITE_79,
  SPRITE_80,
  SPRITE_81,
  SPRITE_82, //seto wannabe
  SPRITE_83,
  SPRITE_84,
  SPRITE_85,
  SPRITE_86,
  SPRITE_87,
  SPRITE_88,
  SPRITE_PLAYER_RUNNING,
  SPRITE_90,
  SPRITE_91,
  SPRITE_92,
  SPRITE_93,
  SPRITE_94,
  SPRITE_95,
  SPRITE_96,
  SPRITE_PARADOX,
  SPRITE_NOAH,
  SPRITE_MONKEY_ROBOT,
  SPRITE_REBECCA,
  SPRITE_101,
  SPRITE_102,
  SPRITE_NIGHTMARE_PENGUIN,
  SPRITE_DEEPSEA_WARRIOR,
  SPRITE_ROBOTIC_KNIGHT,
  SPRITE_JUDGE_MAN,
  SPRITE_JINZO,
  SPRITE_KAIBAMAN,
  SPRITE_JOHNNY_STEPS,
  SPRITE_ARTHUR,
  SPRITE_111,
  SPRITE_112,
  SPRITE_VIDEO_CARD,
  SPRITE_114,
  SPRITE_MILLENNIUM_NECKLACE,
  SPRITE_MILLENNIUM_ROD,
  SPRITE_MILLENNIUM_PUZZLE,
  SPRITE_MILLENNIUM_KEY,
  SPRITE_MILLENNIUM_EYE,
  SPRITE_MILLENNIUM_RING,
  SPRITE_MILLENNIUM_SCALE,
  SPRITE_PARA_FLIPPING,
  SPRITE_DOX_FLIPPING,
  SPRITE_MEDIUM_RUBBLE,
  SPRITE_SMALL_RUBBLE,
  SPRITE_BIG_RUBBLE,
  SPRITE_DOX_WITH_MOKUBA,
  SPRITE_128,
  SPRITE_BIG_FIVE,
  SPRITE_TEDDY,
  SPRITE_131,
  SPRITE_132,
  SPRITE_133,
  SPRITE_134,
  SPRITE_135,
  SPRITE_136,
  SPRITE_137,
  SPRITE_138,
  SPRITE_ODION,
  SPRITE_FGD_BODY,
  SPRITE_FGD_MIDDLE_HEAD,
  SPRITE_FGD_TAIL,
  SPRITE_FGD_RIGHT_HEADS,
  SPRITE_FGD_LEFT_HEADS,
  SPRITE_145,
  SPRITE_146,
  SPRITE_147,
  SPRITE_148,
  SPRITE_BUTTERFLY,
  SPRITE_150,
  SPRITE_151,
  SPRITE_YUGI_WITH_MILLENNIUM_PUZZLE
};

enum PortraitPosition {
  PORTRAIT_POSITION_LEFT,
  PORTRAIT_POSITION_RIGHT,
  PORTRAIT_POSITION_OFF_SCREEN,
  PORTRAIT_POSITION_AUTO = 8
};

enum Portrait {
  PORTRAIT_NONE,
  PORTRAIT_TEA = 7,
  PORTRAIT_TRISTAN = 8,
  PORTRAIT_MOKUBA_GRINNING = 10
};

//TODO: create PortraitExpression enum for each character

enum Motion {
  MOTION_STATIONARY,
  MOTION_WALKING,
  MOTION_RUNNING
};

enum OverworldBackground {
  OVERWORLD_BACKGROUND_NORMAL,
  OVERWORLD_BACKGROUND_RESHEF,
  OVERWORLD_BACKGROUND_GOEMON_IMPACT
};

void OverworldMain (void);
void sub_804DF5C (int objectId);
void sub_804EB04 (struct OamData* arg0, u8 arg1);
void sub_804EC4C (void);
void sub_804EC64 (void);
void sub_804ECA8 (void);
void OverworldLoadGraphics (void);

//script structs
struct Script
{
    u8* start;
    struct Script* unk4; // script to execute when flag is cleared/selected yes/duel won...
    struct Script* unk8; // script to execute when flag is set/selected no/duel lost...
};

//TODO: rename to ScriptContext?
struct ScriptCtx {
  unsigned short portraitId;
  u32 pointer; // rename to offset?
  u32 unk8; //current glyph offset?
  u8 unkC;
  u8 unkD;
  struct Script currentScript;
  u16 unk1C; //frame counter for text cursor when waiting for user input
  u8 unk1E; //decides the next script to be executed based on certain outcomes
  u16 unk20;
  u8 unk22[0x52];
  u16 unk74;
  u16 unk76;
  u8 unk78;
  u16 unk7A;
  u16 unk7C;
  u16 unk7E;
  u16 unk80;
  u16 unk82;
  u8 unk84;
  u8 unk85;
  u8 unk86;
};

//TODO: change terminology from Map to Location? (struct OverworldLocation)

//overworld structs
struct Map //MapHeader?
{
    u16 id;
    u16 state;
    u16 unk4; //which connection the player came from?
    u8 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
};

//struct OverworldObject
struct Object
{
    s16 spriteId;
    u8 direction; //facing D L U R
    s16 x; //pos[0]?
    s16 y; //pos[1]?
    s16 unk8;
    u8 unkA;
    u16 unkC;
    u8 unkE;
    u8 unkF;
    struct Script *scriptA;
    struct Script *scriptR;
    unsigned char motionState;
    s16 unk1A;
    u8 unk1C;
    u8 hasShadow : 1;
    u8 facePlayer : 1;
    u8 wander : 1;
    u8 unk1Dl : 1;
    u8 enableBlending : 1;
    u8 unk1E;
};

struct Overworld
{
    struct Map map; //inline instead?
    struct Object objects[15];
    unsigned char unk1F0;
    unsigned char unk1F1;
    unsigned char unk1F2;
    unsigned char unk1F3;
    struct Script *unk1F4[5];
    struct Script *unk208[5];
    signed short unk21C[15];
    unsigned char unk23A;
    u16 *unk23C; //collision data
    unsigned char flags;
    unsigned short music;
    long unk244;
    long unk248;
    s16 unk24C; // used when the screen shakes due to earthquake effect; it modifies the background and sprite y position
    s16 unk24E; // ^same but x position
    enum OverworldBackground background;
};

struct ObjectData {
  signed short spriteId;
  enum Direction direction;
  unsigned short x; //signed short? (also matches)
  unsigned short y; //signed short? (also matches)
  struct Script *scriptA;
  struct Script *scriptR;
  unsigned char hasShadow : 1;
  unsigned char facePlayer : 1;
  unsigned char wander : 1;
  unsigned char unk11; //elevation? modifies y coord of sprite (y -= unk11)
                       //(the higher the value, the higher the sprite is on the screen)
};

struct MapScript
{
    struct Script *unk0;
    unsigned char unk4;  //unused?? //mapid, map connection
    unsigned char unk5;  //unused??
};

struct MapData
{
    struct ObjectData objects[16];  //terminated by a -1 (0xFFFF) spriteId
    struct MapScript unk140[5];
    struct MapScript unk168[5];
    struct ObjectData playerInitialState[5]; //TODO: playerInitialStates? // num_connections (including world map)
    u16 music;
    u8 unk1F6; //bitfield?
};

extern struct Overworld gOverworld;
extern u16* gMapCollisions[]; //gMapCollisionData
extern struct MapData** gMapData[]; //0xE19274

extern unsigned char * gOverworldEntitySprites[];
extern u16 gUnk08103264[];
extern u16 g8103284[];
extern u16 g81032A2[];
extern struct Script* g8F04040;

void sub_8052088(u8); //implicit declaration?
void sub_804DF5C(int);
void sub_804EF10 (void);
void InitiateScript (struct Script *);
u16 sub_80520E0(u8 x, u8 y);
u32 CheckFlag(u32);


void sub_8053388(struct ScriptCtx *script);
void sub_805339C (void);
void sub_80533BC (void);
void sub_8053404 ();  //TODO: implicit declaration
void sub_8053CF0 (u8 obj, s16 x, s16 y, u16 arg3, struct ScriptCtx* script);
void sub_8053D50(u8, u8, struct ScriptCtx *script);
void sub_8053D88(u8, u8, u8, struct ScriptCtx *script);
void sub_8053E34(u8);
inline void sub_8053E94(struct ScriptCtx* script);


extern const u32 g8E0E4CC[];
extern const u32 g8E0E53C[];

void ClearFlag(u32);
void DuelTrunkMenu(void);
void OverworldSetRegDispcnt2(void);



void sub_805345C(u8, u8, u8, u8, struct ScriptCtx *script);
void sub_8034FE0(void);
void sub_8053520(u8, s16, s16, u16, u8, u8, struct ScriptCtx *script);
void sub_8053984(u8, u8, struct ScriptCtx *script);
void sub_8053A74(u8, u8, struct ScriptCtx *script);
void sub_8053884(u16, u8, struct ScriptCtx *script);
void sub_8054AB0(u8, struct ScriptCtx *script);
void sub_804F218(void);


void sub_8053C18(struct ScriptCtx *script, u8);
unsigned sub_80524A4(u16);
void sub_805339C(void);
void OverworldSetRegDispcnt(void);
void sub_8053B40(u8, u16, struct ScriptCtx *script);
void sub_80512E0(struct ScriptCtx *script, u8);

void PlayOverworldMusic (void);


void sub_804F750(u8);

void sub_80523EC(u16, u16, u16);
void sub_0804F76C(void);
void SetFlag(u32);
void SaveGame(void);
void InitiateScript(struct Script *);
void PlayOverworldMusic(void);
void sub_804F5D8(void);

void sub_8035038(u16);


extern u16 g82AD48C[];
extern const u32 g82AD2D0[];

extern u32 gE0E674[];
extern u32 gE0E754[];

s8 sub_8051E48 (u8, u8, u8);
void sub_804F19C (int);



void sub_804F124 (u8 objectId);
void sub_804F254 (void);
void sub_804F054 (int spriteId, int arg1, u8* dest);
void sub_804F1F4 (void);
void SaveLfsrState (u32);

extern u32 g84C9FBC[];
extern u16 g84D0CE0[];
extern u16 g84CFCE0[];
extern u16 g84D04E0[];
extern u32 g84D0EC0[];
extern u16 g84D69D0[];
extern u16 g84D59D0[];
extern u16 g84D61D0[];

extern const unsigned char ShadowTiles[];
extern const unsigned char ReactionBubbleTiles[];

#endif // GUARD_OVERWORLD_H
