from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    talker_container = ComposableNodeContainer(
        package='rclcpp_components',
        executable='component_container',
        namespace='arwo',
        name='talker_container',
        output='both',
        composable_node_descriptions=[
            ComposableNode(
                package='arwo_04_composition',
                plugin='arwo::LifecycleTalkerNode',
                namespace='arwo',
                name='lifecycle_talker_node',
            ),
            ComposableNode(
                package='arwo_04_composition',
                plugin='arwo::HeartbeatPubNode',
                namespace='arwo',
                name='heartbeat_pub_node',
            ),
        ],
    )

    listener_container = ComposableNodeContainer(
        package='rclcpp_components',
        executable='component_container',
        namespace='arwo',
        name='listener_container',
        output='both',
        composable_node_descriptions=[
            ComposableNode(
                package='arwo_04_composition',
                plugin='arwo::ListenerNode',
                namespace='arwo',
                name='listener_node',
            ),
            ComposableNode(
                package='arwo_04_composition',
                plugin='arwo::HeartbeatSubNode',
                namespace='arwo',
                name='heartbeat_sub_node',
            ),
        ],
    )

    return LaunchDescription([talker_container, listener_container])
