/*
  btt_octopus_max_map.h - Board map for BIGTREETECH Octopus Pro v1.1

  Part of grblHAL

  Copyright (c) 2024 Joe Corelli
  Copyright (c) 2024 Jon Escombe

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#if N_ABC_MOTORS > 8
#error "Octopus Pro v1.1 board map is only configured for 8 motors max."
#endif

#if !(defined(STM32H723xx)) || HSE_VALUE != 25000000
#error "This board has a STM32H723 processor with 25MHz crystal, select a corresponding build!"
#endif

#define BOARD_NAME "BTT Octopus Pro v1.1"
#define BOARD_URL "https://github.com/bigtreetech/BIGTREETECH-OCTOPUS-Pro"

#define SERIAL_PORT                 32      // GPIOD: TX = 8, RX = 9
#define I2C_PORT                    1       // GPIOB: SCL = 8, SDA = 9
#define SPI_PORT                    1       // GPIOA: SCK = 5, MISO = 6, MOSI = 7

// Motor Reference:
// Motor-1: X-axis
// Motor-2: Y-axis
// Motor-3: Z-axis
// Motor-4: M3-axis
// Motor-5: M4-axis
// Motor-6: M5-axis
// Motor-7: M6-axis
// Motor-8: M7-axis

// Define step pulse output pins.
#define X_STEP_PORT                 GPIOF
#define X_STEP_PIN                  13
#define Y_STEP_PORT                 GPIOG
#define Y_STEP_PIN                  0
#define Z_STEP_PORT                 GPIOF
#define Z_STEP_PIN                  11
#define STEP_OUTMODE                GPIO_SINGLE

// Define step direction output pins.
#define X_DIRECTION_PORT            GPIOF
#define X_DIRECTION_PIN             12
#define Y_DIRECTION_PORT            GPIOG
#define Y_DIRECTION_PIN             1
#define Z_DIRECTION_PORT            GPIOG
#define Z_DIRECTION_PIN             3
#define DIRECTION_OUTMODE           GPIO_SINGLE

// Define stepper driver enable/disable output pin.
#define X_ENABLE_PORT               GPIOF
#define X_ENABLE_PIN                14
#define Y_ENABLE_PORT               GPIOF
#define Y_ENABLE_PIN                15
#define Z_ENABLE_PORT               GPIOG
#define Z_ENABLE_PIN                5


//to do
// Define homing/hard limit switch input pins.
#define X_LIMIT_PORT                GPIOG
#define X_LIMIT_PIN                 6       // MIN1
#define Y_LIMIT_PORT                GPIOG
#define Y_LIMIT_PIN                 9       // MIN2
#define Z_LIMIT_PORT                GPIOG
#define Z_LIMIT_PIN                 10       // MIN3
#define LIMIT_INMODE                GPIO_SINGLE

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 0
#define M3_AVAILABLE                        // Motor-4
#define M3_STEP_PORT                GPIOG
#define M3_STEP_PIN                 4
#define M3_DIRECTION_PORT           GPIOC
#define M3_DIRECTION_PIN            1
//#define M3_LIMIT_PORT               GPIOG 
//#define M3_LIMIT_PIN                11       // MIN4
#define M3_ENABLE_PORT              GPIOA
#define M3_ENABLE_PIN               2       // EN for M3 motor
#endif

// Define ganged axis or B axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 1
#define M4_AVAILABLE                        // Motor-5
#define M4_STEP_PORT                GPIOF
#define M4_STEP_PIN                 9
#define M4_DIRECTION_PORT           GPIOF
#define M4_DIRECTION_PIN            10
//#define M4_LIMIT_PORT               GPIOG   
//#define M4_LIMIT_PIN                12       // MIN5
#define M4_ENABLE_PORT              GPIOG
#define M4_ENABLE_PIN               2      // EN for M4
#endif

// Define ganged axis or C axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 2
#define M5_AVAILABLE                        // Motor-6
#define M5_STEP_PORT                GPIOC
#define M5_STEP_PIN                 13
#define M5_DIRECTION_PORT           GPIOF
#define M5_DIRECTION_PIN            0
#define M5_LIMIT_PORT               GPIOG 
#define M5_LIMIT_PIN                13      // MIN6
#define M5_ENABLE_PORT              GPIOF
#define M5_ENABLE_PIN               1       // EN for M5 motor
#endif

#if N_ABC_MOTORS > 3
#define M6_AVAILABLE                        // Motor-7
#define M6_STEP_PORT                GPIOE
#define M6_STEP_PIN                 2
#define M6_DIRECTION_PORT           GPIOE
#define M6_DIRECTION_PIN            3
#define M6_LIMIT_PORT               GPIOG 
#define M6_LIMIT_PIN                14      // MIN6
#define M6_ENABLE_PORT              GPIOD
#define M6_ENABLE_PIN               4       // EN for M5 motor
#endif

#if N_ABC_MOTORS > 4
#define M7_AVAILABLE                        // Motor-8
#define M7_STEP_PORT                GPIOE
#define M7_STEP_PIN                 6
#define M7_DIRECTION_PORT           GPIOA
#define M7_DIRECTION_PIN            14
#define M7_LIMIT_PORT               GPIOG   
#define M7_LIMIT_PIN                15      // MIN6
#define M7_ENABLE_PORT              GPIOE
#define M7_ENABLE_PIN               0       // EN for M5 motor
#endif

//this might need to be changed
//needs to be pwm_signal_t pwm_pin[] array in pwm.c?
#define AUXOUTPUT0_PORT             GPIOA   // Spindle PWM - FAN1
#define AUXOUTPUT0_PIN              8
#define AUXOUTPUT1_PORT             GPIOD   // Spindle direction - FAN5
#define AUXOUTPUT1_PIN              15
#define AUXOUTPUT2_PORT             GPIOD   // Spindle enable - FAN4
#define AUXOUTPUT2_PIN              14

#define AUXOUTPUT3_PORT             GPIOA   // Coolant flood - HE0
#define AUXOUTPUT3_PIN              0
#define AUXOUTPUT4_PORT             GPIOA   // Coolant mist - HE1
#define AUXOUTPUT4_PIN              3

// Define driver spindle pins.
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
#define SPINDLE_ENABLE_PORT         AUXOUTPUT2_PORT
#define SPINDLE_ENABLE_PIN          AUXOUTPUT2_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
#define SPINDLE_PWM_PORT            AUXOUTPUT0_PORT
#define SPINDLE_PWM_PIN             AUXOUTPUT0_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
#define SPINDLE_DIRECTION_PORT      AUXOUTPUT1_PORT
#define SPINDLE_DIRECTION_PIN       AUXOUTPUT1_PIN
#endif

// Define flood and mist coolant enable output pins.
#if COOLANT_ENABLE & COOLANT_FLOOD
#define COOLANT_FLOOD_PORT          AUXOUTPUT3_PORT
#define COOLANT_FLOOD_PIN           AUXOUTPUT3_PIN
#endif
#if COOLANT_ENABLE & COOLANT_MIST
#define COOLANT_MIST_PORT           AUXOUTPUT4_PORT
#define COOLANT_MIST_PIN            AUXOUTPUT4_PIN
#endif

// Define user-control controls (cycle start, reset, feed hold) input pins.
#define RESET_PORT                  GPIOE
#define RESET_PIN                   11      // PS-ON 
#define FEED_HOLD_PORT              GPIOB
#define FEED_HOLD_PIN               1       // IND-PROBE
#define CYCLE_START_PORT            GPIOB 
#define CYCLE_START_PIN             2       // FWS

#define AUXINPUT0_PORT              GPIOC
#define AUXINPUT0_PIN               0       // PWR-DET

#define AUXINPUT1_PORT              GPIOB
#define AUXINPUT1_PIN               6      // Z probe //pb7 can also be used

#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PORT            AUXINPUT0_PORT
#define SAFETY_DOOR_PIN             AUXINPUT0_PIN
#endif

#if PROBE_ENABLE
#define PROBE_PORT                  AUXINPUT1_PORT
#define PROBE_PIN                   AUXINPUT1_PIN
#endif

#define CONTROL_INMODE              GPIO_SINGLE

/*
//not supported
#if TRINAMIC_UART_ENABLE

#define MOTOR_UARTX_PORT            GPIOG
#define MOTOR_UARTX_PIN             14
#define MOTOR_UARTY_PORT            GPIOG
#define MOTOR_UARTY_PIN             13
#define MOTOR_UARTZ_PORT            GPIOG
#define MOTOR_UARTZ_PIN             12

#ifdef  M3_AVAILABLE
#define MOTOR_UARTM3_PORT           GPIOG
#define MOTOR_UARTM3_PIN            11
#endif

#ifdef  M4_AVAILABLE
#define MOTOR_UARTM4_PORT           GPIOG
#define MOTOR_UARTM4_PIN            10
#endif

#ifdef  M5_AVAILABLE
#define MOTOR_UARTM5_PORT           GPIOG
#define MOTOR_UARTM5_PIN            9
#endif

#ifdef  M6_AVAILABLE
#define MOTOR_UARTM6_PORT           GPIOG
#define MOTOR_UARTM6_PIN            9
#endif

#ifdef  M7_AVAILABLE
#define MOTOR_UARTM7_PORT           GPIOG
#define MOTOR_UARTM7_PIN            9
#endif

#endif//TRINAMIC_UART_ENABLE
*/

