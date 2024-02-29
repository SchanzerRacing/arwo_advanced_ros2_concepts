#include <rclcpp/rclcpp.hpp>
#include "04_composition/listener_component.hpp"
#include "04_composition/heatbeat_sub_component.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor;
    auto listener = std::make_shared<arwo::ListenerNode>();
    auto heartbeat_sub = std::make_shared<arwo::HeartbeatSubNode>();
    executor.add_node(listener);
    executor.add_node(heartbeat_sub);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}