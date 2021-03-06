= ROS のセットアップ
== ROS の種類
現段階では，ROS とは「Ubuntu 上で動くロボットアプリ作成プラットフォーム」だと思っておけば良いと思います（嘘 50%．動かせるようになったら詳しく正しく勉強してください）．

インストール時に迷わないために，以下の点を理解しておくと良いです．

 * ROS1 と ROS2 があるけど違うものです．本書では ROS1 について解説しています．
 * ROS1 にもバージョンがあり，何を使うかは Ubuntu のバージョンで決まります．
 * 現在なら，Ubuntu を 20.04 LTS とすると，ROS1 なら Noetic，ROS2 なら Foxy が対応しており，以降の作業は「Ubuntu 20.04 LTS に ROS1 Noetic をインストールする」ということになります．

== ROS の情報源：

基本的には，ROS.org（英語）を見ることをお勧めします．
日本語ページもありますが，情報が古く，コマンドがそのまま実行できないことがあります．

 * @<href>{https://www.ros.org/, ROS Home Page（英語）}
 * @<href>{http://wiki.ros.org/ja, ROS Home Page（日本語）}

書籍もありますが（以下参照），同様に，インストール手順などは英語 HP を参照し，バージョン違いなどに影響されない事を調べる際には書籍を参照するなど，使い分けたほうが良いと思います．

参考までに，著者は (1) を良く開きます（最初に買ったから．他意はありません）．また，「ROS2 ってなんなの？」と思うおませさんは，(3) も読むと良いと思います．

また，少し話は異なりますが，ROS を使用時には，Linux コマンドの入力を求められる場面が多々あります．
WEB でも調べられますが，コマンドリファレンスを持っておくのも良いと思います．

 1. 表允皙, 倉爪亮, じょんりょうん：@<href>{https://www.amazon.co.jp/ROS%E3%83%AD%E3%83%9C%E3%83%83%E3%83%88%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E3%83%90%E3%82%A4%E3%83%96%E3%83%AB-%E8%A1%A8%E5%85%81%E7%9A%99-ebook/dp/B07BKVQG5B/ref=sr_1_1?__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&dchild=1&keywords=ROS&qid=1615683157&sr=8-1, ROS ロボットプログラミングバイブル}, オーム社（2018）．
 1. 西田健ほか, @<href>{https://www.amazon.co.jp/%E5%AE%9F%E7%94%A8%E3%83%AD%E3%83%9C%E3%83%83%E3%83%88%E9%96%8B%E7%99%BA%E3%81%AE%E3%81%9F%E3%82%81%E3%81%AEROS%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0-%E8%A5%BF%E7%94%B0-%E5%81%A5/dp/462767581X/ref=sr_1_3?__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&dchild=1&keywords=ROS&qid=1615683157&sr=8-3, 実用ロボット開発のためのROSプログラミング}, 森北出版（2018）．
 1. 近藤豊, @<href>{https://www.amazon.co.jp/ROS2%E3%81%A7%E3%81%AF%E3%81%98%E3%82%81%E3%82%88%E3%81%86-%E6%AC%A1%E4%B8%96%E4%BB%A3%E3%83%AD%E3%83%9C%E3%83%83%E3%83%88%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0-%E8%BF%91%E8%97%A4-%E8%B1%8A/dp/4297107422/ref=sr_1_5?__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&dchild=1&keywords=ROS&qid=1615683157&sr=8-5, ROS2ではじめよう 次世代ロボットプログラミング}, 技術評論社（2019）．
 1. 沓名亮典, @<href>{https://www.amazon.co.jp/%EF%BC%BB%E6%94%B9%E8%A8%82%E7%AC%AC3%E7%89%88%EF%BC%BDLinux%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89%E3%83%9D%E3%82%B1%E3%83%83%E3%83%88%E3%83%AA%E3%83%95%E3%82%A1%E3%83%AC%E3%83%B3%E3%82%B9-%E6%B2%93%E5%90%8D%E4%BA%AE%E5%85%B8-ebook/dp/B00Z5OCH1G/ref=sr_1_2?__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&crid=2SOQPURRGL7R7&dchild=1&keywords=linux+%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89%E3%83%AA%E3%83%95%E3%82%A1%E3%83%AC%E3%83%B3%E3%82%B9&qid=1615688576&sprefix=linux+%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89%2Caps%2C266&sr=8-2,［改定第3版］Linuxコマンドポケットリファレンス}, 技術評論社（2015）．

== ROS のインストール

実作業に入る前に，Ubuntu バージョンの確認と手順の把握をしておきましょう．

@<ami>{Ubuntu バージョンの確認：}

ターミナルで以下コマンドを実行し，VERSION の項目に 20.04.x（x は変化する）と表示されていれば OK です．違ったときは，OS のインストールをやり直すか，ROS のバージョンを変更するかしましょう．

 * @<code>{cat /etc/os-release}

@<ami>{手順の把握：}

インストールは公式 HP（英語）を参照して実施します（@<href>{http://wiki.ros.org/noetic/Installation/Ubuntu, Ubuntu install of ROS Noetic}）．

目次は以下のようになっています．ここでは 1.1-1.6 を実施します．
上から順に全部実施すると「場合分け」に引っかかるので気を付けて下さい（目次に注意点を追記）．
2. Tutorial は ラズパイOS と同じですので，次節にまとめます．

1. Installation

 1. Configure your Ubuntu repositories
 1. Setup your sources.list
 1. Set up your keys（注：枠囲みの2個目は実施しない）
 1. Installation（注：太字部分が場合分け．Desktop-Full Install を実施）
 1. Environment setup（注：枠囲み Bash の方を実施）
 1. Dependencies for building packages

2. Tutorials

== Tutorials：ワークスペースの作成

@<href>{http://wiki.ros.org/ROS/Tutorials, ROS Tutorials} の目次は，以下のようになっています（インストールページの 2. Tutorials のリンク先です）．

これを全部読めば，ROS に詳しくなれますが，英語なので辛いと思います．
よって，本内容は参考文献 [1] で勉強することにして，ここでは，1.1.1 のみ行います．

 * 1. Core ROS Tutorials
 * 1.1 Beginner Level
 * @<b>{1.1.1 Installing and Configuring ROS Environment} ◀◀◀ これだけ実施
 * 1.1.2 Navigating the ROS Filesystem
 * 1.1.3 ...
 * 1.2 Intermediate Level
 * 2. ROS Standards
 * 3. Tutorials for Other ROS Libraries
 * ...

さらに，@<href>{http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment, 1.1.1} の中の目次は以下のようになっています．この中の (3) だけを行います．

 1. Install ROS
 1. Managing Your Environment
 1. @<b>{Create a ROS Workspace} ◀◀◀ 「ワークスペースの作成」．これだけ実施

@<ami>{ワークスペースとは}

ワークスペースとは，あるロボット用のプログラム一式を置くフォルダの事です．
プログラムには，センサの受信やモーター制御のような低レベルのものから，AI のような高レベルのものまで全てを含みます．

例えば，GPS を使って自律走行するロボット A を考えると，ロボットには「GPS 値から経路を決定する機能」と「決定された経路に従って移動する機能」が必要となり，その機能を実現するプログラムが，ワークスペース A に置かれることになります．

一方で，マイクロマウスでは GPS を使わないので，マウス用プログラムは別のワークスペース B に置きます．

このような仕組みにより，同じ PC 上で，複数ロボットのプログラムを分けて開発できます．

@<ami>{ワークスペースの作成}

ワークスペース作成は，以下のコマンドで作成します．

1. ディレクトリの作成（catkin_ws がワークスペースの名前．複数のワークスペースを作る際はここを変える）

 * mkdir -p ~/catkin_ws/src

2. ワークスペースの初期化／ROS 開発システムへの組み込み

 * cd ~/catkin_ws/
 * catkin_make
 * source devel/setup.bash