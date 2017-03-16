cmake_minimum_required(VERSION 3.6)
project(libsccc)

include(CMakeForceCompiler)

# specify what we're currently working with
# valid options: david_desktop, david_laptop
set(COMPILE_ENV david_laptop)
set(SCCC_CONFIG 2017_INNO)

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
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

# define macros to enable "go to declaration" feature
if (${SCCC_CONFIG} STREQUAL INNO)
    add_definitions(
            # from MakeConfig.inc
            -DK60_INNO=1
            -DMK60DZ10=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_OV7725=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_AMBIENT_LIGHT0=libbase::k60::Pin::Name::kPta8
            -DLIBSC_OV77250_SCL=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_OV77250_SDA=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_OV77250_PCLK=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_OV77250_VSYNC=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_OV77250_DATA0=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_OV77250_DMA_CH=1
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta6
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_INFRA_RED0=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_LCD_RST=libbase::k60::Pin::Name::kPta6
            -DLIBSC_LCD_DC=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_LCD_CS=libbase::k60::Pin::Name::kPta8
            -DLIBSC_LCD_SDAT=libbase::k60::Pin::Name::kPte5
            -DLIBSC_LCD_SCLK=libbase::k60::Pin::Name::kPte4
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte24
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte25
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPte26
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPte27
            -DLIBSC_LIGHT_SENSOR0=libbase::k60::Pin::Name::kPta10
            -DLIBSC_LINEAR_CCD0_AO=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPta8
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta10
            -DLIBSC_SYSTEM_TIMER_PIT_CHANNEL=0
            -DLIBSC_TEMPERATURE0=libbase::k60::Pin::Name::kPta10
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPte4
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPte5
    )
elseif (${SCCC_CONFIG} STREQUAL 2014_CAMERA)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2014_CAMERA=1
            -DMK60DZ10=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BUTTON=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_MPU6050=1
            -DLIBSC_USE_MMA8451Q=1
            -DLIBSC_USE_SOFT_MMA8451Q=0
            -DLIBSC_USE_UART=1
            -DLIBSC_USE_LINEAR_CCD=1
            -DLIBSC_ACCELEROMETER_RX=libbase::k60::Adc::Name::kAdc0Ad17
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc1Ad4B
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPtc10
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta8
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta9
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPtb18
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPtb19
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPta13
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPta17
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPta14
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPta16
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPta15
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPtd0
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPtd1
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPte7
            -DLIBSC_MOTOR1_PWM=libbase::k60::Pin::Name::kPtd6
            -DLIBSC_MOTOR1_DIR=libbase::k60::Pin::Name::kPte6
            -DLIBSC_DIR_MOTOR_CW_LEVEL=0
            -DLIBSC_TEMPERATURE0=libbase::k60::Pin::Name::kPtc2
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtc17
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtc16
            -DLIBSC_MPU6050_SCL=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MPU6050_SDA=libbase::k60::Pin::Name::kPtb1
            -DLIBSC_MMA8451Q0_SCL=libbase::k60::Pin::Name::kPtb2
            -DLIBSC_MMA8451Q0_SDA=libbase::k60::Pin::Name::kPtb3
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPta7
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPte0
    )
elseif (${SCCC_CONFIG} STREQUAL 2014_CCD)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2014_CCD=1
            -DMK60DZ10=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_ENCODER=1
            -DLIBSC_USE_GYROSCOPE=1
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_LIGHT_SENSOR=2
            -DLIBSC_USE_LINEAR_CCD=2
            -DLIBSC_NEGATE_LINEAR_CCD
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_SWITCH=5
            -DLIBSC_USE_UART=1
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPtc11
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPtc10
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPtd5
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta8
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta9
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPtb18
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPtb19
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_LCD_RST=libbase::k60::Pin::Name::kPta13
            -DLIBSC_LCD_DC=libbase::k60::Pin::Name::kPta17
            -DLIBSC_LCD_CS=libbase::k60::Pin::Name::kPta14
            -DLIBSC_LCD_SDAT=libbase::k60::Pin::Name::kPta16
            -DLIBSC_LCD_SCLK=libbase::k60::Pin::Name::kPta15
            -DLIBSC_ST7735R_BGR_PANEL=1
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPtd0
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPtd1
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtc1
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtc2
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPtb20
            -DLIBSC_LINEAR_CCD1_SI=libbase::k60::Pin::Name::kPtc3
            -DLIBSC_LINEAR_CCD1_CLK=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_LINEAR_CCD1_AD=libbase::k60::Pin::Name::kPtb21
            -DLIBSC_LIGHT_SENSOR0=libbase::k60::Pin::Name::kPte25
            -DLIBSC_LIGHT_SENSOR1=libbase::k60::Pin::Name::kPtb22
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPtd6
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPte6
            -DLIBSC_MOTOR1_PWM=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_MOTOR1_DIR=libbase::k60::Pin::Name::kPte7
            -DLIBSC_DIR_MOTOR_CW_LEVEL=0
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta10
            -DLIBSC_SERVO0_SOFT_PWM_PIT_CHANNEL=1
            -DLIBSC_SYSTEM_TIMER_PIT_CHANNEL=0
            -DLIBSC_SWITCH0=libbase::k60::Pin::Name::kPte8
            -DLIBSC_SWITCH1=libbase::k60::Pin::Name::kPte9
            -DLIBSC_SWITCH2=libbase::k60::Pin::Name::kPte10
            -DLIBSC_SWITCH3=libbase::k60::Pin::Name::kPte11
            -DLIBSC_SWITCH4=libbase::k60::Pin::Name::kPte12
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtc17
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtc16
    )
