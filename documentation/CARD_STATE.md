# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Mini art 22×22 + 159 ring (vanilla layout)

**Files touched:**
- `tools/add_card_art.py` — `make_paletted_mini`: resize to 22×22, paste on 159-filled 24×24 (no edge-crop)
- `build/cards/24x24/*.lz` — all 595 regenerated

**Outcome:** Matches vanilla cards 1–100: 1px index-159 outline, art fills inner 22×22. Prior “paint 159 over 24×24” cropped art. `make` exits 0.

**Open / next:** In-game confirm custom + synchro field minis vs vanilla size/border.
