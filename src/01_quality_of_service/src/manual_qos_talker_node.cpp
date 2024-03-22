#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/header.hpp>

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

class ManualQosTalkerNode : public rclcpp::Node
{
public:
    ManualQosTalkerNode()
        : Node("manual_qos_talker")
    {
        rclcpp::QoS qos_policy(10);
        qos_policy.reliable();

        header_pub_ = create_publisher<std_msgs::msg::Header>("/manual_qos_chatter", qos_policy);
        timer_ = create_wall_timer(1s, std::bind(&ManualQosTalkerNode::timer_callback, this));
    }

    void timer_callback()
    {
        std_msgs::msg::Header msg;
        msg.stamp = now();
        header_pub_->publish(msg);
    }

private:
    rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr header_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace arwo

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<arwo::ManualQosTalkerNode>());
    rclcpp::shutdown();
    return 0;
}