elseif (${SCCC_CONFIG} STREQUAL 2014_INNO)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2014_INNO=1
            -DMK60DZ10=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_LINEAR_CCD=1
            -DLIBSC_USE_MMA8451Q=1
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc1Ad17
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPtb23
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_BUZZER_ACIVE_LEVEL=0
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc12
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte12
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte11
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPte10
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPte9
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtb1
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_MMA8451Q0_SCL=libbase::k60::Pin::Name::kPta4
            -DLIBSC_MMA8451Q0_SDA=libbase::k60::Pin::Name::kPta6
            -DLIBSC_MOTOR0_PWMA=libbase::k60::Pin::Name::kPtc3
            -DLIBSC_MOTOR0_PWMB=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_MOTOR0_DEADTIME=1000
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtd6
            -DLIBSC_MPU6050_SCL=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MPU6050_SDA=libbase::k60::Pin::Name::kPtb1
    )
elseif (${SCCC_CONFIG} STREQUAL 2014_INNO_FX)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2014_INNO=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_LINEAR_CCD=1
            -DLIBSC_USE_MMA8451Q=1
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc1Ad17
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPtb23
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_BUZZER_ACIVE_LEVEL=0
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc12
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte12
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte11
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPte10
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPte9
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtb1
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_MMA8451Q0_SCL=libbase::k60::Pin::Name::kPta4
            -DLIBSC_MMA8451Q0_SDA=libbase::k60::Pin::Name::kPta6
            -DLIBSC_MOTOR0_PWMA=libbase::k60::Pin::Name::kPtc3
            -DLIBSC_MOTOR0_PWMB=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_MOTOR0_DEADTIME=1000
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtd6
            -DLIBSC_MPU6050_SCL=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MPU6050_SDA=libbase::k60::Pin::Name::kPtb1
    )
elseif (${SCCC_CONFIG} STREQUAL 2014_MAGNETIC)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2014_MAGNETIC=1
            -DMK60DZ10=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LCD_HW_SPI
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_SWITCH=4
            -DLIBSC_USE_UART=1
            -DLIBSC_BUTTON0=PTC11
            -DLIBSC_BUTTON1=PTC10
            -DLIBSC_ENCODER0_QDA=PTA8
            -DLIBSC_ENCODER0_QDB=PTA9
            -DLIBSC_ENCODER1_QDA=PTB18
            -DLIBSC_ENCODER1_QDB=PTB19
            -DLIBSC_JOYSTICK0_UP=PTC6
            -DLIBSC_JOYSTICK0_DOWN=PTC5
            -DLIBSC_JOYSTICK0_LEFT=PTC8
            -DLIBSC_JOYSTICK0_RIGHT=PTC7
            -DLIBSC_JOYSTICK0_SELECT=PTC9
            -DLIBSC_LED0=PTD0
            -DLIBSC_LED1=PTD1
            -DLIBSC_LED2=PTD2
            -DLIBSC_LED3=PTD3
            -DLIBSC_MOTOR0_PWM=PTD6
            -DLIBSC_MOTOR0_DIR=PTE6
            -DLIBSC_MOTOR1_PWM=PTD7
            -DLIBSC_MOTOR1_DIR=PTE7
            -DLIBSC_SERVO0=PTA10
            -DLIBSC_SWITCH0=PTE8
            -DLIBSC_SWITCH1=PTE9
            -DLIBSC_SWITCH2=PTE10
            -DLIBSC_SWITCH3=PTE11
            -DLIBSC_SWITCH4=PTE12
    )
    if (DEFINED LIBSC_USE_LCD_HW_SPI)
        add_definitions(
                -DLIBSC_LCD_RST=PTA13
                -DLIBSC_LCD_DC=PTA17
                -DLIBSC_LCD_CS=PTA14
                -DLIBSC_LCD_MOSI=PTA16
                -DLIBSC_LCD_MISO=PTA17
                -DLIBSC_LCD_SCLK=PTA15
        )
    else ()
        add_definitions(
                -DLIBSC_LCD_RST=PTA13
                -DLIBSC_LCD_DC=PTA17
                -DLIBSC_LCD_CS=PTA14
                -DLIBSC_LCD_SDAT=PTA16
                -DLIBSC_LCD_SCLK=PTA15
        )
    endif ()
