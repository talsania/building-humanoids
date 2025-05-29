from setuptools import find_packages, setup

package_name = 'half_humanoid_control_actions'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ishaan',
    maintainer_email='ishaankathiriya2005@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'humanoid_action_client = half_humanoid_control_actions.humanoid_action_client:main',
            'humanoid_command_listener = half_humanoid_control_actions.humanoid_command_listener:main',
            'humanoid_command_publisher = half_humanoid_control_actions.humanoid_command_publisher:main',
            'obstacle_publisher = half_humanoid_control_actions.obstacle_publisher:main',
        ],
    },
)