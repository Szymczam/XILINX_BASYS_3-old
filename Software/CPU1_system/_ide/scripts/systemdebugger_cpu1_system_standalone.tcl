# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: F:\GitHub\XILINX_BASYS_3\Software\CPU1_system\_ide\scripts\systemdebugger_cpu1_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source F:\GitHub\XILINX_BASYS_3\Software\CPU1_system\_ide\scripts\systemdebugger_cpu1_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
loadhw -hw F:/GitHub/XILINX_BASYS_3/Software/main/export/main/hw/main.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow F:/GitHub/XILINX_BASYS_3/Software/CPU1/Debug/CPU1.elf
bpadd -addr &main
