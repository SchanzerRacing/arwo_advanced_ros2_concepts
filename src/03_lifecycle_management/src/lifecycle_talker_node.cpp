#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;

namespace arwo
{

class LifecycleTalkerNode : public rclcpp_lifecycle::LifecycleNode
{
    using LNI = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface;

public:
    LifecycleTalkerNode()
        : LifecycleNode("lifecycle_talker")
    {}

    LNI::CallbackReturn on_configure(const rclcpp_lifecycle::State& state)
    {
        (void) state;

        chatter_pub_ = create_publisher<std_msgs::msg::String>("/chatter", 10);
        chatter_timer_ = create_wall_timer(1s, std::bind(&LifecycleTalkerNode::timer_callback, this));

        return LNI::CallbackReturn::SUCCESS;
    }

    LNI::CallbackReturn on_cleanup(const rclcpp_lifecycle::State& state)
    {
        (void) state;

        chatter_pub_.reset();
        chatter_timer_->cancel();
        chatter_timer_.reset();

        return LNI::CallbackReturn::SUCCESS;
    }

    void timer_callback()
    {
        static int n = 0;

        if(get_current_state().label() != "active") {
            RCLCPP_INFO(get_logger(), "I'm not publishing because I'm inactive, but the timer is still running.");
        }

        std_msgs::msg::String msg;
        msg.data = "Hello world! " + n++;
        chatter_pub_->publish(msg);
    }

private:
    rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>::SharedPtr chatter_pub_;
    rclcpp::TimerBase::SharedPtr chatter_timer_;
};

} // namespace arwo

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<arwo::LifecycleTalkerNode>();
    rclcpp::spin(node->get_node_base_interface());
    rclcpp::shutdown();
}