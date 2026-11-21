/**
 * @file main.c
 *
 * @brief Main source code for the BLE_UART program.
 *
 * This file contains the main entry point for the BLE_UART program,
 * which is used to demonstrate the BLE_UART driver.
 *
 * It interfaces with the Adafruit Bluefruit LE UART Friend Bluetooth Low Energy (BLE) module, which uses the UART communication protocol.
 *  - Product Link: https://www.adafruit.com/product/2479
 *
 * @note For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @author John Lacebal
 *
 */

// CTRL + / to comment/decomment multiple lines

#include <stdint.h>
#include <math.h>
#include "msp.h"

#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/Motor.h"
#include "inc/BLE_UART.h"

#define PWM_NOMINAL 4500

void Process_BLE_UART_Data (char BLE_UART_Buffer[]) {
    if (Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED GREEN")) {
        LED2_Output(RGB_LED_GREEN);
    } else if (Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED OFF")) {
        LED2_Output(RGB_LED_OFF);
    } else {
        printf("BLE UART Command Not Found\n");
    }
}

int Decode_Controller_Packet(char BLE_UART_Data_Buffer[])
{
    // Verify '!' header
    if (BLE_UART_Data_Buffer[0] != 0x21) {
        return -1;
    }

    // Verify 'B' (button packet)
    if (BLE_UART_Data_Buffer[1] != 0x42) {
        return -2;
    }

    // Check if pressed or released
    if (BLE_UART_Data_Buffer[3] == 0x31) {
        printf("State: Pressed\n");
        switch (BLE_UART_Data_Buffer[2]) {
                case 0x35:
                    printf("Button: Up\n");
                    Motor_Forward(PWM_NOMINAL, PWM_NOMINAL);
                    break;
                case 0x36:
                    printf("Button: Down\n");
                    Motor_Backward(PWM_NOMINAL, PWM_NOMINAL);
                    break;
                case 0x37:
                    printf("Button: Left\n");
                    Motor_Left(PWM_NOMINAL, PWM_NOMINAL);
                    break;
                case 0x38:
                    printf("Button: Right\n");
                    Motor_Right(PWM_NOMINAL, PWM_NOMINAL);
                    break;
                default:
                    return -3;
        }
    } else if (BLE_UART_Data_Buffer[3] == 0x30) {
            printf("State: Released\n");
            Motor_Stop();
    }
    return 0;
}

int main(void)
{
    DisableInterrupts();

    Clock_Init48MHz();

    LED2_Init();

    EUSCI_A0_UART_Init_Printf();

    BLE_UART_Init();

    Motor_Init();

    PMOD_SWT_Init();

    char BLE_UART_Buffer[BLE_UART_BUFFER_SIZE] = {0};

    EnableInterrupts();

    Clock_Delay1ms(1000);
    BLE_UART_Reset();

    BLE_UART_OutString("BLE UART Active \r\n");
    Clock_Delay1ms(1000);

    while(1)
    {

//        int string_size = BLE_UART_InString(BLE_UART_Buffer, BLE_UART_BUFFER_SIZE);
//        printf("BLE UART Data: ");
//        for (int i = 0; i < string_size; i++) {
//            printf("%c", BLE_UART_Buffer[i]);
//        }
//        printf("\n");
//        Process_BLE_UART_Data(BLE_UART_Buffer);

//// UART Protocol Verification with Oscilloscope
//        for (int i = 1; i <= 4; i++) {
//            switch (i) {
//                case 1:
//                    BLE_UART_OutChar(0xAA);
//                    break;
//                case 2:
//                    BLE_UART_OutChar(0x55);
//                    break;
//                case 3:
//                    BLE_UART_OutChar(0xFF);
//                    break;
//                case 4:
//                    BLE_UART_OutChar(0x00);
//                    break;
//                default:
//                    break;
//            }
//            Clock_Delay1ms(3000);
//        }

// UART Transmission Using PMOD SWT
//        uint8_t switch_status = Get_PMOD_SWT_Status();
//        switch (switch_status) {
//            case 0x01:
//                BLE_UART_OutChar(0xAA);
//                break;
//            case 0x02:
//                BLE_UART_OutChar(0x10);
//                break;
//            case 0x04:
//                BLE_UART_OutChar(0xF0);
//                break;
//            case 0x08:
//                BLE_UART_OutChar(0x0F);
//                break;
//            default:
//                BLE_UART_OutChar(0x00);
//                break;
//        }
//        Clock_Delay1ms(1000);

// BLE Controller – Arrow Button Motor Control
        if (BLE_UART_InPacket(BLE_UART_Buffer)) {
            Decode_Controller_Packet(BLE_UART_Buffer);
        }

    }
}
