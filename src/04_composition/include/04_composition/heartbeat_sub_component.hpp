#ifndef ARWO_04_COMPOSITION_HEARTBEAT_SUB_COMPONENT_HPP_
#define ARWO_04_COMPOSITION_HEARTBEAT_SUB_COMPONENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/header.hpp>

namespace arwo
{

class HeartbeatSubNode : public rclcpp::Node
{
public:
    HeartbeatSubNode(const rclcpp::NodeOptions& options);
    void heartbeat_callback(const std_msgs::msg::Header::SharedPtr msg);

private:
    rclcpp::Subscription<std_msgs::msg::Header>::SharedPtr heartbeat_sub_;
}

} // namespace arwo

#endif // ARWO_04_COMPOSITION_HEARTBEAT_SUB_COMPONENT_HPP_