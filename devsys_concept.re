= 開発環境の準備：概念編
== 開発の全体像
ラズパイマウスの開発で必要なのは，@<b>{開発用PC}と@<b>{ロボット（ラズパイマウス）}の２つです．開発環境のイメージを@<img>{fig_devsys}に示します．

//image[fig_devsys][開発の全体像]{
開発の全体像
//}

この環境（全部入り）は，以下の開発／実行プロセスを想定しています．

 1. PC で制御プログラムを開発．
 1. シミュレーションで動作を確認．
 1. 制御プログラムを github@<fn>{github} にアップロード．
 1. 開発機からマウスにリモート接続（もしくは直接ログイン）．
 1. 制御プログラムを github@<fn>{github} からダウンロード．
 1. 制御プログラムを実行．
 1. 開発機上の ROS 標準ツール@<fn>{rqt}でマウスの状態をリモートモニタリング．
 1. 1 に戻る（不具合修正など）．

//footnote[github][git（プログラムの変更履歴を管理するソフトウェア）をホストするwebサービス．無料で使える．]
//footnote[rqt][rqtなど．]

一方，上記のように，マウスを購入し，web サービスを利用しないと開発ができないわけではありません．極端な話，紙と鉛筆があれば（或いは無くても）開発は可能ですが，ここでは，素の Windows PC を想定した開発プロセスを考えます（マウスは共用物を利用．ただし，OS 用 micro SD は自前で準備）．

 1. windows 10 上のエディタ（メモ帳など）で制御プログラムを開発する．
 1. マウス（借り物）に micro SD を差して起動．
 1. 開発機からマウスにリモート接続してプログラムを転送・実行．

しかし，このような方法はあまりお勧めできません（人的ミスによるトラブルが多そう）．

一方で，全部入り環境の整備には結構な費用がかかるので，これを準備できる人はあまりいないと思います．具体的には，

 * ラズパイマウス：90,200円（フルキット・税込み）
 * シミュレーションが満足に動くPC（例：core i7 / 16GB．独立 GPU は多分あまり効果ない．120,000~）．

そこで，全部入り環境が持つ機能

 1. プログラム作成機能
 1. シミュレーション機能
 1. プログラムの変更履歴管理／転送機能（git/github）
 1. 動作確認（ラズパイマウス）
 1. マウスのモニタリング機能
 
 からマウス（4）を割愛して，1, 2, 3, 5 の機能を持つ開発環境／開発プロセスを想定することにします（@<table>{shoppinglist}）．ポイントは以下の通りです．

 * マウスは借りる（micro SD カードは準備）．
 * 開発機に ROS はインストールする．
 
さらに，シミュレーションをしないのであれば，PC はその辺に転がって いる i5/8GB ぐらいで十分です．シミュレーション環境も，遅いけど動く（らしい）ので，インストールしてみましょう（便利だと思ったら買えばいいのです買えば）．
 
また，詳細は次章に記載しますが，Raspberry Pi 4 B を 開発用機として使うことも可能です（@<table>{dev_raspi}．シミュレーションは完全に諦めることになりますが）．

//table[shoppinglist][必要なものリスト]{
品名				単価		備考
---------
開発用 PC（ノート）	120,000		core i7 / 16GB
開発用 PC（ノート）	80,000		core i5 / 8GB
micro SD (32G)		1,000		マウス起動用
//}

//table[dev_raspi][ラズパイ価格]{
品名				単価		備考
---------
Raspberry Pi 4 B	10,000		スターターキット@<fn>{raspi4kit}			
キーボード＆マウス@<fn>{kbd}	2,530	Logicool MK240/MK245 NANO（コンボ）
モバイルモニタ		20,000		HDMI 入力，Full HD 13.3 インチ（cocopar など）
//}

@<ami>{最後に}

上記のようにスペックを記載すると「〇〇じゃだめですか？」などと質問する人がいますが，アドバイスとしては，「使えるものが手元にあるならとりあえずやってみれ！」です．やってみれば何とかなるし，何とかできるようになるものです．寧ろ，そうなるためにやっているのですから．

//footnote[devnote][i7 メモリ 8G だとシミュレーションも動く．ノートが便利．]
//footnote[raspi3kit][ケース，ACアダプタ，HDMI ケーブル，micro SD (32G) 付き．別途キーボード，マウス，モニタが必要．@<href>{https://www.switch-science.com/, スイッチサイエンス} などで購入可能．]
//footnote[raspi4kit][ 付属機器などの条件は同じ．@<href>{https://jp.rs-online.com/web/p/raspberry-pi/2067510/, RS コンポーネンツ}などで購入可能．]
//footnote[kbd][ワイヤレスなら bluetooth より USB 2.4 GHz がお薦め（接続が切れる）．]


== 色々な開発環境

はじめに開発用 PC をセットアップしますが，PC の OS が windows 10 ／ ubuntu のどちらかで，作業内容が変わります．

というわけで，開発環境セットアップの流れを@<img>{fig_devchart}にまとめてみました．作業は，大きく４つに分けることができます．

 1. windows 上で ubuntu を動かす．
 2. 開発ツール（Visual Studio Code，git など）のセッティング．
 3. ROS のセッティング．
 4. ROS 上に「マウス開発のもと」の準備．
 5. 「マウス開発のもと」を改造（＝開発）．

//image[fig_devchart][開発環境構築フローチャート]{
開発環境構築フローチャート
//}

つまり，PC の OS が ubuntu の場合は作業 1 が不要になります．

一方で，ubuntu を選ぶと，日常的に Linux Desktop に住むという苦行（？）が待っているので，どちらが良いとは言えないかもしれません．

デュアルブート@<fn>{dualboot}という選択肢もありますが，起動領域をいじるので，たまにトラブルが起こります（windows を壊すとダメージ大）．

//footnote[dualboot][一台のパソコンで起動 OS を切り替える方法．ブートローダ（grub など）を使う]

というわけで，普段使いの windows ／開発用 ubuntu 2 台の PC を準備するという富豪的アプローチが使い勝手／安全性の観点かベストです．お金がかかりますが．

遅い PC と割り切ってラズパイを使う方法もありますが，大した節約にはなりません（ノートPC：5 万円 v.s. Raspberry Pi 4B（1 万円）+ キーボードマウスコンボ（3 千円）+ モバイルモニタ（2 万円））．

というわけで，@<table>{devenvlist} に開発環境メリット／デメリットをまとめてみました（こういう所が環境構築大好き民）．個人的なお薦めは，「windows 上で ubuntu を動かす」か「ラズパイ 4 を使う」です・・・が，そこは．ご自身の技量，懐具合，趣味性癖を考慮して開発環境を選び，つぎに進んでください．

 1. 開発機が windows 10 の人	>  2 章 に進む
 2. 開発機が ubuntu の人		> 3 章 に進む
 3. 開発機に ラズパイ 4 を使う人	> 4 章に進む

//table[devenvlist][開発環境メリット・デメリット]{
.	方法	利点	欠点
----------
1	win 上で ubuntu			使い慣れた環境			構築が面倒
2	ubuntu PC				構築が楽				ubuntu 上に移住
3	デュアルブート			PC 一台で 両 OS が使える	PC 起動の知識が必要
4	2台持ち					安全					お金がかかる
5	ラズパイを開発機に使う	安い（?）				遅い
//}

