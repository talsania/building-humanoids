from setuptools import find_packages, setup

package_name = 'ik_pick_place'

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
            'ik_pick_place_node = ik_pick_place.ik_pick_place_node:main',
            'debug_ik_node = ik_pick_place.debug_ik_node:main',
            'simple_ik_test = ik_pick_place.simple_ik_test:main',
        ],
    },
)
