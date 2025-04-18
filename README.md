# cloud_merge
ROS2(humble)上で複数の点群データを統合するためのパッケージ

## Usage
```
ros2 launch cloud_merge cloud_merge.launch.py
```

## Note
本プログラムではlaunchファイル内でcloud topicを最大4つまで指定することができ、config下のyamlファイルで指定できる。
