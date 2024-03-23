#include <rclcpp/rclcpp.hpp>
#include "04_composition/lifecycle_talker_component.hpp"
#include "04_composition/heartbeat_pub_component.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor;

    rclcpp::NodeOptions node_options;
    node_options.use_intra_process_comms(true);
    auto lifecycle_talker = std::make_shared<arwo::LifecycleTalkerNode>(node_options);
    auto heartbeat_pub = std::make_shared<arwo::HeartbeatPubNode>(node_options);
    executor.add_node(lifecycle_talker->get_node_base_interface());
    executor.add_node(heartbeat_pub);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}