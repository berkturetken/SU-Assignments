`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:18:38 05/10/2020 
// Design Name: 
// Module Name:    Sobel 
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
module Sobel(clk, rst, start, pixel_in, busy, finish, pixel_out);

input clk, rst;
input start;
input [7:0] pixel_in;
output reg busy, finish;
output reg [7:0] pixel_out;

//BRAM Interface of input image
reg wea_in;
reg [15:0] waddr_in;
reg signed [8:0] w_in;
reg [15:0] raddr_in;
wire signed [8:0] r_in;

//BRAM Interface of output image
reg wea_out;
reg [15:0] waddr_out;
reg signed [8:0] w_out;
reg [15:0] raddr_out;
wire signed [8:0] r_out;

reg [16:0] inp_cntr, opr_cntr, out_cntr;
reg [3:0] itr_cntr;
reg signed [10:0] Sx, Sy;
reg [1:0] curr_state, next_state;
reg go_to_state_2;

always @ (posedge clk or posedge rst)
begin
	if(rst)
		curr_state <= 0;
	else
		curr_state <= next_state;
end

always @ (*)
begin
	case(curr_state)
	0: begin //idle state
		if(busy == 0 && start == 1)
			next_state = 1;
		else
			next_state = 0;
	end
	1: begin //taking input and storing it in the BRAM
		if(go_to_state_2 == 1)
			next_state = 2;
		else
			next_state = 1;
	end
	2: begin //reading input BRAM and processing it, then writing it to the output BRAM
		if(finish == 1)
			next_state = 3;
		else
			next_state = 2;
	end
	3: begin //reading output BRAM and giving output
		if(busy == 0)
			next_state = 0;
		else
			next_state = 3;
	end
	endcase
end

always @ (*)
begin
	if(curr_state == 1)
		wea_in = 1;
	else
		wea_in = 0;
	
	if(curr_state == 2)
		wea_out = 1;
	else
		wea_out = 0;
end

always @ (posedge clk or posedge rst)
begin
	if(rst)
	begin
		inp_cntr <= 0;
		opr_cntr <= 0;
		itr_cntr <= 0;
		out_cntr <= 0;
		Sx <= 0;
		Sy <= 0;
		waddr_in <= 0;
		raddr_in <= 0;
		raddr_out <= 0;
		waddr_out <= 0;
		w_in <= 0;
		w_out <= 0;
		busy <= 0;
		finish <= 0;
		pixel_out <= 0;
		go_to_state_2 <= 0;
	end
	else
	begin
		if(curr_state == 1)
		begin
			busy <= 1;
			waddr_in <= inp_cntr;
			w_in <= pixel_in;
			if(inp_cntr == 65535)
				go_to_state_2 <= 1;
			else
				inp_cntr <= inp_cntr + 1;
		end
		else if(curr_state == 2)
		begin
			if(opr_cntr == 0) //top-left corner
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr + 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx + r_in * (-1) + r_in * (-2);
					Sy <= Sy + r_in * 1 + r_in * 2;
					raddr_in <= opr_cntr + 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx + r_in * 3;
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr + 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * (-3);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * 1;
					Sy <= Sy + r_in * (-1);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else if(opr_cntr == 255) //top-right corner
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx + r_in * (-3);
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr + 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx + r_in * 3;
					Sy <= Sy + r_in * 3;
					raddr_in <= opr_cntr + 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx - r_in;
					Sy <= Sy - r_in;
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in;
					Sy <= Sy + r_in * (-3);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else if(opr_cntr == 65280) //bottom-left corner
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr - 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * 3;
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx + r_in;
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr + 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in * (-3);
					Sy <= Sy + r_in * (-3);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * 3;
					Sy <= Sy + r_in * (-1);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else if(opr_cntr == 65535) //bottom-right corner
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr - 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx - r_in;
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr - 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx + r_in;
					Sy <= Sy + r_in * 3;
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in * (-3);
					Sy <= Sy + r_in * (-1);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * 3;
					Sy <= Sy + r_in * (-3);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					finish <= 1;
					itr_cntr <= 0;
					raddr_out <= out_cntr;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else if(0 < opr_cntr && opr_cntr < 255) //top line
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx + r_in * (-3);
					Sy <= Sy + r_in * (1);
					raddr_in <= opr_cntr + 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx;
					Sy <= Sy + r_in * (2);
					raddr_in <= opr_cntr + 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in * (3);
					Sy <= Sy + r_in * (1);
					raddr_in <= opr_cntr + 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * (-1);
					raddr_in <= opr_cntr + 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					Sx <= Sx;
					Sy <= Sy + r_in * (-2);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 7)
				begin
					Sx <= Sx + r_in * (1);
					Sy <= Sy + r_in * (-1);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 8)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else if(65280 < opr_cntr && opr_cntr < 65535) //bottom line
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr - 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * (1);
					raddr_in <= opr_cntr - 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx;
					Sy <= Sy + r_in * (2);
					raddr_in <= opr_cntr - 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in * (1);
					Sy <= Sy + r_in * (1);
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * (-3);
					Sy <= Sy + r_in * (-1);
					raddr_in <= opr_cntr + 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					Sx <= Sx;
					Sy <= Sy + r_in * (-2);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 7)
				begin
					Sx <= Sx + r_in * (3);
					Sy <= Sy + r_in * (-1);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 8)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else if(opr_cntr % 256 == 0) //left line
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr - 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * (3);
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx + r_in;
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr + 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in * (-2);
					Sy <= Sy;
					raddr_in <= opr_cntr + 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * (2);
					Sy <= Sy;
					raddr_in <= opr_cntr + 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * (-3);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 7)
				begin
					Sx <= Sx + r_in * (1);
					Sy <= Sy + r_in * (-1);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 8)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else if(opr_cntr % 256 == 255) //right line
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr - 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr - 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx + r_in;
					Sy <= Sy + r_in * (3);
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in * (-2);
					Sy <= Sy;
					raddr_in <= opr_cntr + 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * (2);
					Sy <= Sy;
					raddr_in <= opr_cntr + 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * (-1);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 7)
				begin
					Sx <= Sx + r_in * (1);
					Sy <= Sy + r_in * (-3);
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 8)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
			else //every other pixel in the image
			begin
				if(itr_cntr == 0)
				begin
					Sx <= 0;
					Sy <= 0;
					raddr_in <= opr_cntr - 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 1)
				begin
					raddr_in <= opr_cntr - 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 2)
				begin
					Sx <= Sx - r_in;
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr - 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 3)
				begin
					Sx <= Sx;
					Sy <= Sy + r_in * (2);
					raddr_in <= opr_cntr - 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 4)
				begin
					Sx <= Sx + r_in;
					Sy <= Sy + r_in;
					raddr_in <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 5)
				begin
					Sx <= Sx + r_in * (-2);
					Sy <= Sy;
					raddr_in <= opr_cntr + 1;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 6)
				begin
					Sx <= Sx;
					Sy <= Sy;
					raddr_in <= opr_cntr + 255;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 7)
				begin
					Sx <= Sx + r_in * (2);
					Sy <= Sy;
					raddr_in <= opr_cntr + 256;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 8)
				begin
					Sx <= Sx + r_in * (-1);
					Sy <= Sy + r_in * (-1);
					raddr_in <= opr_cntr + 257;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 9)
				begin
					Sx <= Sx;
					Sy <= Sy + r_in * (-2);
					waddr_out <= opr_cntr;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 10)
				begin
					Sx <= Sx + r_in;
					Sy <= Sy - r_in;
					itr_cntr <= itr_cntr + 1;
				end
				else if(itr_cntr == 11)
				begin
					if(Sx < 0 && Sy < 0)
					begin
						if(((-1) * Sx + (-1) * Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sx < 0)
					begin
						if(((-1) * Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else if(Sy < 0)
					begin
						if(((-1) * Sy + Sx) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					else
					begin
						if((Sx + Sy) >= 128)
							w_out <= 0;
						else
							w_out <= 255;
					end
					opr_cntr <= opr_cntr + 1;
					itr_cntr <= 0;
				end
				else
				begin
					itr_cntr <= 0;
				end
			end
		end
		else if(curr_state == 3)
		begin
			finish <= 0;
			raddr_out <= out_cntr + 1;
			pixel_out <= r_out;
			if(out_cntr == 65535)
				busy <= 0;
			else
				out_cntr <= out_cntr + 1;
		end
		else
		begin
			inp_cntr <= 0;
			opr_cntr <= 0;
			itr_cntr <= 0;
			out_cntr <= 0;
			Sx <= 0;
			Sy <= 0;
			waddr_in <= 0;
			raddr_in <= 0;
			raddr_out <= 0;
			waddr_out <= 0;
			w_in <= 0;
			w_out <= 0;
			busy <= 0;
			finish <= 0;
			pixel_out <= 0;
			go_to_state_2 <= 0;
		end
	end
end


//Module Instantiations
BRAM_Unit b0(.clka(clk),
					.wea(wea_in),
					.addra(waddr_in),
					.dina(w_in),
					.clkb(clk),
					.addrb(raddr_in),
					.doutb(r_in)
					);

BRAM_Unit b1(.clka(clk),
					.wea(wea_out),
					.addra(waddr_out),
					.dina(w_out),
					.clkb(clk),
					.addrb(raddr_out),
					.doutb(r_out)
					);

endmodule
