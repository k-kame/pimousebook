= 開発用 PC の設定（windows 10 上に Ubuntu 環境を構築）
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

X Window System（以下 X あるいは X11）とは，UNIX 系 OS で標準的に用いられるウィンドウシステムです．簡単に言うと，UNIX 系 OS で，「複数のウィンドウをマウスで操作」という Windows のような操作を実現するためのシステムソフトウェアです．

つまり，素の Linux では，コマンドで使うソフトウェアしか使うことができません．一方で，ROS にはマウスを使うアプリ（rqt など）も含まれますので X が必要となります．

X の機能を提供するソフトウェアを「X サーバー」といい，幾つかの種類があります．
ここでは，無償／有償の観点から 2 種類を取り上げます（@<table>{list_x}）．結論から言うと，X410 を安売りの時に買うのが，楽で安定していると思います（定価 5,850 円だが，かなりの頻度で1,000 円ぐらいで安売りしている）．

//table[list_x][Windows 用 X サーバー一覧]{
ソフトウェア	概要	備考
----------
X410		（有償）	Microsoft Store で販売されている X サーバー 
VcXsrc		（無償）	
//}

X410のインストール／利用方法

 * インストール
 ** Microsoft store でポチるだけ．
 * 利用方法
 ** アイコンをクリックするだけ（一般的な windows アプリと同じ）

VcXsrcのインストール／利用方法

 * インストール
 ** @<href>{https://www.atmarkit.co.jp/ait/articles/1812/06/news040.html, WSL上にXサーバをインストールしてGUIを実現する（VcXsrv編）}
 * 利用方法 
 ** [スタートメニュー] から [VcXsrv] > [XLaunch] を起動
 ** 起動過程で，基本［次へ (N)＞］を押していればいいが，Extra settings ページの［Additional parameters for VcXsrc］には［:0 -ac -multiwindow -reset -terminate -nowgl］と入力
 
X を使うための設定

 * ~/.bashrc （bashの設定ファイル）に設定を追加（bashはshellの一種．シェルに疑問を持った粗忽者はこちら．~ は home directory の意（=/home/ユーザー名））
 * vi ~/.bashrc   （vi はエディタ．代わりに nano ~/.bashrc でもよい．だが vim は避けて通れない道）
 * 以下を最後の行に追加・保存
 ** export DISPLAY=localhost:0.0
 ** export GAZEBO_IP=127.0.0.1
 ** export LIBGL_ALWAYS_INDIRECT=0
 ** source ~/.bashrc

X の動作試験（X サーバー対応アプリをインストール／実行）
 * ターミナル（Ubuntu）を起動
 * @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y}
 * @<code>{sudo apt install x11-apps}
 * @<code>{xeyes}
目玉がでたらOK