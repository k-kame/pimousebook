= 開発用マシンの設定（PC + windows 10 + Ubuntu）
== 前提条件の確認／事前作業
本節では，windows 10 PC で Ubuntu PC と同じ作業ができるようにします．

作業は，以下3つのソフトウェアのインストールに分けることができます．

 1. Windows Subsystem for Linux (WSL)@<fn>{wsl} 
 1. Ubuntu
 1. X windows system@<fn>{xwin}

//footnote[wsl][仮想化技術により windows から Linux を利用するための仕組み．Ubuntu 以外の Linux もインストールできます]
//footnote[xwin][Linux で windows のようなマウス操作を実現するための基本ソフトウェア]

では，早速作業をすすめ・・・る前に，前提条件の確認と，事前作業を済ませておきましょう．

@<ami>{前提条件}
 * Windows 10 64bit 入りPC（できればメモリ16GB／できればCore i7／独立 GPU は無くても多分OK）

@<ami>{事前作業}
 * データのバックアップ（ google drive, one drive などのクラウドストレージを利用 ）
 * Windows のアップデート：［設定]＞[更新とセキュリティ］で windows のバージョンを 1909 以上に上げておく（［設定＞システム＞バージョン情報］で確認できる）

== WSL のインストール

以下の，マイクロソフトのドキュメントに従って，WSLをインストールします．

 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/, WSL に関するドキュメント}（読み物）
 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/install-win10, Windows 10 用 Windows Subsystem for Linux のインストール ガイド}の「手動インストールの手順」の手順 1 を実行

実行上の注意点：

 * powershell の起動：winキーを左クリックして出るメニューの［ファイル名を指定して実行］で，powershell と書けば立ち上がる．
 * powershellの管理者権限への変更：立ち上げ後，以下のコマンドを入力
 ** @<code>{Start-Process powershell.exe -Verb runas}
 * WSL には WSL1 と WSL2（バージョン違い）がありますが，使用するのは WSL1 です．手順 1 で終了して 「Ubuntu のインストール」に進んでください．WSL2 までインストールした場合は，以下のコマンドで，バージョンを WSL1 に設定してください．
 ** @<code>{wsl --set-version 1}

== Ubuntu のインストール

マイクロソフトのドキュメントに従って，Ubuntu をインストールします．
バージョンが選べますが，ここでは 20.04 LTS を選びます（Ubuntu の バージョンに対応する ROS のバージョンが異なります）．

 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/install-win10, （こちらの「手動インストールの手順」の手順 6 を実行）Windows 10 用 Windows Subsystem for Linux のインストール ガイド}
 * Ubuntu のインストールが終わったら，以下のコマンドで package を最新にしておきましょう（結構時間がかかります）．
 ** @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y}
 
//image[fig_Ubuntuex][fig_Ubuntuex]{
Ubuntu のアイコン
//}

== X Window System のインストール
=== X Window System とは

X Window System（以下 X あるいは X11）とは，UNIX 系 OS で標準的に用いられるウィンドウシステムです．簡単に言うと，UNIX 系 OS で，「複数のウィンドウをマウスで操作」という Windows のような操作を実現するためのシステムソフトウェアです．

つまり，素の Linux では，コマンドで使うソフトウェアしか使うことができません．一方で，ROS にはマウスを使うアプリ（rqt など）も含まれますので X が必要となります．

X の機能を提供するソフトウェアを「X サーバー」といい，幾つかの種類があります．
ここでは，無償／有償の観点から 2 種類を取り上げます（@<table>{list_x}）．結論から言うと，X410 を安売りの時に買うのが，楽で安定していると思います（定価 5,850 円だが，かなりの頻度で1,000 円ぐらいで安売りしている）．

//table[list_x][Windows 用 X サーバー一覧]{
ソフトウェア		メリット／デメリット					備考
----------
（有償）X410		導入・起動が楽．安定している／有償		MS ストアで販売 
（無償）VcXsrc		無償／起動時にひと手間必要．時々謎の挙動をする
//}

どちらを使うか決めたら，早速インストール作業を始めます．

まず，インストール前に，以下の設定をしておきます（共通）．作業内容は以下の通りです

 * エディタで ~/.bashrc（bashの設定ファイル）を編集して，一番下に環境変数 DISPLAY を追加（以下の内容）．

@<code>{export DISPLAY=localhost:0.0}

上の説明は，Linux 初心者の人には意味不明だと思いますので，補足します．

@<ami>{よくわからない人のための補足説明}

 * .bashrc は，bash というシェル（shell）の設定ファイルです．
 * シェルとは，コマンドを入力するための黒い画面の事です．興味のある人は@<href>{https://ja.wikipedia.org/wiki/%E3%82%B7%E3%82%A7%E3%83%AB, こちら}．@<href>{https://www.ohmsha.co.jp/book/9784274064067/, この本も読もう}．
 * ~ は，ホームディレクトリの事です（自分用設定ファイルやデータファイルを置くフォルダ）．つまり ~/.bashrc とは，自分専用の bash の設定ファイルです．
 * 編集にはエディタを使います（windows のメモ帳のようなもの）．Linux では vim がよく使われますが，vim は操作が特殊なので初心者には拷問です．（@<href>{https://vim.rtorr.com/lang/ja, vim cheat sheat}でググって下さい（リンク先は一例））．ですので，この冊子では，メモ帳っぽい nano というエディタを使います（逃げない素敵な人は頑張ってください．今逃げても決して逃れられませんし）．

@<ami>{nano エディタによる .bashrc の編集}

 * nano のインストール： @<code>{sudo apt install nano}
 * ファイルを開く： @<code>{nano ~/.bashrc}
 * 一番下に以下を追加： @<code>{export DISPLAY=localhost:0.0}
 * nano を終了（保存すること）：^x （CTRL を押しながら x．その後，保存するか聞いてくるので y）
 * 設定を反映させる：@<code>{source ~/.bashrc}

以上の設定を終えたら，2.4.2, 2.4.3 のいずれかに進んでください．

=== X410 のインストール／利用方法

 * インストール
 ** Microsoft store でポチるだけ．
 * 利用方法
 ** アイコンをクリックするだけ（一般的な windows アプリと同じ）

=== VcXsrc のインストール／利用方法

 * インストール
 ** @<href>{https://www.atmarkit.co.jp/ait/articles/1812/06/news040.html, WSL上にXサーバをインストールしてGUIを実現する（VcXsrv編）}を参照．
 * 利用方法 
 ** [スタートメニュー] から [VcXsrv] > [XLaunch] を起動
 ** 起動過程で，基本［次へ (N)＞］を押していればいいが，Extra settings ページの［Additional parameters for VcXsrc］には［:0 -ac -multiwindow -reset -terminate -nowgl］と入力
 
=== X の動作試験（X サーバー対応アプリをインストール／実行）

 * ターミナル（Ubuntu）を起動
 * @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y}
 * @<code>{sudo apt install x11-apps}
 * @<code>{xeyes}

以上の作業で，マウスを追いかける目玉が表示されれば OK．