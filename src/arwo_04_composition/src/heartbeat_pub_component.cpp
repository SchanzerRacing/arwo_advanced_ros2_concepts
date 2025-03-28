#include "arwo_04_composition/heartbeat_pub_component.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

HeartbeatPubNode::HeartbeatPubNode(const rclcpp::NodeOptions & options)
: Node("heartbeat_publisher", options)
{
  rclcpp::QoS qos_policy(10);

  heartbeat_pub_ = create_publisher<std_msgs::msg::Header>("/heartbeat", qos_policy);
  heartbeat_timer_ =
    create_wall_timer(1s, std::bind(&HeartbeatPubNode::heartbeat_timer_callback, this));
}

void HeartbeatPubNode::heartbeat_timer_callback()
{
  std_msgs::msg::Header msg;
  msg.frame_id = "heartbeat_publisher";
  msg.stamp = now();
  heartbeat_pub_->publish(msg);
}

} // namespace arwo

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(arwo::HeartbeatPubNode)
