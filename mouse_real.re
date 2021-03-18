= ラズパイマウスを走らせる（実機編）
== ROS の基礎とマウス制御プログラム開発の準備

前章までで，ROS までの準備が終わったので，ここからはマウス固有の準備を行っていきます．
また，準備の過程で，ROS を使ったプログラム開発の基礎について説明します．

準備／開発の手順は以下のようになります．

 1. 制御プログラムのダウンロード
 2. ROS への関係づけ
 3. DLしたプログラムの改造（＝マウスプログラムの開発）

== ROS プログラムの構成

ここでは，ROS プログラムの構成（Arduino などのプログラムとの違い）について，カンタンに説明します（かなりはしょります．正しい理解のために，後日書籍を参照してください）．

例として，センサ，モータ，コンピュータひとつずつから構成されるシステムを考えます．

@<ami>{Arduino のプログラム}

多くの場合，Arduino のプログラムはひとつのファイルに記載され，記載された命令を順に実行するという形で実行されます．つまり，ひとつのプログラムの中で，「センサ値受信　→　制御入力の計算　→　モータ制御」が繰り返されます．

@<ami>{ROS のプログラム}

ROS では，モータ用，センサ用，統括用のプログラムを別々に作り，各プログラム間のやりとりは通信で行う，という風に作ります．


以下に，実機用プログラムに必要な

//table[list_repo][リポジトリ一覧]{
No.	リポジトリ名			役割											実機	シミュ
----------
1	pimouse_sim_act			launch main node/ 								o		o
2	pimouse_ros				launch buzzer, lightsensors, motors nodes		o		-
3	raspimouse_ros_2		仮想モーター									-		o
4	raspimouse_sim			シミュレーション環境							-		o
//}



 * ROS初期設定（ワークスペースの準備）

 * github からリポジトリをクローン


== プログラムの説明

 * 走らせてみよう
 * 改造の仕方
 * 迷路を解かせよう


@<ami>{マウスの実行方法}

 * roslaunch pimouse_sim_act raspimouse_act.launch


