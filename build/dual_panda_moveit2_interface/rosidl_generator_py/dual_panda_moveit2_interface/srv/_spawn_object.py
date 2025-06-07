# generated from rosidl_generator_py/resource/_idl.py.em
# with input from dual_panda_moveit2_interface:srv/SpawnObject.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SpawnObject_Request(type):
    """Metaclass of message 'SpawnObject_Request'."""

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
                'dual_panda_moveit2_interface.srv.SpawnObject_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__spawn_object__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__spawn_object__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__spawn_object__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__spawn_object__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__spawn_object__request

            from dual_panda_moveit2_interface.msg import ObjectSpec
            if ObjectSpec.__class__._TYPE_SUPPORT is None:
                ObjectSpec.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SpawnObject_Request(metaclass=Metaclass_SpawnObject_Request):
    """Message class 'SpawnObject_Request'."""

    __slots__ = [
        '_objects',
    ]

    _fields_and_field_types = {
        'objects': 'sequence<dual_panda_moveit2_interface/ObjectSpec>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['dual_panda_moveit2_interface', 'msg'], 'ObjectSpec')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.objects = kwargs.get('objects', [])

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
        if self.objects != other.objects:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def objects(self):
        """Message field 'objects'."""
        return self._objects

    @objects.setter
    def objects(self, value):
        if __debug__:
            from dual_panda_moveit2_interface.msg import ObjectSpec
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, ObjectSpec) for v in value) and
                 True), \
                "The 'objects' field must be a set or sequence and each value of type 'ObjectSpec'"
        self._objects = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SpawnObject_Response(type):
    """Metaclass of message 'SpawnObject_Response'."""

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
                'dual_panda_moveit2_interface.srv.SpawnObject_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__spawn_object__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__spawn_object__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__spawn_object__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__spawn_object__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__spawn_object__response

            from dual_panda_moveit2_interface.msg import ObjectSpec
            if ObjectSpec.__class__._TYPE_SUPPORT is None:
                ObjectSpec.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SpawnObject_Response(metaclass=Metaclass_SpawnObject_Response):
    """Message class 'SpawnObject_Response'."""

    __slots__ = [
        '_success',
        '_current_objects',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'current_objects': 'sequence<dual_panda_moveit2_interface/ObjectSpec>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['dual_panda_moveit2_interface', 'msg'], 'ObjectSpec')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.current_objects = kwargs.get('current_objects', [])

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
        if self.success != other.success:
            return False
        if self.current_objects != other.current_objects:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def current_objects(self):
        """Message field 'current_objects'."""
        return self._current_objects

    @current_objects.setter
    def current_objects(self, value):
        if __debug__:
            from dual_panda_moveit2_interface.msg import ObjectSpec
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, ObjectSpec) for v in value) and
                 True), \
                "The 'current_objects' field must be a set or sequence and each value of type 'ObjectSpec'"
        self._current_objects = value


class Metaclass_SpawnObject(type):
    """Metaclass of service 'SpawnObject'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('dual_panda_moveit2_interface')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'dual_panda_moveit2_interface.srv.SpawnObject')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__spawn_object

            from dual_panda_moveit2_interface.srv import _spawn_object
            if _spawn_object.Metaclass_SpawnObject_Request._TYPE_SUPPORT is None:
                _spawn_object.Metaclass_SpawnObject_Request.__import_type_support__()
            if _spawn_object.Metaclass_SpawnObject_Response._TYPE_SUPPORT is None:
                _spawn_object.Metaclass_SpawnObject_Response.__import_type_support__()


class SpawnObject(metaclass=Metaclass_SpawnObject):
    from dual_panda_moveit2_interface.srv._spawn_object import SpawnObject_Request as Request
    from dual_panda_moveit2_interface.srv._spawn_object import SpawnObject_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
