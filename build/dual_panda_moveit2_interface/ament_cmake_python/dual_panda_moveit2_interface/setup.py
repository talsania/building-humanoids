from setuptools import find_packages
from setuptools import setup

setup(
    name='dual_panda_moveit2_interface',
    version='0.0.0',
    packages=find_packages(
        include=('dual_panda_moveit2_interface', 'dual_panda_moveit2_interface.*')),
)
