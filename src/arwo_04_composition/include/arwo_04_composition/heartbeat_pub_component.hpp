#ifndef ARWO_04_COMPOSITION_HEARTBEAT_PUB_COMPONENT_HPP_
#define ARWO_04_COMPOSITION_HEARTBEAT_PUB_COMPONENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/header.hpp>

namespace arwo
{

class HeartbeatPubNode : public rclcpp::Node
{
public:
  HeartbeatPubNode(const rclcpp::NodeOptions & options);
  void heartbeat_timer_callback();

private:
  rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr heartbeat_pub_;
  rclcpp::TimerBase::SharedPtr heartbeat_timer_;
};

}  // namespace arwo

#endif  // ARWO_04_COMPOSITION_HEARTBEAT_PUB_COMPONENT_HPP_
