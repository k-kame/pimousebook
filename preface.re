= はじめに
== コンテンツ整理

 * 本書のねらい：マイクロマウス（競技） < ラズパイマウス < Linux <<< ROS　手を動かしながらROSを理解するため本です
 * ラズパイマウスの開発プロセスと開発環境 

自主学習のための環境構築（概念編）

 * ラズパイマウス（実機）の開発環境と開発プロセス
 ** 松：ラズパイマウスを買ってしまう編
 *** 1 -> 2/3 
 ** 竹：ラズパイを買ってしまう編
 *** 1（部分）-> 2/3 
 ** 梅：Windows PC もしくは Linux PC だけで済ます編
 *** 2/3

 * シミュレーターの開発環境と開発プロセス
 ** 4/5

自主学習のための環境構築（実作業編）

 1. ラズパイマウス（もしくはラズパイ）のセットアップ
 1. 開発用PCのセットアップ（Windows 10 PC 編）
 1. 開発用PCのセットアップ（Linux PC 編）
 1. ラズパイマウス（実機編）を走らせる
 1. シミュレーション環境のセットアップ（Windows 10 編）
 1. シミュレーション環境のセットアップ（Linux 編）
 1. ラズパイマウスを走らせる（シミュレーション編）
 1. シミュレーション用迷路を作る
 1. 総合：シミュレーションで開発して実機を走らせる 

//image[totalimage][開発の全体像]{
開発の全体像
//}

== 本書のねらい

本書は，これからロボット開発（ハードもソフトも）に関わる人は知っておくべき（と著者が勝手に思っている）ROS（Robot Operating System）について，『@<b>{環境構築}と@<b>{制御プログラム開発}のとっかかりがつかめる』ようになることを目的として作られました．

教材には，Raspberry Pi Mouse（以下「ラズパイマウス」） を利用します．その理由は，システム構成がシンプルで扱いやすいからです．

ちなみに，ラズパイマウスは「マイクロマウス競技」というロボット競技のための自律型ロボットで， CPU に Raspberry Pi（以下「ラズパイ」）を使用しており，ラズパイには Linux ディストリビューションの一種類である ubuntu がインストールされて，その上で ROS が動いています．

@<b>{「もう何言ってるんだかわからねぇ寝る！」}

と思った人．そういう人のための冊子であり，そういう人が，上のセリフを言う側になるための冊子です．

