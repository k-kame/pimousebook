= ラズパイマウスを走らせる（実機編）

== マウス制御プログラム開発の準備

 * ROS初期設定（ワークスペースの準備）
 * github からリポジトリをクローン

//table[list_repository][関連リポジトリ]{
リポジトリ名	役割
----------
pimouse_sim_act			メイン
pimouse_ros				？？
pimouse_run_corridor	？？
raspimouse_ros			？？
raspimouse_ros_2		？？
raspimouse_sim			？？
raspimouse_sim_tutorial_program
//}

== プログラムの説明

 * 走らせてみよう
 * 改造の仕方
 * 迷路を解かせよう


├── pimouse_ros
│   ├── action
│   │   └── Music.action
│   ├── CMakeLists.txt
│   ├── launch
│   │   ├── pimouse.launch
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
│   │   ├── buzzer.py
│   │   ├── lightsensors1.py
│   │   ├── lightsensors2.py
│   │   ├── lightsensors.py
│   │   ├── motors1.py
│   │   ├── motors2.py
│   │   └── motors.py
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
├── pimouse_sim_act
│   ├── CMakeLists.txt
│   ├── howtouse.txt
│   ├── launch
│   │   ├── raspimouse_act.launch
│   │   └── raspimouse_sim.launch
│   ├── package.xml
│   ├── pimouse_sim_act.code-workspace
│   └── scripts
│       ├── left_hand3.py
│       ├── left_hand.py
│       ├── pimouse_sim_run.py
│       └── wall_around.py
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
├── raspimouse_ros_2
│   ├── action
│   │   └── Music.action
│   ├── CMakeLists.txt
│   ├── launch
│   │   ├── raspimouse.launch
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
│   │   └── buzzer.py
│   ├── src
│   │   ├── buttons.cpp
│   │   ├── leds.cpp
│   │   ├── lightsensors.cpp
│   │   └── motors.cpp
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
│   │   │   └── raspimouse_control.launch
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
│   │   │   └── raspimouse_with_samplemaze.launch
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

