// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of e
//        bit 31~0 - e[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of Kp
//        bit 31~0 - Kp[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of Ki
//        bit 31~0 - Ki[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of Ts
//        bit 31~0 - Ts[31:0] (Read/Write)
// 0x2c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XADDEQ_CONTROL_ADDR_E_DATA  0x10
#define XADDEQ_CONTROL_BITS_E_DATA  32
#define XADDEQ_CONTROL_ADDR_KP_DATA 0x18
#define XADDEQ_CONTROL_BITS_KP_DATA 32
#define XADDEQ_CONTROL_ADDR_KI_DATA 0x20
#define XADDEQ_CONTROL_BITS_KI_DATA 32
#define XADDEQ_CONTROL_ADDR_TS_DATA 0x28
#define XADDEQ_CONTROL_BITS_TS_DATA 32

