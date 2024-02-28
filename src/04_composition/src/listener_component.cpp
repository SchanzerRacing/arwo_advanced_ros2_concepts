#include "04_composition/listener_component.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

ListenerNode::ListenerNode(const rclcpp::NodeOptions& options)
    : Node("listener", options)
{
    chatter_sub_ = create_subscription<std_msgs::msg::String>("chatter", 10, std::bind(&ListenerNode::chatter_callback, this, _1));
}

void ListenerNode::chatter_callback(const std_msgs::msg::String::SharedPtr msg)
{
    RCLCPP_INFO(get_logger(), "I heard: '%s'", msg->data.c_str());
}

} // namespace arwo

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(arwo::ListenerNode)