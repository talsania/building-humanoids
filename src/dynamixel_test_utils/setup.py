from setuptools import setup, find_packages

package_name = 'dynamixel_test_utils'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools', 'dynamixel_sdk'],
    zip_safe=True,
    maintainer='krishang',
    maintainer_email='talsania.k@outlook.com',
    description='Utilities for testing Dynamixel motors',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'dynamixel_cli=dynamixel_test_utils.dynamixel_cli:main',
            'dynamixel_scan=dynamixel_test_utils.dynamixel_scan:main',
            'dynamixel_move=dynamixel_test_utils.dynamixel_move:main',
        ],
    },
)