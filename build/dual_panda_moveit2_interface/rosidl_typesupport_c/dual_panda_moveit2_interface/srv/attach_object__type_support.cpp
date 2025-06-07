// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from dual_panda_moveit2_interface:srv/AttachObject.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "dual_panda_moveit2_interface/srv/detail/attach_object__struct.h"
#include "dual_panda_moveit2_interface/srv/detail/attach_object__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _AttachObject_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _AttachObject_Request_type_support_ids_t;

static const _AttachObject_Request_type_support_ids_t _AttachObject_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _AttachObject_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _AttachObject_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _AttachObject_Request_type_support_symbol_names_t _AttachObject_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dual_panda_moveit2_interface, srv, AttachObject_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, AttachObject_Request)),
  }
};

typedef struct _AttachObject_Request_type_support_data_t
{
  void * data[2];
} _AttachObject_Request_type_support_data_t;

static _AttachObject_Request_type_support_data_t _AttachObject_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _AttachObject_Request_message_typesupport_map = {
  2,
  "dual_panda_moveit2_interface",
  &_AttachObject_Request_message_typesupport_ids.typesupport_identifier[0],
  &_AttachObject_Request_message_typesupport_symbol_names.symbol_name[0],
  &_AttachObject_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t AttachObject_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_AttachObject_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dual_panda_moveit2_interface, srv, AttachObject_Request)() {
  return &::dual_panda_moveit2_interface::srv::rosidl_typesupport_c::AttachObject_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/attach_object__struct.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/attach_object__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _AttachObject_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _AttachObject_Response_type_support_ids_t;

static const _AttachObject_Response_type_support_ids_t _AttachObject_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _AttachObject_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _AttachObject_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _AttachObject_Response_type_support_symbol_names_t _AttachObject_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dual_panda_moveit2_interface, srv, AttachObject_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, AttachObject_Response)),
  }
};

typedef struct _AttachObject_Response_type_support_data_t
{
  void * data[2];
} _AttachObject_Response_type_support_data_t;

static _AttachObject_Response_type_support_data_t _AttachObject_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _AttachObject_Response_message_typesupport_map = {
  2,
  "dual_panda_moveit2_interface",
  &_AttachObject_Response_message_typesupport_ids.typesupport_identifier[0],
  &_AttachObject_Response_message_typesupport_symbol_names.symbol_name[0],
  &_AttachObject_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t AttachObject_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_AttachObject_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, dual_panda_moveit2_interface, srv, AttachObject_Response)() {
  return &::dual_panda_moveit2_interface::srv::rosidl_typesupport_c::AttachObject_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/attach_object__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _AttachObject_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _AttachObject_type_support_ids_t;

static const _AttachObject_type_support_ids_t _AttachObject_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _AttachObject_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _AttachObject_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _AttachObject_type_support_symbol_names_t _AttachObject_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dual_panda_moveit2_interface, srv, AttachObject)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, AttachObject)),
  }
};

typedef struct _AttachObject_type_support_data_t
{
  void * data[2];
} _AttachObject_type_support_data_t;

static _AttachObject_type_support_data_t _AttachObject_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _AttachObject_service_typesupport_map = {
  2,
  "dual_panda_moveit2_interface",
  &_AttachObject_service_typesupport_ids.typesupport_identifier[0],
  &_AttachObject_service_typesupport_symbol_names.symbol_name[0],
  &_AttachObject_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t AttachObject_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_AttachObject_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, dual_panda_moveit2_interface, srv, AttachObject)() {
  return &::dual_panda_moveit2_interface::srv::rosidl_typesupport_c::AttachObject_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
