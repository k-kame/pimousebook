= 開発 PC のセットアップ

はじめに開発用 PC のセットアップをしますが（ROS のインストール），PC の OS が windows 10 ／ ubuntu のどちらかで，やらなければならない内容が異なります．

というわけで，開発環境セットアップの流れを@<img>{fig_devchart}にまとめてみました．作業は，大きく３つに分けることができます．

 1. windows 上で ubuntu を動かす
 2. 開発ツールのインストール
 3. マウス開発環境の準備

ここで，作業 2 と 3 は，どちらの場合でも必要ですが，PC の OS が ubuntu の場合は作業 1 が不要となります．
個人的には，「windows 上で ubuntu」はとても快適ですが，構築時のオーバーヘッドが大きいので，環境構築大好き民以外にはおススメできないかも．

一方で，ubuntu PC を選ぶと，Linux Desktop に住むという苦行（？）が待っているので，どちらがいいとは言えないかもしれません．

デュアルブート@<fn>{dualboot}という選択肢もありますが，それなりにトラブル対応できる能力が必要だと思いますし，windows をぶっ壊すとダメージが大きいです（結構トラブったりする）．

というわけで，PC を windows 用／ubuntu 用 の二台準備するという富豪的アプローチがベストではありますが，お金がかかります．

遅い PC と割り切って，Raspberry Pi で ubuntu Desktop を使うという方法もありますが，現時点（2021.3）では，arm@<fn>{fn_arm}用 ubuntu Desktop は 20.10（短期サポート版）でしかサポートされておらず，20.10 では Visual Studio Code が ubuntu software からインスト―ル出来ないという問題点があります．おそらく，他にも様々な問題点が立て続けに起こることが予想されるので，自分で藪を開いて進める人しか使うことはできないでしょう．

というわけで，開発環境構築メリット／　デメリットをまとめてみました（こういう所が環境構築大好き民）．全てを満たす環境というものはないものですね．

//image[fig_devchart][開発環境構築フローチャート]{
開発環境構築フローチャート
//}

//footnote[dualboot][一台のパソコンで起動 OS を切り替える方法．ブートローダ（grub など）を使う]
//footnote[fn_arm][Raspberry Pi で使われている CPU．X64 と記載されているのは intel/AMD 系用なので動きません]

@<table>{devenvlist}

//table[devenvlist][開発環境メリット・デメリット]{
.	方法	利点	欠点
-----------
1	win 上で ubuntu	便利・最強	構築が面倒．ちょっとお金がかかる（X）
2	ubuntu PC	構築が楽	ubuntu 上に住むことになる
3	二台持ち	win に 影響せずに ubuntu が使える	お金がかかる．メンテが面倒		
4	デュアルブート	win に 影響せずに ubuntu が使える	トラブった時に win が消えることも
5	raspi Desktop	安く ubuntu Desktop が使える	最新版でしか使えない（トラブルが起こる）．遅い．熱暴走する．
//}

というわけで，自身の技量，懐具合，趣味性癖を考慮したうえで開発環境を選び，つぎに進んでください．

 1. OS が windows 10 の人　　>  4.1 章 に進む
 2. OS が ubuntu の人　　　　> 4.2 章 に進む

== windows 10 PC に WSL / ubuntu をインストール

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

@<ami>{WSLのインストール}

以下の，マイクロソフトのドキュメントに従って，WSLをインストールします．
 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/, （読み物）Windows Subsystem for Linux に関するドキュメント}
 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/install-win10, （こちらの「手動インストールの手順」の手順 1 を実行）Windows 10 用 Windows Subsystem for Linux のインストール ガイド}

実行上の注意点：
 * powershell の起動：winキーを左クリックして出るメニューの［ファイル名を指定して実行］で，powershell と書けば立ち上がる．
 * powershellの管理者権限への変更：立ち上げ後，以下のコマンドを入力
 ** @<code>{Start-Process powershell.exe -Verb runas}
 * WSL にはバージョン 1, 2 がありますが，使用するのは WSL 1 ですので，手順 1 で終了して 「ubuntu のインストール」に進んでください．WSL 2 までインストールした場合は，以下のコマンドで，バージョンを 1 に設定しておいてください．
 ** @<code>{wsl --set-version 1}

