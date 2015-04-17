cmake_minimum_required(VERSION 2.8)

project(firmware)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_definitions(-DF_CPU=48000000 -DUSB_HID -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE -D__MKL26Z64__ -DARDUINO=10600 -DTEENSYDUINO=121 -mcpu=cortex-m0plus -mthumb -Os -nostdlib)

set(CMAKE_CXX_FLAGS "-std=gnu++11 -fno-rtti -fno-exceptions")
set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/mkl26z64.ld -Wl,--gc-sections -Os -mcpu=cortex-m0plus -mthumb")

include_directories(.)
file(GLOB c_srcs *.c)
file(GLOB cpp_srcs *.cpp)
add_executable(main.elf ${c_srcs} ${cpp_srcs})

# This makes 'gcc' the linker, rather than 'g++', so we don't link against the C++ standard library.
set_target_properties(main.elf PROPERTIES LINKER_LANGUAGE C)

function(add_objcopy target extension)
  if (${ARGC} GREATER 1)
    set(OUTPUT_TYPE ${ARGV1})
  else()
    set(OUTPUT_TYPE ${extension})
  endif()
  get_filename_component(BASENAME ${target} NAME_WE)
  add_custom_command(TARGET ${target} POST_BUILD COMMAND arm-none-eabi-objcopy -O ${OUTPUT_TYPE} -R .eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target} bin/${BASENAME}.${extension} COMMENT "Creating .${extension} file")
endfunction(add_objcopy)

add_objcopy(main.elf "srec")
