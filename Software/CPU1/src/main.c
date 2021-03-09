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
#include "xil_exception.h"
//#include "xadd.h"
#include "xaddeq.h"
#include "xparameters.h"
#include "GPIO.h"

#define Timer_VALUE 100000000UL
static volatile int TotalReceivedCount;
static volatile int TotalSentCount;


u8 cnt;
u32 cnt32;
#define TEST_BUFFER_SIZE 4
u8 SendBuffer[TEST_BUFFER_SIZE];
u8 ReceiveBuffer[TEST_BUFFER_SIZE];


// The Instance of the Interrupt Controller Driver
XIntc Intc;
u32 cc;
u32 aa;
u32 bb;
u32 cc;
//XAdd addd;
XAddeq addde;


typedef struct{
    u8  rst;
    float Ts;
    float Kp;
    float Ki;
    float kogr;
    float uogr;
    float u_max;
    float u_min;
    float e;
    float u;
    float e_old;
    float u_old;
    u8  Anti_windup;
} REG_PI_t;
REG_PI_t regu;


u32 cc;

int main(){
    init_platform();
    Init_GPIO();

    aa = 5;
    bb = 2;
//    XAdd_Initialize(&addd,XPAR_ADD_0_DEVICE_ID);
    XAddeq_Initialize(&addde, XPAR_ADDEQ_0_DEVICE_ID);
    regu.e = 123.456;

    Init_TIMER(&TimerCounterInst, Timer_VALUE);
    Init_UART(&Uart);
    Init_Interrupt(&Intc);
    Start_Interrupt();


	XUartLite_Recv(&Uart, ReceiveBuffer, TEST_BUFFER_SIZE);

    while(1){
  //  	if(cnt++>0xFF) cnt = 0;
  //  	xil_printf("-----------%x:-----------\r\n", cnt32);
    	//print("Hello Marek\n\r");

 		//XUartLite_Recv(&UartLite, RecvBuffer, TEST_BUFFER_SIZE);
    	//uart_send((u8*)&str, 13);
    	//dane = XUartLite_Recv(&Uart, RecvBuffer, 3);
    //	u16 but = XGpio_DiscreteRead(&Gpio1_in1, GPIO_CHANNEL_0);
    //	xil_printf("BUT : %x\r\n", but);
    //	 xil_printf("-----------%d:-----------\r\n", (int)dataa);
    //	dataa = XSysMon_GetAdcData(SysMonInstPtr, 0x1F);
    //	data = ((dataa)*1000.0) /0xFFFF;
    //	XGpio_DiscreteWrite(&Gpio0_out1, GPIO_CHANNEL_0, 0x1);
    //	usleep(200000);
    //	XGpio_DiscreteWrite(&Gpio0_out1, GPIO_CHANNEL_0, 0x0);
    //	usleep(200000);
   //     XAdd_Set_a(&addd,aa);
   //     XAdd_Set_b(&addd,bb);

   // 	cc = XAdd_Get_c(&addd);
    }
    cleanup_platform();
    return 0;
}


u32 count;
float usage;

void timer_int_handler(void * CallBackRef, u8 TmrCtrNumber){

    XAddeq_Set_e(&addde,			regu.e);
    XAddeq_Set_Ts(&addde,		regu.Ts);
    XAddeq_Set_Kp(&addde,		regu.Kp);
    XAddeq_Set_Ki(&addde,		regu.Ki);
  //  XAdde_Set_e_old(&addde,		regu.e_old);
 //   XAdde_Set_u_old(&addde,		regu.e_old);
//    XAdde_Set_rst_r(&addde, 	regu.rst);


   // regu.u =  XAddeq_Get_u(&addde);


	XGpio_DiscreteWrite(&Gpio0_out1, GPIO_CHANNEL_0, 0x01 & cnt32);
	count = Timer_VALUE - (0xFFFFFFFF - cnt32);
	usage = 100.0*(float)count/(float)Timer_VALUE;

/*	XTmrCtr * InstancePtr = (XTmrCtr *)CallBackRef;

	if(XTmrCtr_IsExpired(InstancePtr, TmrCtrNumber)){
		count++;
		xil_printf("Count value is: %x\n\r", count);
	}*/
	xil_printf("-----------%d-----------\r\n",count);
	cnt32 = XTmrCtr_GetValue(&TimerCounterInst, XPAR_AXI_TIMER_0_DEVICE_ID);
}



void PushButtonHandle(void *pshButton)
{
	// Disable GPIO interrupts
	XGpio_InterruptDisable(&Gpio1_in1, BTN_INT);

	// Ignore additional button presses
    XGpio* PushButton = (XGpio*) pshButton;
    u8 btnState = XGpio_DiscreteRead(PushButton, 1);
    xil_printf("BUT : %x\r\n", btnState);
   // XUartLite_Send(&Uart, "BUT", 4);
    XGpio_InterruptEnable(&Gpio1_in1, BTN_INT);
    XGpio_InterruptClear(PushButton, 0xFF);
}


void SendHandler(void *CallBackRef, unsigned int EventData)
{
	TotalSentCount = EventData;

}

void RecvHandler(void *CallBackRef, unsigned int EventData)
{
	TotalReceivedCount = EventData;
	XUartLite_Recv(&Uart, ReceiveBuffer, TEST_BUFFER_SIZE);
	XUartLite_Send(&Uart, ReceiveBuffer, 4);
}

