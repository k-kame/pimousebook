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

.launch ファイルとは，実行するファイルや設定を記載し，まとめて実行するためのファイルで，yaml という形式で書かれています．@<list>{raspimouse_act}と@<list>{raspimouse_sim}に，実機用とシミュレーション用の lauch ファイルを示します．

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

== script ファイルの説明と改造の勘所

@<list>{runmouse_base}に runmouse_base.py を示します．本構成では，このファイルにマウスの制御ルール全てを書く構成になっています．使用言語は python です．

実行プロセス順にファイルを読み，改造ポイントを押さえていきましょう．

まず，プログラムは大きく3パートに分けることができます．

 1. 1~29行：
 1. 31~127行：
 1. 127~136行：


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