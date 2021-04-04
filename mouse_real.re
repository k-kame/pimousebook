= プログラムの説明／改造
== 導入ファイルの構造と実行プロセス

@<chap>{mouse_setup}で導入したファイルは，以下の構成になっています．

 * ├── pimouse_sim_act
 *     　	　	├── launch
 *     	　	　	│	　	　├── raspimouse_act.launch
 *     	　	　	│	　	　└── raspimouse_sim.launch
 *     	　	　	└── scripts
 *     	　	　	　	　	　├── runmouse_base.py
 * │
 * ├── pimouse_ros
 * ├── raspimouse_ros_2
 * ├── raspimouse_sim

この中で，@<b>{直接編集するファイルは runmouse_base.py だけ}です）．

また，@<b>{実行するファイルは pimouse_sim_act/launch の launch ファイルの2つだけ}で，act が実機用，sim がシミュレーション用の起動ファイルで，どちらも runmouse_base.py を呼び出しています（ROS の parameter という機能で，runmouse_base.py の動作を分岐させています）．

.launch ファイルとは，実行するファイルや設定を記載し，まとめて実行するためのファイルで，yaml という形式で書かれています．@<list>{raspimouse_act}と@<list>{raspimouse_sim}に，実機用とシミュレーション用の lauch を，@<list>{pimouse_ros}に@<list>{raspimouse_act}から呼び出される，モーター／センサノード起動用 launch を示します．

実行プロセスの観点から，.launch の中身を見てみましょう．

 * 2行目：
 ** 実機用では別の launch が登録されています．ここで，pimouse_ros に含まれるデバイスノードをまとめて実行しています．このように，launch から別のパッケージの launch を呼び出すことができます．
 ** シミュレーション用では空白になっています．これは，シミュレーションではデバイスノードを立ち上げないのではなく，事前に多数のファイルを実行しなければならず，それらはコマンド入力により実行しなければならないため，launch では 3-4 行だけを実行するという方式をとっているためです（詳細は後述）．
 * 3行目：
 ** コメントです（実行されません） 
 * 4行目：
 ** parameter を設定し，runmouse_base から参照して，実機／シミュレーション時で動作を分岐させています．
 * 5行目：
 ** runmouse_base というノード名で，runmouse_base.py を実行しています．ノード名とファイル名は一致していなくても構いません．

//listnum[raspimouse_act][実機用 launch ファイル（raspimouse_act.launch）]{
<launch>
  <include file="$(find pimouse_ros)/launch/pimouse.launch" />
  <!-- パラメータ設定（シミュ:0/実機:1） -->
  <param name="sim_act" value="1" />
  <node pkg="pimouse_sim_act" name="runmouse_base" type="runmouse_base.py" required="true" />
</launch>
//}

//listnum[raspimouse_sim][シミュレーション用 launch ファイル（raspimouse_sim.launch）]{
<launch>

  <!-- パラメータ設定（シミュ:0/実機:1） -->
  <param name="sim_act" value="0" />
  <node pkg="pimouse_sim_act" name="runmouse_base" type="runmouse_base.py" required="true" />
</launch>
//}

//listnum[pimouse_ros][実機センサ／モーターノード用 launch ファイル（pimouse_ros.launch）]{
<launch>
  <node pkg="pimouse_ros" name="buzzer" type="buzzer.py" required="true" />
  <node pkg="pimouse_ros" name="lightsensors" type="lightsensors.py" required="true" />
  <node pkg="pimouse_ros" name="motors" type="motors.py" required="true" />
</launch>
//}

== runmouse_base.py の構成／実行順と改造の勘所（前半戦）

@<list>{runmouse_base}に runmouse_base.py を示します．本構成では，このファイルにマウスの制御ルール全てを書く構成になっています．使用言語は python です．

実行プロセス順にファイルを読み，改造ポイントを押さえていきましょう．

プログラムを理解するには，@<b>{制御対象}と@<b>{プログラムの目的}を理解しておく必要があります．

制御対象の特徴／制御方法：

 * 制御対象：左右の二輪が独立に回転する走行ロボット（マウス）．前進・後退・旋回等の動作を行う．
 * マウスに与える命令は，「前方向に 〇 [m/sec]で前進しなさい」，「〇[rad/sec]で旋回しなさい」の2種類だけ．
 * 光センサ4つ（左斜め前，左前，右前，右斜め前）で進行方向の壁の有無を探知する．