#@# =========================
├── pimouse_sim_act
│   ├── CMakeLists.txt
│   ├── howtouse.txt
│   ├── launch
│   │   ├── raspimouse_act.launch			◀
│   │   └── raspimouse_sim.launch			◀
│   ├── package.xml
│   ├── pimouse_sim_act.code-workspace
│   └── scripts
│       ├── left_hand3.py					◀◀ from raspimouse_act/sim.launch
│       ├── left_hand.py
│       ├── pimouse_sim_run.py
│       └── wall_around.py
#@# =========================
├── pimouse_ros
│   ├── action
│   │   └── Music.action
│   ├── CMakeLists.txt
│   ├── launch
│   │   ├── pimouse.launch					◀◀ from raspimouse_act.launch
│   │   └── test.launch
│   ├── LICENSE
│   ├── msg
│   │   ├── LightSensorValues.msg
│   │   └── MotorFreqs.msg
│   ├── package.xml
│   ├── README.md
│   ├── scripts
│   │   ├── buzzer1.py
│   │   ├── buzzer2.py
│   │   ├── buzzer3.py
│   │   ├── buzzer4.py
│   │   ├── buzzer.py						◀◀◀ from pimouse.launch
│   │   ├── lightsensors1.py
│   │   ├── lightsensors2.py
│   │   ├── lightsensors.py					◀◀◀ from pimouse.launch
│   │   ├── motors1.py
│   │   ├── motors2.py
│   │   └── motors.py						◀◀◀ from pimouse.launch
│   ├── srv
│   │   └── TimedMotion.srv
│   └── test
│       ├── travis_package_make.bash
│       ├── travis_prepare_dummy_files.bash
│       ├── travis_ros_install.bash
│       ├── travis_test_buzzer.py
│       ├── travis_test_lightsensors.py
│       ├── travis_test_motors1.py
│       ├── travis_test_motors2.py
│       └── travis_test_motors.py
#@# =========================（不要？）
├── pimouse_run_corridor
│   ├── CMakeLists.txt
│   ├── launch
│   │   ├── wall_around.launch
│   │   ├── wall_stop_accel.launch
│   │   ├── wall_stop.launch
│   │   └── wall_trace.launch
│   ├── LICENSE
│   ├── package.xml
│   ├── README.md
│   ├── scripts
│   │   ├── wall_around.py
│   │   ├── wall_stop_accel.py
│   │   ├── wall_stop.py
│   │   └── wall_trace.py
│   └── test
│       ├── travis_package_make.bash
│       ├── travis_prepare_dummy_files.bash
│       ├── travis_ros_install.bash
│       ├── travis_test_wall_stop_accel.py
│       ├── travis_test_wall_stop.py
│       └── travis_test_wall_trace.py
#@# =========================（不要？）
├── raspimouse_ros
│   ├── action
│   │   └── Music.action
│   ├── CMakeLists.txt
│   ├── LICENSE
│   ├── misc
│   │   ├── keikyu.bash
│   │   └── keikyu_stop.bash
│   ├── msg
│   │   ├── LightSensorValues.msg
│   │   ├── MotorFreqs.msg
│   │   └── Switches.msg
│   ├── package.xml
│   ├── raspimouse.launch
│   ├── raspimouse_ns.launch
│   ├── README.md
│   ├── scripts
│   │   ├── check_driver_io.py
│   │   ├── rtbuzzer.py
│   │   ├── rtlightsensors.py
│   │   ├── rtmotor.py
│   │   └── rtswitches.py
│   ├── srv
│   │   ├── PutMotorFreqs.srv
│   │   └── SwitchMotors.srv
│   └── test
│       ├── lightsensors_output
│       ├── switches_output
│       ├── travis_prepare.bash
│       └── travis_test.bash
#@# =========================
├── raspimouse_ros_2
│   ├── action
│   │   └── Music.action
│   ├── CMakeLists.txt
│   ├── launch
│   │   ├── raspimouse.launch				◀ 3. モータ通電（9axis_sensor は呼べてない？）
│   │   └── test.launch
│   ├── LICENSE
│   ├── msg
│   │   ├── ButtonValues.msg
│   │   ├── LedValues.msg
│   │   ├── LightSensorValues.msg
│   │   └── MotorFreqs.msg
│   ├── package.xml
│   ├── README.md
│   ├── scripts
│   │   └── buzzer.py						◀◀　from raspimouse.launch
│   ├── src
│   │   ├── buttons.cpp						◀◀　from raspimouse.launch
│   │   ├── leds.cpp						◀◀　from raspimouse.launch
│   │   ├── lightsensors.cpp				◀◀　from raspimouse.launch
│   │   └── motors.cpp						◀◀　from raspimouse.launch
│   ├── srv
│   │   └── TimedMotion.srv
│   └── test
│       ├── travis_package_make.bash
│       ├── travis_prepare_dummy_files.bash
│       ├── travis_ros_install.bash
│       ├── travis_test_buzzer.py
│       ├── travis_test_lightsensors.py
│       ├── travis_test_motors1.py
│       ├── travis_test_motors2.py
│       └── travis_test_motors.py
#@# =========================
├── raspimouse_sim
│   ├── docs
│   │   └── images
│   │       ├── raspimouse_samplemaze.png
│   │       └── raspimouse_urg.png
│   ├── LICENSE
│   ├── raspimouse_control
│   │   ├── CMakeLists.txt
│   │   ├── config
│   │   │   └── controller.yaml
│   │   ├── launch
│   │   │   └── raspimouse_control.launch					◀ 1. バーチャルデバイスのドライバとROSの関連付け
│   │   ├── misc
│   │   │   └── ms_sound.wav
│   │   ├── package.xml
│   │   └── scripts
│   │       ├── clean_dev_file.sh
│   │       ├── controller_vel_publisher.py
│   │       ├── gen_dev_file.sh
│   │       ├── virtual_led_sensors.py
│   │       └── virtual_motors.py
│   ├── raspimouse_description
│   │   ├── CMakeLists.txt
│   │   ├── launch
│   │   │   ├── config
│   │   │   │   └── urdf.rviz
│   │   │   ├── display_urdf.launch
│   │   │   └── display_xacro.launch
│   │   ├── meshes
│   │   │   ├── dae
│   │   │   │   ├── body
│   │   │   │   │   ├── RasPiMouse_body.dae
│   │   │   │   │   ├── RasPiMouse_body-TopPlate.dae
│   │   │   │   │   ├── RasPiMouse_body-TopPlate-URG.dae
│   │   │   │   │   └── RasPiMouse_TopPlate.dae
│   │   │   │   ├── sensor
│   │   │   │   │   ├── URG_center.dae
│   │   │   │   │   └── URG.dae
│   │   │   │   └── wheel
│   │   │   │       └── RasPiMouse_wheel.dae
│   │   │   └── stl
│   │   │       ├── color
│   │   │       │   ├── RasPiMouse_body_black.stl
│   │   │       │   ├── RasPiMouse_body_gray.stl
│   │   │       │   ├── RasPiMouse_body_green.stl
│   │   │       │   ├── RasPiMouse_body_red.stl
│   │   │       │   ├── RasPiMouse_wheel_black.stl
│   │   │       │   └── RasPiMouse_wheel_gray.stl
│   │   │       ├── RasPiMouse_base-metric.stl
│   │   │       ├── RasPiMouse_sensor-metric.stl
│   │   │       ├── RasPiMouse_TopPlate.stl
│   │   │       ├── RasPiMouse_wheel-metric.stl
│   │   │       ├── RasPiMouse_wheel-mm.stl
│   │   │       └── URG-04LX-UG01.stl
│   │   ├── model.config
│   │   ├── package.xml
│   │   └── urdf
│   │       ├── body
│   │       │   ├── body.gazebo.xacro
│   │       │   ├── body.urdf.xacro
│   │       │   ├── body_urg.gazebo.xacro
│   │       │   └── body_urg.urdf.xacro
│   │       ├── raspimouse.urdf
│   │       ├── raspimouse.urdf.xacro
│   │       ├── raspimouse_urg.urdf.xacro
│   │       ├── sensors
│   │       │   ├── hokuyo.gazebo.xacro.org
│   │       │   ├── lightsens.gazebo.xacro
│   │       │   ├── lightsens.urdf.xacro
│   │       │   ├── lrf.gazebo.xacro
│   │       │   └── lrf.urdf.xacro
│   │       └── wheel
│   │           ├── wheel.gazebo.xacro
│   │           ├── wheel.transmission.xacro
│   │           └── wheel.urdf.xacro
│   ├── raspimouse_gazebo
│   │   ├── CMakeLists.txt
│   │   ├── launch
│   │   │   ├── open_emptyworld.launch
│   │   │   ├── raspimouse_with_emptyworld.launch
│   │   │   ├── raspimouse_with_gasstand.launch
│   │   │   └── raspimouse_with_samplemaze.launch			◀　2. シミュレータ起動（含バーチャルデバイスのノード起動）
│   │   ├── materials
│   │   │   ├── gen_maze.sh
│   │   │   ├── sample_maze.wall.xacro
│   │   │   └── sample_maze.world.xacro
│   │   ├── package.xml
│   │   └── worlds
│   │       ├── gas_station.world
│   │       ├── hello.world
│   │       └── sample_maze.world
│   ├── raspimouse_sim
│   │   ├── CMakeLists.txt
│   │   └── package.xml
│   ├── README.ja.md
│   └── README.md
└── raspimouse_sim_tutorial_program
    ├── CMakeLists.txt
    ├── config
    │   └── gmapping.rviz
    ├── launch
    │   └── raspimouse_sim_gmapping.launch
    ├── map
    │   ├── sample_map.pgm
    │   └── sample_map.yaml
    ├── package.xml
    ├── README.md
    └── scripts
        ├── left_hand.py
        └── raspimouse_sim_teleop.py

