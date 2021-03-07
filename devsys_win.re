= 開発 PC（windows 10）上に ubuntu 環境を構築（WSL/ubuntu/X window system）

本節では，OS が windows 10 の PC に，ubuntu をインストールし，ubuntu PC と同じ作業ができるようにします．

作業は，windows subsystem for Linux (WSL) のインストールと，ubuntu のインストールに分けることができます．ここで，WSL とは，仮想化技術により，windows から Linux を利用するためのしくみであり，その上に ubuntu 以外の Linux distribution もインストールすることができます．

では，早速作業をすすめていきましょう．

その前に，以下の前提条件と事前作業を済ませておきましょう．

@<ami>{前提条件}
 * Windows 10 64bit 入りPC（できればメモリ16GB，できればCore i7，GPUはなくても多分OK）
 * ubuntu 18.04 インストールPCを使う人は，「windows環境の整備」，「ubuntu環境の整備」を飛ばす
 * 消えたら困るデータはバックアップを取っておく（あるいは無料のクラウドストレージ（google drive, one drive など）に入れておく）
 * Windows のアップデート
 * ［設定＞更新とセキュリティ］で windows のバージョンを1909まで上げておく（［設定＞システム＞バージョン情報］で確認できる）

== WSLのインストール

以下の，マイクロソフトのドキュメントに従って，WSLをインストールします．
 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/, （読み物）Windows Subsystem for Linux に関するドキュメント}
 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/install-win10, （こちらの「手動インストールの手順」の手順 1 を実行）Windows 10 用 Windows Subsystem for Linux のインストール ガイド}

実行上の注意点：
 * powershell の起動：winキーを左クリックして出るメニューの［ファイル名を指定して実行］で，powershell と書けば立ち上がる．
 * powershellの管理者権限への変更：立ち上げ後，以下のコマンドを入力
 ** @<code>{Start-Process powershell.exe -Verb runas}
 * WSL にはバージョン 1, 2 がありますが，使用するのは WSL 1 ですので，手順 1 で終了して 「ubuntu のインストール」に進んでください．WSL 2 までインストールした場合は，以下のコマンドで，バージョンを 1 に設定しておいてください．
 ** @<code>{wsl --set-version 1}

== ubuntu のインストール

以下の，マイクロソフトのドキュメントに従って，ubuntu をインストールします．バージョンが選べますが，ここでは 20.04 LTS を選びます（ubuntu の バージョンに対応する ROS のバージョンが異なります）．
 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/install-win10, （こちらの「手動インストールの手順」の手順 6 を実行）Windows 10 用 Windows Subsystem for Linux のインストール ガイド}
 * ubuntu のインストールが終わったら，以下のコマンドで，package を最新にしておきましょう（結構時間がかかります）．
 ** @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y}
 
//image[fig_ubuntuex][fig_ubuntuex]{
ubuntu のアイコン
//}

== X Window System のインストール

X Window System（以下，X 或いは X11）とは，UNIX 系 OS で標準的に用いられるウィンドウシステムです．簡単に言うと，UNIX 系 OS を windows みたく「複数のウィンドウをマウスで操作」という操作形態を実現するために必要なシステムソフトウェアです．

つまり，素の Linux では，コマンドラインで使うソフトウェアしか使うことができません．一方で，ROS にはマウス操作が必要なアプリ（rqt など）も含まれますので，これを使うために，X をインストールします．

X の機能を提供するソフトウェアを「X サーバー」といい，幾つかの種類があります．著者も大してわかっていないので，ここでは，無償／有償の観点から 2 種類を取り上げます（@<table>{list_x}）．結論から言うと，X410 を安売りの時に買うのが，楽で安定していると思います（定価 5,850 円だが，かなりの頻度で1,000 円ぐらいで安売りしている）．

//table[list_x][windows 用 X サーバー一覧]{
ソフトウェア	概要
X410		Microsoft Store で販売されている有償の X サーバー 
VcXsrc		フリーの X サーバー 
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
 * ターミナル（ubuntu）を起動
 * @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y}
 * @<code>{sudo apt install x11-apps}
 * @<code>{xeyes}
目玉がでたらOK