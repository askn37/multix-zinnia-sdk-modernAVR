# bootloaders

- optiboot_x2 -- ブートローダーソース群（megaAVR用）
- optiboot_dx2 -- ブートローダーソース群（modernAVR用）
- empty -- 空のダミーHEXだけがある
- hex -- ビルド済のブートローダーHEXファイル群
（Arduino IDE サブメニューから選択される）

このフォルダ以下に含まれる
`optiboot_x2`または
`optiboot_dx2`は
`optiboot`ver.8 を原型とするが、実体は大きく異なる。

## optiboot_x2

これは megaAVR/tinyAVR系統用の NVM v1仕様ブートローダーだ。
ほぼ`MCUdude`版に似るが以下の点で異なる。

- マクロ`APP_NOSPM`が有効でビルドされた場合、
PGMEMアドレス`MAPPED_PROGMEM_START+2`以降にSPM命令群スニペットが配置される。
既定で有効。
- マクロ`RS485`が有効でビルドされる場合、
周辺機能USARTによるRS485機能の`XDIR`ペリフェラルピン出力が有効になる。
（原型はGPIO操作で`RS485_XDIR`を制御していた。）
- マクロ`USART`が有効でビルドされる場合、
同期従装置USARTが有効になり`XCK`ペリフェラルピンで外部同期クロックを受給できるようになる。
`XCK`ピンは該当USART周辺機能固定となるので任意には変更できない。
- EEPROM領域リード/ライトに対応。

`megaAVR` `tinyAVR`各系統の全品種でバイナリは原則共通だ。
HEXフォルダには主だったUART/LED違いのバリエーションが置かれている。

> 28pin以上の品種は
```TX:PA0```
```RX:PA1```
```LED:PA7```
で基本的に統一されている。\
> 小ピン品種ではこの設定はできないので
バリエーションがある。

## optiboot_dx2

これは AVR DA/DB/DD/EA系統用の NVM v2仕様ブートローダーだ。
`DxCore`版と似ているが以下の点で異なる。

- マクロ`APP_NOSPM`が有効でビルドされた場合、
PGMEMアドレス`PROGMEM_START+2`以降にSPM命令群スニペットが配置される。
既定で有効。
- マクロ`RS485`が有効でビルドされる場合、
周辺機能USARTによるRS485機能の`XDIR`ペリフェラルピン出力が有効になる。
（原型はGPIO操作で`RS485_XDIR`を制御していた。）
- マクロ`USART`が有効でビルドされる場合、
同期従装置USARTが有効になり`XCK`ペリフェラルピンで外部同期クロックを受給できるようになる。
`XCK`ピンは該当USART周辺機能固定となるので任意には変更できない。
- EEPROM領域リード/ライトに対応。
- `STK_GET_PARAMETER`コマンドに対して
`not BIGBOOT`ビルドでは常にダミー値（0x03固定）を返す。
`BIGBOOT`ビルドでは正しく`optiboot`バージョンを返す。

AVR DA/DB/DD系統の全品種でバイナリは原則共通だ。
HEXフォルダには主だったUART/LED違いのバリエーションが置かれている。
（DxCore版は品種別にバイナリが異なる）

> 28pin以上の品種は
```TX:PA0```
```RX:PA1```
```LED:PA7```
で基本的に統一されている。\
> 小ピン品種ではこの設定はできないので
バリエーションがある。

## EEPROM書込＋検証

Arduino IDE サブメニューの
`FUSE EEPROM`\>`"Erase" and "Replace"`
を選択すると、
EEPROM領域をスケッチと同時に書くことが出来る。

```c
#include <avr/eeprom.h>
char estring[] EEMEM = "0123456789ABVDEF";  // <-- HERE
```

その後`Save guard "Retained"`とした場合、
新たなスケッチを書き込んでも
EEPROMは以前に書き込んだ状態を維持する。

この状態は
`Save guard "Erase"`
として消去するか、
`"Erase" and "Replace"`
として改めて書き込み直すまで変わらない。

> EEPROM領域量は MCU品種によって異なる。
その大きさはマクロ`EEPROM_SIZE`で知ることが出来る。

- この機能は`MCUdude`版と運用互換性がある。
- この機能は`DxCore`版には実装されていない。

## SPMスニペット

以下の PGMEMアドレスに、この機能が有効なら以下の固定値が書かれている。

|Series|Address|マジックナンバー : uint32_t (LE)|
|-|-|-|
|megaAVR-0 , tinyAVR-0/1/2|MAPPED_PROGMEM_START + 2 Byte|0xE99DC009|
|AVR DA/DB/DD|PROGMEM_START + 2 Byte|0x950895F8|

これらは
BOOT領域保護特権で
CODE領域 / APPEND領域の
FLASH消去/書換を行うのに使うことが出来る。

- `MCUdude`版や`DxCore`版の同種の機能とは仕様が異なり、相互に互換性はない。

> 実際の使用例は
[FlashNVM_sample](https://github.com/askn37/MacroMicroAPI_lib/tree/b5d0d734ce43017d904106a845f7fc4c8ccb3f91/examples/EEPROM%20and%20NVM/FlashNVM_sample)
を参照のこと。



## optibootバージョン

以下の PGMEMアドレスに固定値が書かれている。

|ADDR|NAME|内容|
|----|----|---|
|$01AE|OPTIBOOT_MINVER|0x02|
|$01AF|OPTIBOOT_MAJVER|0x29|

## リビルド

詳細は```makeall.*.sh```や
```parse_options.mk```を参照のこと。
それぞれのカレントディレクトリで
次のようにすれば```hex```フォルダが更新される。

```c
optiboot_x2> sh makeall.megaAVR.sh
optiboot_dx2> sh makeall.modernAVR.sh
```

> Windows環境での動作確認はされていない。（要makeコマンド）

## 著作表示

optibootは GPL v2 で提供されているため、これもまたそれに準じる。

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp

----

Notes on GPLv2 WRT the Optiboot bootloader:

In general, it can be hard to interpret exactly how the GPL license
applies to microcontroller embedded software.  Assumptions about
logically distinct applications, oepratnig systems, dynamically loaded
libraries, and the end-user ability to re-compile, re-link, or
re-install, don't quite "fit."

There is a "Bootloader Exception" which seems applicable and I've
included below, but it's current use seems to be in the PyInstaller
utility, which is still very far from a Flashed microcontroller bootloader.

The INTENT of the Optiboot maintainers is that Optiboot may be treated
much like the operating system on a larger computer, and that it's
GPLv2 status has no effect on the application itself.  That means that
there are no restrictions to using Optiboot with commercial, closed
source, or proprietary applications, and no "viral OSSW" infection of
any applications by the bootloader.  The only requirement is that
fixes and enhancements to Optiboot itself be fed back to the Optiboot
project.

Bootloader Exception

In addition to the permissions in the GNU General Public License, the
authors give you unlimited permission to link or embed compiled
bootloader and related files into combinations with other programs,
and to distribute those combinations without any restriction coming
from the use of those files. (The General Public License restrictions
do apply in other respects; for example, they cover modification of
the files, and distribution when not linked into a combined
executable.)
