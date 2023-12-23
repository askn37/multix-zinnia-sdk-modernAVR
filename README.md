# MultiX Zinnia Product SDK [modernAVR]

このソフトウェア開発キットは、主に新世代のAVRファミリ
（Microchipブランド統合以降で発表されたもの）
について、Arduino IDEでの開発を支援するために構成されている。
AVR-GCC/AVR-LIBC を用いて書かれた C/C++/アセンブラ プログラムを
avrdude を用いて対象MCUにアップロードするまでの作業フローを提供する。

## 概要

- Arduino互換APIは提供されない。
  - ごく限られた互換性は配慮されており Blinkスケッチ（標準Lチカ）はそのままビルドできる。
  - 原則として割込や計数器/計時器周辺機能を専有せず、利用者が自由に使える。
    - __協調的マルチタスク__ 支援ライブラリは RTC周辺機能を必要とする。\
      （任意選択：明示的インクルードで有効化）
- 超低消費電力超低速駆動対応。
  - 32768Hzの超低消費電力動作を支援。
- 安価なプログラムライタ（書込器）の利用を想定。
  - 高度なデバッグトレース機能は提供されない。シリアルコンソールだけが使える想定。
- makeコマンドによる高度なビルド進行は提供されない。
  - Arduino IDE自体が makeコマンドに対応していない。
  - Arduino IDEによる自動ビルド進行は提供される。
  - 大規模開発には不向き。
  - むしろMakefileを書かなくて良いから割り切れて簡単。
  - 単機能テスト、スクラッチビルド、先行検証、各種実験に好適。
- 改良されたブートローダーの提供。（reduceAVR以外）
  - スケッチプログラムと同時に EEPROM 領域を定数初期化/アップロード可能。
  - フラッシュメモリ領域の自己消去/書換機能を支援。
    - 余っている領域を大容量不揮発メモリストレージとして活用可能。
- 新規構築・再構築が簡単。
  - セットアップは数分で済む。公式IDEのように何GBも大量ダウンロードすることはない。
  - セミナー講習等での一斉大量導入に向く。

## 対応AVRアーキテクチャ

現在この SDK は複数の異なる対象アーキテクチャ向けにリポジトリを分けて提供される。

- __MultiX Zinnia Product SDK [megaAVR]__
  - megaAVR-0 と tinyAVR-0/1/2 系統。（Atmelブランド世代）
- __MultiX Zinnia Product SDK [modernAVR]__ <--
  - （Microchipブランド世代）
  - AVR DA 系統
    - AVR32DA28 AVR64DA28 AVR128DA28
    - AVR32DA32 AVR64DA32 AVR128DA32
    - AVR32DA48 AVR64DA48 AVR128DA48
    - AVR32DA64 AVR64DA64 AVR128DA64
  - AVR DB 系統
    - AVR32DB28 AVR64DB28 AVR128DB28
    - AVR32DB32 AVR64DB32 AVR128DB32
    - AVR32DB48 AVR64DB48 AVR128DB48
    - AVR32DB64 AVR64DB64 AVR128DB64
  - AVR DD 系統
    - AVR16DD14 AVR32DD14 AVR64DD14
    - AVR16DD20 AVR32DD20 AVR64DD20
    - AVR16DD28 AVR32DD28 AVR64DD28
    - AVR16DD32 AVR32DD32 AVR64DD32
  - AVR EA 系統
    - AVR16EA48 AVR32EA48 AVR64EA48
    - AVR16EA32 AVR32EA32 AVR64EA32
    - AVR16EA28 AVR32EA28 AVR64EA28
  - AVR EB 系統
    - AVR16EB32
    - AVR16EB28
    - AVR16EB20
    - AVR16EB14
- __MultiX Zinnia Product SDK [reduceAVR]__
  - 旧世代AVRのうち TPI方式に対応した系統。（Atmelブランド世代）

