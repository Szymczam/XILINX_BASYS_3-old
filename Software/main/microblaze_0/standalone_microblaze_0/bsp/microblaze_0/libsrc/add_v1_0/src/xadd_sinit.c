// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xadd.h"

extern XAdd_Config XAdd_ConfigTable[];

XAdd_Config *XAdd_LookupConfig(u16 DeviceId) {
	XAdd_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XADD_NUM_INSTANCES; Index++) {
		if (XAdd_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XAdd_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAdd_Initialize(XAdd *InstancePtr, u16 DeviceId) {
	XAdd_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAdd_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAdd_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

