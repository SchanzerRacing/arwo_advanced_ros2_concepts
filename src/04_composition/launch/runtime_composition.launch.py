from launch import LaunchDescription
from launch.actions import ExecuteProcess, TimerAction, RegisterEventHandler
from launch.event_handlers import OnProcessExit
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

    configure_lifecycle_talker_node = ExecuteProcess(
        name='configure_socket_can_receiver',
        cmd=['ros2', 'lifecycle', 'set', 'arwo/lifecycle_talker_node', 'configure']
    )

    activate_lifecycle_talker_node = ExecuteProcess(
        name='configure_socket_can_receiver',
        cmd=['ros2', 'lifecycle', 'set', 'arwo/lifecycle_talker_node', 'activate']
    )

    configure_lifecycle_talker_node_timer = TimerAction(
        period=2.0,
        actions=[configure_lifecycle_talker_node]
    )

    activate_lifecycle_talker_node_event = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=configure_lifecycle_talker_node,
            on_exit=[activate_lifecycle_talker_node],
        )
    )

    return LaunchDescription([
        talker_container,
        listener_container,
        configure_lifecycle_talker_node_timer,
        activate_lifecycle_talker_node_event
    ])