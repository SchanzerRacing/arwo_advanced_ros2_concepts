#include "class_loader/class_loader.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/node_factory.hpp"

#define DLOPEN_COMPOSITION_LOGGER_NAME "dlopen_composition"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Requires at least one argument to be passed with the library to load\n");
        return 1;
    }

    rclcpp::init(argc, argv);
    rclcpp::Logger logger = rclcpp::get_logger(DLOPEN_COMPOSITION_LOGGER_NAME);
    rclcpp::executors::SingleThreadedExecutor executor;
    rclcpp::NodeOptions options;
    std::vector<std::unique_ptr<class_loader::ClassLoader>> loaders;
    std::vector<rclcpp_components::NodeInstanceWrapper> node_wrappers;

    std::vector<std::string> libraries;
    for (auto library : libraries) {
        RCLCPP_INFO(logger, "Load library %s", library.c_str());
        auto loader = std::make_unique<class_loader::ClassLoader>(library);
        auto classes = loader->getAvailableClasses<rclcpp_components::NodeFactory>();
        for (auto c : classes) {
            RCLCPP_INFO(logger, "Instantiate class %s", c.c_str());
            auto node_factory = loader->createInstance<rclcpp_components::NodeFactory>(c);
            auto wrapper = node_factory->create_node_instance(options);
            auto node = wrapper.get_node_base_interface();
            node_wrappers.push_back(wrapper);
            executor.add_node(node);
        }
        loaders.push_back(std::move(loader));
    }

    executor.spin();

    for (auto wrapper : node_wrappers) {
        executor.remove_node(wrapper.get_node_base_interface());
    }
    node_wrappers.clear();

    rclcpp::shutdown();

    return 0;
}