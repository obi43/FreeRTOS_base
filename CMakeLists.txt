# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)


project(FreeRTOS_base C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()



### Add FreeRTOS
set(FREERTOS_KERNEL_PATH  ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel CACHE STRING "" FORCE )
include(FreeRTOS_Kernel_import.cmake)
set(LINK_LIBRARIES 
    FreeRTOS-Kernel-Heap4
)
###

# Set PICO_W define if this is a board with a Wifi module
if( "${PICO_BOARD}" STREQUAL "pico2_w" OR "${PICO_BOARD}" STREQUAL "pico_w" )
    add_compile_definitions(PICO_W)
    list(APPEND LINK_LIBRARIES pico_cyw43_arch_none)
endif()



# Add executable. Default name is the project name, version 0.1
FILE(GLOB app_sources src/*)
add_executable(${PROJECT_NAME} ${app_sources} )

pico_set_program_name(${PROJECT_NAME} "FreeRTOS_base")
pico_set_program_version(${PROJECT_NAME} "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME}
    "${LINK_LIBRARIES}"
    pico_stdlib
)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(${PROJECT_NAME})

