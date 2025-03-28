from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
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
            {'bond_respawn_max_duration': 10.0},
        ],
    )

    return LaunchDescription([lifecycle_manager])
