/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <sleep.h>
#include "xgpio.h"
#include "xil_exception.h"
#include "xintc.h"
#include "xuartlite.h"
#include "xuartlite_l.h"
#include "xparameters.h"

u8 cnt;

#define GPIO_CHANNEL_0			0x01
#define GPIO_CHANNEL_1			0x02

#define GPIO1_OUT  	  	XPAR_GPIO_0_DEVICE_ID
#define GPIO1_IN  	  	XPAR_GPIO_1_DEVICE_ID

XGpio Gpio1_out;

int main(){
    init_platform();

    int status;
	status = XGpio_Initialize(&Gpio1_out, XPAR_GPIO_0_DEVICE_ID);
	if (status != XST_SUCCESS)	return XST_FAILURE;
    XGpio_SetDataDirection(&Gpio1_out, GPIO_CHANNEL_0, 0x00);







    while(1){
    	if(cnt++>0xFF) cnt = 0;
    	xil_printf("-----------%x:-----------\r\n", cnt);
    	//print("Hello Marek\n\r");
    	//uart_send((u8*)&str, 13);
/*
    	 if(TotalReceivedCount > 0){
    		 XUartLite_Send(&Uart, ReceiveBuffer, TEST_BUFFER_SIZE);
    		 TotalReceivedCount= 0;
    		 XUartLite_Recv(&Uart, ReceiveBuffer, TEST_BUFFER_SIZE);
    	 }
*/
 		//XUartLite_Recv(&UartLite, RecvBuffer, TEST_BUFFER_SIZE);
    	//uart_send((u8*)&str, 13);
    	//dane = XUartLite_Recv(&Uart, RecvBuffer, 3);
    	//9//but = XGpio_DiscreteRead(&BTNInst, GPIO_CHANNEL_0);
    	//99xil_printf("BUT : %x\r\n", but);
    //	 xil_printf("-----------%d:-----------\r\n", (int)dataa);
    //	dataa = XSysMon_GetAdcData(SysMonInstPtr, 0x1F);
    //	data = ((dataa)*1000.0) /0xFFFF;
    	XGpio_DiscreteWrite(&Gpio1_out, GPIO_CHANNEL_0, 1);
    	usleep(100000);
    	XGpio_DiscreteWrite(&Gpio1_out, GPIO_CHANNEL_0, 0);
    	usleep(100000);
    }
    cleanup_platform();
    return 0;
}