elseif (${SCCC_CONFIG} STREQUAL VCAN_FX15DEV)
    add_definitions(
            # from MakeConfig.inc
            -DK60_VCAN_FX15DEV=1
            -DMK60F15=1
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
elseif (${SCCC_CONFIG} STREQUAL 2015_CAMERA)
    add_definitions(
            # from MakeConfig.inc
            -DK60_VCAN_FX15DEV=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_OV7725=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc0Ad11
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPta4
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPte7
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_BUZZER_ACIVE_LEVEL=0
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta11
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPta12
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPta13
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc4
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
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_MOTOR1_PWM=libbase::k60::Pin::Name::kPtd0
            -DLIBSC_MOTOR1_DIR=libbase::k60::Pin::Name::kPtd1
            -DLIBSC_OV77250_VSYNC=libbase::k60::Pin::Name::kPte24
            -DLIBSC_OV77250_PCLK=libbase::k60::Pin::Name::kPtb3
            -DLIBSC_OV77250_DATA0=libbase::k60::Pin::Name::kPtb16
            -DLIBSC_OV77250_SDA=libbase::k60::Pin::Name::kPtc1
            -DLIBSC_OV77250_SCL=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_OV77250_DMA_CH=1
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta6
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtd6
    )
elseif (${SCCC_CONFIG} STREQUAL 2015_MAGNETIC)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2015_MAGNETIC=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_SWITCH=8
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_LINEAR_CCD=1
            -DLIBSC_USE_US100=1
            -DLIBSC_USE_I2C=1
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_MAGSEN=6
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_USE_ENCODER=1
            -DLIBSC_USE_SPI=1
            -DLIBSC_USE_YUANYANG=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc0Ad5B
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPte26
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPte27
            -DLIBSC_SWITCH0=libbase::k60::Pin::Name::kPte28
            -DLIBSC_SWITCH1=libbase::k60::Pin::Name::kPta5
            -DLIBSC_SWITCH2=libbase::k60::Pin::Name::kPta6
            -DLIBSC_SWITCH3=libbase::k60::Pin::Name::kPta7
            -DLIBSC_SWITCH4=libbase::k60::Pin::Name::kPta8
            -DLIBSC_SWITCH5=libbase::k60::Pin::Name::kPta9
            -DLIBSC_SWITCH6=libbase::k60::Pin::Name::kPta10
            -DLIBSC_SWITCH7=libbase::k60::Pin::Name::kPta11
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPtd4
            -DLIBSC_BUZZER_ACIVE_LEVEL=0
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPte8
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPte7
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPte6
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPte10
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPte9
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_US1000_TX=libbase::k60::Pin::Name::kPtd9
            -DLIBSC_US1000_RX=libbase::k60::Pin::Name::kPtd8
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtd6
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPtd5
            -DLIBSC_I2C0_SCL=libbase::k60::Pin::Name::kPtd8
            -DLIBSC_I2C0_SDA=libbase::k60::Pin::Name::kPtd9
            -DLIBSC_MOTOR0_DIRMOTOR=1
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_MAGSEN0=libbase::k60::Pin::Name::kPta26
            -DLIBSC_MAGSEN1=libbase::k60::Pin::Name::kPta27
            -DLIBSC_MAGSEN2=libbase::k60::Pin::Name::kPta28
            -DLIBSC_MAGSEN3=libbase::k60::Pin::Name::kPta29
            -DLIBSC_MAGSEN4=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MAGSEN5=libbase::k60::Pin::Name::kPtb1
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta12
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta13
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPtb18
            -DLIBSC_SPI0_PCS0=libbase::k60::Pin::Name::kPtd11
            -DLIBSC_SPI0_PCS1=libbase::k60::Pin::Name::kPtd15
            -DLIBSC_SPI0_SCK=libbase::k60::Pin::Name::kPtd12
            -DLIBSC_SPI0_SOUT=libbase::k60::Pin::Name::kPtd13
            -DLIBSC_SPI0_SIN=libbase::k60::Pin::Name::kPtd14
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPta14
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPta15
            -DLIBSC_YUANYANG_DO=libbase::k60::Pin::Name::kPtc13
            -DLIBSC_YUANYANG_STATE=libbase::k60::Pin::Name::kPtc12
    )
elseif (${SCCC_CONFIG} STREQUAL 2015_CCD)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2015_CCD=1
            -DMK60DZ10=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LED=3
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_UART=1
            -DLIBSC_USE_LINEAR_CCD=2
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_MPU6050=1
            -DLIBSC_USE_MMA8451Q=1
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta8
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta9
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPta11
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_ST7735R_BGR_PANEL=1
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtb2
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtb4
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPtb7
            -DLIBSC_LINEAR_CCD1_SI=libbase::k60::Pin::Name::kPta28
            -DLIBSC_LINEAR_CCD1_CLK=libbase::k60::Pin::Name::kPtb3
            -DLIBSC_LINEAR_CCD1_AD=libbase::k60::Pin::Name::kPtb6
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc1Ad17
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPta27
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPta26
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta5
            -DLIBSC_BUZZER_ACIVE_LEVEL=0
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc5=//=LEFT
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc6=//DOWN
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc3=//SELECT
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc7=//RIGHT
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPtd15
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPtd11
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPtd4
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPtc16
            -DLIBSC_MOTOR1_PWM=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_MOTOR1_DIR=libbase::k60::Pin::Name::kPtc15
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtb17
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtb16
            -DLIBSC_MPU6050_SCL=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MPU6050_SDA=libbase::k60::Pin::Name::kPtb1
            -DLIBSC_MMA8451Q0_SCL=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MMA8451Q0_SDA=libbase::k60::Pin::Name::kPtb1
    )
