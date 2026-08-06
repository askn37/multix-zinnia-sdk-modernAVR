# Bootloaders for modernAVR

- *boot_ax -- ブートローダーソース群（tinyAVR-0/1/2、megaAVR-0用）*
- boot_dx -- ブートローダーソース群（AVR_DA/DB/DD/DU用）
- boot_ex -- ブートローダーソース群（AVR_EA/EB/LA用）
- boot_sx -- ブートローダーソース群（AVR_SD用）
- *euboot -- AVR_DU用USBブートローダー*
- empty -- 空のダミーHEXだけがある
- hex -- ビルド済のブートローダーHEXファイル群
（Arduino IDE サブメニューから選択される）

> [megaAVR / tinyAVR系統用ブートローダー]（boot_ax）は[こちら](https://github.com/askn37/multix-zinnia-sdk-megaAVR/tree/main/bootloaders)

> [AVR_DU用USBブートローダー]（euboot）は[こちら](https://github.com/askn37/euboot)

## 概要

この moderAVR 用ブートストラップローダー・ファームウェアは ATMEL STK500 version 1 プロトコルに基づいており、Arduino ブートローダー（シリアル通信方式）と完全な互換性がある。

ファームウェアが起動すると、RESET情報フラグが点検され、WDT またはソフトウェアリセットの場合、アプリケーションコード (0x200 から始まる) がすぐに実行を開始する。それ以外ではタイムアウト期間内に有効な STK500 version 1 コマンドが受信されたならば、UART を開いて NVM 操作を開始する。

ビルドは AVR-GCC および AVR-LIBC で可能だが、他のコンパイラに付いては考慮されていない。バイナリコードは 512バイト以内におさまる。

過去のソースコードは`Optiboot`のクローンであったが、現在はそうではない。彼らの支援対象は原則としてより古い世代のデバイスだけである。そうした理由により、ここで公開されているソースコードは改めて書き起こされた。

使用許諾と再配布には MIT ライセンスが適用される。

> [!WARNING]
> AVR-GCC のバージョン選択は重要で v7.x 系の使用が前提である。おそらく v10 以降では大部分をアセンブラで書き直さなければ所定のバイナリサイズに納まらない。

### boot_ax.c

これは __tinyAVR-0/1/2__ 系統と __megaAVR-0__ 系統用の NVMCTRL version 0 仕様に適合するブートローダーだ。
生成されるバイナリは対応全品種に共通してインストール可能であり、バリエーションは UARTや LEDの選択違いだけである。
EEPROM は バイト粒度で、リード 256 byte、ライト 32 byte または 64 byte に対応する。
FLASH は最大容量 48 KiB、ワード粒度で、リード 256 byte、ライト 64 byte または 128 byte に対応する。

> この系統は BOOTCODE 粒度が 256 byte なので、FUSE_BOOTSIZE（fuse8）には `2` を指定する。

### boot_dx.c

これは __AVR_DA/DB/DD__ 系統用の NVMCTRL version 2 仕様と、__AVR_DU__ 系統用の NVMCTRL version 4 仕様に適合するブートローダーだ。
生成されるバイナリは __AVR_DA/DB/DD__ 系統、または __AVR_DU__ それぞれの全品種に共通してインストール可能であり、バリエーションは UARTや LEDの選択違いだけである。
EEPROM は バイト粒度で、リード 256 byte、ライト 2 byte に対応する。
FLASH は最大容量 128 KiB、ワード粒度で、リード 512 byte、ライト 512 byte に対応する。

> この系統は BOOTCODE 粒度が 512 byte なので、FUSE_BOOTSIZE（fuse8）には `1` を指定する。

> __AVR_DD__ は `PORTMUX`仕様が異なるため、DA/DBと共用可能なのは`UART0.PA0`と`UART0.PA4`用だけで、その他は DD専用のバイナリが必要。

> __AVR_DU__ は NVM制御方法が異なるため他の AVR_Dx 系統とはバイナリ共用ではない。
また USBインタフェースを持っているため、シリアルポート方式のブートローダーを選択する必要性は薄い。
おそらく USBインタフェースファームウェアそれ自体を開発する目的に限定される。

### boot_ex.c

これは __AVR_EA__ 系統用の NVMCTRL version 3 仕様と、__AVR_EB/LA__ 系統用の NVMCTRL version 5 仕様に適合するブートローダーだ。両者の差は僅かなので、同一のソースコードからそれぞれのバイナリを作り分ける。
生成されるバイナリは __AVR_EA/EB__ 各系統別に共通してインストール可能であり、バリエーションは UARTや LEDの選択違いだけである。__AVR_LA__ は USART周辺機能に互換性がないため異なるバイナリとなる。
EEPROM は バイト粒度で、リード 256 byte、ライト 8 byte に対応する。
FLASH は最大容量 64 KiB、ワード粒度で、リード 256 byte、ライト 64 byte または 128 byte に対応する。

> この系統は BOOTCODE 粒度が 256 byte なので、FUSE_BOOTSIZE（fuse8）には `2` を指定する。

### boot_sx.c

> [!CAUTION]
> この実装は極めて実験的なものだ。技術的可能性を示しはするが、実用に供されるものではない。

これは __AVR_SD__ 系統用の NVMCTRL version 6 仕様に適合するブートローダーだ。
この製品は航空宇宙用途に耐えられるよう設計されており、ECC Flashメモリ搭載等の強固なシステム監視機能を持つため、それらを一時的に解除して不揮発メモリを書き換えなければならない。
故にこの系統用については 1KiB バイナリサイズで作成されている。
また FUSE設定が既にシステム監視機能を強制しているならば、ブートローダーはもはや機能しないだろう。
その段階に至るまで応用アプリケーションが熟成したならば、本ブートローダーはシステムから取り去られるべきである。

EEPROM は バイト粒度で、リード 256 byte、ライト 2 byte に対応する。
FLASH は最大容量 128 KiB、ワード粒度で、リード 512 byte、ライト 512 byte に対応する。

> この系統は BOOTCODE 粒度が 512 byte かつ 1KiB バイナリなので、FUSE_BOOTSIZE（fuse8）には `2` を指定する。

### euboot

__AVR_DU__ 系統専用の USBブートローダー。これは UARTシリアル通信ではなく、USB-HID/CMSIS-DAP/EDBG プロトコルを使用する。`PICKit4` や `CURIOSITY NANO` と互換性がある。

## 特徴

`Optiboot` やその亜種とは以下の点で異なる。

- UART `TxD` ピンの既定 Hi-Z。
- EEPROM領域リード/ライト対応。
- PGMEMアドレス`PROGMEM_START+2`以降にSPM命令スニペットが配置される。
- `RS485` と `USART` 機能のハードウェア応用支援。
- CRCSCAN機能用のCRC16/32検査符号付与。

> `RxD`、`XDIR`、`XCLK`の各ピンは`TxD`ピンが定まれば一意に決定され、任意のピンに割り当てることはできない。

HEXフォルダとBINフォルダには主だったUART/LED違いのバリエーションが置かれている。既定ビルドは、20pin以上の品種用は `TX:PA0`、`RX:PA1`、`LED:PA7` で統一されている。

> 14pin 品種には PA7 がないため PD7 あるいは PC3 が代わりに使用される。

## Arduino IDE での EEPROM リード/ライト

Arduino IDE サブメニューの `FUSE EEPROM`\>`"Erase" and "Replace"` を選択すると、EEPROM領域をスケッチと同時に書くことが出来る。

```c
#include <avr/eeprom.h>
char estring[] EEMEM = "0123456789ABCDEF";  // <-- HERE
```

その後`Save guard "Retained"`とした場合、新たなスケッチを書き込んでも EEPROMは以前に書き込んだ状態を維持する。

この状態は `Save guard "Erase"` としてブートローダーを書き込むか、`"Erase" and "Replace"` として改めて EEPROM（ファイル）を書き込み直すまで変わらない。

> EEPROM領域量は MCU品種によって異なる。その大きさはマクロ`EEPROM_SIZE`で知ることが出来る。

- この機能は`DxCore`版ブートローダーには実装されていない。

### USERROW リード

ATMEL STK500 version 1 プロトコルの制約により、ブートローダーでの対応 NVM 種別は FLASH と EEPROM に限られる。ただし UPDI 世代デバイスの特性により EEPROM 種別選択を流用すると全 64KiB のデータ空間を読むことが可能だ。書き込みはできないが EEPROM 設定を USERROW のそれに（ユーザー構成ファイルを使って）置き換えると、USERROW 空間へもアクセスできる。これは施錠されたデバイスの USERROW をブートローダー経由で読むことが可能になるため、知っておくと便利だ。

> [!NOTE]
> v3.71 以降では USERROW領域 / BOOTROW領域 の読み書き、および全 64KiB データ空間の読み出しが可能。ただし最近の標準的な`AVRDUDE`では`urclock`との一貫性のため、これには対応しない。（`AVRDUDE 7.1`は可能）

### CURIOSITY / Xplained 等での注意点

これらのオンボードデバッガー付属機種では、シリアル通信ブートローダーの運用は非実用的なので使用は推奨されない。
しかしながら *ブートローダーそのもの* の開発検証を行うことは有り得るので、その場合は以下のように対処する。

- オンボード UART-CDC に接続されていないピンを使用できる UARTモジュールを選択し、外部に検証用シリアルコンバーターを別途接続する。 __これが最も現実的である。__
  - UPDI4AVR-USBの場合、RSTも接続するとIDEの自動リセット制御に対応する。
- オンボード UART-CDC 経由でスケッチアップロードを行おうとすると、以下の問題が生じる。ボードリセット後のデバッガーの UART-CDC 初期化完了より早く MPU が起動してしまうので、ホストから送られる最初のパケットを取りこぼす。しかもリトライ毎に規定で Arduino IDE（AVRDUDE）はボードリセットを行うので永久に問題が改善しない。
- どうにか対処するには`AVRDUDE@8.0+`の場合`-x noautoreset`オプションをコマンド行に追加する。さらにボードの`RESET`端子（MPUの`PF6`）にリセットボタンを追加する。これを押しながら`AVRDUDE`起動を待ち、タイミングよくボタンを離すとスケッチアップロードが始まる。
  - IDEの場合`platform.txt`の`tools.avrdude.upload.pattern`が該当するコマンド行。

## バージョン表記

`avrdude -c arduino -v`を使用した場合、以下の例のような情報を得られる。

```plain
Programming modes     : UPDI, SPM
Programmer Type       : Arduino
Description           : Arduino for bootloader using STK500 v1 protocol
HW Version            : 53
FW Version            : 53.73
```

`FW Version`(FWV)は一般原則に従う、ブートローダーファームウェアの版番号だ。
`HW Version`(HWV)は次の分類を示し、対象デバイスの`NVMCTRL version`に一致する。

|HWV|ASCII|Series|
|-|-|-|
|48|'0'|tinyAVR-0/1/2、megaAVR-0
|50|'2'|AVR_DA/DB/DD
|51|'3'|AVR_EA
|52|'4'|AVR_DU
|53|'5'|AVR_EB/LA
|54|'6'|AVR_SD

- 一部を除き`3.72`以降は`FW Major`（通常は`3`）を返さず、`HW Version`と`FW Minor`だけを返す。

> `avrdude -c urclock`では、バージョン表記は取得できない。

## SPMスニペット

以下の PROGMEMアドレスに、以下の固定値が書かれている。（`@3.71+`）

|Series|Address|マジックナンバー : uint32_t (LE)|
|-|-|-|
|megaAVR-0 tinyAVR-0/1/2|MAPPED_PROGMEM_START + 2 Byte|0x95089361|
|AVR Dx/Ex/Lx/Sx|PROGMEM_START + 2 Byte|0x95089361|

> `MAPPED_PROGMEM_START`は通常のデータ空間、`PROGMEM_START`は PROGMEM 空間にある。

使用可能なスニペットは2種あるいは4種存在する。
これらは実行コード権限のプログラムカウンタ（PC）検査を回避するために、ここに配置されている。

|Offset|HWV=48|HWV=50以上|OP-Code|
|-|-|-|-|
|$02|nvm_stz|nvm_stz|ST Z+, R22
|$06|nvm_cmd|nvm_ldz|LD R24, Z+
|$0A|-      |nvm_spm|SPM Z+
|$0E|-      |nvm_cmd|(function)

これらは BOOT領域保護特権で CODE領域 / APPEND領域（そして一部品種の BOOTCODE領域）の FLASH消去/書換を行うのに使うことが出来る。

- HWV=48は 16bitアドレス品種用のため`SPM+`が存在せず、`LPM/LD`の使い分けもない。
- `LDZ/STZ`は BOOTROW 非採用デバイスでは不要だが、コード互換性のために存在する。
- C/C++言語からスニペットを呼ぶにはラッパーアセンブリが必要。
- `MCUdude`や`DxCore`での同種の機能とは仕様が異なり、相互に互換性はない。

> 実際の使用例は [[FlashNVM ツールリファレンス]](https://github.com/askn37/askn37.github.io/wiki/FlashNVM) を参照のこと。

## リビルド

詳細は`make_all.sh`や `Makefile`を参照のこと。それぞれのカレントディレクトリで 次のようにすれば`hex`フォルダが更新される。
使用する avr-gccツールチェインには、AVR_Dx/Exサポートパックがマージ（あるいはGCCの`-B`パス指定）されていなければならない。

avr-gcc-7.x を使用すること。__それ以降の avr-gcc は推奨されない。__

> avr-gcc-15.x 等では 512byte を超える肥大したバイナリが出力され、それを回避する方法は発見されていない。

```c
boot_ax> sh make_all.sh
boot_dx> sh make_all.sh
boot_ex> sh make_all.sh
```

> Windows環境でのビルド確認はされていない。gmakeコマンドを別途用意し、各ファイル中のファイルパス指定他を Windows流儀に修正する必要がある。

### CRCSCAN機能用CRC16/32検査値付与

リビルド環境で`Perl`コマンドにパスが通っている場合、`FUSE_SYSCFG0`中の`CRCSRC`ビット（`BOOTCODE`領域が対象）に対応した CRC16/32検査値を hex/bin 出力ファイルに付与する。この検査値は FLASH上に書き込まれた状態でのみ検証可能になるため、通常の`chksum/crc32`コマンドで妥当性を検証することはできない。

- CRC16/32検査値は hex/bin 出力ファイルの末尾から次の 512byte境界までが全て`0xff`で埋められていると仮定して計算されている。
- `FUSE_SYSCFG0`の最上位2bitは、CRC検査無効なら一般に`11`、CRC検査有効なら`01`を設定する。詳細はデータシートを確認されたい。（__AVR_Lx__ 以外の場合）
- megaAVR、tinyAVR 系統用は CRC16 検査値が埋め込まれている。`FUSE_SYSCFG0`に`CRCSEL`ビットはない。
- AVR_Dx/Ex/Lx系統には CRC32 検査値が埋め込まれる。`FUSE_SYSCFG0`の`CRCSEL`ビットは`FUSE_CRCSEL_bp`をセットする。

> AVR_Ex系統は、最初期のシリコンでは Eratta によりブート領域のみの CRC検査は事実上使用できない。

### ビルドオプション

以下のビルドオプションは make コマンドラインオプションに指定できる。

> [!NOTE]
> __AVR_Dx__ を指定してのビルド時は空き領域が非常に少ないため、すべての追加機能を同時に有効化することができない。実行バイナリ量が 512byte に収まらない場合は、`LED_BLINK=0`あるいは`LED=0`を試すと軽減される。

#### ビルドターゲット

`avr128db64` 等の対象AVR-MCU品種を指示する。常に必須。同一グループ内（データシートの区分）であれば何を指定しても同一のバイナリが生成されるが、品種により以下の違いが現れる。

- AVR_DAとAVR_DBの同格品種では、同一のバイナリとなる。`hex`中のファイルでは *avrdx* ラベルで示される。
- 128KiB 品種は 17bit アドレス幅対応のためバイナリサイズが増加する。
- ピン数の少ない下位品種ほど選択可能な UART と、LED の選択肢が減少する。

```sh
make avr16eb32 BOOTNAME=boot_avreb UART=A0 LED=A7 PULLUP_RX=1
```

#### UART=A0

UART の TxD ピンをシンボルで指定する。既定値は`A0`。品種指定により対応できない無効値の場合はビルドが停止する。

#### LED=A7

LED インジケーターに使用するピンをシンボルで指定する。既定値は`A7`。無効値（例えば`0`）の場合は LED インジケーターを使用しない。

#### LED_BLINK=6

LED インジケーターの点滅反転回数を指定する。偶数か奇数で点滅後の ON/OFF が反転する。既定値は`6`。`1`を指定すると TIMEOUTSEC 周期の交互ブリンクになる。

#### TIMEOUTSEC=1

ホストからの通信開始を待機する秒数を指定する。`0`、`1`、`2`、`4`、`8`が指定可能。既定値は`1`。`0`指定は 0.5秒待機となる。
応用コードがソフトウェアリセット、BOD、WDTのいずれかで再起動した場合は、待機時間はない。

> 以前は`TIMEOUT`であったが AVR-Sx の `<avr/io.h>` で予約語となったため変更された。

> 4と 8は、PORでしかブートローダーを起動できない（UPDIピンをRESET機能に変更していない）tinyAVR のために用意されている。UPDI外部リセット機能を備えた支援アダプター（例えば UPDI4AVR-USB）と併用する場合は変更の必要はない。

#### BAUD_RATE=115200

UARTの調歩同期通信速度を指定する。既定値は`115200`。より高速に変更する場合は`F_CPU_Scale`も調整すべきだ。2線式でのみ使用され、`USART`、`RS485`選択時は無効。

> 逆に有効な最低速度は`4800`である。

#### F_CPU_Scale=1

起動時の主クロック速度を調整する。規定値は`1`で、これは `BAUD_RATE=200000` 以下に対応する。
`BAUD_RATE`をより大きくしたい場合には`2`以上を指定する。
`AVR_DA/DB/DD`は `1...6`を、`tinyAVR`、`megaAVR`、`AVR_EA/EB`は `1...4`を指定可能。
ただし通信エラーには過敏になるため、この変更は推奨されない。

#### PULLUP_RX=1

RxDピンの内蔵プルアップ抵抗を有効にする。既定値は無効。6byteを追加消費する。通常は送信側がプッシュプル動作を行うので指定の必要はない。一部のハードウェア（USBシリアル変換器）はこれを有効にしないと最初の受信動作に入れないことがある。（なので`hex`プリコンパイルバイナリは有効化されている）

#### PORSTRAP=1

POR および BOD 検出時に、ブートローダーを起動するか否か。
tinyAVR 系統以外の既定値は無効で、ユーザーコードを実行する。

tinyAVR 系統は有効とし、ブートローダーの起動を優先することが推奨される。
これは規定ではハードウェアリセットピンを持たないことによる。

この設定に関わらず、WDT リセットはユーザーコードを実行し、ソフトウェアリセット（未定義命令の実行も含む）はブートローダーを起動する。
また CODE領域先頭の遷移（`JMP 0`）は、ソフトウェアリセット＝ブートローダー起動となる。

> CPU起動時には、`GPIOR0`汎用レジスタには`RSTCTRL_SWRR`レジスタの内容が保存され、`RSTCTRL_SWRR`は常にゼロクリアされている。

#### USART=1

通常の二線式調歩同期ではなく、XCK入力ピンによる同期通信 **従装置** モード（つまり3線式）を選択する。`BAUD_RATE`設定は無効になる。`F_CPU_Scale=1`では約 1Mbps以上で通信可能。

#### RS485=1

RS485モード（**従装置** 4線式）を有効にし、XDIR出力ピンを有効にする。

#### RS485_SINGLE=1

RS485モード有効時に、RxD入力ピンを無効にした単線半二重通信モード（**従装置** 3線式）を有効にする。TxDピンが双方向で使われ、内蔵プルアップも有効になる。ループバック読み戻し処理も含むため、増加コード量は大きい。

#### RS485_INVERT=1

RS485モード有効時の XDIR出力ピンを負論理に反転する。6byteを追加消費する。

## 更新履歴

- v3.73 (26/08/05)
  - __AVR-LA__、__AVR-SD__ 系統対応（`AVRDUDE@8.2+` が必要）
  - RS485対応等のコードフィックス
  - 定義名`TIMEOUT`を`TIMEOUTSEC`に変更（AVR-Sxで名前衝突のため）

- v3.72 (24/4/28)
  - __AVR-DU__ 系統対応と実機確認
  - `FW`メジャー番号の代わりに`HW`バージョンを返すように変更
  - AVR_DA-S ファミリ対応を暫定追加 (26/07/06)

- v3.71 (24/01/10)
  - __AVR16EB32__ での実機確認
  - BOOTROW 対応に伴う SPMスニペット仕様の変更

- v3.7 (23/12/11)
  - （Optibootから分離した）初版

## Copyright and Contact

Twitter(X): [@askn37](https://twitter.com/askn37) \
BlueSky Social: [@multix.jp](https://bsky.app/profile/multix.jp) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) 2022,2023 askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
