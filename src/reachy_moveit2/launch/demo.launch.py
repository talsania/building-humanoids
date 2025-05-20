#!/usr/bin/env python3
import os
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='reachy_moveit2',
            executable='reachy_sdk',
            name='reachy_sdk',
            output='screen'
        )
    ])
