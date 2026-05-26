# Password Terminal Feedback

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The password terminal now gives explicit UI feedback after the player confirms a password. Valid passwords show an accepted popup and then charge the player. Invalid passwords show a rejected popup and do not take money.

The feature is controlled by `gRuntimeConfig.enable_password_terminal_feedback` in `configs/runtime.c`.

## Plan

The feature replaces the original password result flow with a guarded custom path:

| State | Popup | Money |
|------|-------|-------|
| Config disabled | None | Original upfront terminal charge |
| Valid card password | `Password accepted.` | Charge after validation |
| Valid special password | `Password accepted.` | Charge after validation |
| Invalid password | `Password not found.` | No charge |

The popup uses the link duel arena frame assets, but splits rendering across backgrounds:

| Layer | Purpose | Notes |
|------|---------|-------|
| BG0 | Result text | Uses generated text tiles in `sbb1E` |
| BG1 | Link duel popup frame | Uses `gDE7888`, `gDEDF50`, and `sbb1D` |
| BG3 | Password terminal | Remains visible behind the popup |

The popup palettes are moved away from the terminal palettes. The link duel frame is remapped to BG palette 14, and the popup text uses BG palette 15. This prevents the password button numbers from changing color while the popup is visible.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `gRuntimeConfig.enable_password_terminal_feedback` in `configs/runtime.c` | Enables or disables the popup feedback path |
| Config field | `RuntimeConfig` in `configs/runtime.h` | Stores the build-time feature toggle |
| Terminal charge hook | `sub_8054AB0__Replacement` in `src_custom/script_commands2_hooks.c` | Skips the original upfront charge when feedback is enabled |
| Password lookup guard | `SearchForMatchingCard__Replacement` in `src_custom/card_password_hooks.c` | Bounds card password scanning to avoid invalid-password softlocks |
| Popup rendering | `DrawPasswordFeedbackBgs` in `src_custom/card_password_hooks.c` | Draws BG0 text and BG1 link duel frame |
| Result handling | `CardPasswordMain__Replacement` in `src_custom/card_password_hooks.c` | Shows feedback and charges only after valid password matches |
| Hook wiring | `src_custom/LynJump.event` | Redirects vanilla functions to custom replacements |