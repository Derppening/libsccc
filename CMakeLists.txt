cmake_minimum_required(VERSION 3.6)
project(libsccc)

include(CMakeForceCompiler)

# specify what we're currently working with
set(COMPILE_MACHINE Desktop)
set(SCCC_CONFIG VCAN_FX15DEV)

# specify the cross compiler
set(TOOLCHAIN_PREFIX arm-none-eabi-)
set(CC ${TOOLCHAIN_PREFIX}gcc)
set(CXX ${TOOLCHAIN_PREFIX}g++)
set(AR ${TOOLCHAIN_PREFIX}ar)
set(CMAKE_C_COMPILER ${CC})
SET(CMAKE_CXX_COMPILER ${CXX})
CMAKE_FORCE_C_COMPILER(${CC} GNU)
CMAKE_FORCE_CXX_COMPILER(${CXX} GNU)

# define the c++ standard and includes to resolve *.h
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
include_directories(
        inc
        inc/libbase
        inc/libbase/cmsis
        inc/libbase/k60
        inc/libbase/k60/cmsis
        inc/libbase/k60/pinout
        inc/libbase/kl26/
        inc/libbase/kl26/cmsis
        inc/libbase/kl26/pinout
        inc/libsc
        inc/libsc/device_h
        inc/libsc/k60
        inc/libsc/k60/config
        inc/libsc/kl26
        inc/libsc/kl26/config
        inc/libsc/next
        inc/libutil
        )

# define macros to enable "go to declaration" feature
if(${SCCC_CONFIG} STREQUAL VCAN_FX15DEV)
    add_definitions(
            # from MakeConfig.inc
            -DMK60F15
            # from inc/libsc/k60/config
            -DLIBSC_USE_BUTTON=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_MPU6050=1
            -DLIBSC_USE_OV7725=1
            -DLIBSC_USE_OV7725_FIFO=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPtb20
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPtb21
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPtb22
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPtb23
            -DLIBSC_MOTOR0_PWMA=libbase::k60::Pin::Name::kPtc1
            -DLIBSC_MOTOR0_PWMB=libbase::k60::Pin::Name::kPtc2
            -DLIBSC_MOTOR0_DEADTIME=1000
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_MPU6050_SCL=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MPU6050_SDA=libbase::k60::Pin::Name::kPtb1
            -DLIBSC_OV77250_SCL=libbase::k60::Pin::Name::kPtc16
            -DLIBSC_OV77250_SDA=libbase::k60::Pin::Name::kPtc17
            -DLIBSC_OV77250_DATA0=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_OV77250_PCLK=libbase::k60::Pin::Name::kPtb9
            -DLIBSC_OV77250_VSYNC=libbase::k60::Pin::Name::kPta29
            -DLIBSC_OV77250_DMA_CH=1
            -DLIBSC_OV7725_FIFO0_SCL=libbase::k60::Pin::Name::kPtc16
            -DLIBSC_OV7725_FIFO0_SDA=libbase::k60::Pin::Name::kPtc17
            -DLIBSC_OV7725_FIFO0_DATA0=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_OV7725_FIFO0_VSYNC=libbase::k60::Pin::Name::kPta29
            -DLIBSC_OV7725_FIFO0_WEN=libbase::k60::Pin::Name::kPtb5
            -DLIBSC_OV7725_FIFO0_WRST=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_OV7725_FIFO0_RCLK=libbase::k60::Pin::Name::kPtd5
            -DLIBSC_OV7725_FIFO0_RRST=libbase::k60::Pin::Name::kPtb2
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPtd0
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPta13
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPta17
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPta14
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPta16
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPta15
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtb17
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtb16
            )
elseif(${SCCC_CONFIG} STREQUAL 2016_INNO)
    add_definitions(
            # from MakeConfig.inc
            -DMK60F15
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_LINEAR_CCD=2
            -DLIBSC_USE_OV7725=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc3Ad6A
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPte7
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPtc12
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta8
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta11
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPta12
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPta13
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte12
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte11
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPte10
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPte9
            -DLIBSC_MOTOR0_PWMA=libbase::k60::Pin::Name::kPtd0
            -DLIBSC_MOTOR0_PWMB=libbase::k60::Pin::Name::kPtd1
            -DLIBSC_MOTOR0_DEADTIME=2500
            -DLIBSC_MOTOR1_PWMA=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_MOTOR1_PWMB=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_MOTOR1_DEADTIME=1000
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtb7
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtb10
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPtb4
            -DLIBSC_LINEAR_CCD1_SI=libbase::k60::Pin::Name::kPta28
            -DLIBSC_LINEAR_CCD1_CLK=libbase::k60::Pin::Name::kPtb2
            -DLIBSC_LINEAR_CCD1_AD=libbase::k60::Pin::Name::kPtb3
            -DLIBSC_OV77250_VSYNC=libbase::k60::Pin::Name::kPtc2
            -DLIBSC_OV77250_PCLK=libbase::k60::Pin::Name::kPtb6
            -DLIBSC_OV77250_DATA0=libbase::k60::Pin::Name::kPtb16
            -DLIBSC_OV77250_SDA=libbase::k60::Pin::Name::kPtc1
            -DLIBSC_OV77250_SCL=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_OV77250_DMA_CH=1
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtd6
            )
endif()

# set build type according to what we have in CLion
if(${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(MAKE_BUILD_TYPE RELEASE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(MAKE_BUILD_TYPE DEBUG)
else(${CMAKE_BUILD_TYPE} STREQUAL Release)
    message(WARNING "No build type configured. Defaulting to Debug")
    set(MAKE_BUILD_TYPE DEBUG)
endif(${CMAKE_BUILD_TYPE} STREQUAL Release)

# set make parameters
if(${COMPILE_MACHINE} STREQUAL Desktop)
    set(MAKE_PATH "D:\\Program Files (x86)\\GnuWin32\\bin\\make.exe")
else(${COMPILE_MACHINE} STREQUAL Desktop)
    set(MAKE_PATH "C:\\Program Files (x86)\\GnuWin32\\bin\\make.exe")
endif(${COMPILE_MACHINE} STREQUAL Desktop)
set(MAKE_ARGS -f ${libsccc_SOURCE_DIR}/Makefile -k -j4)
set(MAKE_VARS SCCC_BUILD=${MAKE_BUILD_TYPE} PWD=${libsccc_SOURCE_DIR} CWD=${PWD})

# buiders
add_custom_target(make_once
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=${SCCC_CONFIG} all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_INNO_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_INNO all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(VCAN_FX15DEV_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=VCAN_FX15DEV all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})

# cleane-then-builders
add_custom_target(clean_and_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=${SCCC_CONFIG} clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=${SCCC_CONFIG} all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_INNO_clean_and_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_INNO clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_INNO all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(VCAN_FX15DEV_clean_and_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=VCAN_FX15DEV clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=VCAN_FX15DEV all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})

# for generation of symbols and declarations
file(GLOB_RECURSE SOURCES src/libbase/*.cpp src/libsc/*.cpp src/libutil/*.cpp)
add_executable(DoNotBuild ${SOURCES})