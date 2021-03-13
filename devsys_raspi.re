= 開発用マシンの設定（Rasperry Pi + Raspberry Pi OS + ROS）

== Raspberry Pi（ラズパイ）に Raspberry Pi OS（ラズパイ OS）をインストールする

Raspberry Pi OS（旧 Raspbian）は標準OSで，これに ROS をインストールして開発マシンにできます．ラズパイには ubuntu もインストールできますが，現時点（20.04 LTS）では Desktop 版がリリースされていないので，ラズパイ OS を前提として話を進めます．20.10 には Desktop 版がありますが，後述の　VS code が標準の方法でインストールできないなどの問題があります．種々の問題を自分で解決できる人は，Ubuntu 20.10 Desktop をインストールするのも良いでしょう．

ラズパイ OS のインストールは以下の手順で行います（注意：Imager のダウンロードから ROS インストール終了まで半日ぐらいかかります）．

@<ami>{準備する物}

 * Raspbery Pi 4 B (4GB) および付属物（電源ケーブル，キーボード，マウス，モニタ）
 * micro SD card (8 GB 以上)
 * PC (windows / ubuntu どちらでも)．インターネットに繋がっていること．micro SD が読めること．

@<ami>{Windows / Ubuntu PC での作業}

 1. PC で，@<href>{https://www.raspberrypi.org/, Raspberry Pi 財団 HP} から Raspberry Pi Imager（以下「Imager」）をダウンロード（win 用だと imager_1.5.exe）．
 1. imager_1.5.exe を実行して Imager をインストール．
 1. ラズパイ OS のインストール：micro SD が読める状態にして Imager を実行．インストール先とインストール OS を選ぶと，ダウンロードとインストールが始まる． 

@<ami>{Raspberry Pi での作業}

 1. 動作確認：micro SD をラズパイに差して起動．

@<ami>{Raspberry Pi OS 独自の設定}

 * ssh の設定@<fn>{app_ssh} ：最初からインストールされていますが，外からの接続が許可されていないので，[メインメニュー] > [Raspberry Pi の設定] の [システムタブ] で自動ログインを無効に，[インターフェースタブ] で ssh を有効にしておく．設定については，4.2 章を参照．

== Raspberry Pi OS への ROS インストール（ROSberryPi）

ラズパイ OS への ROS のインストールは，Ubuntu へのそれとは少々手順が異なります．@<href>{http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Melodic%20on%20the%20Raspberry%20Pi, 公式ドキュメント}に従ってインストールしてください．



