#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/header.hpp>

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

class ManualQosListenerNode : public rclcpp::Node
{
public:
    ManualQosListenerNode()
        : Node("manual_qos_listener")
    {
        rclcpp::QoS qos_profile(10);
        //qos_profile.history();
        //qos_profile.depth();
        qos_profile.best_effort();
        qos_profile.durability_volatile();
        qos_profile.deadline(100ms);
        qos_profile.lifespan(100ms);
        //qos_profile.liveliness();
        qos_profile.liveliness_lease_duration(100ms);

        reliable_sub_ = create_subscription<std_msgs::msg::Header>(
            "/manual_qos_chatter", 
            qos_profile,
            std::bind(&ManualQosListenerNode::callback, this, _1)
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
    rclcpp::spin(std::make_shared<arwo::ManualQosListenerNode>());
    rclcpp::shutdown();
    return 0;
}