elseif (${SCCC_CONFIG} STREQUAL VCAN_Z4DEV)
    add_definitions(
            # from MakeConfig.inc
            -DKL26_VCAN_Z4DEV=1
            -DMKL26Z4=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BUTTON=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_LINEAR_CCD=1
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_MPU6050=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_USE_US100=1
            -DLIBSC_BUTTON0=libbase::kl26::Pin::Name::kPta20
            -DLIBSC_ENCODER0_QDA=libbase::kl26::Pin::Name::kPtc12
            -DLIBSC_ENCODER0_QDB=libbase::kl26::Pin::Name::kPtc18
            -DLIBSC_ENCODER0_TPM_MODULE=1
            -DLIBSC_ENCODER1_QDA=libbase::kl26::Pin::Name::kPta12
            -DLIBSC_ENCODER1_QDB=libbase::kl26::Pin::Name::kPta13
            -DLIBSC_ENCODER1_TPM_MODULE=2
            -DLIBSC_LED0=libbase::kl26::Pin::Name::kPtd4
            -DLIBSC_LED1=libbase::kl26::Pin::Name::kPtd5
            -DLIBSC_LED2=libbase::kl26::Pin::Name::kPtd6
            -DLIBSC_LED3=libbase::kl26::Pin::Name::kPtd7
            -DLIBSC_LINEAR_CCD0_CLK=libbase::kl26::Pin::Name::kPte18
            -DLIBSC_LINEAR_CCD0_SI=libbase::kl26::Pin::Name::kPte17
            -DLIBSC_LINEAR_CCD0_AD=libbase::kl26::Pin::Name::kPte16
            -DLIBSC_MOTOR0_PWMA=libbase::kl26::Pin::Name::kPte20
            -DLIBSC_MOTOR0_PWMB=libbase::kl26::Pin::Name::kPte21
            -DLIBSC_MPU6050_SCL=libbase::kl26::Pin::Name::kPtb0
            -DLIBSC_MPU6050_SDA=libbase::kl26::Pin::Name::kPtb1
            -DLIBSC_SERVO0=libbase::kl26::Pin::Name::kPte20
            -DLIBSC_ST7735R_RST==libbase::kl26::Pin::Name::kPtc8
            -DLIBSC_ST7735R_DC==libbase::kl26::Pin::Name::kPtc7
            -DLIBSC_ST7735R_CS=libbase::kl26::Pin::Name::kPtc4
            -DLIBSC_ST7735R_SDAT==libbase::kl26::Pin::Name::kPtc6
            -DLIBSC_ST7735R_SCLK==libbase::kl26::Pin::Name::kPtc5
            -DLIBSC_UART0_TX=libbase::kl26::Pin::Name::kPte0
            -DLIBSC_UART0_RX=libbase::kl26::Pin::Name::kPte1
            -DLIBSC_US1000_TX=libbase::kl26::Pin::Name::kPte0
            -DLIBSC_US1000_RX=libbase::kl26::Pin::Name::kPte1
    )
elseif (${SCCC_CONFIG} STREQUAL 2015_CCD2)
    add_definitions(
            # from MakeConfig.inc
            -DKL26_2015_CCD2=1
            -DMKL26Z4=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_UART=1
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_BUTTON=3
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_MPU6050=1
            -DLIBSC_USE_MMA8451Q=1
            -DLIBSC_USE_LINEAR_CCD=2
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_MOTOR0_PWM=libbase::kl26::Pin::Name::kPta5
            -DLIBSC_MOTOR0_DIR=libbase::kl26::Pin::Name::kPta6
            -DLIBSC_MOTOR1_PWM=libbase::kl26::Pin::Name::kPta7
            -DLIBSC_MOTOR1_DIR=libbase::kl26::Pin::Name::kPta12
            -DLIBSC_ENCODER0_QDA=libbase::kl26::Pin::Name::kPtc12
            -DLIBSC_ENCODER0_QDB=libbase::kl26::Pin::Name::kPtc16
            -DLIBSC_ENCODER0_TPM_MODULE=1
            -DLIBSC_ENCODER1_QDA=libbase::kl26::Pin::Name::kPtc13
            -DLIBSC_ENCODER1_QDB=libbase::kl26::Pin::Name::kPtc17
            -DLIBSC_ENCODER1_TPM_MODULE=2
            -DLIBSC_JOYSTICK0_UP=libbase::kl26::Pin::Name::kPtd0
            -DLIBSC_JOYSTICK0_LEFT=libbase::kl26::Pin::Name::kPtd1
            -DLIBSC_JOYSTICK0_DOWN=libbase::kl26::Pin::Name::kPtd2
            -DLIBSC_JOYSTICK0_SELECT=libbase::kl26::Pin::Name::kPtd3
            -DLIBSC_JOYSTICK0_RIGHT=libbase::kl26::Pin::Name::kPtd4
            -DLIBSC_BUTTON0=libbase::kl26::Pin::Name::kPtc9
            -DLIBSC_BUTTON1=libbase::kl26::Pin::Name::kPtc10
            -DLIBSC_BUTTON2=libbase::kl26::Pin::Name::kPtc11
            -DLIBSC_ST7735R_RST==libbase::kl26::Pin::Name::kPtc8
            -DLIBSC_ST7735R_DC==libbase::kl26::Pin::Name::kPtc7
            -DLIBSC_ST7735R_CS=libbase::kl26::Pin::Name::kPtc4
            -DLIBSC_ST7735R_SDAT==libbase::kl26::Pin::Name::kPtc6
            -DLIBSC_ST7735R_SCLK==libbase::kl26::Pin::Name::kPtc5
            -DLIBSC_LED0=libbase::kl26::Pin::Name::kPtb20
            -DLIBSC_LED1=libbase::kl26::Pin::Name::kPtb21
            -DLIBSC_LED2=libbase::kl26::Pin::Name::kPtb22
            -DLIBSC_LED3=libbase::kl26::Pin::Name::kPtb23
            -DLIBSC_UART0_TX=libbase::kl26::Pin::Name::kPta14
            -DLIBSC_UART0_RX=libbase::kl26::Pin::Name::kPta15
            -DLIBSC_MPU6050_SCL=libbase::kl26::Pin::Name::kPte24
            -DLIBSC_MPU6050_SDA=libbase::kl26::Pin::Name::kPte25
            -DLIBSC_MMA8451Q0_SCL=libbase::kl26::Pin::Name::kPte1
            -DLIBSC_MMA8451Q0_SDA=libbase::kl26::Pin::Name::kPte0
            -DLIBSC_LINEAR_CCD0_CLK=libbase::kl26::Pin::Name::kPte18
            -DLIBSC_LINEAR_CCD0_SI=libbase::kl26::Pin::Name::kPte17
            -DLIBSC_LINEAR_CCD0_AD=libbase::kl26::Pin::Name::kPte16
            -DLIBSC_LINEAR_CCD1_CLK=libbase::kl26::Pin::Name::kPte21
            -DLIBSC_LINEAR_CCD1_SI=libbase::kl26::Pin::Name::kPte20
            -DLIBSC_LINEAR_CCD1_AD=libbase::kl26::Pin::Name::kPte19
            -DLIBSC_BATTERY_METER=libbase::kl26::Adc::Name::kAdc0DAd3
            -DLIBSC_BUZZER0=libbase::kl26::Pin::Name::kPta13;
    )