@<ami>{ubuntu のインストール}

以下の，マイクロソフトのドキュメントに従って，ubuntu をインストールします．バージョンが選べますが，ここでは 20.04 LTS を選びます（ubuntu の バージョンに対応する ROS のバージョンが異なります）．
 * @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/install-win10, （こちらの「手動インストールの手順」の手順 6 を実行）Windows 10 用 Windows Subsystem for Linux のインストール ガイド}
 * ubuntu のインストールが終わったら，以下のコマンドで，package を最新にしておきましょう（結構時間がかかります）．
 ** @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y}
 
//image[fig_ubuntuex][fig_ubuntuex]{
ubuntu のアイコン
//}

@<ami>{X Window System のインストール}

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

== 関連するソフトウェアのインストール

=== Visual Studio Code のインストール

@<ami>{windows 編}
　
 * @<href>{https://code.visualstudio.com/download, Visual Studio Code（エディタ）}のインストール ［↓Windwos 7, 8, 10 というアイコンをクリックしてインストーラーをDL，インストール］（※ Visual Studio とは異なるので注意）
 * 拡張機能のインストール（参考ページ）
 * Windows 側で Visual Studio Code（以下 vs code）を立ち上げる
 * 拡張機能の欄で［Remote Development］，[Remote - WSL]と検索してそれぞれインストールする＞
 * vs code を終了させる
 * ubuntu を起動させ，［code］と入力してvs code を起動する（最初は少し時間がかかる．これで，WSL にインストールした ubuntu から，windows 側の vs code を起動できるようになった）

@<ami>{ubuntu 編}



以上で，Linux 関係のインストールは終わりです．今後は，windows / ubuntu 共通で話を進めていきます．

=== ssh

ssh のインストールと設定（公開鍵暗号という謎ワードに反応してしまう人は@<href>{こちら, https://knowledge.sakura.ad.jp/3543/}．

 * cd ~
 * ssh-keygen と入力してEnterすると色々聞いてくるが，Enterで流す．
 * ls -al ~/.ssh で id_rsa と id_rsa.pub ができてるか確認（id_rsaは決して人に見せない）

=== git/github

「gitとはなんだ？」と思ってしまった迂闊な人は@<href>{こちら, https://o2project.github.io/steins-git/#chapter0-introduction}．

git のインストール

 * @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove}
 * @<code>{sudo apt install git}

ssh のインストールと設定（公開鍵暗号という謎ワードに反応してしまう人はこちら）

 * cd ~
 * ssh-keygen と入力してEnterすると色々聞いてくるが，Enterで流す．
 * ls -al ~/.ssh で id_rsa と id_rsa.pub ができてるか確認（id_rsaは決して人に見せない）
 * github にアカウントを作成
 * github HPに移動
 * 右上の sing up を選んで必要事項を記入．アカウント種別は無料（free）でOK（なんも難しいことはないと思うが参考ページ）
 * github に公開鍵を登録
 * github にログインして右上のメニューから［Settings］を選択
 * 左柱のメニューから［SSH & GPG keys］を選択
 * ［SSH key］欄の［New SSH key］を選び
 * Title欄はなんでもよい（my wsl とか）
 * key には以下の手順で id_rsa.pub の中身をコピペ
 * cat ~/.ssh/id_rsa.pub
 * ↑で画面に文字列が表示されるので，以下のssh-rsa から k-kame@control-kame （これは人によって違う）をマウスで選択して ctrl-c
 * key 欄にペーストして［Add SSH key］

//image[fig_gitset][fig_gitset]{
githubの環境設定
//}

//image[fig_sshset][fig_sshset]{
sshhubの環境設定
//}

== ubuntu に ROS をインストール

ROS
