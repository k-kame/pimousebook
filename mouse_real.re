= ラズパイマウスを走らせる（実機編）

//lead{
前章までで，ROS のインストールとワークスペースの順義が終わったので，以降はマウス固有の準備を行っていきます．
また，準備の過程で，ROS を使ったプログラム開発の基礎について説明します．
//}

== ROS プログラムの構成

ここでは，ROS プログラムの構成（Arduino などのプログラムとの違い）について，カンタンに説明します（かなりはしょります．正しい理解のためには，書籍を参照してください）．

例として，センサ，モータ，コンピュータひとつずつから構成されるシステムを考えます．

@<ami>{Arduino のプログラム}

多くの場合，Arduino のプログラムはひとつの大きなループを繰り返す形で実行されます（@<img>{fig_comp_arduros} 左）．つまり，ひとつのループの中で，「センサ値受信　→　制御入力の計算　→　モータ制御」が繰り返されます．この方式では，プログラムはひとつのプロセッサ上で動くので，「集中処理」と呼ばれます．

@<ami>{ROS のプログラム}

ROS では，モータ用，センサ用，統括用のプログラムを別々に作り，各プログラム間のやりとりは通信で行う，という風に作ります（（@<img>{fig_comp_arduros}） 右）．この方式では，プログラムは複数のプロセッサ上でも動くことができ，「分散処理」と呼ばれます（ひとつのプロセッサで動かすこともできます）．
ROS では，個々のプログラムを「ノード」，ノード間のやりとり（通信内容）を「メッセージ」と言います．
また，1～複数個のノードからなる機能は「パッケージ」としてまとめられ，github などに登録されています．このまとめたものは「リポジトリ」と呼ばれ，github からクローン@<fn>{note_clone}して利用できます．

//image[fig_comp_arduros][Arduino と ROS のプログラムの比較]{
開発の全体像
//}

//footnote[note_clone][github ではリポジトリをダウンロードすることをクローンと言うと思っておいて下さい（嘘 50%）]

@<table>{list_repo}に，実機開発／シミュレーションの改造元になるリポジトリをまとめます．

//table[list_repo][リポジトリ一覧]{
No.	リポジトリ名			役割									実機	シミュ
----------
1	pimouse_sim_act			統合プログラム 			                o		o
2	pimouse_ros				実機のデバイス@<fn>{note_device}ノード	o		-
3	raspimouse_ros_2		仮想機のデバイスノード	                -		o
4	raspimouse_sim			シミュレーション環境	                -		o
//}

//footnote[note_device][デバイス＝ブザー，光センサ，モータ]

== マウス用プログラムの準備（開発機）

この冊子では，マウスは借りるので，以下の設定がされた micro SD カードが配布されているという前提で話を進めます@<href>{https://www.evernote.com/shard/s26/client/snv?noteGuid=72299e08-8340-4dac-b207-f518c737a301&noteKey=a67d2f5450dd2a7b&sn=https%3A%2F%2Fwww.evernote.com%2Fshard%2Fs26%2Fsh%2F72299e08-8340-4dac-b207-f518c737a301%2Fa67d2f5450dd2a7b&title=ROS-Raspi%2B%25E3%2582%25BB%25E3%2583%2583%25E3%2583%2586%25E3%2582%25A3%25E3%2583%25B3%25E3%2582%25B0%25E3%2582%25AC%25E3%2582%25A4%25E3%2583%2589, （後日追記）}．

 1. Raspberry Pi に ubuntu server のインストール
 1. ubuntu の設定
 1. ubuntu に ROS をインストール
 1. ROS の設定
 1. ドライバの設定

各自で行う作業の手順は以下の通りです．

@<ami>{github での準備}

 1. リポジトリの fork

@<ami>{マウスの準備}

 1. マウスの起動
 1. ワークスペースの作成
 1. リポジトリのクローン／関連付け

以上で準備内容について以下を行います

 1. DLしたプログラムの改造（＝マウスプログラムの開発（次章））
 1. 実行

1. リポジトリの fork

fork とは，他の人のリポジトリを自分のリポジトリにコピーすることです（嘘 50%）．fork することにより，変更履歴を管理したり，変更結果を github 経由で開発機からマウスにコピーしたりできるようにすることです．ここでは，アカウント k-kame のリポジトリ pimouse_sim_act.git を，自分のアカウントにコピーします．

 * ブラウザのアドレス欄に@<href>{https://github.com/k-kame/pimouse_sim_act}と入力
 * ページ右上の fork ボタンを押す（参考：@<img>{fig_github_fork}）

//image[fig_github_fork][github での fork]
github での fork
//

同様に，pimouse_ros.git も fork しておきましょう．

2. マウスの起動

 キーボード，マウス，モニタが必要（ip アドレスを調べるので，リモートの場合にも必要）

 * micro SD を差して起動，ログイン（配布 micro SD では user:ubuntu, pass:fnctcontrol）

3. ワークスペースの作成

 * work_pimouse などの名前で作成 

4. リポジトリのクローン／関連付け

以下の手順で，fork したリポジトリをマウスに clone します．<username> には github のアカウントを入れてください．

 * @<code>{cd ~/<workspacename>/src}
 * @<code>{git clone http://github.com/<username>/pimouse_sim_act.git}
 * @<code>{git clone http://github.com/<username>pimouse_ros.git}
 * @<code>{cd /<workspacename>}
 * @<code>{catkin_make}

@<ami>{マウスの走らせ方}

以上で準備が終わりました．ベースとなるプログラムには最低限の機能しかなく，まともに走行することすらできません・・・が，確認のために起動してみましょう．

 * @<code>{roslaunch pimouse_sim_act raspimouse_act.launch}

== プログラムの改造

 * ├── pimouse_sim_act
 *     ├── launch
 *     │   ├── raspimouse_act.launch
 *     │   └── raspimouse_sim.launch
 *     └── scripts
 *         ├── left_hand3.py

 * ├── pimouse_ros

プログラムの解説／改造のポイント

2種類のファイル

 * .launch：ローンチファイル．必要なファイルをまとめて登録・実行するためのファイル，yaml という形式で書かれている．
 * .py：phtyon で書かれたファイル．ここではマウス制御プログラム．

実機用／シミュレーション用のローンチファイル．ROS の parameter という機能で，left_hand3.py 内の動作を分岐させ，実機用／シミュレーション用のプログラムを混在させている．本書では改造しない．

 * raspimouse_sim.launch
 * raspimouse_act.launch

マウス制御プログラム．このファイルだけ編集する

 * left_hand3.py

リポジトリ pimouse_ros はモーターと光センサのノードのために利用している．本書では改造しない．

== 迷路を解かせよう