プログラムの目的：

 * 「迷路を１区画進んで壁の有無を確認し，前方に壁があれば時計回りに 90 度旋回する」を繰り返す．
 * シミュレーションと実機で動作やパラメータ（移動速度など）を切り替える．

以上がプログラムの全てです@<fn>{comm_sample}．

//footnote[comm_sample][本冊子は ROS プログラミング勘所の学習を目的としているので，サンプルプログラムはしょぼいです．本来はもっと速く走れ・・・る筈なので頑張ってください．]

では，気を取り直してプログラムを読んでいきます．
プログラムは大きく3パートに分けることができます．

 1. 1~29行：ライブラリ・パッケージのインポート／変数の定義
 1. 31~127行：クラス RunMouse の定義
 1. 129~136行：プログラム本体

というわけで，129 行目からプログラムを読んでいきましょう．

129~136 行目では，シミュレーション／実機の切り替えと，マウス制御全般を詰め込んだクラス RunMouse の実行までを行っています（嘘50% ．正しくは，インスタンスの生成とノードの実行．インスタンスについては@<href>{https://26gram.com/what-is-object-oriented, こちらなど}を参照）．

 * 129 行目：python のお約束で，runmouse_base.py が直接呼ばれたときは 130-136行が実行され，他から import された場合には，130-136行が実行されず，class RunMouse() のみ参照されるというものです．
 * 131 行目：RunMouse ノードを生成して
 * 133 行目：launch で設定した parameter を変数 sim_act に読み込みます．今後，sim_act の値で，実機用／シミュレーション用に動作を分岐させます．C言語からプログラミングに入った人は「どこで宣言された？」と疑問を持つと思いますが，python では宣言なしで変数が使えます．
 * RunMouse ノードの関数 run の呼び出し．

つぎに，31行目からの RunMouse 本体を読んでいく・・・前に，1~29行目を確認しておきましょう．
このパートは大きく4つに分けることができます．

 * 1,2 行目：python のおまじない．詳しくは初心者向け python の本を読む．
 * 4,5 行目：python パッケージ rospy, math, numpy のインポート．numpy だけ np と名前をつけなおしている．
 * 6~8 行目：ROS 他パッケージの message を利用する準備
 * 10~29 行目：定数の設定

ここで，プログラム改造のために理解する必要があるのは 10~28 行目です．
順番が異なりますが，まず，16~19 行目を見てみましょう．

ここでは，4つの変数が定義されています．

 * DT_SIM：制御ループ1回の上限時間 [ms]
 * V_X_SIM：Ｘ方向速度（ロボットの前進速度）[m/sec]
 * R_Z_SIM：旋回速度（正が反時計回り）[rad/sec]
 * S_TH_SIM：光センサの閾値

変数の名前は，前半（DT など）が機能，後半（SIM）がシミュレーション用の値であることを指しています．
21~24 行目では，後半だけが ACT となっており，実機用の値を設定しています．
一方で，26~29 行目では，後半がありません．

これらの値の利用方法は，（少し飛んで）41~51 行を見ると，変数 sim_act == 0 の時は DT = DT_SIM，sim_act == 1 の時は DT = DT_ACT として，以降プログラムの中では，DT を使うという様になっています．

10~13 行目は，マウスが1マス進む／90度旋回するために必要な時間を定義する値で，本来ならシミュレーションと実機で違うのですが，サボって同じものを使っています．改造が進んで，別の値を設定する必要が出てきた時点で同じルールで改造して貰えばよいと思います．

== runmouse_base.py の構成／実行順と改造の勘所（後半戦）

では，RunMouse を読んでいきましょう．

本当は，オブジェクト指向とかクラスとかインスタンスとかメンバ関数とか，ややこしい話をしないといけないのですが，ここではウソをつきます（マウスではマルチスレッドとか使わないので・・・．興味がある人は上の用語を Wikipedia とかで調べてみてください）．

=== RunMouse の初期化

まず，131行で RunMouse が呼び出されると（このへんがウソ），32~57行目の __init__(self) が実行されます．ここで，def 関数名 となって字下げされている部分が，一塊の関数です．

 def __init__(self) では，大きく分けて3つの事を行っています．

 * センサ／モーター値をやり取りする方法の設定
 * シミュレーション／実機用変数の切り替え
 * シミュレーション環境の初期化（シミュレーションの場合のみ）

では，上から順に説明していきます．

光センサ値の読み取りとモーターの制御は，実機では，raspimouse_act.launch が pimouse.launch 経由で呼び出したノードが実施しています（シミュレーションでは，環境の起動に含まれます）．ので，RunMouse では，これらとの通信方法を設定します．

光センサだと，センサノードが /lightSensors という名前，LightSensorValues という型でデータを送りつけてくるので，その受取口を34行目で作成しています．この，ノード間を行き来するデータを topic といいます（/lightSensors という名前で，型が LightSensorValues の topic ということになります）．

また，sensor_callback は，「受け取ったら sensor_callback という名前の関数に処理させます」という意味です．

なお，データ型 LightSensorValues は 8行目の raspimouse_ros_2 というパッケージ内で定義しています．つまり，8行目は「データ型を使いますよ」という意味だったわけですね（他も使ってますが）．
ちなみに，LightSensorValues 型は，以下の変数を含むデータの塊です．

 * int16 right_forward
 * int16 right_side
 * int16 left_side
 * int16 left_forward
 * int16 sum_all
 * int16 sum_forward

36行目：self.sensor_values=LightSensorValues() は，LightSensorValue型の変数（正確にはオブジェクト）sensor_value を作っています．コールバック関数 sensor_callback はここに値を読み込みます．

モーターについては，「/cmd_vel という名前で Twist 型のデータを送りつけます」という意味です．
受け取りについては，pimouse_ros.launch で立ち上げたモーターノードが良しなにやってくれる筈なので，気にしないことにします（気になる人は，pimouse_ros パッケージを読みましょう）．

なお，Twist 型は，XZY方向速度と，XZY軸を中心とした旋回速度を表す Vector3 型変数

 * Vector3 linear
 * Vector3 angular

を含みます@<fn>{variabletype}．Vector3 型は，以下のような構成の変数です．

//footnote[variabletype][Twist.msg, Vector3.mgs は元から定義されており，/opt/ros/melodic/share/geometry_msgs/ で定義されています．]

 * float64 x
 * float64 y
 * float64 z

41~50行目は前述したように，シミュレーションと実機でのパラメータの切り替えです．
53~57行目は，シミュレータの初期化なので，いまは触れないことにしましょう．

=== 関数 run()

では，136行目で呼び出された関数 run() の動作を見ていきます．
ちなみに，RunMouse().run()とは，131行目で呼び出された RunMouse() に含まれる関数 run() という意味です（嘘50%）．

106行目でセットされた変数 rate で，116~124行目のループ1回の実行時間を決めています．
関数 Rate() が何か気になる人は，随時 rospy の@<href>{http://wiki.ros.org/rospy, 公式ドキュメント}を読むようにしましょう．

//footnote[doc_rospy][rospy は python の ROS 用ライブラリなので（つまり特殊），一般的な python の書籍を見ても載っていないことが沢山あります．python の話か rospy の話かは，関数が rospy. についているかで判断しましょう．そして，諦めて英語を読みましょう．]

あとは，115行目~126行目を繰り返すだけです．
継続条件は「rospy がシャットダウンされていない間ずっと」なので，ノードが kill されるまでです．

動作ですが，ここでプログラムの目的，「（１）迷路を１区画進んで壁の有無を確認し，（２）前方に壁があれば時計回りに 90 度旋回する」を思い出してください．
117~で 一定時間（T_INTEREVAL）毎に，119行目：左右センサの値が閾値（S_TH）を超えていないかチェックして，超えていれば 90 度旋回，超えていなければ1マス前進するという動作を繰り返しているだけです．

「90度」・「1マス」と書いていますが，これは時間（T_INTERVAL）と速度（V_X, R_Z）の兼ね合いで調整しているので，うまくいっていません．頑張って調整するなり，他の方法を試すなりしてください．

以上で大まかな解説は終了です．
59~102行目に定義された関数については，各自で読んでみてください．
なお，関数は

 1. 59~68行目：subscriber, publisher が使う関数
 2. 70~85行目：ロボットの動作を表す関数
 3. 87~102行名：環境設定のための関数

になっており，(1)-(3) は触る必要が無いと思います．

ですので，改造のすすめ方としては，

 1. ロボットの動作を考える．
 2. 117~123行目を変更する．必要なら，ロボット動作関数を追加する．

 というようになると思います．

 それでは，充実した ROS ライフを！

//listnum[runmouse_base][マウス制御]{
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy,math
import numpy as np
from geometry_msgs.msg import Twist
from std_srvs.srv import Trigger, TriggerResponse, Empty
from raspimouse_ros_2.msg import *

# シミュと実機のグローバル定数
T_INTERVAL = 3
T_MOVE = 1.8
T_ROT  = 1.02 # 1/8角度回転に要する時間

# シミュのための定数
DT_SIM   = 10
V_X_SIM  = 0.1
R_Z_SIM  = -math.pi/4    # 時計回りの角速度
S_TH_SIM = 1500
# 実機のための定数
DT_ACT   = 10
V_X_ACT  = 0.05
R_Z_ACT  = -math.pi/4
S_TH_ACT = 1500
# 参照される定数（編集しない）
DT = 0
V_X  = 0
R_Z  = 0
S_TH = 0

class LeftHand():
    def __init__(self):
        # 光センサのサブスクライバー
        rospy.Subscriber('/lightsensors', LightSensorValues, self.sensor_callback)
        # 光センサのメッセージオブジェクト
        self.sensor_values = LightSensorValues()
        # モータのパブリッシャー（シミュ（周波数）▶ 実機（x速度とz回転角に統一））
        # self.motor_raw_pub = rospy.Publisher('/motor_raw', MotorFreqs, queue_size = 10)
        self.cmd_vel = rospy.Publisher('/cmd_vel', Twist, queue_size=1)

        # グローバル変数の再定義
        global V_X, R_Z, S_TH, DT
        if sim_act == 0:
            DT   = DT_SIM
            V_X  = V_X_SIM
            R_Z  = R_Z_SIM
            S_TH = S_TH_SIM
        else:
            DT   = DT_ACT
            V_X  = V_X_ACT
            R_Z  = R_Z_ACT

        # （シミュ）シミュレータを初期状態にする
        if sim_act == 0:
            self.modeSimReset = True
            self.ls_count = 0
            self.rs_count = 0

    # センサコールバック関数
    def sensor_callback(self, msg):
        self.sensor_values = msg

    # （実機）モーターパブリッシャ（シミュでも利用）
    def motor_cont_act(self, xv, zrot):
        d = Twist()
        d.linear.x  = xv
        d.angular.z = zrot
        self.cmd_vel.publish(d)

    # ロボット動作関数　＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    # 停止
    def move_stop(self):
        self.motor_cont_act(0, 0)

    # １ブロック前進
    def move_front_1bk(self):
        tb = rospy.get_time()
        while rospy.get_time() - tb < T_MOVE:
            self.motor_cont_act(V_X, 0)

    # 旋回：角速度・時間指定
    def move_turn(self, r_z, t_rot):
        tb = rospy.get_time()
        while rospy.get_time() - tb < t_rot:
            self.motor_cont_act(0.0, r_z)

    # 環境設定のための関数　＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    # シミュレーション環境の初期化
    def init_simu(self):
        if self.modeSimReset:
            rospy.wait_for_service('/gazebo/reset_world')
            try: rospy.ServiceProxy('/gazebo/reset_world', Empty).call()
            except rospy.ServiceException as e: print('Service call failed: %s', e)

    # ロボット初期化
    def init_robot(self):
        rospy.wait_for_service('/motor_on')
        rospy.wait_for_service('/motor_off')
        try: rospy.ServiceProxy('/motor_on', Trigger).call()
        except rospy.ServiceException as e: print('Service call failed: %s', e)
        # シャットダウンのためのフックを登録
        rospy.on_shutdown(self.move_stop)

    # 主関数　＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    def run(self):
        self.rate = rospy.Rate(DT)

        # シミュレーション環境初期化
        if sim_act == 0:
            self.init_simu()
        # ロボット初期化
        self.init_robot()

        # 以下メインループ
        tb = rospy.get_time()
        while not rospy.is_shutdown():
            if rospy.get_time() - tb > T_INTERVAL:
                tb = rospy.get_time()
                if self.sensor_values.left_forward > S_TH or self.sensor_values.right_forward > S_TH:
                    self.move_turn(R_Z, T_ROT)
                    self.move_stop()
                else:
                    self.move_front_1bk()
                    self.move_stop()

            self.rate.sleep()
            # メインループ（ここまで）

if __name__ == '__main__':
    # ノード初期化
    rospy.init_node('LeftHand', log_level=rospy.DEBUG)
    # シミュ／実機パラメータの取得（シミュ:0/実機:1）
    sim_act = rospy.get_param("sim_act")

    # run 関数の呼び出し
    LeftHand().run()
//}