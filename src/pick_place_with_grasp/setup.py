from setuptools import find_packages, setup

package_name = 'pick_place_with_grasp'

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
    maintainer='krishang',
    maintainer_email='talsania.k@outlook.com',
    description='pick and place with grippers',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'pick_place_node = pick_place_with_grasp.pick_place_node:main',
        ],
    },
)
