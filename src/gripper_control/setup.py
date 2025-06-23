from setuptools import setup

package_name = 'gripper_control'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),  # <- required for ROS 2 index
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='kptal',
    maintainer_email='kptal@todo.todo',
    description='Gripper control using Dynamixel SDK',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'gripper_control_node = gripper_control.gripper_control_node:main',
        ],
    },
)
