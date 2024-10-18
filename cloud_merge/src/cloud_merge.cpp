#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

class CloudMergeNode : public rclcpp::Node
{
public:
    CloudMergeNode() : Node("cloud_merge_node")
    {
        sub_pc1_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/cloud_in1", 10, std::bind(&CloudMergeNode::pointcloud1_callback, this, std::placeholders::_1));

        sub_pc2_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/cloud_in2", 10, std::bind(&CloudMergeNode::pointcloud2_callback, this, std::placeholders::_1));

        pub_concatenated_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/concatenated_pointcloud", 10);
    }

private:
    void pointcloud1_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        pcl::fromROSMsg(*msg, cloud1_);
        process_pointclouds();
    }

    void pointcloud2_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        pcl::fromROSMsg(*msg, cloud2_);
        process_pointclouds();
    }

    void process_pointclouds()
    {
        if (!cloud1_.empty() && !cloud2_.empty())
        {
            pcl::PointCloud<pcl::PointXYZ> concatenated_cloud = cloud1_;
            concatenated_cloud += cloud2_;  // +=演算子でポイントクラウドを結合

            sensor_msgs::msg::PointCloud2 output_msg;
            pcl::toROSMsg(concatenated_cloud, output_msg);
            output_msg.header.frame_id = "map";
            pub_concatenated_->publish(output_msg);
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_pc1_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_pc2_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_concatenated_;

    pcl::PointCloud<pcl::PointXYZ> cloud1_;
    pcl::PointCloud<pcl::PointXYZ> cloud2_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CloudMergeNode>());
    rclcpp::shutdown();
    return 0;
}
