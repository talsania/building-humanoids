# generated from rosidl_generator_py/resource/_idl.py.em
# with input from dual_panda_moveit2_interface:msg/RobotPose.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RobotPose(type):
    """Metaclass of message 'RobotPose'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('dual_panda_moveit2_interface')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'dual_panda_moveit2_interface.msg.RobotPose')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__robot_pose
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__robot_pose
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__robot_pose
            cls._TYPE_SUPPORT = module.type_support_msg__msg__robot_pose
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__robot_pose

            from geometry_msgs.msg import PoseStamped
            if PoseStamped.__class__._TYPE_SUPPORT is None:
                PoseStamped.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RobotPose(metaclass=Metaclass_RobotPose):
    """Message class 'RobotPose'."""

    __slots__ = [
        '_head',
        '_left_pose',
        '_right_pose',
    ]

    _fields_and_field_types = {
        'head': 'geometry_msgs/PoseStamped',
        'left_pose': 'geometry_msgs/PoseStamped',
        'right_pose': 'geometry_msgs/PoseStamped',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseStamped'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseStamped'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseStamped'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from geometry_msgs.msg import PoseStamped
        self.head = kwargs.get('head', PoseStamped())
        from geometry_msgs.msg import PoseStamped
        self.left_pose = kwargs.get('left_pose', PoseStamped())
        from geometry_msgs.msg import PoseStamped
        self.right_pose = kwargs.get('right_pose', PoseStamped())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.head != other.head:
            return False
        if self.left_pose != other.left_pose:
            return False
        if self.right_pose != other.right_pose:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def head(self):
        """Message field 'head'."""
        return self._head

    @head.setter
    def head(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseStamped
            assert \
                isinstance(value, PoseStamped), \
                "The 'head' field must be a sub message of type 'PoseStamped'"
        self._head = value

    @builtins.property
    def left_pose(self):
        """Message field 'left_pose'."""
        return self._left_pose

    @left_pose.setter
    def left_pose(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseStamped
            assert \
                isinstance(value, PoseStamped), \
                "The 'left_pose' field must be a sub message of type 'PoseStamped'"
        self._left_pose = value

    @builtins.property
    def right_pose(self):
        """Message field 'right_pose'."""
        return self._right_pose

    @right_pose.setter
    def right_pose(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseStamped
            assert \
                isinstance(value, PoseStamped), \
                "The 'right_pose' field must be a sub message of type 'PoseStamped'"
        self._right_pose = value
