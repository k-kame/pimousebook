= ラズパイマウスを走らせる（シミュレーション編）

== シミュレーション環境のセットアップ

@<href>{https://raspimouse-sim-tutorial.gitbook.io/project/introduction, このページ}を順に実施．以下の点をやればよい

 * はじめに　◀　全部読む
 * セットアップ
 * ［ROS Melodic のインストール方法］に従って ROS をインストール
 * ［Raspberry Pi Mouse Simulator のインストール方法］でシミュレーターをインストール
 * ［Raspberry Pi Mouse Simulator の動作確認］
 * ROSのチュートリアル　◀　実行するととても良い
 * シミュレーターのチュートリアル　◀　Part 4 以外はできるのでやるととても良い

== 迷路を作る

Raspberry Pi Mouse Simulator の迷路を自作する

やること
 * 迷路自作プログラムを組み込む（src/raspimouse_sim）
 * シミュレーターの迷路を自作する
 * 自作迷路でマウスを走らせる

迷路自作プログラムの組み込み（初回のみ）
（PiMouseSimulatorがインストールされ動作する状態で実施のこと）

 * 既存リポジトリの削除／差し替え

 * cd ~/catkin_ws/src
 * rm -rf ./raspimouse_sim
 * cd ~/catkin_ws
 * catkin_make
 * cd ~/catkin_ws/src
 * git clone http://github.com/k-kame/raspimouse_sim.git
 * cd ~/catkin_ws
 * catkin_make

迷路の自作
 * 迷路データの作成／変更

 * cd ~/catakin_ws/src/raspimouse_sim/raspimouse_gazebo/materials
 * gen_mousemaze.py の迷路データを編集（※）
 * 迷路を生成

 * ./gen_newmaze.sh newmaze
 * gazebo での表示（チェック）

 * cd ..
 * x を起動しておく（VcXsrv, X410 など）
 * gazebo ./worlds/newmaze.world

自作迷路でマウスを走らせる

 1. デバイスドライバの生成
 1. ls /dev/rt*（ドライバ設定の確認）
 2. rosrun raspimouse_control gen_dev_file.sh（ドライバがが無ければ生成）
 2. 迷路の準備とマウスの配置

 1. x server を立てておく（Xsrvの場合はオプション （:0 -ac -multiwindow -reset -terminate -nowgl）をつける）
 2. roslaunch raspimouse_gazebo raspimouse_with_newmaze.launch
 3. cat /dev/rtlightsensor0（センサ出力の確認）
 4. roslaunch raspimouse_sim_tutorial_program raspimouse_sim.launch（"roslaunch raspimouse_ros_2 raspimouse.launch"の置き換え）
 5. rosservice call /motor_on
 3. 制御プログラムの起動（お好みのものでOK）

 * rosrun raspimouse_sim_tutorial_program left_hand.py
 * lefthand.py の起動時のポイント
 * pimouse の配置：src/raspimouse_sim/raspimouse_description/urdf/raspimouse.urdf.xacro のbase footprint が対応パラメーター？

 * <xacro:base parent="base_footprint">
 * <origin xyz="0.10 0.1 0"/>
 * </xacro:base>
 * https://rt-net.jp/mobility/archives/3305
 * サンプル命令：rosrun gazebo_ros spawn_model -file `rospack find raspimouse_description`/robots/raspimouse.urdf -urdf -x 0 -y 0 -z 1 -model raspimouse

備考

 * 迷路設定ファイルの場所：~/catkin_ws/src/raspimouse_sim/raspimouse_gazebo/materials
 * 壁データの作成（samplemaze.wall.xacro）
 * 壁を呼び出すファイル（sample_maze_world.xacro）
 * worldファイルに変化するスクリプト（gen_maze.sh）

ーーーーー
※迷路データ（gen_mousemaze.py）の編集方法

テキストエディタで以下の変数を編集するだけ

 * 迷路サイズ：sizeX, sizeY
 * 素直に迷路サイズを入れる（正方以外作ったことが無いが多分任意サイズ）
 * しきり板の箇所：mazeH, mazeV

 * それぞれ「横板」，「縦板」の有無を示す行列
 * 0 / 1 はそのマスのしきり板の有無を示す，mazeHだと下側，mazeVだと左側
 * sizeX, sizeY = 16, 16 なのに行列が 17x17なのは，一番上と一番右の外壁を表示するため


//image[fig_mazeex][fig_mazeex]{
迷路のサンプル
//}