elseif (${SCCC_CONFIG} STREQUAL 2015_M2)
    add_definitions(
            # from MakeConfig.inc
            -DKL26_2015_M2=1
            -MKL26Z4=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_ENCODER=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=2
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_JOYSTICK0_UP=libbase::kl26::Pin::Name::kPta5
            -DLIBSC_JOYSTICK0_DOWN=libbase::kl26::Pin::Name::kPta6
            -DLIBSC_JOYSTICK0_LEFT=libbase::kl26::Pin::Name::kPta7
            -DLIBSC_JOYSTICK0_RIGHT=libbase::kl26::Pin::Name::kPta12
            -DLIBSC_JOYSTICK0_SELECT=libbase::kl26::Pin::Name::kPta13
            -DLIBSC_ENCODER0_QDA=libbase::kl26::Pin::Name::kPte30
            -DLIBSC_ENCODER0_QDB=libbase::kl26::Pin::Name::kPtc18
            -DLIBSC_ENCODER0_TPM_MODULE=0
            -DLIBSC_UART0_TX=libbase::kl26::Pin::Name::kPta14
            -DLIBSC_UART0_RX=libbase::kl26::Pin::Name::kPta15
            -DLIBSC_UART1_TX=libbase::kl26::Pin::Name::kPte0
            -DLIBSC_UART1_RX=libbase::kl26::Pin::Name::kPte1
            -DLIBSC_ST7735R_RST=libbase::kl26::Pin::Name::kPtd3
            -DLIBSC_ST7735R_DC=libbase::kl26::Pin::Name::kPtc18
            -DLIBSC_ST7735R_CS=liwbbase::kl26::Pin::Name::kPtd0
            -DLIBSC_ST7735R_SDAT=libbase::kl26::Pin::Name::kPtd2
            -DLIBSC_ST7735R_SCLK=libbase::kl26::Pin::Name::kPtd1
            -DLIBSC_LED0=libbase::kl26::Pin::Name::kPtc10
            -DLIBSC_LED1=libbase::kl26::Pin::Name::kPtc11
            -DLIBSC_LED2=libbase::kl26::Pin::Name::kPtc12
            -DLIBSC_LED3=libbase::kl26::Pin::Name::kPtc13
            -DLIBSC_MOTOR0_PWM=libbase::kl26::Pin::Name::kPtb1
            -DLIBSC_MOTOR0_DIR=libbase::kl26::Pin::Name::kPtb0
            -DLIBSC_SERVO0=libbase::kl26::Pin::Name::kPtb2
            -DLIBSC_BATTERY_METER=libbase::kl26::Adc::Name::kAdc0DAd3
    )
elseif (${SCCC_CONFIG} STREQUAL 2016_INNO)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2016_INNO=1
            -DMK60F15=1
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
elseif (${SCCC_CONFIG} STREQUAL 2016_CAMERA)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2016_CAMERA=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER 1
            -DLIBSC_USE_BUTTON 2
            -DLIBSC_USE_BUZZER 1
            -DLIBSC_USE_ENCODER 1
            -DLIBSC_USE_JOYSTICK 1
            -DLIBSC_USE_LCD 1
            -DLIBSC_USE_LED 4
            -DLIBSC_USE_MOTOR 1
            -DLIBSC_USE_OV7725 1
            -DLIBSC_USE_SERVO 1
            -DLIBSC_USE_UART 2
            -DLIBSC_USE_MPU6050 1
            -DLIBSC_USE_MMA8451Q 1
            -DLIBSC_BATTERY_METER libbase::k60::Adc::Name::kAdc3Ad6A
            -DLIBSC_BUTTON0 libbase::k60::Pin::Name::kPtc12
            -DLIBSC_BUTTON1 libbase::k60::Pin::Name::kPte7
            -DLIBSC_BUZZER0 libbase::k60::Pin::Name::kPta8
            -DLIBSC_ENCODER0_QDA libbase::k60::Pin::Name::kPta10
            -DLIBSC_ENCODER0_QDB libbase::k60::Pin::Name::kPta11
            -DLIBSC_JOYSTICK0_UP libbase::k60::Pin::Name::kPtc8
            -DLIBSC_JOYSTICK0_DOWN libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_LEFT libbase::k60::Pin::Name::kPtc4
            -DLIBSC_JOYSTICK0_RIGHT libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_SELECT libbase::k60::Pin::Name::kPtc7
            -DLIBSC_ST7735R_RST libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK libbase::k60::Pin::Name::kPte2
            -DLIBSC_LED0 libbase::k60::Pin::Name::kPte12
            -DLIBSC_LED1 libbase::k60::Pin::Name::kPte11
            -DLIBSC_LED2 libbase::k60::Pin::Name::kPte10
            -DLIBSC_LED3 libbase::k60::Pin::Name::kPte9
            -DLIBSC_MOTOR0_DIRMOTOR 1
            -DLIBSC_MOTOR0_PWM libbase::k60::Pin::Name::kPtd0
            -DLIBSC_MOTOR0_DIR libbase::k60::Pin::Name::kPtd1
            -DLIBSC_OV77250_VSYNC libbase::k60::Pin::Name::kPtc2
            -DLIBSC_OV77250_PCLK libbase::k60::Pin::Name::kPtb6
            -DLIBSC_OV77250_DATA0 libbase::k60::Pin::Name::kPtb16
            -DLIBSC_OV77250_SDA libbase::k60::Pin::Name::kPtc1
            -DLIBSC_OV77250_SCL libbase::k60::Pin::Name::kPtc0
            -DLIBSC_OV77250_DMA_CH 1
            -DLIBSC_SERVO0 libbase::k60::Pin::Name::kPta7
            -DLIBSC_UART0_TX libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX libbase::k60::Pin::Name::kPtd6
            -DLIBSC_UART1_TX libbase::k60::Pin::Name::kPte24
            -DLIBSC_UART1_RX libbase::k60::Pin::Name::kPte25
            -DLIBSC_MPU6050_SCL libbase::k60::Pin::Name::kPtc10
            -DLIBSC_MPU6050_SDA libbase::k60::Pin::Name::kPtc11
            -DLIBSC_MMA8451Q0_SCL libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MMA8451Q0_SDA libbase::k60::Pin::Name::kPtb1
    )
