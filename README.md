# cloud_merge
ROS2(humble)上で複数の点群データを統合するためのパッケージ

## Usage
```
ros2 launch cloud_merge cloud_merge.launch.py
```

## Note
本プログラムではlaunchファイル内でcloud topicを最大4つまで指定することができ、config下のyamlファイルで指定できる。

# cloud_merge 仕様書

## 概要
`cloud_merge`は、ROS2 (humble) 環境で複数のセンサから受信した点群データ（PointCloud2）を、各センサのリンクフレームを考慮し、共通の`base_link`座標系で統合・出力するパッケージです。

---

## 主な機能
- 最大4つまでのPointCloud2トピックを購読し、各点群を`base_link`座標系に変換して統合
- URDFで定義された各センサのリンクフレームと`base_link`間のTFを自動で利用
- 統合結果を`cloud_out`トピックとして配信

---

## 動作要件
- ROS2 humble
- 各センサのframeがURDFで`base_link`に紐づいていること
- TFツリーが正しくブロードキャストされていること

---

## 使い方

### 起動
```
ros2 launch cloud_merge cloud_merge.launch.py
```

### 設定
- サブスクライブするcloudトピック名はlaunchファイルで最大4つまで指定可能
- configディレクトリ下のyamlファイルで詳細設定が可能

---

## 注意事項
- 各点群の`header.frame_id`が異なる場合も、TFを用いて自動的に`base_link`へ変換されます
- TFが取得できない場合は、その点群は統合されません（警告が出力されます）

---

## トピック一覧

| 名前         | 型                                   | 説明                       |
|--------------|--------------------------------------|----------------------------|
| cloud_in1    | sensor_msgs/msg/PointCloud2          | 入力点群1                  |
| cloud_in2    | sensor_msgs/msg/PointCloud2          | 入力点群2                  |
| cloud_in3    | sensor_msgs/msg/PointCloud2          | 入力点群3                  |
| cloud_in4    | sensor_msgs/msg/PointCloud2          | 入力点群4                  |
| cloud_out    | sensor_msgs/msg/PointCloud2          | 統合後の出力点群           |

---

## ライセンス
本パッケージはMITライセンスです。
