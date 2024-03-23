from launch import LaunchDescription
from launch.actions import EmitEvent
from launch.events import matches_action
from launch_ros.actions import LifecycleNode
from launch_ros.events.lifecycle import ChangeState
from lifecycle_msgs.msg import Transition

def generate_launch_description():
    talker_node = LifecycleNode(
        package='03_lifecycle_management',
        executable='lifecycle_talker_node',
        namespace='arwo',
        name='lifecycle_talker_node',
        output='both'
    )

    listener_node = LifecycleNode(
        package='03_lifecycle_management',
        executable='lifecycle_listener_node',
        namespace='arwo',
        name='lifecycle_listener_node',
        output='both'
    )

    configure_talker_node = EmitEvent(
        event=ChangeState(
            lifecycle_node_matcher=matches_action(talker_node),
            transition_id=Transition.TRANSITION_CONFIGURE
        )
    )

    configure_listener_node = EmitEvent(
        event=ChangeState(
            lifecycle_node_matcher=matches_action(listener_node),
            transition_id=Transition.TRANSITION_CONFIGURE
        )
    )

    return LaunchDescription([
        talker_node,
        listener_node,
        configure_talker_node,
        configure_listener_node
    ])