#ifdef TRINAMIC_SPI_ENABLE

// The BTT Octopus Pro uses hardware SPI1 for Trinamic drivers
#define TRINAMIC_MOSI_PORT          GPIOA
#define TRINAMIC_MOSI_PIN           7
#define TRINAMIC_SCK_PORT           GPIOA
#define TRINAMIC_SCK_PIN            5
#define TRINAMIC_MISO_PORT          GPIOA
#define TRINAMIC_MISO_PIN           6

#define MOTOR_CSX_PORT              GPIOC
#define MOTOR_CSX_PIN               4
#define MOTOR_CSY_PORT              GPIOD
#define MOTOR_CSY_PIN               11
#define MOTOR_CSZ_PORT              GPIOC
#define MOTOR_CSZ_PIN               6

#ifdef  M3_AVAILABLE
#define MOTOR_CSM3_PORT             GPIOC
#define MOTOR_CSM3_PIN              7
#endif

#ifdef  M4_AVAILABLE
#define MOTOR_CSM4_PORT             GPIOF
#define MOTOR_CSM4_PIN              2
#endif

#ifdef  M5_AVAILABLE
#define MOTOR_CSM5_PORT             GPIOE
#define MOTOR_CSM5_PIN              4
#endif

#ifdef  M6_AVAILABLE
#define MOTOR_CSM6_PORT             GPIOE
#define MOTOR_CSM6_PIN              1
#endif

#ifdef  M7_AVAILABLE
#define MOTOR_CSM7_PORT             GPIOD
#define MOTOR_CSM7_PIN              3
#endif

#endif

// EOF
