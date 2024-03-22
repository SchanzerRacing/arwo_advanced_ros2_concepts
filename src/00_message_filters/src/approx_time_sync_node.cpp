#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo 
{

class ApproxTimeSyncNode : public rclcpp::Node
{
public:
    ApproxTimeSyncNode()
        : Node("approx_time_sync_node")
    {
        rclcpp::QoS qos_policy(10);
        auto rmw_qos_profile = qos_policy.get_rmw_qos_profile();
        image_1_sub_.subscribe(this, "camera_1/image_raw", rmw_qos_profile);
        image_2_sub_.subscribe(this, "camera_2/image_raw", rmw_qos_profile);
        image_sync_ = std::make_shared<ImageSynchronizer>(ImageSyncPolicy(10), image_1_sub_, image_2_sub_);
        image_sync_->setMaxIntervalDuration(rclcpp::Duration(10ms));
        image_sync_->registerCallback(std::bind(&ApproxTimeSyncNode::sensor_callback, this, _1, _2));
    }

    void sensor_callback(
        const sensor_msgs::msg::Image::ConstSharedPtr& image_1, 
        const sensor_msgs::msg::Image::ConstSharedPtr& image_2)
    {
        RCLCPP_INFO(get_logger(), 
            "image1: %d.%d image2: %d.%d",
            image_1->header.stamp.sec,
            image_1->header.stamp.nanosec,
            image_2->header.stamp.sec,
            image_2->header.stamp.nanosec
        );
    }

private:
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::msg::Image, sensor_msgs::msg::Image> ImageSyncPolicy;
    typedef message_filters::Synchronizer<ImageSyncPolicy> ImageSynchronizer;
    message_filters::Subscriber<sensor_msgs::msg::Image> image_1_sub_;
    message_filters::Subscriber<sensor_msgs::msg::Image> image_2_sub_;
    std::shared_ptr<ImageSynchronizer> image_sync_;
};

} // namespace arwo

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<arwo::ApproxTimeSyncNode>());
    rclcpp::shutdown();
    return 0;
}