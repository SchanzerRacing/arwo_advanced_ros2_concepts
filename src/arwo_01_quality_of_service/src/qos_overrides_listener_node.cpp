#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"

using namespace std::placeholders;

namespace arwo
{

class QosOverridesListenerNode : public rclcpp::Node
{
public:
  QosOverridesListenerNode()
  : Node("qos_overrides_listener")
  {
    rclcpp::SubscriptionOptions sub_options;
    sub_options.qos_overriding_options = rclcpp::QosOverridingOptions {
      {
        rclcpp::QosPolicyKind::Depth,
        rclcpp::QosPolicyKind::Durability,
        rclcpp::QosPolicyKind::History,
        rclcpp::QosPolicyKind::Reliability,
      },
      [](const rclcpp::QoS & qos) {
        rclcpp::QosCallbackResult result;
        result.successful = false;
        if (qos.depth() > 10u) {
          result.reason = "expected history depth less or equal than 10";
          return result;
        }
        result.successful = true;
        return result;
      }
    };

    sub_ = create_subscription<std_msgs::msg::Header>(
      "/qos_overrides_chatter",
      1,
      std::bind(&QosOverridesListenerNode::callback, this, _1),
      sub_options
    );
  }

  void callback(const std_msgs::msg::Header::ConstSharedPtr & msg)
  {
    rclcpp::Time stamp(msg->stamp);
    RCLCPP_INFO(get_logger(), "%f", stamp.seconds());
  }

private:
  rclcpp::Subscription<std_msgs::msg::Header>::SharedPtr sub_;
};

} // namespace arwo

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<arwo::QosOverridesListenerNode>());
  rclcpp::shutdown();
  return 0;
}
