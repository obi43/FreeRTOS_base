# Raspberry Pico FreeRTOS Start code 

This is a starting point for a Raspberry Pico project using FreeRTOS. 

Either use this repositorry, and add FreeRTOS to the projects root directory by:

```bash
git clone https://github.com/raspberrypi/FreeRTOS-Kernel/
```

Or alternatively do it manually like this:

- Use the VScode Raspberry Pi Pico extension to create a "New C/C++ Project"
- Copy FreeRTOS-Kernel folder into the new project's root directory. Use the "git clone" command above to clone the FreeRTOS repossitory.
- Copy \FreeRTOS-Kernel\portable\ThirdParty\GCC\RP2350_ARM_NTZ\FreeRTOS_Kernel_import.cmake into project root
- Copy the [FreeRTOSConfig.h](https://github.com/raspberrypi/pico-examples/tree/master/freertos) file from SDK example into project root. 
- Do the following modifications to your CMakeLists.txt, below pico_sdk_init():
    ```CMake
    set(FREERTOS_KERNEL_PATH  ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel CACHE STRING "" FORCE )
    include(FreeRTOS_Kernel_import.cmake)
    ```

## FreeRTOS API reference

[FreeRTOS API](https://www.freertos.org/Documentation/02-Kernel/04-API-references/01-Task-creation/00-TaskHandle)