> この分割は NVM書換プロトコルおよび/すなわちブートローダーの相互共有性による。\
> 共通基盤の AVR-GCC/AVR-LIBC toolchain は既知の AVR 8bit 系全種に対応している。

## 対応するホストOS

- Windows (32bit/64bit)
- macOS (64bit)
- Linux (主にintel系64bit)

## 対応する主なプログラムライタ

完成品として販売されている製品以外の、
工場出荷状態ではブートローダーが書き込まれていないため
何らかの書込器準備は必要。

- [__UPDI4AVR__](https://askn37.github.io/product/UPDI4AVR/) -- このSDKでもメンテナンスされている。JTAG2UPDI上位互換。
  - __HV書込__ とUSB-USARTパススルーに対応可。（要外部回路）
  - ゼロからこれを自作する場合は __卵と鶏__ の関係になるため注意。
- [__SerialUPDI__](https://avrdudes.github.io/avrdude/7.2/avrdude_19.html#index-SerialUPDI/) -- 一般のUSB-UARTと簡易な回路による高速書込環境。
  - 準備にはいくらかの部品と配線準備が必要だが難易度は低い。HV書込は望めない。
  - 対象MCUの UART通信とは回路が排他で外部切替が必要。（自動切替は要外付制御回路）
- PICkit4 -- 公式のプログラム書込装置兼 __デバッグトレース__ 装置。
  - 使用開始前に MPLAB X によるFWアップデートが要求される。購入状態での対応範囲不明。
  - フルスペックの公式開発環境が別途必須なのでエンドユーザーのPC環境によっては難がある。\
    Arduino IDEの動作スペックより数倍大きなディスク空容量やハードウェア性能とIDE操作習熟が必要。
- プログラムライタ内蔵完成市販品 -- これらはブートローダー書込不要。（あるいは対応不可）
  - Microchip Curiosity Nano Series の一部 -- AVR DA/DB + nEDBG

## 導入方法

- Arduino IDE の「環境設定」「追加のボードマネージャーのURL」に以下のリンクを追加
  - [`https://askn37.github.io/package_multix_zinnia_index.json`](https://askn37.github.io/package_multix_zinnia_index.json)
- 「ボードマネージャー」ダイアログパネルを開き、検索欄に "multix" と入力
- 目的のアーキテクチャを選択して「インストール」\
  `megaAVR` `modernAVR` `reduceAVR`

### Developer Preview

- 上記リンクは更新がある程度まとまってから差し替えられるため、公開リポジトリより古い場合がある。
なる早で Arduino IDE に更新を取り込みたい場合は、下記リンクを使用されたい。
  - [`https://askn37.github.io/package_multix_zinnia_index_preview.json`](https://askn37.github.io/package_multix_zinnia_index_preview.json)

## ボード選択メニュー

SDK種別と対象ブートローダー使用の有無をここで選ぶ。

- __MultiX Zinnia Product SDK [megaAVR]__
- __MultiX Zinnia Product SDK [modernAVR]__ <--
  - AVR DB with Bootloader
  - AVR DA with Bootloader
  - AVR DD with Bootloader
  - AVR DU with Bootloader (Preliminary)
  - AVR EA with Bootloader
  - AVR EB with Bootloader (Preliminary)
  - AVR DD 14pin with Bootloader
  - AVR EB 14pin with Bootloader
  - AVR DB w/o Bootloader
  - AVR DA w/o Bootloader
  - AVR DD w/o Bootloader
  - AVR DU w/o Bootloader (Preliminary)
  - AVR EA w/o Bootloader
  - AVR EB w/o Bootloader (Preliminary)
- __MultiX Zinnia Product SDK [reduceAVR]__

## ボード選択サブメニュー

Arduino IDE でこのSDKを選択すると、
サブメニューでは以下のオプションが選択可能となる；

> FUSE設定の変更は 書換器使用時に反映。ブートローダー書込時は変更不能。

- __Variant__ -- 具体的な製品型番を選択。（必須）
  - 外囲器ピン数＋型番＋フラッシュメモリ量＋SRAM量別になっている。
- __Clock(Dx)__ -- AVR_DA/DB/DD用の主装置動作基準周波数選択（F_CPUマクロ初期値） -- 既定値は定格内最高速度
  - F_CPUマクロを参照しないプログラムでは効果なし
  - __FUSE無関係に常時どれでも変更可能__
  - 高周波内蔵発振器による 24MHz〜1MHz
  - 高周波内蔵発振器のオーバークロック 32MHz、28MHz（AVR_DA/DB/DDでは定格外）
  - 超低消費電力発振器による 32.768kHz (OSC-ULP)
- __Clock(Ex)__ -- AVR_Ex専用の主装置動作基準周波数選択（F_CPUマクロ初期値） -- 既定値は定格内最高速度
  - F_CPUマクロを参照しないプログラムでは効果なし
  - __20MHz系列と16Mhz系列は FUSE書込依存で排他選択__
  - 高周波内蔵発振器による 20MHz/10MHz/5MHz -- 20MHz系列用
  - 高周波内蔵発振器による 16MHz/8MHz/4MHz/1MHz -- 16MHz系列用
  - 高周波内蔵発振器による 2MHz -- FUSE設定非依存
  - 超低消費電力発振器による 32.768kHz (OSC-ULP) -- FUSE設定非依存
- __BOD Mode__ -- Brown Out Detect（FUSE設定）
  - BOD Disabled -- 無効 -- 既定値
  - BOD Enabled -- 有効
  - BOD Sampled -- 各個別データシート参照のこと
  - BOD Enabled hold wakeup -- 各個別データシート参照のこと
- __BOD Level__ -- BOD監視電圧レベル（FUSE設定）
  - 1.90V or 1.75V -- 既定値
  - 2.45V or 1.90V
  - 2.70V or 2.60V
  - 2.85V or 4.30V
- __FUSE PF6__ -- AVR_DA/DB/DD/EA のリセット端子用途変更（FUSE設定）
  - PF6 pin=Reset -- 既定値
  - PF6 pin=GPIO -- 各個別データシート参照のこと
- __FUSE UPDI__ -- AVR_DD/EAの UPDIピン用途変更（FUSE設定）
  - __原則、既定値からの変更禁止（復元にはHV対応書換器が必須）__
  - 各個別データシート参照のこと
- __FUSE EEPROM__ -- EEPROM保護フラグ（FUSE設定）
  - Save guard "Retained" -- チップ消去時保護
  - Save guard "Erase" -- チップ消去時一括初期化
  - "Erase" and "Replace" -- ブートローダー/書込器でのEEPROM書換有効
- __FUSE BOOTROW__ -- AVR_DU/EB の BOOTROW保護フラグ（FUSE設定）
  - Save guard "Retained" -- チップ消去時保護
  - Save guard "Erase" -- チップ消去時一括初期化
- __FUSE MVIO__ -- AVR_DB/DD の復電圧機能種別（FUSE設定）
  - MVIO "Dual" -- 有効（VDD2へ要外部電圧供給）
  - MVIO "Single" -- 無効（VDD2へ内部固定電圧供給）
  - 各個別データシート参照のこと
- __Build Option__ -- DEBUGマクロ有無（任意選択）
  - Build Release -- 既定値（NDEBUG設定）
  - Build DEBUG=1
  - Build DEBUG=2
- __Build API__ -- API拡張（任意選択）
  - Macro API Enable -- 既定値
  - Macro API Disable -- 無効
    - Arduino互換APIの導入は要外部支援（本SDKサポート外）
  - Standard Library All Disable
    - フルアセンブラ記述/純粋C言語環境（LIBC無効）
- __Build "printf"__ -- LIBC printf拡張（任意選択）
  - default -- 浮動小数点フォーマット出力不可
  - Float Support -- 浮動小数点フォーマット出力対応
- __Console and LED__ -- （任意選択：w/o Bootloader 選択時に表示）
  - 選択肢は系統選択に依存
- __Console__ -- コンソール既定速度（CONSOLE_BAUDマクロ初期値）任意選択
  - CONSOLE_BAUDマクロを参照しないスケッチプログラムには効果なし
  - 9600 bps -- 標準
  - 38400 bps
  - 57600 bps
  - 115200 bps
  - 230400 bps
  - 1000000 bps
  - 2400 bps -- OSC-LUP対応
- __Bootloader__ -- ブートローダー選択
  - 選択肢は系統選択に依存
  - w/o Bootloader 選択時は変更不可
- __シリアルポート選択__
  - 環境依存
- __書込装置選択__
  - [UPDI4AVR over UART](https://askn37.github.io/product/UPDI4AVR/) (Standard)
  - [UPDI4AVR over UART](https://askn37.github.io/product/UPDI4AVR/) (HV Enable) -- __HV書込対応__
  - [SerialUPDI over UART](https://avrdudes.github.io/avrdude/7.2/avrdude_19.html#index-SerialUPDI/)
  - PICkit4 over USB (UPDI)
  - Curiosity Nano (nEDBG: ATSAMD21E18)
  - JTAG2UPDI over UART (NVMCTRL v2 Remodeling)-- NVMCTRL v2 非対応のバリアントは使用不可
  - dryrun (Emulates programming without a programmer) -- 実際には何もしないダミーの書込器で、各種設定の論理的妥当性を検証するのに使用する

> FUSE UPDI -> UPDI (default) 選択以外に書換えた場合の復元は __HV対応書込器が必須。__\
> FUSE EEPROM -> "Erase" and "Replace" 選択は、対応するブートローダーか書込器使用時のみ可。\
> Build API -> Standard Library All Disable 選択は、一切の既定コンパイル前提を除去する。

## プログラム書込

### ブートローダーでのスケッチ書込 ```Ctrl+U``` ```⌘+U```

ボードメニューでブートローダー有を選んだ場合はこのモードが標準。
書込器は不要。MCUの UART経由でスケッチを書き込む。
FUSEを書き換えることは出来ない。
Arduino IDE のシリアルコンソールを閉じる必要はない。

以下のサブメニュー設定は必須；

- Bootloader
- シリアルポート選択

EEPROM対応ブートローダーを使用しているならば以下の選択も可能。

- FUSE EEPROM -> "Erase" and "Replace"

tinyAVR/megaAVR系統では Clock 選択と現在の真のFUSE設定が一致していないと
UARTが正しく動作しない。
FUSE現在値が不明な場合は __2MHz__ を選択するとよい。

### 書込器でのブートローダー付スケッチ書込 ```Ctrl+Shift+U``` ```⌘+Shift+U```

ボードメニューでブートローダー有を選んでおり、かつ書込器も併用している場合に有効。
FUSEも同時に更新される。
Arduino IDE のシリアルコンソールを閉じる必要はない。

以下のサブメニュー設定が必須；

- Bootloader
- シリアルポート選択（over UART 書込器の場合）
- 書込装置選択
- すべてのFUSE関連

EEPROM対応書込器を使用しているなら以下も選択可能。

- FUSE EEPROM -> "Erase" and "Replace"

tinyAVR/megaAVR系統では任意の Clock 選択が有効となる。

### 書込器でのブートローダー無スケッチ書込 ```Ctrl+U``` ```⌘+U```

ボードメニューでブートローダー無を選んだ場合はこのモード。
FUSEも同時に更新される。
Arduino IDE のシリアルコンソールを閉じる必要はない。

以下のサブメニュー設定が必須；

- シリアルポート選択（over UART 書込器の場合）
- 書込装置選択選択
- すべてのFUSE関連

EEPROM対応書込器を使用しているなら以下も選択可能。

- FUSE EEPROM -> "Erase" and "Replace"

tinyAVR/megaAVR系統では任意の Clock 選択が有効となる。

### 書込器でのブートローダー単独書込

> IDEメニューで選択

ボードメニューでブートローダー有を選んでおり、かつ書込器も併用している場合に有効。
FUSEも同時に更新される。
Arduino IDE のシリアルコンソールは __閉じていなければならない。__
ブートローダー無の設定でこれを行うとチップ消去が為される。

以下のサブメニュー設定が必須；

- Bootloader
- シリアルポート選択（over UART 書込器の場合）
- 書込装置選択
- すべてのFUSE関連

tinyAVR / megaAVR系統では任意の Clock 選択が有効となる。
FUSE変更以後は 20MHz / 16MHz 各系統内の選択のみが FUSE変更なしで可能となる。

### ビルド出力確認 ```Ctrl+Alt+S``` ```⌘+Alt+S```

（書込み可能な場合の）スケッチフォルダに、
スケッチがビルドされた HEX ファイル、
ブートローダーも一体に結合された HEX ファイル、
逆アセンブルコードリスト、
（IDE2.0では）EEPROM 初期化用 HEX ファイル
が出力される。

> スケッチがビルドエラーになる場合は何も出力されない。\
> スケッチが SDKサンプル直接の場合は（パスが書込禁止なので）出力されない。

### ブートローダー

STK500 version 1 プロトコルに基づく Arduino互換ブートローダーを同梱している。
代表的な UART と LED の組み合わせについてはビルド済のバイナリが用意されている。

> ブートローダーバイナリのリビルドは、makeコマンド（OS依存）が別途用意できれば本 SDKのみで行える。\
> v0.2.9から独自のコードに変更された。

### AVR_EA/EB 系統への対応

23/10現在、*avrdude* 内蔵の [__SerialUPDI__](https://avrdudes.github.io/avrdude/7.2/avrdude_19.html#index-SerialUPDI/) は、AVR_EA 系統を正しく操作することができない。
確実に AVR_EA 系統の不揮発メモリを読み書きできると判明しているプログラムライターは、[__UPDI4AVR__](https://askn37.github.io/product/UPDI4AVR/) と __PICkit4/5__ だけである。
本SDKに付属の *avrdude.conf.updi* は [__UPDI4AVR__](https://askn37.github.io/product/UPDI4AVR/) でのみ正しく動作する記述であることに注意されたい。

- *avrdude 7.2* で [__SerialUPDI__](https://avrdudes.github.io/avrdude/7.2/avrdude_19.html#index-SerialUPDI/) は AVR_EA に部分対応したが、標準添付の avrdude.conf はまだ十分検証されておらず、ほとんどの品種で正常動作の担保が取れていない。

### その他注意事項

以下に上げる完成販売品は本来、それぞれ既定の開発環境があり
この SDK が本来対応すべき範疇のものではないが、
搭載された MCU は対応範囲内なので
以下のようにすれば使用可能である。

#### Microchip Curiosity Nano AVR128DB48

この製品使用時のメニュー選択は次のようにしなければならない；

- ボードメニュー -> __MultiX Zinnia SDK [modernAVR]__ -> __AVR DB w/o Bootloader__ 必須
- Variant -> __48pin AVR128DB48 (128KiB+16KiB)__ 必須
- Console and LED -> __UART3 TX:PB0 RX:PB1 LED=PB3 (AVR128DB48 Curiosity Nano)__ 必須
- 書込装置選択 -> __Curiosity Nano (nEDBG: ATSAMD21E18)__ 必須

その他の同種製品も同様に、適切なオプションの手動選択が必要。

## 更新履歴

- v0.2.10 (23/12/20)
  - `7.3.0-avr8-gnu-toolchain-231214`に更新。
    - __AVR64DU28/32__ に暫定対応。
  - __Core Modules__ の `<api/UarfUART.h>`を微修正。`AVR_EVSYS=201`修正。
  - __Core Libraries__ に `<ReadUART.h>`を追加。`AVR_EVSYS=201`修正。

- v0.2.9 (23/12/11)
  - megaVAR/modernAVRについて、同梱ブートローダー全体を独自のArduino上位互換動作コードに変更。（`Optiboot`由来ソースコードを除去）
  - 同、CRCSCAN機能用CRC16/32検査値付与。
  - `<api/btools.h>`に`crc16_ccitt_false`関数を追加。

- v0.2.8 (23/11/24)
  - `7.3.0-avr8-gnu-toolchain-231113`に更新。

- v0.2.7 (23/10/18)
  - __AVR16EBxx__ に実験的対応
    - bootloader の正常動作は未確認
  - `dryrun`を書込器選択に追加。
  - `avrdude.conf`参照ルールの変更。
    - `arduino`/`UPDI4VAR`/`TPI4AVR`/`dryrun`を書込器に指定した場合のみ、ローカルの特別な設定ファイルを参照する。それ以外は規定の（tools/avrdude/etc内の）`avrdude.conf`を参照する。
    - この変更により、AVR_EA系統のようにまだ他の書込器で未対応／未検証のパーツ設定が分離された。

- v0.2.6 (23/10/16)
  - `7.2-arduino.1`に更新。
    - この版でも`serialupdi`は現状、AVR_EAを正しく操作できない。
  - `7.3.0-avr8-gnu-toolchain-231004`に更新。
    - `Atmel.ATautomotive_DFP.2.0.214.atpack (2022-03-03)`追加。`ATtiny416auto`対応。
    - `Atmel.AVR-Ex_DFP.2.7.184 (2023-10-02)`対応。

- v0.2.5 (23/10/09)
  - *avrdude.conf.updi* 記述を avrdude 7.1 準拠に改正

- v0.2.4 (23/09/09)
  - `7.3.0-avr8-gnu-toolchain-230831`に更新。
  - `programmers.txt`を改正。
    - `SerialUPDI`の`-xrtsdtr=High`オプションを有効化。

- v0.2.3 (23/07/09)
  - `7.3.0-avr8-gnu-toolchain-230628`に更新。
    - `<avr/eeprom.h>`が`AVR_EA`でも正常動作するよう改善。

- v0.2.2 (23/05/23)
  - `7.1-arduino.1`に更新。

- v0.2.1 (23/05/08)
  - `7.3.0-avr8-gnu-toolchain-230418`に更新。
    - __注意__ : この版では未だ`<avr/eeprom.h>`が`AVR_EA`では正常動作しない。
  - __AVR16EAxx__、__AVR32EAxx__ をバリアント選択に追加。
  - 添付 *avrdude.conf* での`UPDI4AVR`規定速度を`460800`に制限。
    - 古いCH3xx用ドライバにて速度上限があるため。（現行最新では改善されている）

- v0.2.0 (23/04/08)
  - `modernAVR`で`AVR_EA`対応。
    - 現時点の`AVR-LIBC`でビルド可能な __AVR64EA28/32/48__ をバリアント選択に追加。
    - __AVR64EA32__ を動作検証済表に追加。
    - 専用ブートローダー`optiboot_ex1`を追加。
    - `<api/FlashNVM.h>`に`AVR_EA`対応を追加。
    - __注意__ : 現時点の`AVR-LIBC`では`<avr/eeprom.h>`が`AVR_EA`で正常動作しない。

## 許諾

各構成要素はそれぞれ異なる配布ライセンスに属する。条件はそれぞれの規約に従う。

- BSD License
  - avr-libc
- GNU General Public License v2.0
  - avr-gcc
  - avrdude
- MIT License
  - other original document and code

## 著作表示

Twitter: [@askn37](https://twitter.com/askn37) \
GitHub: [https://github.com/askn37/](https://github.com/askn37/) \
Product: [https://askn37.github.io/](https://askn37.github.io/)

Copyright (c) askn (K.Sato) multix.jp \
Released under the MIT license \
[https://opensource.org/licenses/mit-license.php](https://opensource.org/licenses/mit-license.php) \
[https://www.oshwa.org/](https://www.oshwa.org/)
