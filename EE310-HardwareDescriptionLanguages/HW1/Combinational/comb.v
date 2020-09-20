`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:04:12 02/26/2020 
// Design Name: 
// Module Name:    comb 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module comb(A3,A2,A1,A0,B3,B2,B1,B0,C3,C2,C1,C0);
	input [7:0] A3,A2,A1,A0,B3,B2,B1,B0;
	output reg [7:0] C3,C2,C1,C0;
	reg [7:0] T6, T5, T4, T3, T2, T1, T0;
	
	always @ (*)
	begin
		T0 = (A0*B0) % 256;
		T1 = (((A1*B0)%256) + ((A0*B1)%256)) % 256;
		T2 = (((A2*B0)%256) + ((A1*B1)%256) + ((A0*B2)%256)) % 256;
		T3 = (((A3*B0)%256) + ((A2*B1)%256) + ((A1*B2)%256) + ((A0*B3)%256)) % 256;
		T4 = (((A3*B1)%256) + ((A2*B2)%256) + ((A1*B3)%256)) % 256;
		T5 = (((A3*B2)%256) + ((A2*B3)%256)) % 256;
		T6 = (A3*B3) % 256;

		C3 = T3 % 256;
		C2 = (T2 - T6) % 256;
		C1 = (T1 - T5) % 256;
		C0 = (T0 - T4) % 256;
	end


endmodule
