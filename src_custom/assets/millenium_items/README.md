# Status menu millennium item icons

Indexed **32×32** PNGs for the seven Millennium Items shown on the field Status screen.

| File | Item |
|------|------|
| `puzzle.png` | Millennium Puzzle |
| `ring.png` | Millennium Ring |
| `key.png` | Millennium Key |
| `scale.png` | Millennium Scale |
| `rod.png` | Millennium Rod |
| `eye.png` | Millennium Eye |
| `necklace.png` | Millennium Necklace |

## Regenerating from overworld sprites

```bash
python3 tools/export_millennium_item_pngs.py
make all
```

Export reads `src/overworld/entities/115.4bpp` … `121.4bpp` and writes PNGs here. Edit PNGs manually if needed, then rebuild so `tools/generate_millennium_item_assets.py` embeds them for `src_custom/status_menu_hooks.c`.

All icons must share the same 16-color indexed palette (mode `P`).
