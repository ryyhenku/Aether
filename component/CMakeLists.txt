cmake_minimum_required(VERSION 3.5.0)

set_property(GLOBAL PROPERTY Component_Sources
    ${PATH_WORKSPACE_ROOT}/component/debug/serial_debug.c
    ${PATH_WORKSPACE_ROOT}/component/ssc/ssc_adapter.c
)
set_property(GLOBAL PROPERTY Component_Includes
    ${PATH_WORKSPACE_ROOT}/component/debug/
    ${PATH_WORKSPACE_ROOT}/component/ssc/
)