elseif (${SCCC_CONFIG} STREQUAL 2016_CCD)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2016_CCD=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=2
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_LINEAR_CCD=4
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc3Ad6A
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPte7
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta11
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPta12
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPta13
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte12
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte11
            -DLIBSC_MOTOR0_PWMA=libbase::k60::Pin::Name::kPtd0
            -DLIBSC_MOTOR0_PWMB=libbase::k60::Pin::Name::kPtd1
            -DLIBSC_MOTOR0_DEADTIME=2500
            -DLIBSC_MOTOR1_PWMA=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_MOTOR1_PWMB=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_MOTOR1_DEADTIME=2500
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_LINEAR_CCD0_SI=libbase::k60::Pin::Name::kPtb4
            -DLIBSC_LINEAR_CCD0_CLK=libbase::k60::Pin::Name::kPtb3
            -DLIBSC_LINEAR_CCD0_AD=libbase::k60::Pin::Name::kPtb2
            -DLIBSC_LINEAR_CCD1_SI=libbase::k60::Pin::Name::kPtb7
            -DLIBSC_LINEAR_CCD1_CLK=libbase::k60::Pin::Name::kPtb6
            -DLIBSC_LINEAR_CCD1_AD=libbase::k60::Pin::Name::kPtb5
            -DLIBSC_LINEAR_CCD2_SI=libbase::k60::Pin::Name::kPta28
            -DLIBSC_LINEAR_CCD2_CLK=libbase::k60::Pin::Name::kPta27
            -DLIBSC_LINEAR_CCD2_AD=libbase::k60::Pin::Name::kPta26
            -DLIBSC_LINEAR_CCD3_SI=libbase::k60::Pin::Name::kPtc2
            -DLIBSC_LINEAR_CCD3_CLK=libbase::k60::Pin::Name::kPtc1
            -DLIBSC_LINEAR_CCD3_AD=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtd6
    )
elseif (${SCCC_CONFIG} STREQUAL 2016_RAIL)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2016_RAIL=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_ENCODER=1
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=1
            -DLIBSC_USE_LDC1000=2
            -DLIBSC_USE_SERVO=1
            -DLIBSC_USE_UART=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc3Ad6A
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPte7
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPtc12
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta8
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta11
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc5
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtc4
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_LDC1000_2_DC=libbase::k60::Pin::Name::kPte3
            -DLIBSC_LDC1000_2_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_LDC1000_2_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_LDC1000_2_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_LDC1000_1_DC=libbase::k60::Pin::Name::kPtb23
            -DLIBSC_LDC1000_1_CS=libbase::k60::Pin::Name::kPtb20
            -DLIBSC_LDC1000_1_SDAT=libbase::k60::Pin::Name::kPtb22
            -DLIBSC_LDC1000_1_SCLK=libbase::k60::Pin::Name::kPtb21
            -DLIBSC_LDC1000_0_DC=libbase::k60::Pin::Name::kPta17
            -DLIBSC_LDC1000_0_CS=libbase::k60::Pin::Name::kPta14
            -DLIBSC_LDC1000_0_SDAT=libbase::k60::Pin::Name::kPta16
            -DLIBSC_LDC1000_0_SCLK=libbase::k60::Pin::Name::kPta15
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte12
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte11
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPte10
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPte9
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPtd5
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtd6
    )
elseif (${SCCC_CONFIG} STREQUAL 2016_MAGNETIC)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2016_MAGNETIC=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=3
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_MAGSEN=6
            -DLIBSC_USE_UART=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_MPU6050=1
            -DLIBSC_USE_MMA8451Q=1
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc0Ad14
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPtc13
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPtc14
            -DLIBSC_BUTTON2=libbase::k60::Pin::Name::kPtc15
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta5
            -DLIBSC_BUZZER_ACIVE_LEVEL=0
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPtd1
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPtc19
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPtd0
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPta17
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPtc3
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPta14
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPta16
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPta15
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte8
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte9
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPte10
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPte11
            -DLIBSC_MOTOR0_DIRMOTOR=2
            -DLIBSC_MOTOR0_PWM=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_MOTOR0_DIR=libbase::k60::Pin::Name::kPtc6
            -DLIBSC_MOTOR1_PWM=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_MOTOR1_DIR=libbase::k60::Pin::Name::kPtc7
            -DLIBSC_MAGSEN0=libbase::k60::Pin::Name::kPte26
            -DLIBSC_MAGSEN1=libbase::k60::Pin::Name::kPte28
            -DLIBSC_MAGSEN2=libbase::k60::Pin::Name::kPte27
            -DLIBSC_MAGSEN3=libbase::k60::Pin::Name::kPte12
            -DLIBSC_MAGSEN4=libbase::k60::Pin::Name::kPte24
            -DLIBSC_MAGSEN5=libbase::k60::Pin::Name::kPte25
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPtd7
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPtd6
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPta8
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPta9
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPta10
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPta11
            -DLIBSC_MPU6050_SCL=libbase::k60::Pin::Name::kPtd8
            -DLIBSC_MPU6050_SDA=libbase::k60::Pin::Name::kPtd9
            -DLIBSC_MMA8451Q0_SCL=libbase::k60::Pin::Name::kPtc10
            -DLIBSC_MMA8451Q0_SDA=libbase::k60::Pin::Name::kPtc11
    )
