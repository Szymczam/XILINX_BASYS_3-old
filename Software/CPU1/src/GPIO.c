
#include "GPIO.h"



// Instance of the GPIO Device
XGpio Gpio0_out1;
XGpio Gpio0_out2;
XGpio Gpio1_in1;
XGpio Gpio1_in2;


// Instance of the UART Device
XUartLite Uart;



int Init_GPIO(){
	int status;

	status = XGpio_Initialize(&Gpio0_out1, GPIO0_OUT);
	if (status != XST_SUCCESS)	return XST_FAILURE;
    XGpio_SetDataDirection(&Gpio0_out1, GPIO_CHANNEL_0, 0x00000000);

	status = XGpio_Initialize(&Gpio0_out2, GPIO0_OUT);
	if (status != XST_SUCCESS)	return XST_FAILURE;
    XGpio_SetDataDirection(&Gpio0_out2, GPIO_CHANNEL_1, 0x00000000);

	status = XGpio_Initialize(&Gpio1_in1, GPIO1_IN);
	if (status != XST_SUCCESS)	return XST_FAILURE;
    XGpio_SetDataDirection(&Gpio1_in1, GPIO_CHANNEL_0, 0xFFFFFFFF);

	status = XGpio_Initialize(&Gpio1_in2, GPIO1_IN);
	if (status != XST_SUCCESS)	return XST_FAILURE;
    XGpio_SetDataDirection(&Gpio1_in2, GPIO_CHANNEL_1, 0xFFFFFFFF);

	return status;
}


int Init_UART(XUartLite* InstancePtr){
	int status;

	status = XUartLite_Initialize(InstancePtr, XPAR_AXI_UARTLITE_0_DEVICE_ID);
	if (status != XST_SUCCESS) return XST_FAILURE;

	// Perform a self-test to ensure that the hardware was built correctly.
	status = XUartLite_SelfTest(InstancePtr);
	if (status != XST_SUCCESS) return XST_FAILURE;

	//status = SetupInterruptSystem(&Uart);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return status;
}


void Init_Interrupt(XIntc* InstancePtr){
    XIntc_Initialize(InstancePtr, INTC_DEVICE_ID);
    XIntc_Connect(InstancePtr, BTN_IRTP_ID, PushButtonHandle, &Gpio1_in1);
	XIntc_Connect(InstancePtr, UARTLITE_INT_IRQ_ID,(XInterruptHandler)XUartLite_InterruptHandler, &Uart);

	XIntc_Start(InstancePtr, XIN_REAL_MODE);

    XIntc_Enable(InstancePtr, BTN_IRTP_ID);
	XIntc_Enable(InstancePtr, UARTLITE_INT_IRQ_ID);


	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler)XIntc_InterruptHandler, InstancePtr);
	Xil_ExceptionEnable();
}











void Start_Interrupt(){
	XGpio_InterruptEnable(&Gpio1_in1, 0xFFFF);
	XGpio_InterruptGlobalEnable(&Gpio1_in1);

	XUartLite_SetRecvHandler(&Uart, RecvHandler, &Uart);
	XUartLite_SetSendHandler(&Uart, SendHandler, &Uart);
	XUartLite_EnableInterrupt(&Uart);

}

