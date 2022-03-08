
#include "xparameters.h"
#include "xgpio.h"
#include "xintc.h"

#include "xuartlite.h"
#include "xuartlite_l.h"

#include <xtmrctr.h>



#define GPIO0_OUT  	  			XPAR_GPIO_0_DEVICE_ID
#define GPIO1_IN  	  			XPAR_GPIO_1_DEVICE_ID
#define INTC_DEVICE_ID		  	XPAR_INTC_0_DEVICE_ID

#define BTN_INT 				XGPIO_IR_CH2_MASK

#define UARTLITE_INT_IRQ_ID     XPAR_INTC_0_UARTLITE_0_VEC_ID
#define GPIO_INT_IRQ_ID     	XPAR_INTC_0_GPIO_1_VEC_ID
#define TIMER_INT_IRQ_ID     	XPAR_INTC_0_TMRCTR_0_VEC_ID



#define GPIO_CHANNEL_0			0x01
#define GPIO_CHANNEL_1			0x02



extern XGpio 		Gpio0_out1;
extern XGpio 		Gpio0_out2;
extern XGpio 		Gpio1_in1;
extern XGpio 		Gpio1_in2;
extern XUartLite 	Uart;

extern XTmrCtr TimerCounterInst;


void PushButtonHandle(void *pshButton);
int Init_GPIO();
void Init_Interrupt(XIntc* InstancePtr);
void Start_Interrupt();
void SendHandler(void *CallBackRef, unsigned int EventData);
void RecvHandler(void *CallBackRef, unsigned int EventData);
int Init_UART(XUartLite* InstancePtr);
int Init_TIMER(XTmrCtr* InstancePtr, u32 value);
void timer_int_handler(void * CallBackRef, u8 TmrCtrNumber);