elseif (${SCCC_CONFIG} STREQUAL 2016_MAGNETIC_YANG)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2016_MAGNETIC_YANG=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_PASSIVE_BUZZER=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
            -DLIBSC_USE_UART=1
            -DLIBSC_USE_MPU6050=1
            -DLIBSC_USE_MMA8451Q=1
            -DLIBSC_USE_MAGSEN=6
            -DLIBSC_BATTERY_METER=libbase::k60::Adc::Name::kAdc0Ad14
            -DLIBSC_BUTTON0=libbase::k60::Pin::Name::kPta4
            -DLIBSC_BUTTON1=libbase::k60::Pin::Name::kPte28
            -DLIBSC_BUZZER0=libbase::k60::Pin::Name::kPta5
            -DLIBSC_PASSSIVE_BUZZER0_PIT_CHANNEL=0
            -DLIBSC_MPU6050_SCL=libbase::k60::Pin::Name::kPtb2
            -DLIBSC_MPU6050_SDA=libbase::k60::Pin::Name::kPtb3
            -DLIBSC_ENCODER0_QDA=libbase::k60::Pin::Name::kPtb0
            -DLIBSC_ENCODER0_QDB=libbase::k60::Pin::Name::kPtb1
            -DLIBSC_ENCODER1_QDA=libbase::k60::Pin::Name::kPtb18
            -DLIBSC_ENCODER1_QDB=libbase::k60::Pin::Name::kPtb19
            -DLIBSC_JOYSTICK0_UP=libbase::k60::Pin::Name::kPta12
            -DLIBSC_JOYSTICK0_DOWN=libbase::k60::Pin::Name::kPta13
            -DLIBSC_JOYSTICK0_LEFT=libbase::k60::Pin::Name::kPta14
            -DLIBSC_JOYSTICK0_RIGHT=libbase::k60::Pin::Name::kPta15
            -DLIBSC_JOYSTICK0_SELECT=libbase::k60::Pin::Name::kPta16
            -DLIBSC_ST7735R_RST=libbase::k60::Pin::Name::kPte3
            -DLIBSC_ST7735R_DC=libbase::k60::Pin::Name::kPte0
            -DLIBSC_ST7735R_CS=libbase::k60::Pin::Name::kPte4
            -DLIBSC_ST7735R_SDAT=libbase::k60::Pin::Name::kPte1
            -DLIBSC_ST7735R_SCLK=libbase::k60::Pin::Name::kPte2
            -DLIBSC_LED0=libbase::k60::Pin::Name::kPte27
            -DLIBSC_LED1=libbase::k60::Pin::Name::kPte26
            -DLIBSC_LED2=libbase::k60::Pin::Name::kPte25
            -DLIBSC_LED3=libbase::k60::Pin::Name::kPte24
            -DLIBSC_MOTOR0_PWMA=libbase::k60::Pin::Name::kPtc8
            -DLIBSC_MOTOR0_PWMB=libbase::k60::Pin::Name::kPtc9
            -DLIBSC_MOTOR0_DEADTIME=1000
            -DLIBSC_MOTOR1_PWMA=libbase::k60::Pin::Name::kPtc10
            -DLIBSC_MOTOR1_PWMB=libbase::k60::Pin::Name::kPtc11
            -DLIBSC_MOTOR1_DEADTIME=1000
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPte8
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPte9
            -DLIBSC_MMA8451Q0_SCL=libbase::k60::Pin::Name::kPtd8
            -DLIBSC_MMA8451Q0_SDA=libbase::k60::Pin::Name::kPtd9
            -DLIBSC_MAGSEN0=libbase::k60::Pin::Name::kPta11
            -DLIBSC_MAGSEN1=libbase::k60::Pin::Name::kPta10
            -DLIBSC_MAGSEN2=libbase::k60::Pin::Name::kPta9
            -DLIBSC_MAGSEN3=libbase::k60::Pin::Name::kPta6
            -DLIBSC_MAGSEN4=libbase::k60::Pin::Name::kPta7
            -DLIBSC_MAGSEN5=libbase::k60::Pin::Name::kPta8
    )
elseif (${SCCC_CONFIG} STREQUAL 2017_INNO)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2017_INNO=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
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
            -DLIBSC_MOTOR0_DEADTIME=1000
            -DLIBSC_MOTOR1_PWMA=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_MOTOR1_PWMB=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_MOTOR1_DEADTIME=1000
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_OV77250_VSYNC=libbase::k60::Pin::Name::kPtc2
            -DLIBSC_OV77250_PCLK=libbase::k60::Pin::Name::kPtb6
            -DLIBSC_OV77250_DATA0=libbase::k60::Pin::Name::kPtb16
            -DLIBSC_OV77250_SDA=libbase::k60::Pin::Name::kPtc1
            -DLIBSC_OV77250_SCL=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_OV77250_DMA_CH=1
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPte25
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPte24
    )
