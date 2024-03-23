#ifndef ARWO_04_COMPOSITION_LISTENER_COMPONENT_HPP_
#define ARWO_04_COMPOSITION_LISTENER_COMPONENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace arwo
{

class ListenerNode : public rclcpp::Node
{
public:
    ListenerNode(const rclcpp::NodeOptions& options);
    void chatter_callback(const std_msgs::msg::String::SharedPtr msg);

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr chatter_sub_;
};

} // namespace arwo

#endif // ARWO_04_COMPOSITION_LISTENER_COMPONENT_HPP_