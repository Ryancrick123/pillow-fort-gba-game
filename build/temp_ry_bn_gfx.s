
@{{BLOCK(temp_ry_bn_gfx)

@=======================================================================
@
@	temp_ry_bn_gfx, 16x32@4, 
@	+ palette 16 entries, not compressed
@	+ 8 tiles Metatiled by 2x4 not compressed
@	Total size: 32 + 256 = 288
@
@	Time-stamp: 2025-01-26, 02:45:42
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global temp_ry_bn_gfxTiles		@ 256 unsigned chars
	.hidden temp_ry_bn_gfxTiles
temp_ry_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0xD0000000,0xDDD00000,0xDDDE0000,0xDDDDD000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x000000ED,0x00000EED,0x0000DEDD,0x000DD5DD
	.word 0x395DD000,0x8395D000,0x8695D000,0x8A39D000,0x8839D000,0x88890000,0xBBCB7000,0xBBC4B700
	.word 0x000D9D59,0x0009D593,0x00095968,0x000559A8,0x000D9388,0x00009888,0x000B7CBB,0x00B22CBB
	.word 0xB994B200,0x99948800,0x99948800,0x999C8800,0x99918800,0x999C8800,0x9CCC8800,0xC99C8000
	.word 0x00B22C9B,0x00882999,0x00882999,0x0088C999,0x0088C999,0x00881999,0x00881CC9,0x0008199C
	.word 0x999C0000,0x999C0000,0x099C0000,0x099C0000,0x09980000,0x08820000,0x02222000,0x07772000
	.word 0x0000C999,0x00009999,0x0000C9C0,0x0000CCC0,0x00008CC0,0x00002880,0x00022220,0x00027770

	.section .rodata
	.align	2
	.global temp_ry_bn_gfxPal		@ 32 unsigned chars
	.hidden temp_ry_bn_gfxPal
temp_ry_bn_gfxPal:
	.hword 0x0000,0x1CA8,0x4DEA,0x35F7,0x30E7,0x2951,0x6BBF,0x5ACD
	.hword 0x429A,0x24EF,0x1465,0x4149,0x24ED,0x2935,0x3DF8,0x0000

@}}BLOCK(temp_ry_bn_gfx)
