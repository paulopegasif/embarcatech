# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Board setup
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

project(metronome C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Diretórios de código-fonte e headers
add_subdirectory(src)
include_directories(include)

# ===========================
# Projeto Principal
# ===========================

add_executable(metronome
    src/main.c
    src/display.c
    src/buzzer.c
    src/buttons.c
    src/hardware_init.c
)

pico_set_program_name(metronome "metronome")
pico_set_program_version(metronome "0.1")

# UART e USB
pico_enable_stdio_uart(metronome 0)
pico_enable_stdio_usb(metronome 1)

# Bibliotecas padrão e hardware
target_link_libraries(metronome
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_dma
    hardware_pio
    hardware_interp
    hardware_timer
    hardware_watchdog
    hardware_clocks
)

# Diretórios de include
target_include_directories(metronome PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Outputs (arquivo .uf2)
pico_add_extra_outputs(metronome)

# ===========================
# Testes de Hardware
# ===========================

# Teste do Display OLED
add_executable(test_display
    tests/test_display.c
    src/display.c
)
target_link_libraries(test_display pico_stdlib hardware_i2c)
target_include_directories(test_display PRIVATE include)
pico_add_extra_outputs(test_display)

# Teste do Buzzer
add_executable(test_buzzer
    tests/test_buzzer.c
    src/buzzer.c
)
target_link_libraries(test_buzzer pico_stdlib hardware_pwm)
target_include_directories(test_buzzer PRIVATE include)
pico_add_extra_outputs(test_buzzer)

# Teste dos Botões
add_executable(test_buttons
    tests/test_buttons.c
    src/buttons.c
)
target_link_libraries(test_buttons pico_stdlib hardware_gpio)
target_include_directories(test_buttons PRIVATE include)
pico_add_extra_outputs(test_buttons)