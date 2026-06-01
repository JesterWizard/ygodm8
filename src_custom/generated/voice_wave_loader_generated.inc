extern u8 CustomVoice_duke_1_Wave[];
extern u8 CustomVoice_duke_1_Part[];
extern u8 CustomVoice_duke_2_Wave[];
extern u8 CustomVoice_duke_2_Part[];
extern u8 CustomVoice_duke_3_Wave[];
extern u8 CustomVoice_duke_3_Part[];
extern u8 CustomVoice_tristan_1_Wave[];
extern u8 CustomVoice_tristan_1_Part[];
extern u8 CustomVoice_tristan_2_Wave[];
extern u8 CustomVoice_tristan_2_Part[];
extern u8 CustomVoice_tristan_3_Wave[];
extern u8 CustomVoice_tristan_3_Part[];
extern u8 CustomVoice_mai_1_Wave[];
extern u8 CustomVoice_mai_1_Part[];
extern u8 CustomVoice_mai_2_Wave[];
extern u8 CustomVoice_mai_2_Part[];
extern u8 CustomVoice_mai_3_Wave[];
extern u8 CustomVoice_mai_3_Part[];
extern u8 CustomVoice_tea_1_Wave[];
extern u8 CustomVoice_tea_1_Part[];
extern u8 CustomVoice_tea_2_Wave[];
extern u8 CustomVoice_tea_2_Part[];
extern u8 CustomVoice_tea_3_Wave[];
extern u8 CustomVoice_tea_3_Part[];
extern u8 CustomVoice_weevil_1_Wave[];
extern u8 CustomVoice_weevil_1_Part[];
extern u8 CustomVoice_weevil_2_Wave[];
extern u8 CustomVoice_weevil_2_Part[];
extern u8 CustomVoice_weevil_3_Wave[];
extern u8 CustomVoice_weevil_3_Part[];
extern u8 CustomVoice_rex_1_Wave[];
extern u8 CustomVoice_rex_1_Part[];
extern u8 CustomVoice_rex_2_Wave[];
extern u8 CustomVoice_rex_2_Part[];
extern u8 CustomVoice_rex_3_Wave[];
extern u8 CustomVoice_rex_3_Part[];
extern u8 CustomVoice_mako_1_Wave[];
extern u8 CustomVoice_mako_1_Part[];
extern u8 CustomVoice_mako_2_Wave[];
extern u8 CustomVoice_mako_2_Part[];
extern u8 CustomVoice_mako_3_Wave[];
extern u8 CustomVoice_mako_3_Part[];
extern u8 CustomVoice_dark_marik_1_Wave[];
extern u8 CustomVoice_dark_marik_1_Part[];
extern u8 CustomVoice_dark_marik_2_Wave[];
extern u8 CustomVoice_dark_marik_2_Part[];
extern u8 CustomVoice_dark_marik_3_Wave[];
extern u8 CustomVoice_dark_marik_3_Part[];
extern u8 CustomVoice_dark_bakura_1_Wave[];
extern u8 CustomVoice_dark_bakura_1_Part[];
extern u8 CustomVoice_dark_bakura_2_Wave[];
extern u8 CustomVoice_dark_bakura_2_Part[];
extern u8 CustomVoice_dark_bakura_3_Wave[];
extern u8 CustomVoice_dark_bakura_3_Part[];
extern u8 CustomVoice_bandit_keith_1_Wave[];
extern u8 CustomVoice_bandit_keith_1_Part[];
extern u8 CustomVoice_bandit_keith_2_Wave[];
extern u8 CustomVoice_bandit_keith_2_Part[];
extern u8 CustomVoice_bandit_keith_3_Wave[];
extern u8 CustomVoice_bandit_keith_3_Part[];

struct CustomVoiceRomClip {
  const struct WaveData *dpcmWave;
  const u8 *partTrack;
};

static const struct CustomVoiceRomClip sCustomVoiceRomClips[] APPEND_RODATA = {
  { (const struct WaveData *)&CustomVoice_duke_1_Wave, CustomVoice_duke_1_Part },
  { (const struct WaveData *)&CustomVoice_duke_2_Wave, CustomVoice_duke_2_Part },
  { (const struct WaveData *)&CustomVoice_duke_3_Wave, CustomVoice_duke_3_Part },
  { (const struct WaveData *)&CustomVoice_tristan_1_Wave, CustomVoice_tristan_1_Part },
  { (const struct WaveData *)&CustomVoice_tristan_2_Wave, CustomVoice_tristan_2_Part },
  { (const struct WaveData *)&CustomVoice_tristan_3_Wave, CustomVoice_tristan_3_Part },
  { (const struct WaveData *)&CustomVoice_mai_1_Wave, CustomVoice_mai_1_Part },
  { (const struct WaveData *)&CustomVoice_mai_2_Wave, CustomVoice_mai_2_Part },
  { (const struct WaveData *)&CustomVoice_mai_3_Wave, CustomVoice_mai_3_Part },
  { (const struct WaveData *)&CustomVoice_tea_1_Wave, CustomVoice_tea_1_Part },
  { (const struct WaveData *)&CustomVoice_tea_2_Wave, CustomVoice_tea_2_Part },
  { (const struct WaveData *)&CustomVoice_tea_3_Wave, CustomVoice_tea_3_Part },
  { (const struct WaveData *)&CustomVoice_weevil_1_Wave, CustomVoice_weevil_1_Part },
  { (const struct WaveData *)&CustomVoice_weevil_2_Wave, CustomVoice_weevil_2_Part },
  { (const struct WaveData *)&CustomVoice_weevil_3_Wave, CustomVoice_weevil_3_Part },
  { (const struct WaveData *)&CustomVoice_rex_1_Wave, CustomVoice_rex_1_Part },
  { (const struct WaveData *)&CustomVoice_rex_2_Wave, CustomVoice_rex_2_Part },
  { (const struct WaveData *)&CustomVoice_rex_3_Wave, CustomVoice_rex_3_Part },
  { (const struct WaveData *)&CustomVoice_mako_1_Wave, CustomVoice_mako_1_Part },
  { (const struct WaveData *)&CustomVoice_mako_2_Wave, CustomVoice_mako_2_Part },
  { (const struct WaveData *)&CustomVoice_mako_3_Wave, CustomVoice_mako_3_Part },
  { (const struct WaveData *)&CustomVoice_dark_marik_1_Wave, CustomVoice_dark_marik_1_Part },
  { (const struct WaveData *)&CustomVoice_dark_marik_2_Wave, CustomVoice_dark_marik_2_Part },
  { (const struct WaveData *)&CustomVoice_dark_marik_3_Wave, CustomVoice_dark_marik_3_Part },
  { (const struct WaveData *)&CustomVoice_dark_bakura_1_Wave, CustomVoice_dark_bakura_1_Part },
  { (const struct WaveData *)&CustomVoice_dark_bakura_2_Wave, CustomVoice_dark_bakura_2_Part },
  { (const struct WaveData *)&CustomVoice_dark_bakura_3_Wave, CustomVoice_dark_bakura_3_Part },
  { (const struct WaveData *)&CustomVoice_bandit_keith_1_Wave, CustomVoice_bandit_keith_1_Part },
  { (const struct WaveData *)&CustomVoice_bandit_keith_2_Wave, CustomVoice_bandit_keith_2_Part },
  { (const struct WaveData *)&CustomVoice_bandit_keith_3_Wave, CustomVoice_bandit_keith_3_Part },
};
