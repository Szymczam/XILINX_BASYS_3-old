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

#ifdef XPAR_INTC_0_DEVICE_ID
#include "xintc.h"
#else
#include "xscugic.h"
#endif


#define BTNS_DEVICE_ID  	  	XPAR_GPIO_0_DEVICE_ID
#define INTC_DEVICE_ID		  	XPAR_INTC_0_DEVICE_ID
#define BTN_IRTP_ID     	  	XPAR_AXI_GPIO_0_DEVICE_ID
#define BTN_INT 				XGPIO_IR_CH1_MASK


#define GPIO_CHANNEL_0			0x01
#define GPIO_CHANNEL_1			0x02


#define UARTLITE_DEVICE_ID      XPAR_UARTLITE_0_DEVICE_ID
#define INTC_DEVICE_ID          XPAR_INTC_0_DEVICE_ID
#define UARTLITE_INT_IRQ_ID     XPAR_INTC_0_UARTLITE_0_VEC_ID

XUartLite Uart;		/* Instance of the UART Device */

XIntc InterruptController;     /* The instance of the Interrupt Controller */


static volatile int TotalReceivedCount;
static volatile int TotalSentCount;



u8 cnt;
u8 but;

XGpio BTNInst;
XGpio BTNtwo;
XIntc Intc; /* The Instance of the Interrupt Controller Driver */
char str[30] = "Hello Marek\r\n";

u8 dane;

XIntc IntcInstance;	/* The instance of the Interrupt Controller */




void PushButtonHandle(void *pshButton);
void SendHandler(void *CallBackRef, unsigned int EventData);
void RecvHandler(void *CallBackRef, unsigned int EventData);


int uart_send(u8* sendBuffer, u8 size){
	if(XUartLite_IsSending(&Uart))
		return 0;

	int SentCount = XUartLite_Send(&Uart, sendBuffer, size);

	return SentCount;
}



#define TEST_BUFFER_SIZE 4
u8 SendBuffer[TEST_BUFFER_SIZE];
u8 ReceiveBuffer[TEST_BUFFER_SIZE];


