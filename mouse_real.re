= プログラムの説明／改造

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

== raspimouse_act.launch

//listnum[raspimouse_act][raspimouse_act.launch]{
<launch>
  <include file="$(find pimouse_ros)/launch/pimouse.launch" />
  <param name="sim_act" value="1" />
  <!-- <node pkg="pimouse_sim_act" name="wall_around" type="wall_around.py" required="true" /> -->
  <node pkg="pimouse_sim_act" name="runmouse_base" type="runmouse_base.py" required="true" />
</launch>
//}

== raspimouse_sim.launch

//listnum[raspimouse_sim][raspimouse_sim.launch]{
<!-- original file: raspimouse_ros_2/launch/raspimouse.launch -->

<launch>
  <!-- for imu -->
  <!-- <arg name="imu" default="0" /> -->
  <!-- <include if="$(arg imu)" file="$(find rt_usb_9axis_sensor)/launch/rt_usb_9axis_sensor.launch" /> -->

  <!-- for real machine -->
  <!-- <include file="$(find pimouse_ros)/launch/pimouse.launch" /> -->
  <!-- <node pkg="raspimouse_ros_2" name="buzzer" type="buzzer.py" required="true" /> -->

  <!-- <node pkg="raspimouse_ros_2" name="lightsensors" type="lightsensors" required="true">
    <param name="frequency" value="10" />
  </node> -->

  <!-- <arg name="initial_motor_power" default="off" /> -->
  <!-- <node pkg="raspimouse_ros_2" name="motors" type="motors" required="true" output="screen" args="$(arg initial_motor_power)" /> -->

  <!-- <node pkg="raspimouse_ros_2" name="leds" type="leds" required="true" /> -->
  <!-- <node pkg="raspimouse_ros_2" name="buttons" type="buttons" required="true" /> -->

  <!-- for simulation -->
  <!-- <node pkg="raspimouse_sim_tutorial_program" name="LeftHand" type="left_hand.py" required="true" /> -->
  <!-- パラメータ設定（シミュ:0/実機:1） -->
  <param name="sim_act" value="0" />
  <node pkg="pimouse_sim_act" name="runmouse_base" type="runmouse_base.py" required="true" />
  <!-- <node pkg="pimouse_sim_act" name="LeftHand" type="left_hand3.py" required="true" /> -->
</launch>
//}

== runmouse_base.py

//listnum[runmouse_base][runmouse_base.py]{
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