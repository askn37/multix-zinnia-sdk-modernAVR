# Bootloaders for modernAVR

- optiboot_dx2 -- ブートローダーソース群（AVR_DA/DB/DD用）
- optiboot_ex1 -- ブートローダーソース群（AVR_EA用）
- empty -- 空のダミーHEXだけがある
- hex -- ビルド済のブートローダーHEXファイル群
（Arduino IDE サブメニューから選択される）

このフォルダ以下に含まれる
`optiboot_dx2`は
`optiboot`ver.8 を原型とするが、実体は大きく異なる。

> [[megaAVR / tinyAVR系統用ブートローダー]はこちら](https://github.com/askn37/multix-zinnia-sdk-megaAVR/tree/main/bootloaders)

## optiboot_dx2

これは __AVR_DA/DB/DD__ 系統用の NVM v2仕様ブートローダーだ。
`DxCore`版と似ているが以下の点で異なる。

- マクロ`APP_NOSPM`が無効でビルドされた場合、
PGMEMアドレス`PROGMEM_START+2`以降にSPM命令群スニペットが配置される。
既定で有効。
- マクロ`RS485`が有効でビルドされる場合、
周辺機能USARTによるRS485機能の`XDIR`ペリフェラルピン出力が有効になる。
（原型はGPIO操作で`RS485_XDIR`を制御していた。）
- マクロ`USART`が有効でビルドされる場合、
同期従装置USARTが有効になり`XCK`ペリフェラルピンで外部同期クロックを受給できるようになる。
`XCK`ピンは該当USART周辺機能固定となるので任意には変更できない。
- EEPROM領域リード/ライトに対応。

__AVR_DA/DB/DD__ 系統の全品種でバイナリは原則共通だ。
HEXフォルダには主だったUART/LED違いのバリエーションが置かれている。
（DxCore版は品種別にバイナリが異なる）

> 28pin以上の品種用は
```TX:PA0```
```RX:PA1```
```LED:PA7```
で基本的に統一されている。\
> 小ピン品種ではこの設定はできないので
バリエーションがある。

## optiboot_ex1

これは __AVR_EA__ 系統用の NVM v3仕様ブートローダーだ。
`optiboot_dx2`と機能は同等だが、主クロック制御器とSPMスニペットは
`megaAVR`用の`optiboot_x2`に準じている。

## EEPROM書込＋検証

Arduino IDE サブメニューの
`FUSE EEPROM`\>`"Erase" and "Replace"`
を選択すると、
EEPROM領域をスケッチと同時に書くことが出来る。

```c
#include <avr/eeprom.h>
char estring[] EEMEM = "0123456789ABCDEF";  // <-- HERE
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
|megaAVR-0 , tinyAVR-0/1/2, AVR_EA|MAPPED_PROGMEM_START + 2 Byte|0xE99DC009|
|AVR_DA/DB/DD|PROGMEM_START + 2 Byte|0x950895F8|

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
|$01FE|OPTIBOOT_MINVER|0x02|
|$01FF|OPTIBOOT_MAJVER|0x29|

## リビルド

詳細は`makeall.*.sh`や
`parse_options.mk`を参照のこと。
それぞれのカレントディレクトリで
次のようにすれば`hex`フォルダが更新される。

```c
optiboot_dx2> sh makeall.modernAVR.sh
optiboot_ex1> sh makeall.modernAVR.sh
```

> Windows環境での確認はされていない。（要makeコマンド）

## コーディング

原型の optiboot は可能な限りアセンブリコードは含まない方針で設計されていたが、
ここでは少しでもROMサイズを削るため書込処理部で幾らか多めのアセンブリコードを含んでいる。

### フラッシュメモリの最大ブロックサイズ

このコードでは`memory "flash"`において送受信とも最大512バイト＝256ワードに対応している。
端数の奇数バイト量は偶数バイト量に切り詰められる。
しかし`readsize=0x200`指定は他の実装`SerialUPDI`等の動作が異常をきたすので
`readsize=0x100`と指示するのが正しい。

> `AVR_DA/DB/DD`での書込操作は 512Byte単位が最小粒度かつ必須なので、どの書込機でも対応している。

### EEPROMの最小粒度

このコードでのこれは最小1バイトに対応している。
しかし`page_size=1`とすると *avrdude* はフューズ領域操作と混同して異常動作を起こす。
真にEEPROMバイト書込が可能な`AVR_DA/DB/DD`では、嘘でもこれを2以上にしなければならない。

> `AVR_DA/DB/DD`での粒度は`page_size=16`である。\
> `AVR_EA`での粒度は`page_size=8`である。

### BIGBOOT

`BIGBOOT`ビルドが無効の場合、以下のコードを削る。

- `CLKCTRL_MCLKCTRLA`を設定しない。`BIGBOOT`ビルドでは再設定される。
- 書込と検証完了後の`STK_LEAVE_PROGMODE`動作で`WDT_CTRLA`を再設定しない。
`BIGBOOT`ビルドでは設定される。
- `STK_UNIVERSAL`のサブパラメータ`AVR_OP_LOAD_EXT_ADDR`の確認を省略する。`BIGBOOT`ビルドでは正しく確認される。（後述）

### FUSE_OSCCFG

`BIGBOOT`ビルドでない場合、
`CLKCTRL_MCLKCTRLA`を設定しない。
従って`FUSE_OSCFG`による`OSC32K`設定を覆さない。
故にこのフューズが`OSCHF`でない場合は、正しく動作しない。

> ボードサブメニューの`Clock`設定`OSCULP`選択はフューズを書かず、
CPU起動後に初期化コード内で`CLKCTRL_MCLKCTRLA`を設定するようになっている。

### USART[n]_BAUD

書き込むべき値が256未満の場合、下位レジスタ`BAUDL`だけを書く。
`FUSE_OSCCFG`選択が`OSCHF`であるなら既定の`CLK_PER`は4MHzであるから
コンパイル時定数`BAUD_RATE`が`62501L`以上である限り、上位レジスタ`BAUDH`はゼロ初期化値のままと扱う。

> 4MHz駆動の`optiboot_dx2`であれば`62500L`以下を指定すると 4Byteを追加消費する。

### RAMPZ (optiboot_dx2)

コンパイル時の指定品種に関わらず`RAMPZ`すなわち`_SFR_MEM8(0x3B)`レジスタの書込可能なビットは、
それが必要とされる品種に対し、必要な量だけが実装されているものとする。
従って17bit目のアドレスは常にここに書く。
そしてその必要のない品種では結果的に無視される。

> これを考慮すると 64KiB以下品種用はより小さな別バイナリを作れるが、それ専用となる。\
> `AVR_EA`系統は最大64KiBのため、RAMPZは削除されている。

### STK_UNIVERSAL (optiboot_dx2)

`BIGBOOT`ビルドでない場合、
この`STK500`指令は`RAMPZ`のある品種についてのみ出現すると仮定している。
かつそれは必ず`AVR_OP_LOAD_EXT_ADDR`指令であるとも仮定している。

> 従って`AVR_DA/DB/DD`用以外はコードが削除されている。

### RAMSIZE (optiboot_dx2)

`RAMSIZE`値はコンパイル時の指定品種に関わらず `1024`（`RAMSTART`位置が`RAMEND-1023`）であると仮定する。
これは現在公開されている既知のスペックシート中の最低値`2048`より十分低い。
それを`256+512+256`バイトに分けて、`作業メモリ+NVM書換バッファ+スタック`領域として扱う。

### SIGROW_DEVICEID0

`SIGROW_DEVICEID0`すなわち`_SFR_MEM8(0x1100)`は全てのAVRで固定の値`0x1E`を返す。従ってこれは読み出さない。

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
