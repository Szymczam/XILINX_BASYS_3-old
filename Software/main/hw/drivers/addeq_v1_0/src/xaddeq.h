// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XADDEQ_H
#define XADDEQ_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xaddeq_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XAddeq_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XAddeq;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAddeq_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAddeq_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAddeq_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAddeq_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XAddeq_Initialize(XAddeq *InstancePtr, u16 DeviceId);
XAddeq_Config* XAddeq_LookupConfig(u16 DeviceId);
int XAddeq_CfgInitialize(XAddeq *InstancePtr, XAddeq_Config *ConfigPtr);
#else
int XAddeq_Initialize(XAddeq *InstancePtr, const char* InstanceName);
int XAddeq_Release(XAddeq *InstancePtr);
#endif


void XAddeq_Set_e(XAddeq *InstancePtr, u32 Data);
u32 XAddeq_Get_e(XAddeq *InstancePtr);
void XAddeq_Set_Kp(XAddeq *InstancePtr, u32 Data);
u32 XAddeq_Get_Kp(XAddeq *InstancePtr);
void XAddeq_Set_Ki(XAddeq *InstancePtr, u32 Data);
u32 XAddeq_Get_Ki(XAddeq *InstancePtr);
void XAddeq_Set_Ts(XAddeq *InstancePtr, u32 Data);
u32 XAddeq_Get_Ts(XAddeq *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