もちろん，ラスパイや ROS の解説書には，もっと優れたものがありますが，優れ過ぎているため，初学者の特に機械系の高専生が読むと正気度が下がる危険性があります．

 * @<href>{https://www.amazon.co.jp/Raspberry-Pi%E3%81%A7%E5%AD%A6%E3%81%B6-ROS%E3%83%AD%E3%83%9C%E3%83%83%E3%83%88%E5%85%A5%E9%96%80-%E4%B8%8A%E7%94%B0-%E9%9A%86%E4%B8%80/dp/4822239292/ref=sr_1_1?__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&dchild=1&keywords=%E4%B8%8A%E7%94%B0%E9%9A%86%E4%B8%80&qid=1613801044&sr=8-1,上田隆一： Raspberry Piで学ぶ ROSロボット入門，日経BP（2017）}．
 * @<href>{https://www.amazon.co.jp/ROS%E3%83%AD%E3%83%9C%E3%83%83%E3%83%88%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E3%83%90%E3%82%A4%E3%83%96%E3%83%AB-%E8%A1%A8-%E5%85%81%E3%80%93/dp/4274221962/ref=pd_sbs_1?pd_rd_w=NqOlJ&pf_rd_p=98aa37b9-be8c-4afb-83e7-b68aef3d17b4&pf_rd_r=76T7P9S51858HMTD4159&pd_rd_r=606b122c-60ec-4557-80d6-09b1b0e02265&pd_rd_wg=gol6E&pd_rd_i=4274221962&psc=1,ピョ・ユンソク，倉爪亮，ジョン・リョウン：ROSロボットプログラミングバイブル，オーム社（2018）}．

ですので，上記書籍はポチって本棚にカッコよく飾りましょう．本冊子で手を動かし，悩んだり理解が進んだ時点で紐解くのが良いかと思います．

自分の PC と Raspberry Pi に ubuntu と ROS をインストールして，ロボット開発ができるようになりましょう！

参考までに：

 * ラズパイマウスとは：@<href>{https://rt-net.jp/,（株）アールティ} が販売する，Raspberry Pi を搭載したマイクロマウスです．
 * マイクロマウス競技とは：参加者自らが作った自立型ロボットが自律的に（自分の力だけで）迷路を探索し，ゴールまでに達する最短時間を競う競技です．（@<href>{https://www.ntf.or.jp/mouse/, （公）ニューテクノロジー振興財団} HPより抜粋）
 * Raspberry Pi とは：イギリスの @<href>{https://www.raspberrypi.org/,ラズベリーパイ財団} によって開発されている，ARMプロセッサを搭載したシングルボードコンピュータです．
 * ROS（Robot Operating System）とは：ロボット用ソフトウェアの開発を支援するライブラリとツールを提供するミドルウェア．主にLinux上で動作する（ @<href>{http://wiki.ros.org/ja, ROS.org} 参照 ）．
 * Linux：Linux は Linux です（ 参考：@<href>{https://ja.wikipedia.org/wiki/Linux,Wikipedia} ）．

== 開発環境の準備：概念編

ラズパイマウスの開発で必要なのは，開発用PCとラズパイマウス本体の２つです．開発環境のイメージを@<img>{fig_devsys}に示します．

//image[fig_devsys][開発の全体像]{
開発の全体像
//}

この環境（全部入り）は，以下の開発プロセスを想定しています．

 1. PC の ubuntu 上で，制御プログラムを開発する．
 2. シミュレーションで動作を確認する．
 3. 制御プログラムを github@<fn>{github} 経由でマウスに送る．
 4. マウスで制御プログラムを実行
 5. PC 上の ROS 標準モニタリングツール@<fn>{rqt}でマウスの状態をモニタリング
 6. 1 に戻る（不具合修正など）

//footnote[github][git（プログラムの変更履歴を管理するソフトウェア）をホストするwebサービス．無料で使える．]
//footnote[rqt][rqtなど．]

一方で，上記ような，マウスを購入し，web サービスを利用しないと開発ができないわけではありません．極端な話，紙と鉛筆があれば（或いは無くても）開発は可能ですが，ここでは，素の Windows PC を想定した開発プロセスを考えます（マウスは共用物を利用．ただし，ＯS 用 micro SD は自前で準備）．

 1. windows 10 上のエディタ（メモ帳など）で制御プログラムを開発する．
 2. マウス（借り物）に SD を差して起動．
 3. PC をマウスにリモート接続してプログラムを転送・実行．

しかし，このような開発プロセスは，あまりお勧めできません（というか，著者はこんな方法で開発したくありません）．

一方で，全部入り環境の整備には結構な費用がかかるので，これを準備できる人はあまりいないと思います．具体的には，

 * ラズパイマウス：90,200円（フルキット・税込み）
 * シミュレーションが満足に動くPC：独立 GPU を積んだ，いわゆる「ゲーミングPC」．100,000~．

そこで，間をとって，以下の開発環境／開発プロセスを想定することにします．

 * （全部入り）からマウスを引き算．
 * 多少勉強代を出そうという人には，Raspberry Pi の購入をお勧めします@<fn>{buyraspi}．走らないだけで，マウスの制御システムが構築でき，制御プログラムの転送にも便利です．
 * WSLは勿論インストールします．
 * シミュレーション環境は，独立 GPU を積んでいなくても，そこそこの PC なら何とか動くらしいので，インストールしてみましょう（便利だと思ったら買えばいいのです買えば）．

//footnote[buyraspi][ボード単体：約 6,000 円／スターターキット：約 10,000 円．別途モニタ，キーボード，マウス必要．@<href>{https://www.switch-science.com/, スイッチサイエンス} などで購入可能]

ただし，いきなり環境整備だけに勤しむのは普通の人には苦痛らしいので，徐々に構築することにします（著者は楽しいです）．

@<table>{shoppinglist}

//table[shoppinglist][必要なものリスト]{
.	品名				単価		個数	小計		備考
---------
1	ノートPC			100,000		1		100,000		開発用@<fn>{devnote}
2	Raspberry Pi 3 B+	10,000		1		10,000		スターターキット@<fn>{raspikit}
3	USB メモリ (32G)	1,000		1		1,000				
3	micro SD (32G)		1,000		1		1,000
4	ワイヤレスキーボード＆マウス	7260	1	7260	Logicool K380 キーボード M350 マウスコンボ
5	モバイルモニタ		20,000	1	20,000	Full HD 13.3 インチ（cocopar など）
//}


//footnote[devnote][micros SD カードが読めること．ノートが便利／独立GPUがあるとなおよい．]

//footnote[raspikit][ケース，ACアダプタ，HDMIケーブル，micro SD (32G) 付き／別途キーボード，マウス，モニタが必要]

== 開発 PC のセットアップ

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

=== windows 10 PC に WSL / ubuntu をインストール

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

=== 関連するソフトウェアのインストール

==== Visual Studio Code のインストール

@<ami>{windows 編}
　
 * @<href>{https://code.visualstudio.com/download, Visual Studio Code（エディタ）}のインストール ［↓Windwos 7, 8, 10 というアイコンをクリックしてインストーラーをDL，インストール］（※ Visual Studio とは異なるので注意）
 * 拡張機能のインストール（参考ページ）
 * Windows 側で Visual Studio Code（以下 vs code）を立ち上げる
 * 拡張機能の欄で［Remote Development］，[Remote - WSL]と検索してそれぞれインストールする＞
 * vs code を終了させる
 * ubuntu を起動させ，［code］と入力してvs code を起動する（最初は少し時間がかかる．これで，WSL にインストールした ubuntu から，windows 側の vs code を起動できるようになった）

@<ami>{ubuntu 編}




以上で，Linux 関係のインストールは終わりです．今後は，windows / ubuntu 共通で話を進めていきます．

==== ssh

ssh のインストールと設定（公開鍵暗号という謎ワードに反応してしまう人は@<href>{こちら, https://knowledge.sakura.ad.jp/3543/}．

 * cd ~
 * ssh-keygen と入力してEnterすると色々聞いてくるが，Enterで流す．
 * ls -al ~/.ssh で id_rsa と id_rsa.pub ができてるか確認（id_rsaは決して人に見せない）

==== git/github

「gitとはなんだ？」と思ってしまった迂闊な人はこちら．

	* git のインストール

	* sudo apt update && sudo apt upgrade -y && sudo apt autoremove
	* sudo apt install git
	* ssh のインストールと設定（公開鍵暗号という謎ワードに反応してしまう人はこちら）

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

=== ubuntu に ROS をインストール

奇特な人がする作業

その他のソフトウェア
 * Visual Studio Code と拡張機能

 winの人もする作業

 * git，github アカウント
 * ROS

== ラズパイマウスを走らせる（実機編）

=== マウス制御プログラム開発の準備

 * ROS初期設定（ワークスペースの準備）
 * github からリポジトリをクローン

=== プログラムの説明

 * 走らせてみよう
 * 改造の仕方
 * 迷路を解かせよう







== ラズパイマウスを走らせる（シミュレーション編）

=== シミュレーション環境のセットアップ

 * @<href>{https://raspimouse-sim-tutorial.gitbook.io/project/introduction, このページ}を順に実施．以下の点をやればよい
 * はじめに　◀　全部読む
 * セットアップ
 * ［ROS Melodic のインストール方法］に従って ROS をインストール
 * ［Raspberry Pi Mouse Simulator のインストール方法］でシミュレーターをインストール
 * ［Raspberry Pi Mouse Simulator の動作確認］
 * ROSのチュートリアル　◀　実行するととても良い
 * シミュレーターのチュートリアル　◀　Part 4 以外はできるのでやるととても良い

=== 迷路を作る

Raspberry Pi Mouse Simulator の迷路を自作する

やること
	* 
迷路自作プログラムを組み込む（src/raspimouse_sim）
	* 
シミュレーターの迷路を自作する
	* 
自作迷路でマウスを走らせる



迷路自作プログラムの組み込み（初回のみ）
（PiMouseSimulatorがインストールされ動作する状態で実施のこと）

	* 
既存リポジトリの削除／差し替え

		* 
cd ~/catkin_ws/src
		* 
rm -rf ./raspimouse_sim
		* 
cd ~/catkin_ws
		* 
catkin_make
		* 
cd ~/catkin_ws/src
		* 
git clone http://github.com/k-kame/raspimouse_sim.git
		* 
cd ~/catkin_ws
		* 
catkin_make



迷路の自作
	* 
迷路データの作成／変更

		* 
cd ~/catakin_ws/src/raspimouse_sim/raspimouse_gazebo/materials
		* 
gen_mousemaze.py の迷路データを編集（※）
		* 
迷路を生成

			* 
./gen_newmaze.sh newmaze
		* 
gazebo での表示（チェック）

			* 
cd ..
			* 
x を起動しておく（VcXsrv, X410 など）
			* 
gazebo ./worlds/newmaze.world



自作迷路でマウスを走らせる
	1. 
デバイスドライバの生成

		1. 
ls /dev/rt*（ドライバ設定の確認）
		2. 
rosrun raspimouse_control gen_dev_file.sh（ドライバがが無ければ生成）
	2. 
迷路の準備とマウスの配置

		1. 
x server を立てておく（Xsrvの場合はオプション （:0 -ac -multiwindow -reset -terminate -nowgl）をつける）
		2. 
roslaunch raspimouse_gazebo raspimouse_with_newmaze.launch
		3. 
cat /dev/rtlightsensor0（センサ出力の確認）
		4. 
roslaunch raspimouse_sim_tutorial_program raspimouse_sim.launch（"roslaunch raspimouse_ros_2 raspimouse.launch"の置き換え）
		5. 
rosservice call /motor_on
	3. 
制御プログラムの起動（お好みのものでOK）

		* 
rosrun raspimouse_sim_tutorial_program left_hand.py
		* 
lefthand.py の起動時のポイント
		* 
pimouse の配置：src/raspimouse_sim/raspimouse_description/urdf/raspimouse.urdf.xacro のbase footprint が対応パラメーター？

			* 
  <xacro:base parent="base_footprint">
			* 
    <origin xyz="0.10 0.1 0"/>
			* 
  </xacro:base>
			* 
https://rt-net.jp/mobility/archives/3305
			* 
サンプル命令：rosrun gazebo_ros spawn_model -file `rospack find raspimouse_description`/robots/raspimouse.urdf -urdf -x 0 -y 0 -z 1 -model raspimouse



備考
	* 
迷路設定ファイルの場所：~/catkin_ws/src/raspimouse_sim/raspimouse_gazebo/materials
	* 
壁データの作成（samplemaze.wall.xacro）
	* 
壁を呼び出すファイル（sample_maze_world.xacro）
	* 
worldファイルに変化するスクリプト（gen_maze.sh）



ーーーーー
※迷路データ（gen_mousemaze.py）の編集方法

テキストエディタで以下の変数を編集するだけ
	* 
迷路サイズ：sizeX, sizeY

		* 
素直に迷路サイズを入れる（正方以外作ったことが無いが多分任意サイズ）
	* 
しきり板の箇所：mazeH, mazeV

		* 
それぞれ「横板」，「縦板」の有無を示す行列
		* 
0 / 1 はそのマスのしきり板の有無を示す，mazeHだと下側，mazeVだと左側
		* 
sizeX, sizeY = 16, 16 なのに行列が 17x17なのは，一番上と一番右の外壁を表示するため


//image[fig_mazeex][fig_mazeex]{
迷路のサンプル
//}




== 総合演習：シミュレーションと実機で同じ制御プログラムを走らせる
