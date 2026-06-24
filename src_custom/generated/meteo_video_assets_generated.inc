/* Generated — do not edit.
 *
 * If src_custom/assets/videos/intro.bin exists, it is embedded in
 * the .meteo_video section and sMeteoVideoData points to it.
 * Otherwise sMeteoVideoData is still defined (empty section) so the
 * assembly stub links; the C gate (METE0_VIDEO_AVAILABLE) prevents calls.
 */

#if __has_include("src_custom/assets/videos/intro.bin")

__asm__(".section .meteo_video, \"a\"\n"
        ".global sMeteoVideoData\n"
        ".balign 4\n"
        "sMeteoVideoData:\n"
        ".incbin \"src_custom/assets/videos/intro.bin\"\n"
        ".size sMeteoVideoData, . - sMeteoVideoData\n"
        ".previous\n");
extern const u8 sMeteoVideoData[];
#define METE0_VIDEO_AVAILABLE 1

#else

/* Define the symbol so the ARM stub links even without the blob. */
__asm__(".section .meteo_video, \"a\"\n"
        ".global sMeteoVideoData\n"
        "sMeteoVideoData = 0x08000000\n"  /* dummy — never dereferenced */
        ".previous\n");
#define METE0_VIDEO_AVAILABLE 0

#endif
