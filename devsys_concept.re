= 開発環境の準備：概念編
== 開発の全体像
ラズパイマウスの開発で必要なのは，@<b>{開発用PC}と@<b>{ロボット（ラズパイマウス）}の２つです．開発環境のイメージを@<img>{fig_devsys}に示します．

//image[fig_devsys][開発の全体像]{
開発の全体像
//}

この環境（全部入り）は，以下の開発／実行プロセスを想定しています．

 1. PC で制御プログラムを開発する．
 1. シミュレーションで動作を確認する．
 1. 制御プログラムを github@<fn>{github} にアップロードする．
 1. PC からマウスにリモート接続．
 1. 制御プログラムを github@<fn>{github} からダウンロードする．
 1. 制御プログラムを実行．
 1. PC 上の ROS 標準ツール@<fn>{rqt}でマウスの状態をモニタリング．
 1. 1 に戻る（不具合修正など）．

//footnote[github][git（プログラムの変更履歴を管理するソフトウェア）をホストするwebサービス．無料で使える．]
//footnote[rqt][rqtなど．]

一方，上記のように，マウスを購入し，web サービスを利用しないと開発ができないわけではありません．極端な話，紙と鉛筆があれば（或いは無くても）開発は可能ですが，ここでは，素の Windows PC を想定した開発プロセスを考えます（マウスは共用物を利用．ただし，OS 用 micro SD は自前で準備）．

 1. windows 10 上のエディタ（メモ帳など）で制御プログラムを開発する．
 1. マウス（借り物）に micro SD を差して起動．
 1. PC からマウスにリモート接続してプログラムを転送・実行．

しかし，このような方法はあまりお勧めできません（人的ミスによるトラブルが多そう）．

一方で，全部入り環境の整備には結構な費用がかかるので，これを準備できる人はあまりいないと思います．具体的には，

 * ラズパイマウス：90,200円（フルキット・税込み）
 * シミュレーションが満足に動くPC：i7 搭載 PC など．独立 GPU は多分あまり寄与しない．100,000~．

そこで，全部入り環境が持つ機能

 1. プログラム作成機能
 1. シミュレーション機能
 1. プログラムの変更履歴管理／転送機能（git/github）
 1. 動作確認（ラズパイマウス）
 1. マウスのモニタリング機能
 
 からお金のかかる 4 を割愛して，1, 2, 3, 5 の機能を持つ開発環境／開発プロセスを想定することにします（@<table>{shoppinglist}）．ポイントは以下の通りです．

 * マウスは借りる（micro SD カードは準備）．
 * 開発 PC に ROS はインストールする．
 * シミュレーション環境は，そこそこの PC なら何とか動くらしいので，インストールしてみましょう（便利だと思ったら買えばいいのです買えば）．

なお，キーボード，マウス，モニタのチョイスは完全に著者の趣味です．好きなものを使ってください．

多少勉強代を出そうという人には，ラズパイの購入をお勧めします@<fn>{raspi3kit}．走らないだけで，マウスの制御システムが構築でき，プログラムの転送にも便利です．ラズパイを開発用 PC として使ってプログラムを開発し，その micro SD カードをマウスに差して起動するという運用も可能です． 

また，詳細は次章に記載しますが，Raspberry Pi 4 B を 開発用 PC として使うということも可能です．シミュレーションは完全に諦めることになりますが．

//table[shoppinglist][必要なものリスト]{
品名				単価		備考
---------
開発用 PC			100,000		開発用@<fn>{devnote}
micro SD (32G)		1,000		
Raspberry Pi 3 B+	10,000		スターターキット@<fn>{raspi3kit}			
Raspberry Pi 4 B	10,000		スターターキット@<fn>{raspi4kit}			
キーボード＆マウス@<fn>{kbd}	2,530	Logicool MK240/MK245 NANO（コンボ）
モバイルモニタ		20,000		HDMI 入力，Full HD 13.3 インチ（cocopar など）
//}

//footnote[devnote][i7 メモリ 8G だとシミュレーションも動く．ノートが便利．]
//footnote[raspi3kit][ケース，ACアダプタ，HDMI ケーブル，micro SD (32G) 付き．別途キーボード，マウス，モニタが必要．@<href>{https://www.switch-science.com/, スイッチサイエンス} などで購入可能．]
//footnote[raspi4kit][ 付属機器などの条件は同じ．@<href>{https://jp.rs-online.com/web/p/raspberry-pi/2067510/, RS コンポーネンツ}などで購入可能．]
//footnote[kbd][ワイヤレスなら bluetooth より USB 2.4 GHz がお薦め（接続が切れる）．]

== 色々な開発用 PC 環境

はじめに開発用 PC をセットアップしますが，PC の OS が windows 10 ／ ubuntu のどちらかで，作業内容が変わります．

というわけで，開発環境セットアップの流れを@<img>{fig_devchart}にまとめてみました．作業は，大きく４つに分けることができます．

 1. windows 上で ubuntu を動かす．
 2. 開発ツール（vs code，git 等のアプリケーション）の設定．
 3. ROS のインストール．
 4. ROS 上に，マウス制御プログラム開発の準備をする．
 5. ROS のアプリケーションとして，マウス制御プログラムを開発する．

//image[fig_devchart][開発環境構築フローチャート]{
開発環境構築フローチャート
//}

つまり，作業 1 は，元の OS が ubuntu の場合は不要となり，構築の手間が省けます．

一方で，ubuntu を選ぶと Linux Desktop に住むという苦行（？）が待っているので，どちらが良いとは言えないかもしれません．

デュアルブート@<fn>{dualboot}という選択肢もありますが，起動領域をいじるため，たまにトラブルが起こります（windows を壊すとダメージ大）．

//footnote[dualboot][一台のパソコンで起動 OS を切り替える方法．ブートローダ（grub など）を使う]

というわけで，普段使いの windows ／開発用 ubuntu 2台の PC を準備するという富豪的アプローチが使い勝手／安全性の観点かベストです．お金がかかりますが．

遅い PC と割り切って，Raspberry Pi を使うという方法もありますが，大した節約にはなりません（ノートPC（5 万円）v.s. Raspberry Pi 4 B（1 万円） + キーボードマウスコンボ（3千円）+ モバイルモニタ（2万円））．

というわけで，@<table>{devenvlist} に開発環境構築メリット／デメリットをまとめてみました（こういう所が環境構築大好き民）．
個人的なお薦めは，「windows 上で ubuntu を動かす」か「ラズパイを開発機にして使う」です，が，そこは．ご自身の技量，懐具合，趣味性癖を考慮して開発環境を選び，つぎに進んでください．

 1. 開発 PC の OS が windows 10 の人	>  2 章 に進む
 2. 開発 PC の OS が ubuntu の人		> 3 章 に進む
 3. 開発機に Raspberry Pi を使う人		> 4 章に進む

//table[devenvlist][開発環境メリット・デメリット]{
.	方法	利点	欠点
----------
1	win 上で ubuntu			使い慣れた環境			構築が面倒
2	ubuntu PC				構築が楽				ubuntu 上に移住
3	デュアルブート			PC 一台で 両 OS が使える	PC 起動の知識が必要
4	2台持ち					安全					お金がかかる
5	ラズパイを開発機に使う	安い（?）				遅い
//}

