from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    talker_container = Node(
        package='04_composition',
        executable='dlopen_composition',
        namespace='arwo',
        name='dlopen_talker_container',
        output='both',
        arguments=[
            '04_composition/lib/libheartbeat_pub_component.so',
            '04_composition/lib/liblifecycle_talker_component.so'
        ]
    )

    listener_container = Node(
        package='04_composition',
        executable='dlopen_composition',
        namespace='arwo',
        name='dlopen_listener_container',
        output='both',
        arguments=[
            '04_composition/lib/libheartbeat_sub_component.so',
            '04_composition/lib/liblistener_component.so'
        ]
    )

    return LaunchDescription([
        talker_container,
        listener_container
    ])