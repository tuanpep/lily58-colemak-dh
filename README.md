# Lily58 Colemak-DH firmware

Drop-in keymap for a Lily58 split keyboard. Base layer is **Colemak-DH (matrix)**.
A QWERTY layer is included for games and shared machines.

Keep the **operating system keyboard layout on US QWERTY**. The firmware does
the Colemak-DH remapping. If the OS is also set to Colemak, letters will be
wrong.

## Layout

### Base — Colemak-DH

```
ESC   1  2  3  4  5                    6  7  8  9  0  `
TAB   Q  W  F  P  B                    J  L  U  Y  ;  -
CTRL  A  R  S  T  G                    M  N  E  I  O  '
SFT   Z  X  C  D  V   [          ]     K  H  ,  .  /  SFT
            ALT  GUI  LOWER  SPC    ENT  RAISE  BSPC  GUI
```

This is the ortho / column-stagger Colemak-DH arrangement (no ANSI angle-mod).
That is the correct variant for Lily58.

### Lower (hold LOWER)

Function keys on the number row, symbols on the home / bottom rows.

### Raise (hold RAISE)

Home / PgDn / PgUp / End on the right top-letter row.
Arrows on the right home row: Left Down Up Right.
Media keys on the right bottom row.

### Adjust (hold LOWER + RAISE together) — QMK only

| Key | Action |
| --- | --- |
| Esc or ` | Bootloader on that half |
| Q | Make QWERTY the default layer |
| A | Make Colemak-DH the default layer |
| T | Toggle QWERTY on top of Colemak (temporary) |

### QWERTY layer

Same modifiers and thumbs as base. Letters are standard QWERTY.

## Which package to use

| Your Lily58 | Use |
| --- | --- |
| Wired Pro Micro / Elite-C / RP2040 | `qmk/` |
| Wireless Nice!Nano or other ZMK controller | `zmk/` |

Common QMK keyboard targets:

- Classic Lily58 Pro / Rev1: `lily58/rev1`
- Lily58 Light: `lily58/light`
- RP2040 drop-in Pro Micro: add `-e CONVERT_TO=promicro_rp2040`

## Flash with QMK (wired)

1. Install QMK: https://docs.qmk.fm/newbs

2. Copy this keymap into your QMK tree:

```
qmk_firmware/keyboards/lily58/keymaps/colemak_dh/
    keymap.c
    config.h
    rules.mk
```

3. Compile and flash **one half at a time**. Unplug the TRRS cable first.

Pro Micro / ATmega32U4:

```
qmk compile -kb lily58/rev1 -km colemak_dh
qmk flash   -kb lily58/rev1 -km colemak_dh
```

RP2040 (copy the `.uf2` onto the `RPI-RP2` drive that appears after reset):

```
qmk compile -kb lily58/rev1 -km colemak_dh -e CONVERT_TO=promicro_rp2040
```

Double-tap reset on the half you are flashing. Repeat for the other half.

### Compile in the browser instead

1. Open https://config.qmk.fm/#/lily58/rev1/LAYOUT
2. Import `qmk/keymap.json`
3. Compile and download the `.hex` / `.uf2`
4. Flash with QMK Toolbox

The JSON file has Colemak-DH, QWERTY, Lower, and Raise. The C keymap also has
the Adjust tri-layer and OLED text.

## Flash with ZMK (wireless)

1. Fork https://github.com/zmkfirmware/zmk-config or your existing Lily58 config
2. Replace `config/lily58.keymap` with `zmk/lily58.keymap`
3. Push. GitHub Actions builds `lily58_left-nice_nano_v2-zmk.uf2` (name varies)
4. Put each Nice!Nano in bootloader (double-tap reset) and copy the matching uf2

On Lower:

- bottom-left `Z` position: jump to Colemak-DH
- bottom-left `X` position: jump to QWERTY
- Bluetooth profiles on the rest of that row
- top-left: clear Bluetooth bonds

## No OLED?

In `qmk/rules.mk` set:

```
OLED_ENABLE = no
```

## No underglow / RGB

Already off. Turn `RGBLIGHT_ENABLE = yes` only if your PCB has LEDs.

## Learning Colemak-DH

Home row is `A R S T G` / `M N E I O`.
`D` and `H` sit on the bottom row under the index fingers — that is the DH
change, and it is why this layout fits a column-stagger board.

Practice on https://monkeytype.com with layout set to Colemak and custom
remap, or use keybr / colemak.academy. Expect 1–3 weeks before daily work
feels natural if you already touch-type QWERTY.
