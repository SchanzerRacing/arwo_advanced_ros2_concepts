#ifndef ARWO_04_COMPOSITION_TALKER_COMPONENT_HPP_
#define ARWO_04_COMPOSITION_TALKER_COMPONENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace arwo
{

class TalkerNode : public rclcpp::Node
{
public:
    TalkerNode(const rclcpp::NodeOptions& options);
    void timer_callback();

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr chatter_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace arwo

#endif // ARWO_04_COMPOSITION_TALKER_COMPONENT_HPP_