elseif (${SCCC_CONFIG} STREQUAL 2017_CHASING)
    add_definitions(
            # from MakeConfig.inc
            -DK60_2017_CHASING=1
            -DMK60F15=1
            # from inc/libsc/k60/config
            -DLIBSC_USE_BATTERY_METER=1
            -DLIBSC_USE_BUTTON=2
            -DLIBSC_USE_BUZZER=1
            -DLIBSC_USE_ENCODER=2
            -DLIBSC_USE_JOYSTICK=1
            -DLIBSC_USE_LCD=1
            -DLIBSC_USE_LED=4
            -DLIBSC_USE_MOTOR=2
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
            -DLIBSC_MOTOR0_DEADTIME=1000
            -DLIBSC_MOTOR1_PWMA=libbase::k60::Pin::Name::kPtd2
            -DLIBSC_MOTOR1_PWMB=libbase::k60::Pin::Name::kPtd3
            -DLIBSC_MOTOR1_DEADTIME=1000
            -DLIBSC_ALTERNATE_MOTOR_CW_PWM=1
            -DLIBSC_OV77250_VSYNC=libbase::k60::Pin::Name::kPtc2
            -DLIBSC_OV77250_PCLK=libbase::k60::Pin::Name::kPtb6
            -DLIBSC_OV77250_DATA0=libbase::k60::Pin::Name::kPtb16
            -DLIBSC_OV77250_SDA=libbase::k60::Pin::Name::kPtc1
            -DLIBSC_OV77250_SCL=libbase::k60::Pin::Name::kPtc0
            -DLIBSC_OV77250_DMA_CH=1
            -DLIBSC_SERVO0=libbase::k60::Pin::Name::kPta7
            -DLIBSC_UART0_TX=libbase::k60::Pin::Name::kPte25
            -DLIBSC_UART0_RX=libbase::k60::Pin::Name::kPte24
    )
else ()
    message(ERROR Missing/Unknown config '${SCCC_CONFIG}' (set SCCC_CONFIG))
endif ()

# set build type according to what we have in CLion
if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(MAKE_BUILD_TYPE RELEASE)
elseif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(MAKE_BUILD_TYPE DEBUG)
else ()
    message(WARNING "No build type configured. Defaulting to Debug")
    set(MAKE_BUILD_TYPE DEBUG)
endif ()

# set make parameters
if (${COMPILE_ENV} STREQUAL david_desktop)
    set(MAKE_PATH "D:\\Program Files (x86)\\GnuWin32\\bin\\make.exe")
else ()
    set(MAKE_PATH "C:\\Program Files (x86)\\GnuWin32\\bin\\make.exe")
endif ()
set(MAKE_ARGS -f ${libsccc_SOURCE_DIR}/Makefile -k)
if (${COMPILE_ENV} STREQUAL david_desktop)
    set(MAKE_ARGS ${MAKE_ARGS} -j8)
elseif (${COMPILE_ENV} STREQUAL xanthe)
    set(MAKE_ARGS ${MAKE_ARGS} -j2)
else ()
    set(MAKE_ARGS ${MAKE_ARGS} -j4)
endif ()
set(MAKE_VARS SCCC_BUILD=${MAKE_BUILD_TYPE} PWD=${libsccc_SOURCE_DIR} CWD=${PWD})

# buiders
add_custom_target(make_once
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=${SCCC_CONFIG} all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(INNO_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=INNO all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_CAMERA_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_CAMERA all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_CCD_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_CCD all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_INNO_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_INNO all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_INNO_FX_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_INNO_FX all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_MAGNETIC_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_MAGNETIC all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(VCAN_FX15DEV_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=VCAN_FX15DEV all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_CAMERA_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_CAMERA all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_MAGNETIC_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_MAGNETIC all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_CCD_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_CCD all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(VCAN_Z4DEV_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=VCAN_Z4DEV all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_CCD2_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_CCD2 all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_M2_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_M2 all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_INNO_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_INNO all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_CAMERA_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_CAMERA all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_CCD_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_CCD all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_RAIL_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_RAIL all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_MAGNETIC_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_MAGNETIC all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_MAGNETIC_YANG_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_MAGNETIC_YANG all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2017_INNO_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2017_INNO all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2017_CHASING_make
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2017_CHASING all
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})

# cleaners
add_custom_target(clean_only
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=${SCCC_CONFIG} clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(INNO_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=INNO clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_CAMERA_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_CAMERA clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_CCD_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_CCD clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_INNO_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_INNO clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_INNO_FX_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_INNO_FX clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2014_MAGNETIC_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2014_MAGNETIC clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(VCAN_FX15DEV_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=VCAN_FX15DEV clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_CAMERA_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_CAMERA clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_MAGNETIC_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_MAGNETIC clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_CCD_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_CCD clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(VCAN_Z4DEV_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=VCAN_Z4DEV clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_CCD2_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_CCD2 clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2015_M2_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2015_M2 clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_INNO_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_INNO clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_CAMERA_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_CAMERA clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_CCD_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_CCD clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_RAIL_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_RAIL clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_MAGNETIC_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_MAGNETIC clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2016_MAGNETIC_YANG_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2016_MAGNETIC_YANG clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2017_INNO_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2017_INNO clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})
add_custom_target(2017_CHASING_clean
        COMMAND ${MAKE_PATH} ${MAKE_ARGS} ${MAKE_VARS} SCCC_CONFIG=2017_CHASING clean
        WORKING_DIRECTORY ${libsccc_SOURCE_DIR})

# configuration enabling all resolutions
file(GLOB_RECURSE SOURCES src/libbase/*.cpp src/libsc/*.cpp src/libutil/*.cpp)
add_executable(CurrentConfigSymbols ${SOURCES})
