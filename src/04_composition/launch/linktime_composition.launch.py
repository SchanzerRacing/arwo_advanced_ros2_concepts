from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    talker_container = Node(
        package='04_composition',
        executable='linktime_talker_composition',
        namespace='arwo',
        name='linktime_talker_container',
        output='both'
    )
    
    listener_container = Node(
        package='04_composition',
        executable='linktime_listener_composition',
        namespace='arwo',
        name='linktime_listener_container',
        output='both'
    )

    return LaunchDescription([
        talker_container,
        listener_container
    ])