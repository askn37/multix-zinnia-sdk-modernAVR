# Bootloaders for modernAVR

- *boot_ax -- ブートローダーソース群（tinyAVR-0/1/2、megaAVR-0用）*
- boot_dx -- ブートローダーソース群（AVR_DA/DB/DD用）
- boot_ex -- ブートローダーソース群（AVR_EA/EB用）
- empty -- 空のダミーHEXだけがある
- bin -- ビルド済のブートローダーBINファイル群
- hex -- ビルド済のブートローダーHEXファイル群
（Arduino IDE サブメニューから選択される）

> [megaAVR / tinyAVR系統用ブートローダー]（boot_ax）は[こちら](https://github.com/askn37/multix-zinnia-sdk-megaAVR/tree/main/bootloaders)

## 概要

この moderAVR 用ブートストラップローダー・ファームウェアは ATMEL STK500 version 1 プロトコルに基づいており、Arduino ブートローダーと完全な互換性がある。

ファームウェアが起動すると、RESET情報フラグが点検され、WDT またはソフトウェアリセットの場合、アプリケーションコード (0x200 から始まる) がすぐに実行を開始する。それ以外ではタイムアウト期間内に有効な STK500 version 1 コマンドが受信されたならば、UART を開いて NVM 操作を開始する。

ビルドは AVR-GCC および AVR-LIBC で可能だが、他のコンパイラに付いては考慮されていない。バイナリコードは 512バイト以内におさまる。

過去のソースコードは`Optiboot`のクローンであったが、現在はそうではない。彼らの支援対象は原則としてより古い世代のデバイスだけである。そうした理由により、ここで公開されているソースコードは改めて書き起こされた。

使用許諾と再配布には MIT ライセンスが適用される。

### boot_ax.c

これは __tinyAVR-0/1/2__ 系統と __megaAVR-0__ 系統用の NVMCTRL version 0 仕様に適合するブートローダーだ。
生成されるバイナリは対応全品種に共通してインストール可能であり、バリエーションは UARTや LEDの選択違いだけである。
EEPROM は バイト粒度で、リード 256 byte、ライト 32 byte または 64 byte に対応する。
FLASH は最大容量 48 KiB、ワード粒度で、リード 256 byte、ライト 64 byte または 128 byte に対応する。

> この系統は BOOTCODE 粒度が 256 byte なので、FUSE_BOOTSIZE（fuse8）には `2` を指定する。

### boot_dx.c

これは __AVR_DA/DB/DD__ 系統用の NVMCTRL version 2 仕様に適合するブートローダーだ。
生成されるバイナリは __AVR_DA/DB/DD__ 系統の全品種に共通してインストール可能であり、バリエーションは UARTや LEDの選択違いだけである。
EEPROM は バイト粒度で、リード 256 byte、ライト 2 byte に対応する。
FLASH は最大容量 128 KiB、ワード粒度で、リード 512 byte、ライト 512 byte に対応する。

> この系統は BOOTCODE 粒度が 512 byte なので、FUSE_BOOTSIZE（fuse8）には `1` を指定する。

### boot_ex.c

これは __AVR_EA__ 系統用の NVMCTRL version 3 仕様と、
これは __AVR_EB__ 系統用の NVMCTRL version 5 仕様に適合するブートローダーだ。両者の差は僅かなので、同一のソースコードからそれぞれのバイナリを作り分ける。
生成されるバイナリは __AVR_EA/EB__ 各系統別に共通してインストール可能であり、バリエーションは UARTや LEDの選択違いだけである。
EEPROM は バイト粒度で、リード 256 byte、ライト 8 byte に対応する。
FLASH は最大容量 64 KiB、ワード粒度で、リード 256 byte、ライト 128 byte に対応する。

> この系統は BOOTCODE 粒度が 256 byte なので、FUSE_BOOTSIZE（fuse8）には `2` を指定する。

## 特徴

`Optiboot` やその亜種とは以下の点で異なる。

- UART `TxD` ピンの既定 Hi-Z。
- EEPROM領域リード/ライト対応。
- PGMEMアドレス`PROGMEM_START+2`以降にSPM命令スニペットが配置される。
- `RS485` と `USART` 機能のハードウェア応用支援。
- CRCSCAN機能用のCRC16/32検査符号付与。

> `RxD`、`XDIR`、`XCLK`の各ピンは`TxD`ピンが定まれば一意に決定され、任意のピンに割り当てることはできない。

HEXフォルダとBINフォルダには主だったUART/LED違いのバリエーションが置かれている。既定ビルドは、20pin以上の品種用は `TX:PA0`、`RX:PA1`、`LED:PA7` で統一されている。

> AVR_DD/EBの 14pin 品種には PA7 がないため PD7 が代わりに使用される。

## Arduino IDE での EEPROM リード/ライト

Arduino IDE サブメニューの `FUSE EEPROM`\>`"Erase" and "Replace"` を選択すると、EEPROM領域をスケッチと同時に書くことが出来る。

```c
#include <avr/eeprom.h>
char estring[] EEMEM = "0123456789ABCDEF";  // <-- HERE
```

その後`Save guard "Retained"`とした場合、新たなスケッチを書き込んでも EEPROMは以前に書き込んだ状態を維持する。

この状態は `Save guard "Erase"` として消去するか、`"Erase" and "Replace"` として改めて書き込み直すまで変わらない。

> EEPROM領域量は MCU品種によって異なる。その大きさはマクロ`EEPROM_SIZE`で知ることが出来る。

- この機能は`MCUdude`版ブートローダーと運用互換性がある。
- この機能は`DxCore`版ブートローダーには実装されていない。

### USERROW リード

ATMEL STK500 version 1 プロトコルの制約により、ブートローダーでの対応 NVM 種別は FLASH と EEPROM に限られる。ただし UPDI 世代デバイスの特性により EEPROM 種別選択を流用すると全 64KiB のデータ空間を読むことが可能だ。書き込みはできないが EEPROM 設定を USERROW のそれに（ユーザー構成ファイルを使って）置き換えると、USERROW 空間へもアクセスできる。これは施錠されたデバイスの USERROW をブートローダーを使って読むことが可能になるため、知っておくと便利だ。

## SPMスニペット

以下の PGMEMアドレスに、この機能が有効なら以下の固定値が書かれている。

|Series|Address|マジックナンバー : uint32_t (LE)|
|-|-|-|
|megaAVR-0 tinyAVR-0/1/2|MAPPED_PROGMEM_START + 2 Byte|0x95089201|
|AVR_DA/DB/DD/EA/EB|PROGMEM_START + 2 Byte|0x950895F8|

これらは BOOT領域保護特権で CODE領域 / APPEND領域の FLASH消去/書換を行うのに使うことが出来る。

- `MCUdude`や`DxCore`での同種の機能とは仕様が異なり、相互に互換性はない。

> 実際の使用例は [[FlashNVM ツールリファレンス]](https://github.com/askn37/askn37.github.io/wiki/FlashNVM) を参照のこと。

## リビルド

詳細は`make_all.sh`や `Makefile`を参照のこと。それぞれのカレントディレクトリで 次のようにすれば`hex/bin`フォルダが更新される。
使用する avr-gccツールチェインには、AVR_Dx/Exサポートパックがマージされていなければならない。

```c
boot_ax> sh make_all.sh
boot_dx> sh make_all.sh
boot_ex> sh make_all.sh
```

> Windows環境でのビルド確認はされていない。gmakeコマンドを別途用意し、各ファイル中のファイルパス指定他を Windows流儀に修正する必要がある。

### CRCSCAN機能用CRC16/32検査値付与

リビルド環境で`Perl`コマンドにパスが通っている場合、`FUSE_SYSCFG0`中の`CRCSRC`ビット（`BOOTCODE`領域が対象）に対応した CRC16/32検査値を hex/bin 出力ファイルに付与する。この検査値は FLASH上に書き込まれた状態でのみ検証可能になるため、通常の`chksum/crc32`コマンドで妥当性を検証することはできない。

- CRC16/32検査値は hex/bin 出力ファイルの末尾から次の 512byte境界までが全て`0xff`で埋められていると仮定して計算されている。
- `FUSE_SYSCFG0`の最上位2bitは、CRC検査無効なら一般に`11`、CRC検査有効なら`01`を設定する。詳細はデータシートを確認されたい。
- megaAVR、tinyAVR 系統用は CRC16 検査値が埋め込まれている。`FUSE_SYSCFG0`に`CRCSEL`ビットはない。
- AVR_Dx系統用は CRC32 検査値が埋め込まれている。`FUSE_SYSCFG0`の`CRCSEL`ビットは`FUSE_CRCSEL_bp`をセットする。

> AVR_Ex系統用は CRC32 検査値が埋め込まれているが、現行の`B1`シリコンリビジョンでは Eratta により事実上使用できない。

### ビルドオプション

以下のビルドオプションは make コマンドラインオプションに指定できる。

#### ビルドターゲット

`avr128db64` 等の対象AVR-MCU品種を指示する。常に必須。同一グループ内（データシートの区分）であれば何を指定しても同一のバイナリが生成されるが、品種により以下の違いが現れる。

- 128KiB 品種は 17bit アドレス幅対応のためバイナリサイズが若干増える。
- ピン数の少ない下位品種ほど選択可能な UART と、LED の選択肢が減少する。

### UART=A0

UART の TxD ピンをシンボルで指定する。既定値は`A0`。品種指定により対応できない無効値の場合はビルドが停止する。

#### LED=A7

LED インジケーターに使用するピンをシンボルで指定する。既定値は`A7`。無効値（例えば`0`）の場合は LED インジケーターを使用しない。

#### LED_BLINK=6

LED インジケーターの点滅反転回数を指定する。偶数か奇数で点滅後の ON/OFF が反転する。既定値は`6`。`0`を指定すると TIMEOUT 周期の交互ブリンクになる。

#### TIMEOUT=1

ホストからの通信開始を待機する秒数を指定する。`0`、`1`、`2`、`4`、`8`が指定可能。既定値は`1`。`0`指定は 0.5秒待機となる。
応用コードがソフトウェアリセット、BOD、WDTのいずれかで再起動した場合は、待機時間はない。

> 4と 8は、PORでしかブートローダーを起動できない（UPDIピンをRESET機能に変更していない）tinyAVR のために用意されている。UPDI外部リセット機能を備えた支援アダプターと併用する場合は変更の必要はない。

#### BAUD_RATE=115200

UARTの調歩同期通信速度を指定する。既定値は`115200`。より高速に変更する場合は`F_CPU_Scale`も調整すべきだ。`USART`有効時は無効。

> 逆に有効な最低速度は`4800`である。

#### F_CPU_Scale=1

起動時の主クロック速度を調整する。規定値は`1`で、これは `BAUD_RATE=200000` 以下に対応する。
`BAUD_RATE`をより大きくしたい場合には`2`以上を指定する。
`AVR_DA/DB/DD`は `1...6`を、`tinyAVR`、`megaAVR`、`AVR_EA/EB`は `1...4`を指定可能。
ただし通信エラーには過敏になるため、この変更は推奨されない。

#### PULLUP_RX=1

RxDピンの内蔵プルアップ抵抗を有効にする。既定値は無効。通常は送信側がプッシュプル動作を行うので指定の必要はない。

#### USART=1

通常の二線式調歩同期ではなく、XCK入力ピンによる同期通信従装置モードを選択する。RS485とも組み合わせ可能。`BAUD_RATE`設定は無効になる。`F_CPU_Scale=1`では約 1Mbps以上で通信可能。

#### RS485=1

RS485モードを有効にし、XDIR出力ピンを有効にする。

#### RS485_SINGLE=1

RS485モード有効時に、RxD入力ピンを無効にした単線半二重通信モードを有効にする。TxDピンが双方向で使われ、内蔵プルアップも有効になる。

#### RS485_INVERT=1

RS485モード有効時の XDIR出力ピンを負論理に反転する。

## Copyright and Contact

Twitter(X): [@askn37](https://twitter.com/askn37) \
BlueSky Social: [@multix.jp](https://bsky.app/profile/multix.jp) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) 2022,2023 askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
