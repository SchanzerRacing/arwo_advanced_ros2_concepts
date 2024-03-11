#ifndef ARWO_04_COMPOSITION_LIFECYCLE_TALKER_COMPONENT_HPP_
#define ARWO_04_COMPOSITION_LIFECYCLE_TALKER_COMPONENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <std_msgs/msg/string.hpp>

namespace arwo
{

using LNI = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface;

class LifecycleTalkerNode : public rclcpp_lifecycle::LifecycleNode
{
public:
    LifecycleTalkerNode(const rclcpp::NodeOptions& options);
    LNI::CallbackReturn on_configure(const rclcpp_lifecycle::State& state);
    LNI::CallbackReturn on_cleanup(const rclcpp_lifecycle::State& state);
    void timer_callback();

private:
    rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>::SharedPtr chatter_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace arwo

#endif // ARWO_04_COMPOSITION_LIFECYCLE_TALKER_COMPONENT_HPP_