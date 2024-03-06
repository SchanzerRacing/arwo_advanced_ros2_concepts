from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    image1_pub_node = Node(
        package='',
        executable='',
        namespace='arwo',
        name='image1_pub_node',
        output='both',
        remappings=[
        ]
    )

    image2_pub_node = Node(
        package='',
        executable='',
        namespace='arwo',
        name='image2_pub_node',
        output='both'
    )

    approx_time_sync_node = Node(
        package='00_message_filters',
        executable='approx_time_sync_node',
        namespace='arwo',
        name='approx_time_sync_node',
        output='both'
    )

    exact_time_sync_node = Node(
        package='00_message_filters',
        executable='exact_time_sync_node',
        namespace='arwo',
        name='exact_time_sync_node',
        output='both'
    )

    return LaunchDescription([
        image1_pub_node,
        image2_pub_node,
        approx_time_sync_node,
        exact_time_sync_node
    ])