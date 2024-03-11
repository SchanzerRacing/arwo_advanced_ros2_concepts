#include <rclcpp/rclcpp.hpp>
#include "04_composition/listener_component.hpp"
#include "04_composition/heartbeat_sub_component.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor;
    rclcpp::NodeOptions node_options;
    node_options.use_intra_process_comms(true);
    auto listener = std::make_shared<arwo::ListenerNode>(node_options);
    auto heartbeat_sub = std::make_shared<arwo::HeartbeatSubNode>(node_options);
    executor.add_node(listener);
    executor.add_node(heartbeat_sub);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}