int SetupInterruptSystem(XUartLite *UartLitePtr)
{

	int Status;


	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	Status = XIntc_Initialize(&InterruptController, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the
	 * specific interrupt processing for the device.
	 */
	Status = XIntc_Connect(&InterruptController, UARTLITE_INT_IRQ_ID,
			   (XInterruptHandler)XUartLite_InterruptHandler,
			   (void *)UartLitePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts, specific real mode so that
	 * the UartLite can cause interrupts through the interrupt controller.
	 */
	Status = XIntc_Start(&InterruptController, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the UartLite device.
	 */
	XIntc_Enable(&InterruptController, UARTLITE_INT_IRQ_ID);

	// Initialize the exception table.
	Xil_ExceptionInit();

	// Register the interrupt controller handler with the exception table.
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 (Xil_ExceptionHandler)XIntc_InterruptHandler,
			 &InterruptController);

	// Enable exceptions.
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}



int main(){
	int status;

    init_platform();

	// Initialise Push Buttons
	status = XGpio_Initialize(&BTNInst, BTNS_DEVICE_ID);
	if (status != XST_SUCCESS)	return XST_FAILURE;
    XGpio_SetDataDirection(&BTNInst, GPIO_CHANNEL_0, 0xFF);
    XGpio_InterruptClear(&BTNInst, 0x0);

    // Initialise data to 7-seg display
	status = XGpio_Initialize(&BTNtwo, XPAR_GPIO_1_DEVICE_ID);
	if (status != XST_SUCCESS)	return XST_FAILURE;
    XGpio_SetDataDirection(&BTNtwo, GPIO_CHANNEL_0, 0x0);



#ifdef __MICROBLAZE__

    // Initialize the UartLite driver so that it is ready to use.
    status = XUartLite_Initialize(&Uart, XPAR_AXI_UARTLITE_0_DEVICE_ID);
	if (status != XST_SUCCESS) return XST_FAILURE;

	// Perform a self-test to ensure that the hardware was built correctly.
	status = XUartLite_SelfTest(&Uart);
	if (status != XST_SUCCESS) return XST_FAILURE;

	status = SetupInterruptSystem(&Uart);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XUartLite_SetSendHandler(&Uart, SendHandler, &Uart);
	XUartLite_SetRecvHandler(&Uart, RecvHandler, &Uart);

	XUartLite_EnableInterrupt(&Uart);

	int Index;
	for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
		SendBuffer[Index] = Index;
		ReceiveBuffer[Index] = 0;
	}
	XUartLite_Recv(&Uart, ReceiveBuffer, TEST_BUFFER_SIZE);
	XUartLite_Send(&Uart, SendBuffer, TEST_BUFFER_SIZE);
/*
	int Index;
	for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
		SendBuffer[Index] = Index;
		RecvBuffer[Index] = 0;
	}

	unsigned int SentCount;
	SentCount = XUartLite_Send(&Uart, SendBuffer, TEST_BUFFER_SIZE);
	if (SentCount != TEST_BUFFER_SIZE) {
		return XST_FAILURE;
	}
*/

	//XUartLite_SetRecvHandler(&Uart, UARTHandle);
//	XUartLite_SetSendHandler(&Uart, SendHandler_UART_1, &Uart);
//	XUartLite_SetRecvHandler(&Uart, RecvHandler_UART_1, &Uart);
//	XUartLite_EnableInterrupt(&Uart);
#else
   // Uartps for Zynq
   XUartPs_Config *myUartCfgPtr;
   myUartCfgPtr = XUartPs_LookupConfig(SYS_UART_DEVICE_ID);
   XUartPs_CfgInitialize(&myUart, myUartCfgPtr, myUartCfgPtr->BaseAddress);
#endif
/*

    XIntc_Initialize(&Intc, INTC_DEVICE_ID);
    XIntc_Connect(&Intc, BTN_IRTP_ID, PushButtonHandle, &BTNInst);
    XIntc_Enable(&Intc, BTN_IRTP_ID);

    microblaze_register_handler(XIntc_DeviceInterruptHandler, INTC_DEVICE_ID);
	microblaze_enable_interrupts();
	XIntc_Start(&Intc, XIN_REAL_MODE);

    XGpio_InterruptEnable(&BTNInst, 1);
    XGpio_InterruptGlobalEnable(&BTNInst);
*/

 //   status = SetupInterruptSystem(&Uart, XPAR_INTC_0_DEVICE_ID);
//	if (status != XST_SUCCESS) return XST_FAILURE;


    //status = XUartLite_CfgInitialize(&Uart, &uart_conf);
	//if (status != XST_SUCCESS) return XST_FAILURE;





    while(1){
    	if(cnt++>0xFF) cnt = 0;
    //	xil_printf(str, "-----------%x:-----------\r\n", cnt);
    	//print("Hello Marek\n\r");
    	//uart_send((u8*)&str, 13);
    	 XGpio_DiscreteWrite(&BTNtwo, GPIO_CHANNEL_0, cnt);
    	 if(TotalReceivedCount > 0){
    		 XUartLite_Send(&Uart, ReceiveBuffer, TEST_BUFFER_SIZE);
    		 TotalReceivedCount= 0;
    		 XUartLite_Recv(&Uart, ReceiveBuffer, TEST_BUFFER_SIZE);
    	 }

 		//XUartLite_Recv(&UartLite, RecvBuffer, TEST_BUFFER_SIZE);
    	//uart_send((u8*)&str, 13);
    	//dane = XUartLite_Recv(&Uart, RecvBuffer, 3);
    	//9//but = XGpio_DiscreteRead(&BTNInst, GPIO_CHANNEL_0);
    	//99xil_printf("BUT : %x\r\n", but);


    	usleep(1000000);
    }
    cleanup_platform();
    return 0;
}


void SendHandler(void *CallBackRef, unsigned int EventData)
{
	TotalSentCount = EventData;
}

void RecvHandler(void *CallBackRef, unsigned int EventData)
{
	TotalReceivedCount = EventData;
}



void PushButtonHandle(void *pshButton)
{
	// Disable GPIO interrupts
	XGpio_InterruptDisable(&BTNInst, BTN_INT);

	// Ignore additional button presses
    XGpio* PushButton = (XGpio*) pshButton;
    u8 btnState = XGpio_DiscreteRead(PushButton, 1);
    xil_printf("BUT : %x\r\n", btnState);

    XGpio_InterruptEnable(&BTNInst, BTN_INT);
    XGpio_InterruptClear(PushButton, 0xFF);
}

