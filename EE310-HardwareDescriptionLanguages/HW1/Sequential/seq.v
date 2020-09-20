`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:00:08 02/26/2020 
// Design Name: 
// Module Name:    seq 
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
module seq(clk, rst, start, A3, A2, A1, A0, B3, B2, B1, B0, finish, C3, C2, C1, C0);
	input clk, rst, start;
	input [7:0] A3, A2, A1, A0, B3, B2, B1, B0;
	output reg finish;
	output reg [7:0] C3, C2, C1, C0;
	
	reg [7:0] T6, T5, T4, T3, T2, T1, T0;
	reg [5:0] cnt;
	reg [7:0] mult, add, sub, in1, in2;

	always @(*)
	begin
		mult = (in1 * in2) % 256;
		add = (in1 + in2) % 256;
		sub = (in1 - in2) % 256;
	end

	always @(posedge clk or posedge rst)
	begin
		if(rst == 1)
		begin
			C3 <= 0;
			C2 <= 0;
			C1 <= 0;
			C0 <= 0;
			T6 <= 0;
			T5 <= 0;
			T4 <= 0;
			T3 <= 0;
			T2 <= 0;
			T1 <= 0;
			T0 <= 0;
			cnt <= 0;
			finish <= 0;
		end
		else
		begin
			if(finish == 0)
			begin
				if(start)
				begin
					
					if(cnt == 0)
					begin
						in1 <= A0;
						in2 <= B0;
						cnt <= 1;
					end
					else if(cnt == 1)
					begin
						T0 <= mult;
						in1 <= A1;
						in2 <= B0;
						cnt <= 2;
					end
					else if(cnt == 2)
					begin
						T1 <= mult;
						in1 <= A0;
						in2 <= B1;
						cnt <= 3;
					end
					else if(cnt == 3)
					begin
						in1 <= T1;
						in2 <= mult;
						cnt <= 4;
					end
					else if(cnt == 4)
					begin
						T1 <= add;
						in1 <= A2;
						in2 <= B0;
						cnt <= 5;
					end
					else if(cnt == 5)
					begin
						T2 <= mult;
						in1 <= A1;
						in2 <= B1;
						cnt <= 6;
					end
					else if(cnt == 6)
					begin
						in1 <= T2;
						in2 <= mult;
						cnt <= 7;
					end
					else if(cnt == 7)
					begin
						T2 <= add;
						in1 <= A0;
						in2 <= B2;
						cnt <= 8;
					end
					else if(cnt == 8)
					begin
						in1 <= T2;
						in2 <= mult;
						cnt <= 9;
					end
					else if(cnt == 9)
					begin
						T2 <= add;
						in1 <= A3;
						in2 <= B0;
						cnt <= 10;
					end
					else if(cnt == 10)
					begin
						T3 <= mult;
						in1 <= A2;
						in2 <= B1;
						cnt <= 11;
					end
					else if(cnt == 11)
					begin
						in1 <= T3;
						in2 <= mult;
						cnt <= 12;
					end
					else if(cnt == 12)
					begin
						T3 <= add;
						in1 <= A1;
						in2 <= B2;
						cnt <= 13;
					end
					else if(cnt == 13)
					begin
						in1 <= T3;
						in2 <= mult;
						cnt <= 14;
					end
					else if(cnt == 14)
					begin
						T3 <= add;
						in1 <= A0;
						in2 <= B3;
						cnt <= 15;
					end
					else if(cnt == 15)
					begin
						in1 <= T3;
						in2 <= mult;
						cnt <= 16;
					end
					else if(cnt == 16)
					begin
						T3 <= add;
						in1 <= A3;
						in2 <= B1;
						cnt <= 17;
					end
					else if(cnt == 17)
					begin
						T4 <= mult;
						in1 <= A2;
						in2 <= B2;
						cnt <= 18;
					end
					else if(cnt == 18)
					begin
						in1 <= T4;
						in2 <= mult;
						cnt <= 19;
					end
					else if(cnt == 19)
					begin
						T4 <= add;
						in1 <= A1;
						in2 <= B3;
						cnt <= 20;
					end
					else if(cnt == 20)
					begin
						in1 <= T4;
						in2 <= mult;
						cnt <= 21;
					end
					else if(cnt == 21)
					begin
						T4 <= add;
						in1 <= A3;
						in2 <= B2;
						cnt <= 22;
					end
					else if(cnt == 22)
					begin
						
						T5 <= mult;
						in1 <= A2;
						in2 <= B3;
						cnt <= 23;
					end
					else if(cnt == 23)
					begin
						in1 <= T5;
						in2 <= mult;
						cnt <= 24;
					end
					else if(cnt == 24)
					begin
						T5 <= add;
						in1 <= A3;
						in2 <= B3;
						cnt <= 25;
					end
					else if(cnt == 25)
					begin
						T6 <= mult;
						C3 <= T3;
						in1 <= T1;
						in2 <= T5;
						cnt <= 26;
					end
					else if(cnt == 26)
					begin
						C1 <= sub;
						in1 <= T0;
						in2 <= T4;
						cnt <= 27;
					end
					else if(cnt == 27)
					begin
						C0 <= sub;
						in1 <= T2;
						in2 <= T6;
						cnt <= 28;
					end
					else
					begin
						C2 <= sub;
						cnt <= 0;
						finish <= 1;
					end
				end
				else
				begin
					C3 <= 0;
					C2 <= 0;
					C1 <= 0;
					C0 <= 0;
					T6 <= 0;
					T5 <= 0;
					T4 <= 0;
					T3 <= 0;
					T2 <= 0;
					T1 <= 0;
					T0 <= 0;
					cnt <= 0;
					finish <= 0;
				end
			end
		end
	end
	
endmodule
