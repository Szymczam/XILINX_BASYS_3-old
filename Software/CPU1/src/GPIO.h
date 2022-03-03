
#include "xparameters.h"
#include "xgpio.h"
#include "xintc.h"

#include "xuartlite.h"
#include "xuartlite_l.h"

#define GPIO0_OUT  	  			XPAR_GPIO_0_DEVICE_ID
#define GPIO1_IN  	  			XPAR_GPIO_1_DEVICE_ID

#define BTN_INT 				XGPIO_IR_CH2_MASK
#define BTN_IRTP_ID     	  	XPAR_AXI_GPIO_1_DEVICE_ID
#define INTC_DEVICE_ID		  	XPAR_INTC_0_DEVICE_ID
#define UARTLITE_INT_IRQ_ID     XPAR_INTC_0_UARTLITE_0_VEC_ID




#define GPIO_CHANNEL_0			0x01
#define GPIO_CHANNEL_1			0x02



extern XGpio 		Gpio0_out1;
extern XGpio 		Gpio0_out2;
extern XGpio 		Gpio1_in1;
extern XGpio 		Gpio1_in2;
extern XUartLite 	Uart;




void PushButtonHandle(void *pshButton);
int Init_GPIO();
void Init_Interrupt(XIntc* InstancePtr);
void Start_Interrupt();
void SendHandler(void *CallBackRef, unsigned int EventData);
void RecvHandler(void *CallBackRef, unsigned int EventData);
int Init_UART(XUartLite* InstancePtr);



