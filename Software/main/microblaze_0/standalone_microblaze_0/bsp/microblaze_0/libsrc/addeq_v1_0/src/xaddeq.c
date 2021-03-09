// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xaddeq.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAddeq_CfgInitialize(XAddeq *InstancePtr, XAddeq_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAddeq_Set_e(XAddeq *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAddeq_WriteReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_E_DATA, Data);
}

u32 XAddeq_Get_e(XAddeq *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAddeq_ReadReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_E_DATA);
    return Data;
}

void XAddeq_Set_Kp(XAddeq *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAddeq_WriteReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_KP_DATA, Data);
}

u32 XAddeq_Get_Kp(XAddeq *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAddeq_ReadReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_KP_DATA);
    return Data;
}

void XAddeq_Set_Ki(XAddeq *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAddeq_WriteReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_KI_DATA, Data);
}

u32 XAddeq_Get_Ki(XAddeq *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAddeq_ReadReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_KI_DATA);
    return Data;
}

void XAddeq_Set_Ts(XAddeq *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAddeq_WriteReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_TS_DATA, Data);
}

u32 XAddeq_Get_Ts(XAddeq *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAddeq_ReadReg(InstancePtr->Control_BaseAddress, XADDEQ_CONTROL_ADDR_TS_DATA);
    return Data;
}

