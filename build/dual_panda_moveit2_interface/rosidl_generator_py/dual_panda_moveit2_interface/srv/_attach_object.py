# generated from rosidl_generator_py/resource/_idl.py.em
# with input from dual_panda_moveit2_interface:srv/AttachObject.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AttachObject_Request(type):
    """Metaclass of message 'AttachObject_Request'."""

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
                'dual_panda_moveit2_interface.srv.AttachObject_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__attach_object__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__attach_object__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__attach_object__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__attach_object__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__attach_object__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AttachObject_Request(metaclass=Metaclass_AttachObject_Request):
    """Message class 'AttachObject_Request'."""

    __slots__ = [
        '_id',
        '_link',
    ]

    _fields_and_field_types = {
        'id': 'string',
        'link': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.id = kwargs.get('id', str())
        self.link = kwargs.get('link', str())

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
        if self.id != other.id:
            return False
        if self.link != other.link:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'id' field must be of type 'str'"
        self._id = value

    @builtins.property
    def link(self):
        """Message field 'link'."""
        return self._link

    @link.setter
    def link(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'link' field must be of type 'str'"
        self._link = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_AttachObject_Response(type):
    """Metaclass of message 'AttachObject_Response'."""

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
                'dual_panda_moveit2_interface.srv.AttachObject_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__attach_object__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__attach_object__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__attach_object__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__attach_object__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__attach_object__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AttachObject_Response(metaclass=Metaclass_AttachObject_Response):
    """Message class 'AttachObject_Response'."""

    __slots__ = [
        '_success',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())

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


class Metaclass_AttachObject(type):
    """Metaclass of service 'AttachObject'."""

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
                'dual_panda_moveit2_interface.srv.AttachObject')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__attach_object

            from dual_panda_moveit2_interface.srv import _attach_object
            if _attach_object.Metaclass_AttachObject_Request._TYPE_SUPPORT is None:
                _attach_object.Metaclass_AttachObject_Request.__import_type_support__()
            if _attach_object.Metaclass_AttachObject_Response._TYPE_SUPPORT is None:
                _attach_object.Metaclass_AttachObject_Response.__import_type_support__()


class AttachObject(metaclass=Metaclass_AttachObject):
    from dual_panda_moveit2_interface.srv._attach_object import AttachObject_Request as Request
    from dual_panda_moveit2_interface.srv._attach_object import AttachObject_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
