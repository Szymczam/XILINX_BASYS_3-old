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
    //////////// CLOCK //////////
    input           CLK_100MHz,
    
    //////////// SWITCHES //////////
    input   [15:0]  SW,
    
    //////////// BUTTONS //////////  
    input           btnC,
    input           btnU,
    input           btnL,
    input           btnR,
    input           btnD,
    
    //////////// LEDS //////////
    output  [15:0]  LED,
    
    //////////// UART //////////
    input           UART_RX,
    output          UART_TX,   
    
    //////////// 7-seg Display //////////
    output  [6:0]   SEG,
    output  [3:0]   AN,
    output          DP

);

	//	Clocks
	wire 				clk_10MHz;	
	wire 				clk_1Hz;	
	
	// Buttons
	wire 				rst;
	wire 				n_rst;



//===================================================================                       
//                         Clocks
//===================================================================
	clk_div    clk_div_0	(CLK_100MHz, 0, clk_1Hz),
	           clk_div_1	(clk_10MHz, 0, clk_10Hz);
			   defparam 	clk_div_0.div_by	= 100_000_000;
			   defparam 	clk_div_1.div_by	= 1_000_000;

    clk_wiz_1 clk_wiz_1_0(
        // Clock out ports
        .clk_out1(clk_10MHz),     // output clk_out1
        // Status and control signals
        .reset(rst), // input reset
       // Clock in ports
        .clk_in1(CLK_100MHz)
    );      


//===================================================================                       
//                       Processor CPU1
//===================================================================
CPU_1   CPU_1_i(
        .IO_in1     ({28'd0, btnU, btnL, btnR, btnD}),
        .IO_in2     (0),
        .IO_out1    ({31'd0, LED[2]}),
        .IO_out2    (IO_out2),
        .UART_RX1   (UART_RX),
        .UART_TX1   (UART_TX),
        .clk_in1    (CLK_100MHz),
        .reset      (btnC)
);

assign rst      = btnC;
assign LED[15]  = btnC;
assign LED[0]   = clk_1Hz;
assign LED[1]   = clk_10Hz;


endmodule
