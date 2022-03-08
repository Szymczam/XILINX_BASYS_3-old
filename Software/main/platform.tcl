# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct F:\GitHub\XILINX_BASYS_3\Software\main\platform.tcl
# 
# OR launch xsct and run below command.
# source F:\GitHub\XILINX_BASYS_3\Software\main\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {main}\
-hw {F:\GitHub\XILINX_BASYS_3\main.xsa}\
-out {F:/GitHub/XILINX_BASYS_3/Software}

platform write
domain create -name {standalone_microblaze_0} -display-name {standalone_microblaze_0} -os {standalone} -proc {microblaze_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {main}
platform generate -quick
platform generate
platform generate
platform active {main}
platform config -updatehw {F:/GitHub/XILINX_BASYS_3/main.xsa}
platform generate -domains 
platform config -updatehw {F:/GitHub/XILINX_BASYS_3/main.xsa}
platform generate -domains 
platform config -updatehw {F:/GitKraken/XILINX_BASYS_3/main.xsa}
platform generate -domains 
platform generate
platform active {main}
platform config -updatehw {F:/GitKraken/XILINX_BASYS_3/main.xsa}
platform generate -domains 
platform active {main}
platform config -updatehw {F:/GitKraken/XILINX_BASYS_3/main.xsa}
platform generate -domains 
platform config -updatehw {F:/GitKraken/XILINX_BASYS_3/main.xsa}
platform generate -domains 
platform active {main}
platform config -updatehw {F:/GitKraken/XILINX_BASYS_3/main.xsa}
platform generate -domains 
