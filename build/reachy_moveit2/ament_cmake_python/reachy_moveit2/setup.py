from setuptools import find_packages
from setuptools import setup

setup(
    name='reachy_moveit2',
    version='0.0.1',
    packages=find_packages(
        include=('reachy_moveit2', 'reachy_moveit2.*')),
)
