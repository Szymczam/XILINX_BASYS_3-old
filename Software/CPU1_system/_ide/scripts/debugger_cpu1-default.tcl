# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: F:\GitKraken\XILINX_BASYS_3\Software\CPU1_system\_ide\scripts\debugger_cpu1-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source F:\GitKraken\XILINX_BASYS_3\Software\CPU1_system\_ide\scripts\debugger_cpu1-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Basys3 210183A8A23CA" && jtag_device_ctx=="jsn-Basys3-210183A8A23CA-0362d093-0"}
loadhw -hw F:/GitKraken/XILINX_BASYS_3/Software/main/export/main/hw/main.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Basys3 210183A8A23CA" && jtag_device_ctx=="jsn-Basys3-210183A8A23CA-0362d093-0"}
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Basys3 210183A8A23CA" && jtag_device_ctx=="jsn-Basys3-210183A8A23CA-0362d093-0"}
dow F:/GitKraken/XILINX_BASYS_3/Software/CPU1/Debug/CPU1.elf
bpadd -addr &main