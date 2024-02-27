#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/header.hpp>

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

class ReliableSubscriberNode : public rclcpp::Node
{
public:
    ReliableSubscriberNode()
        : Node("reliable_subscriber_node")
    {
        rclcpp::QoS qos_profile(10);
        qos_profile.reliable();
        qos_profile.durability_volatile();

        reliable_sub_ = create_subscription<std_msgs::msg::Header>(
            "/reliable_topic", 
            qos_profile,
            std::bind(&ReliableSubscriberNode::callback, this, _1)
        );
    }

    void callback(const std_msgs::msg::Header::ConstSharedPtr& msg)
    {
        rclcpp::Time stamp(msg->stamp);
        RCLCPP_INFO(get_logger(), "%f", stamp.seconds());
    }

private:
    rclcpp::Subscription<std_msgs::msg::Header>::SharedPtr reliable_sub_;
};

} // namespace arwo

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<arwo::ReliableSubscriberNode>());
    rclcpp::shutdown();
    return 0;
}