from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    manual_qos_listener_node = Node(
        package='01_quality_of_service',
        executable='manual_qos_listener_node',
        namespace='arwo',
        name='manual_qos_listener_node',
        output='screen',
        parameters=[]
    )

    manual_qos_talker_node = Node(
        package='01_quality_of_service',
        executable='manual_qos_talker_node',
        namespace='arwo',
        name='manual_qos_listener_node',
        output='screen',
        parameters=[]
    )

    return LaunchDescription([
        manual_qos_listener_node,
        manual_qos_talker_node
    ])