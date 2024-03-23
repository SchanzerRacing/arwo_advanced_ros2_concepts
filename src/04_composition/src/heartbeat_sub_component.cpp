#include "04_composition/heartbeat_sub_component.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

HeartbeatSubNode::HeartbeatSubNode(const rclcpp::NodeOptions& options)
    : Node("heartbeat_subscriber", options)
{
    rclcpp::QoS qos_profile(10);

    heartbeat_sub_ = create_subscription<std_msgs::msg::Header>(
        "/heartbeat",
        qos_profile,
        std::bind(&HeartbeatSubNode::heartbeat_callback, this, _1)
    );
}

void HeartbeatSubNode::heartbeat_callback(const std_msgs::msg::Header::SharedPtr msg)
{
    rclcpp::Time stamp(msg->stamp);
    RCLCPP_INFO(get_logger(), "Received heartbeat from %s at %f", msg->frame_id.c_str(), stamp.seconds());
}

} // namepsace arwo

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(arwo::HeartbeatSubNode)