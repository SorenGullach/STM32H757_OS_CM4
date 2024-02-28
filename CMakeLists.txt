cmake_minimum_required(VERSION 3.15)

project(STM32H757_OS_CM4 LANGUAGES C CXX ASM)

find_bsp(
	ID com.sysprogs.arm.stm32
	VERSION 2024.01
	MCU STM32H757XI_M4
	CONFIGURATION com.sysprogs.toolchainoptions.arm.syscallspecs=--specs=rdimon.specs
	HWREGISTER_LIST_FILE STM32H7xxxx/DeviceDefinitions/stm32h757xx_m4.xml
	CXX_STANDARD 17
	DISABLE_GNU_EXTENSIONS)

add_bsp_based_executable(
	NAME STM32H757_OS_CM4
	GENERATE_BIN
	GENERATE_MAP
	LINKER_SCRIPT STM32H757XI_M4_flash.lds
	SOURCES
		../../osSTM32H7xx/SystemInitCM4.cpp
		Main.cpp
		../../osSTM32H7xx/HSEM.h
		../../osSTM32H7xx/MemoryDefs.h
		../../osSTM32H7xx/PWR.h
		../../osSTM32H7xx/SystemInit.h
		../../osSTM32H7xx/HSEM.cpp
		../SharedData/SharedData.cpp
		../SharedData/SharedData.h
		../../osSTM32H7xx/StartupSemafor.cpp
		../../osSTM32H7xx/StartupSemafor.h
		../../osSTM32H7xx/MPU.h)
target_include_directories(STM32H757_OS_CM4 PRIVATE ../../CCR/Test2/BSP/CMSIS/Core/Include ../../HeatCentral/HeatPump/riverdi-70-stm32h7-lvgl-main/Drivers/CMSIS/Device/ST/STM32H7xx/Include ../../osSTM32H7xx)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
target_compile_definitions(STM32H757_OS_CM4 PRIVATE STM32H757xx DEBUG DEBUG_DEFAULT_INTERRUPT_HANDLERS)
    message(STATUS "Setting debug flags...")
	target_compile_options(STM32H757_OS_CM4 PRIVATE -O0 -Wall -Wextra)
	message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS_DEBUG})
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
target_compile_definitions(STM32H757_OS_CM4 PRIVATE STM32H757xx RELEASE)
    message(STATUS "Setting release flags...")
	target_compile_options(STM32H757_OS_CM4 PRIVATE -O3)
	message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS_RELEASE})
endif()
