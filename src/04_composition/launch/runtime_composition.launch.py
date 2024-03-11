from launch import LaunchDescription
from launch_ros.actions import Node, ComposableNodeContainer
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
                package='04_composition',
                plugin='arwo::LifecycleTalkerNode',
                namespace='arwo',
                name='lifecycle_talker_node'
            ),
            ComposableNode(
                package='04_composition',
                plugin='arwo::HeartbeatPubNode',
                namespace='arwo',
                name='heartbeat_pub_node'
            )
        ]
    )

    listener_container = ComposableNodeContainer(
        package='rclcpp_components',
        executable='component_container',
        namespace='arwo',
        name='listener_container',
        output='both',
        composable_node_descriptions=[
            ComposableNode(
                package='04_composition',
                plugin='arwo::ListenerNode',
                namespace='arwo',
                name='listener_node'
            ),
            ComposableNode(
                package='04_composition',
                plugin='arwo::HeartbeatSubNode',
                namespace='arwo',
                name='heartbeat_sub_node'
            )
        ]
    )

    lifecycle_manager = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        namespace='arwo',
        name='lifecycle_manager',
        output='both',
        parameters=[
            {'autostart': True},
            {'node_names': ['arwo/lifecycle_talker_node']},
            {'bond_timeout': 4.0},
            {'attempt_respawn_reconnection': True},
            {'bond_respawn_max_duration': 10.0}
        ]
    )

    return LaunchDescription([
        talker_container,
        listener_container,
        configure_lifecycle_talker_node_timer,
        activate_lifecycle_talker_node_event
    ])