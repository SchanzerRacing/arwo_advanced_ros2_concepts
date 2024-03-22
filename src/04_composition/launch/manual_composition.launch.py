from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    talker_container = Node(
        package='04_composition',
        executable='manual_talker_composition',
        namespace='arwo',
        name='manual_talker_container',
        output='both'
    )
    
    listener_container = Node(
        package='04_composition',
        executable='manual_listener_composition',
        namespace='arwo',
        name='manual_listener_container',
        output='both'
    )

    return LaunchDescription([
        talker_container,
        listener_container
    ])