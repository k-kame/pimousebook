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

== Raspberry Pi OS への ROS インストール（ROSberryPi）

ラズパイ OS への ROS のインストールは，Ubuntu へのそれとは少々手順が異なるので，先にやってしまいます（〇章 ROS のインストールは読み飛ばしてください）．@<href>{http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Melodic%20on%20the%20Raspberry%20Pi, 公式ドキュメント}に従ってインストールしてください．

基本的に，インストールされる Linux や ROS のバージョンは公式に従いますが（長いものには巻かれるスタイル），インストール後に確認しておきましょう．確認方法は以下の通りです．

 * @<code>{cat /etc/os-release}
 * @<code>{printenv | grep ROS}

本書籍の執筆時点では，Raspberry Pi OS のバージョンは，上のコマンドの VERSION 行から 10 buster，ROS のバージョンは，下のコマンドの ROS_DISTRO 行から melodic でした（ubuntu 18.04 に対応した ROS1）．
