#include "04_composition/talker_component.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

TalkerNode::TalkerNode(const rclcpp::NodeOptions& options)
    : Node("talker", options)
{
    rclcpp::QoS qos_policy(10);

    chatter_pub_ = create_publisher<std_msgs::msg::String>("chatter", qos_policy);
    timer_ = create_wall_timer(1s, std::bind(&TalkerNode::timer_callback, this));
}

void TalkerNode::timer_callback()
{
    auto msg = std_msgs::msg::String();
    msg.data = "Hello, world!";
    chatter_pub_->publish(msg);
}

} // namespace arwo

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(arwo::TalkerNode)