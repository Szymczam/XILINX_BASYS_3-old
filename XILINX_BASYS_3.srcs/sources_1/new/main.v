`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.02.2022 19:55:44
// Design Name: 
// Module Name: main
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module main(
    input           CLK_100MHz,
    output  [15:0]  led,
    output  [3:0]   an,
    output  [3:0]   an,
    output          dp,
    input           btnC,
    input           btnU,
    input           btnL,
    input           btnR,
    input           btnD,
    input           reset,
    output  [6:0]   seg,
    input           usb_uart_rxd,
    output          usb_uart_txd,
    input           vauxp15  
);






  BASYS3 BASYS3_i
       (.an(an),
        .dp(dp),
        .led(led),
        .push_buttons_4bits_tri_i({btnU,btnL,btnR,btnD}),
        .reset(btnC),
        .seg(seg),
        .sys_clock(CLK_100MHz),
        .usb_uart_rxd(usb_uart_rxd),
        .usb_uart_txd(usb_uart_txd),
        .vauxp15(vauxp15));





    
 
	
	assign led[5] = RST;



endmodule
