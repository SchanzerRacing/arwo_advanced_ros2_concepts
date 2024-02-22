#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo 
{

class ExactTimeSyncNode : public rclcpp::Node
{
public:
    ExactTimeSyncNode()
        : Node("approx_time_sync_node")
    {
        rclcpp::QoS qos_policy(10);
        auto rmw_qos_profile = qos_policy.get_rmw_qos_profile();
        image_sub_.subscribe(this, "/camera_1/image_raw", rmw_qos_profile);
        camera_info_sub_.subscribe(this, "/camera_1/camera_info", rmw_qos_profile);
        camera_info_sync_ = std::make_shared<CameraInfoSynchronizer>(10, image_sub_, camera_info_sub_);
        camera_info_sync_->registerCallback(std::bind(&ExactTimeSyncNode::sensor_callback, this, _1, _2));
    }

    void sensor_callback(
        const sensor_msgs::msg::Image::ConstSharedPtr& image_msg, 
        const sensor_msgs::msg::CameraInfo::ConstSharedPtr& camera_info_msg)
    {
        RCLCPP_INFO(get_logger(), 
            "image: %d.%d info: %d.%d",
            image_msg->header.stamp.sec,
            image_msg->header.stamp.nanosec,
            camera_info_msg->header.stamp.sec,
            camera_info_msg->header.stamp.nanosec
        );
    }

private:
    typedef message_filters::TimeSynchronizer<sensor_msgs::msg::Image, sensor_msgs::msg::CameraInfo> CameraInfoSynchronizer;
    message_filters::Subscriber<sensor_msgs::msg::Image> image_sub_;
    message_filters::Subscriber<sensor_msgs::msg::CameraInfo> camera_info_sub_;
    std::shared_ptr<CameraInfoSynchronizer> camera_info_sync_;
};

} // namespace arwo

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<arwo::ExactTimeSyncNode>());
    rclcpp::shutdown();
    return 0;
}