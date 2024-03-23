from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node

def generate_launch_description():
    qos_overrides = PathJoinSubstitution([FindPackageShare('01_quality_of_service'), 'config', 'qos_overrides.yaml'])

    qos_overrides_listener_node = Node(
        package='01_quality_of_service',
        executable='qos_overrides_listener_node',
        namespace='arwo',
        name='qos_overrides_listener_node',
        output='screen',
        parameters=[qos_overrides]
    )

    qos_overrides_talker_node = Node(
        package='01_quality_of_service',
        executable='qos_overrides_talker_node',
        namespace='arwo',
        name='qos_overrides_talker_node',
        output='screen',
        parameters=[qos_overrides]
    )

    return LaunchDescription([
        qos_overrides_listener_node,
        qos_overrides_talker_node
    ])