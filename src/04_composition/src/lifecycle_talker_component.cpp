#include "04_composition/lifecycle_talker_component.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

LifecycleTalkerNode::LifecycleTalkerNode(const rclcpp::NodeOptions& options)
    : LifecycleNode("talker", options)
{
}

LNI::CallbackReturn LifecycleTalkerNode::on_configure(const rclcpp_lifecycle::State& state)
{
    (void) state;

    rclcpp::QoS qos_policy(10);
    chatter_pub_ = create_publisher<std_msgs::msg::String>("chatter", qos_policy);
    timer_ = create_wall_timer(1s, std::bind(&LifecycleTalkerNode::timer_callback, this));

    return LNI::CallbackReturn::SUCCESS;
}

LNI::CallbackReturn LifecycleTalkerNode::on_cleanup(const rclcpp_lifecycle::State& state)
{
    (void) state;

    chatter_pub_.reset();
    timer_.reset();

    return LNI::CallbackReturn::SUCCESS;
}

void LifecycleTalkerNode::timer_callback()
{
    static int n = 0;

    auto msg = std_msgs::msg::String();
    msg.data = "Hello, world! " + n++;
    chatter_pub_->publish(msg);
}

} // namespace arwo

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(arwo::LifecycleTalkerNode)