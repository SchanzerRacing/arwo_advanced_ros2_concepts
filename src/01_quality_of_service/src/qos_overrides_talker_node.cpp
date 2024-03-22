#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"

using namespace std::chrono_literals;

namespace arwo 
{

class QosOverridesTalkerNode : public rclcpp::Node
{
public:
    QosOverridesTalkerNode()
        : Node("qos_overrides_talker")
    {
        rclcpp::PublisherOptions pub_options;
        pub_options.qos_overriding_options = rclcpp::QosOverridingOptions {
            {
                rclcpp::QosPolicyKind::Depth,
                rclcpp::QosPolicyKind::Durability,
                rclcpp::QosPolicyKind::History,
                rclcpp::QosPolicyKind::Reliability
            },
            [](const rclcpp::QoS &qos) {
                rclcpp::QosCallbackResult result;
                result.successful = false;
                if (qos.depth() > 10u) {
                    result.reason = "expected history depth less or equal than 10";
                    return result;
                }
                result.successful = true;
                return result;
            }
        };

        pub_ = create_publisher<std_msgs::msg::Header>("/qos_overrides_chatter", 1, pub_options);
        timer_ = create_wall_timer(1s, std::bind(&QosOverridesTalkerNode::timer_callback, this));
    }

    void timer_callback()
    {
        std_msgs::msg::Header msg;
        msg.stamp = now();
        pub_->publish(msg);
    }

private:
    rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace arwo

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<arwo::QosOverridesTalkerNode>());
    rclcpp::shutdown();
    return 0;
}