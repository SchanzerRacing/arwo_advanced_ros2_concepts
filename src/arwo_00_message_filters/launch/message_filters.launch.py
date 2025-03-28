from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    image_dir = PathJoinSubstitution([FindPackageShare('arwo_00_message_filters'), 'images'])

    image1_pub_node = Node(
        package='image_publisher',
        executable='image_publisher_node',
        namespace='arwo',
        name='image1_pub_node',
        output='screen',
        parameters=[
            {'frame_id': 'camera_1'},
            {'publish_rate': 29.0},
            {'camera_info_url': 'package://arwo_00_message_filters/config/camera_1_info.yaml'},
            {'filename': PathJoinSubstitution([image_dir, 'left.png'])},
        ],
        remappings=[('image_raw', 'camera_1/image_raw'), ('camera_info', 'camera_1/camera_info')],
    )

    image2_pub_node = Node(
        package='image_publisher',
        executable='image_publisher_node',
        namespace='arwo',
        name='image2_pub_node',
        output='screen',
        parameters=[
            {'frame_id': 'camera_2'},
            {'publish_rate': 30.0},
            {'camera_info_url': 'package://arwo_00_message_filters/config/camera_2_info.yaml'},
            {'filename': PathJoinSubstitution([image_dir, 'right.png'])},
        ],
        remappings=[('image_raw', 'camera_2/image_raw'), ('camera_info', 'camera_2/camera_info')],
    )

    approx_time_sync_node = Node(
        package='arwo_00_message_filters',
        executable='approx_time_sync_node',
        namespace='arwo',
        name='approx_time_sync_node',
        output='both',
    )

    exact_time_sync_node = Node(
        package='arwo_00_message_filters',
        executable='exact_time_sync_node',
        namespace='arwo',
        name='exact_time_sync_node',
        output='both',
    )

    return LaunchDescription(
        [
            image1_pub_node,
            image2_pub_node,
            approx_time_sync_node,
            exact_time_sync_node,
        ]
    )
