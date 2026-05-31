struct CustomVoiceAssetLoad {
  const u8 *romPart;
  u16 partOffset;
  u16 headerOffset;
  u8 songIndex;
};

extern const u8 CustomVoice_duke_turn_start_Part[];

static const struct CustomVoiceAssetLoad sCustomVoiceAssetLoads[] APPEND_RODATA = {
  {CustomVoice_duke_turn_start_Part, 0, 16, 0},
};
