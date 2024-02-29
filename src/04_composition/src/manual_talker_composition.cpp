#include <rclcpp/rclcpp.hpp>
#include "04_composition/talker_component.hpp"
#include "04_composition/heartbeat_pub_component.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor;
    auto talker = std::make_shared<arwo::TalkerNode>();
    auto heartbeat_pub = std::make_shared<arwo::HeartbeatPubNode>();
    executor.add_node(talker);
    executor.add_node(heartbeat_pub);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}