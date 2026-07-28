cmake_minimum_required(VERSION 3.5.0)

file(GLOB SSC_Sources
    ${PATH_WORKSPACE_ROOT}/app/BLDC/Src/*.c
) 
# message("ssc ---- ${SSC_Sources}")
set_property(GLOBAL PROPERTY App_Sources
    ${SSC_Sources}
    ${PATH_WORKSPACE_ROOT}/app/BLDC/main.c
)

set_property(GLOBAL PROPERTY App_Includes
    ${PATH_WORKSPACE_ROOT}/app/BLDC/Src
)
