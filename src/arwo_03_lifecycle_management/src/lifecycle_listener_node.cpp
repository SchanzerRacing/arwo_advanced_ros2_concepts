#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;
using namespace std::placeholders;

namespace arwo
{

class LifecycleListenerNode : public rclcpp_lifecycle::LifecycleNode
{
  using LNI = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface;

public:
  LifecycleListenerNode()
  : LifecycleNode("lifecycle_listener")
  {}

  LNI::CallbackReturn on_configure(const rclcpp_lifecycle::State & state)
  {
    (void) state;
    chatter_sub_ = create_subscription<std_msgs::msg::String>(
      "chatter",
      10,
      std::bind(&LifecycleListenerNode::chatter_callback, this, _1)
    );

    return LNI::CallbackReturn::SUCCESS;
  }

  LNI::CallbackReturn on_cleanup(const rclcpp_lifecycle::State & state)
  {
    (void) state;
    chatter_sub_.reset();

    return LNI::CallbackReturn::SUCCESS;
  }

  void chatter_callback(const std_msgs::msg::String::SharedPtr msg)
  {
    if (get_current_state().label() != "active") {
      RCLCPP_INFO(get_logger(), "I heard something, but I'm not currently active.");
    } else {
      RCLCPP_INFO(get_logger(), "I heard: '%s'", msg->data.c_str());
    }
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr chatter_sub_;
};

}  // namespace arwo

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<arwo::LifecycleListenerNode>();
  rclcpp::spin(node->get_node_base_interface());
  rclcpp::shutdown();
}
