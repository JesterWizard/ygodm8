    .section .rodata

@ RAM map for current shop / trunk / deck state.
@ Addresses come from ldscript.ld and are kept here as a quick reference.
@ End points are inclusive.

@ --------------------------------------------------------------------
@ Trunk / global menu state
@ --------------------------------------------------------------------

@ gRepeatedOrNewButtons : 0x02020DF4 - 0x02020DF5
@ gPressedButtons       : 0x02020DF8 - 0x02020DF9
@ gNewButtons           : 0x02020DFC - 0x02020DFD
@ gRepeatedButtonsCounter: 0x02020E04 - 0x02020E05

@ gTrunkMenu            : 0x02020E10 - 0x02021459
@ gTotalCardQty         : 0x02021460 - 0x0202178F
@ gTrunkCardQty         : 0x02021790 - 0x02021AB3
@ gUnk2021AB4           : 0x02021AB4 - 0x02021AB7

@ --------------------------------------------------------------------
@ Shop state
@ --------------------------------------------------------------------

@ gShopCardQty          : 0x02021DF0 - 0x0202211F
@ gShopTempCardQty      : 0x02022120 - 0x0202244F
@ sCardShop             : 0x02022450 - 0x02022B7F
@ gPlayerTempCardQty    : 0x02022B80 - 0x02022EAF

@ --------------------------------------------------------------------
@ Deck state
@ --------------------------------------------------------------------

@ gCardSortContext      : 0x02022EB0 - 0x02022EBB
@ gDeckMenu             : 0x02021C30 - 0x02021C8B

@ --------------------------------------------------------------------
@ Notes
@ --------------------------------------------------------------------

@ The deck menu block sits earlier in RAM than the shop block.
@ That is intentional in the current linker layout.

@ --------------------------------------------------------------------
@ Free gaps in the current linker layout
@ --------------------------------------------------------------------

@ 0x02020E06 - 0x02020E0F : gap between input state and gTrunkMenu
@ 0x02021AB8 - 0x02021C2F : gap between trunk quantities and gDeckMenu
@ 0x02021C8C - 0x02021DEF : gap between gDeckMenu and gShopCardQty

@ Note: these are linker-layout gaps, not runtime-audited scratch RAM.
