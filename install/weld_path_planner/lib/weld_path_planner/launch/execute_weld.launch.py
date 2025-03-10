from launch import LaunchDescription
from launch_ros.actions import Node
from moveit_ros.planning_interface import MoveGroupInterface # type: ignore

def generate_launch_description():
    return LaunchDescription([
        # Include your simulation launch file
        Node(
            package='ur_simulation_gazebo',
            executable='ur_sim_control.launch.py',
            parameters=[
                {'ur_type': 'ur10'},
                {'launch_rviz': 'false'},
                {'use_fake_hardware': 'true'},
                {'initial_joint_controller': 'joint_trajectory_controller'}
            ]
        ),
        
        # Launch MoveIt
        Node(
            package='ur_moveit_config',
            executable='ur_moveit.launch.py',
            parameters=[
                {'ur_type': 'ur10'},
                {'launch_rviz': 'true'},
                {'use_fake_hardware': 'true'},
                {'use_sim_time': 'true'}
            ]
        ),
        
        # Your node with proper dependencies
        Node(
            package='weld_path_planner',
            executable='waypoint_executor',
            output='screen',
            parameters=[
                {'use_sim_time': True}
            ]
        )
    ])
