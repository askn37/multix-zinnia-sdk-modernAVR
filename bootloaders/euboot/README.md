# euboot -- EDBG USB bootloader for AVR-DU series

## 機能

- AVR-DU シリーズ専用 USB ブートローダー。
- 標準 USB-HID/CMSIS-DAP/EDBG プロトコルを使用し、AVRDUDE<=8.0 からは `jtag3updi` デバイスとして認識される。
- USB Full-Speed の上限に近い、高速なメモリの読み書き速度。
- フットプリントは 2.5KiB 未満。

## 添付バイナリ

- hex/euboot_LA7_SF6.hex - LED=PA7, SW=PF6 - 20pin以上の一般用途
- hex/euboot_LC3_SF6.hex - LED=PC3, SW=PF6 - 14pinを含む全種対応
- hex/euboot_LF2_SF6.hex - LED=PF2(INVERT), SW=PF6 - AVR64DU32 CURIOSITY NANO 用

詳細およびバイナリビルド方法については、[[euboot (EDBG USB bootloaders) for AVR-DU series]](https://github.com/askn37/euboot) を参照のこと。

## Copyright and Contact

Twitter(X): [@askn37](https://twitter.com/askn37) \
BlueSky Social: [@multix.jp](https://bsky.app/profile/multix.jp) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
