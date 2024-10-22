# cloud_merge
ROS2(humble)上で複数の点群を統合するためのパッケージ

## Usage
```
ros2 launch cloud_merge cloud_merge.launch.py
```

## Note
本プログラムではlaunchファイル内でcloud topicを最大4つまで指定することができ、  
デフォルトのlaunchファイルでは```/sick_tim_L/tim_cloud_L```と```/multiScan/cloud_360```と指定している。
