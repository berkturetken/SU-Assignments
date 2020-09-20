`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:59:54 03/06/2020 
// Design Name: 
// Module Name:    PingPongTop 
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
module PingPongTop(clk, rst, BTN_West, BTN_North, BTN_East, SW, LED, Data_Out, LCD_Control);
	
	input clk, rst;
	input BTN_West, BTN_North, BTN_East;
	input [3:0] SW;
	output [7:0] LED;
	output [3:0] Data_Out;
	output [3:0] LCD_Control;
	
	wire BTN_North_corr, BTN_East_corr, BTN_West_corr;
	
	reg [127:0] First_Line, Second_Line;
	
	reg start_round;
	wire player_1, player_2;
	
	reg[3:0] count;
	
	parameter idle=0, score_0_0 = 1, score_0_1 = 2, score_1_0 = 3, score_1_1 = 4, score_2_0 = 5, score_2_1 = 6, score_2_2 = 7, score_1_2 = 8, score_0_2 = 9, score_3_0 = 10, score_3_1 = 11, score_3_2 = 12,		score_2_3 = 13, score_1_3 = 14, score_0_3 = 15, score_4_0 = 16, score_4_1 = 17, score_1_4 = 18, score_0_4 = 19, score_5_0 = 20, score_0_5 = 21, names = 22, temp = 23,		space = 8'b00100000, P = 8'b01010000, I = 8'b01001001, N = 8'b01001110, G = 8'b01000111, O = 8'b01001111, A = 8'b01000001, M = 8'b01001101, E = 8'b01000101, colon = 8'b00111010,		num_0 = 8'b00110000, num_1 = 8'b00110001, num_2 = 8'b00110010, num_3 = 8'b00110011, num_4 = 8'b00110100, num_5 = 8'b00110101,
		W = 8'b01010111, i = 8'b01101001, n = 8'b01101110, e = 8'b01100101, r = 8'b01110010;
	
	reg [4:0] currentstate;
	reg [4:0] nextstate;
	
	always @ (posedge clk or posedge rst)
	begin
		if(rst == 1)
			currentstate <= idle;
		else
			currentstate <= nextstate;
	end
	
	always @ (*)
	begin
		case(currentstate)
		idle:begin
			First_Line = {space, P, I, N, G, space, P, O, N, G, space, G, A, M, E, space};
			Second_Line = {16{space}};
			start_round = 1;
			if(BTN_North_corr == 1)
			begin
				First_Line = {16{space}};
				Second_Line = {16{space}};
				count = 0;
				nextstate = names;
			end
			else
				nextstate = idle;
		end
		
		names:begin
			if(count == 0) begin
				if(BTN_North_corr == 1) begin
					First_Line[127:124] = SW[3:0];
					count = 1;
					end
			end
			else if(count == 1) begin
				if(BTN_North_corr == 1) begin
					First_Line[123:120] = SW[3:0];
					count = 2;
				end
			end
			else if(count == 2) begin
				if(BTN_North_corr == 1) begin
					First_Line[119:116] = SW[3:0];
					count = 3;
				end
			end
			else if(count == 3) begin
				if(BTN_North_corr == 1) begin
					First_Line[115:112] = SW[3:0];
					count = 4;
				end
			end
			else if(count == 4) begin
				if(BTN_North_corr == 1) begin
					First_Line[111:108] = SW[3:0];
					count = 5;
				end
			end
			else if(count == 5) begin
				if(BTN_North_corr == 1) begin
					First_Line[107:104] = SW[3:0];
					count = 6;
				end
			end
			else if(count == 6) begin
				if(BTN_North_corr == 1) begin
					Second_Line[127:124] = SW[3:0];
					count = 7;
				end
			end
			else if(count == 7) begin
				if(BTN_North_corr == 1) begin
					Second_Line[123:120] = SW[3:0];
					count = 8;
				end
			end
			else if(count == 8) begin
				if(BTN_North_corr == 1) begin
					Second_Line[119:116] = SW[3:0];
					count = 9;
				end
			end
			else if(count == 9) begin
				if(BTN_North_corr == 1) begin
					Second_Line[115:112] = SW[3:0];
					count = 10;
				end
			end
			else if(count == 10) begin
				if(BTN_North_corr == 1) begin
					Second_Line[111:108] = SW[3:0];
					count = 11;
				end
			end
			else if(count == 11) begin
				if(BTN_North_corr == 1) begin
					Second_Line[107:104] = SW[3:0];
					nextstate = score_0_0;
				end
			end
			else
				nextstate = temp;	
		end
		
		temp: begin
			First_Line = {16{A}};
			Second_Line = {16{A}};
			count = 0;
		end
		
		score_0_0: begin
			First_Line[103:88] = {colon, num_0};
			Second_Line[103:88] = {colon, num_0};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_1_0;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_0_1;
					start_round = 0;
				end
			end
		end
		score_0_1: begin
			First_Line[103:88] = {colon, num_0};
			Second_Line[103:88] = {colon, num_1};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_1_1;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_0_2;
					start_round = 0;
				end
			end
		end
		score_1_0: begin
			First_Line[103:88] = {colon, num_1};
			Second_Line[103:88] = {colon, num_0};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_2_0;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_1_1;
					start_round = 0;
				end
			end
		end
		score_1_1: begin
			First_Line[103:88] = {colon, num_1};
			Second_Line[103:88] = {colon, num_1};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_2_1;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_1_2;
					start_round = 0;
				end
			end
		end
		score_2_0: begin
			First_Line[103:88] = {colon, num_2};
			Second_Line[103:88] = {colon, num_0};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_3_0;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_2_1;
					start_round = 0;
				end
			end
		end
		score_2_1: begin
			First_Line[103:88] = {colon, num_2};
			Second_Line[103:88] = {colon, num_1};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_3_1;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_2_2;
					start_round = 0;
				end
			end
		end
		score_2_2: begin
			First_Line[103:88] = {colon, num_2};
			Second_Line[103:88] = {colon, num_2};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_3_2;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_2_3;
					start_round = 0;
				end
			end
		end
		score_1_2: begin
			First_Line[103:88] = {colon, num_1};
			Second_Line[103:88] = {colon, num_2};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_2_2;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_1_3;
					start_round = 0;
				end
			end
		end
		score_0_2: begin
			First_Line[103:88] = {colon, num_0};
			Second_Line[103:88] = {colon, num_2};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_1_2;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_0_3;
					start_round = 0;
				end
			end
		end
		score_3_0: begin
			First_Line[103:88] = {colon, num_3};
			Second_Line[103:88] = {colon, num_0};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_4_0;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_3_1;
					start_round = 0;
				end
			end
		end
		score_3_1: begin
			First_Line[103:88] = {colon, num_3};
			Second_Line[103:88] = {colon, num_1};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_4_1;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_3_2;
					start_round = 0;
				end
			end
		end
		score_3_2: begin
			First_Line[103:88] = {colon, num_3};
			Second_Line[103:88] = {colon, num_2};
			First_Line[87:32] = {space, W, i, n, n, e, r};
			if(BTN_North_corr == 1)
				nextstate = idle;
		end
		score_2_3: begin
			First_Line[103:88] = {colon, num_2};
			Second_Line[103:88] = {colon, num_3};
			Second_Line[87:32] = {space, W, i, n, n, e, r};
			if(BTN_North_corr == 1)
				nextstate = idle;
		end
		score_1_3: begin
			First_Line[103:88] = {colon, num_1};
			Second_Line[103:88] = {colon, num_3};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_2_3;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_1_4;
					start_round = 0;
				end
			end
		end
		score_0_3: begin
			First_Line[103:88] = {colon, num_0};
			Second_Line[103:88] = {colon, num_3};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_1_3;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_0_4;
					start_round = 0;
				end
			end
		end
		score_4_0: begin
			First_Line[103:88] = {colon, num_4};
			Second_Line[103:88] = {colon, num_0};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_5_0;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_4_1;
					start_round = 0;
				end
			end
		end
		score_4_1: begin
			First_Line[103:88] = {colon, num_4};
			Second_Line[103:88] = {colon, num_1};
			First_Line[87:32] = {space, W, i, n, n, e, r};
			if(BTN_North_corr == 1)
				nextstate = idle;
		end
		score_1_4: begin
			First_Line[103:88] = {colon, num_1};
			Second_Line[103:88] = {colon, num_4};
			Second_Line[87:32] = {space, W, i, n, n, e, r};
			if(BTN_North_corr == 1)
				nextstate = idle;
		end
		score_0_4: begin
			First_Line[103:88] = {colon, num_0};
			Second_Line[103:88] = {colon, num_4};
			if(BTN_North_corr == 1)
			begin
				start_round = 1;
				if(player_1 == 1)
				begin
					nextstate = score_1_4;
					start_round = 0;
				end
				else if(player_2 == 1)
				begin
					nextstate = score_0_5;
					start_round = 0;
				end
			end
		end
		score_5_0: begin
			First_Line[103:88] = {colon, num_5};
			Second_Line[103:88] = {colon, num_0};
			First_Line[87:32] = {space, W, i, n, n, e, r};
			if(BTN_North_corr == 1)
				nextstate = idle;
		end
		score_0_5: begin
			First_Line[103:88] = {colon, num_0};
			Second_Line[103:88] = {colon, num_5};
			Second_Line[87:32] = {space, W, i, n, n, e, r};
			if(BTN_North_corr == 1)
				nextstate = idle;
		end
		
		endcase
	end
	
	LCDI d0(clk, First_Line, Second_Line, Data_Out, LCD_Control);
	round r0(.clk(clk), .rst(rst), .BTN_West(BTN_West_corr), .BTN_East(BTN_East_corr), .LED(LED), .start_round(start_round), .player_1(player_1), .player_2(player_2));
	debouncer db1(clk, BTN_North, rst, BTN_North_corr);
	debouncer db2(clk, BTN_East, rst, BTN_East_corr);
	debouncer db3(clk, BTN_West, rst, BTN_West_corr);
	
endmodule

module round(clk, rst, BTN_West, BTN_East, LED, start_round, player_1, player_2);

	input clk, rst, BTN_West, BTN_East, start_round;
	output reg [7:0] LED;
	output reg player_1, player_2;

	reg[3:0] current_state, next_state;
	reg start_timer;
	wire time_up;
	
	parameter led_4_f = 0, led_3_f = 1, led_2_f = 2, led_1_f = 3, led_0 = 4, led_1_s = 5, led_2_s = 6, led_3_s = 7,
	led_4_s = 8, led_5_f = 9, led_6_f = 10, led_7 = 11, led_6_s = 12, led_5_s = 13, idle = 14;

	always @ (posedge clk or posedge rst)
	begin
		if(rst == 1)
			current_state <= idle;
		else
		begin
			if(start_round == 1)
				current_state <= next_state;
			else
				current_state <= idle;
		end
	
	/*
		if(start_round == 1)
		begin
			if(rst == 0)
				current_state <= idle;
			else
				current_state <= next_state;
		end
		else
			current_state <= idle;*/
	end

	always @ (*)
	begin
		if(start_round == 1)
		begin
			case(current_state)
			idle: begin
				LED = 7'b00000000;
				next_state = led_4_f;
			end
			led_4_f: begin
				LED[5] = 1'b0;
				LED[4] = 1'b1;
				start_timer = 1'b1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_3_f;
			end
			led_3_f: begin
				LED[4] = 1'b0;
				LED[3] = 1'b1;
				start_timer = 1'b1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_2_f;
			end
			led_2_f: begin
				LED[3] = 1'b0;
				LED[2] = 1'b1;
				start_timer = 1'b1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_1_f;
			end
			led_1_f: begin
				LED[2] = 1'b0;
				LED[1] = 1'b1;
				start_timer = 1'b1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_0;
			end
			led_0: begin
				LED[1] = 1'b0;
				LED[0] = 1'b1;
				start_timer = 1'b1;
				if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
				begin
					player_1 = 1'b1;
					player_2 = 1'b0;
				end
				else if(BTN_East == 1)
				begin
					next_state = led_1_s;
				end
			end
			led_1_s: begin
				LED[0] = 0;
				LED[1] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_2_s;
			end
			led_2_s: begin
				LED[1] = 0;
				LED[2] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_3_s;
			end
			led_3_s: begin
				LED[2] = 0;
				LED[3] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_4_s;
			end
			led_4_s: begin
				LED[3] = 0;
				LED[4] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_5_f;
			end
			led_5_f: begin
				LED[4] = 0;
				LED[5] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_6_f;
			end
			led_6_f: begin
				LED[5] = 0;
				LED[6] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_7;
			end
			led_7: begin
				LED[6] = 0;
				LED[7] = 1;
				start_timer = 1;
				if(BTN_West == 1)
				begin
					next_state = led_6_s;
				end
				else if(time_up == 1'b1)
				begin
					player_1 = 1'b0;
					player_2 = 1'b1;
				end
				else if(BTN_East == 1)
				begin
					player_1 = 1'b1;
					player_2 = 1'b0;
				end
			end
			led_6_s: begin
				LED[7] = 0;
				LED[6] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_5_s;
			end
			led_5_s: begin
				LED[6] = 0;
				LED[5] = 1;
				start_timer = 1;
				if(BTN_East == 1)
				begin
					player_1 = 1;
					player_2 = 0;
				end
				else if(BTN_West == 1)
				begin
					player_1 = 0;
					player_2 = 1;
				end
				else if(time_up == 1'b1)
					next_state = led_4_f;
			end
			
			endcase
		end
		else
			next_state = idle;
	end

	timer my_timer(clk, rst, start_timer, time_up);

endmodule

module timer(clk, rst, start_timer, time_up);


input  clk, rst;
input  start_timer;
output reg time_up;

reg [31:0] counter;

always @(posedge clk or posedge rst) begin
	if(rst) begin
		counter <= 0;
		time_up <= 0;
	end
	else begin
		if(start_timer) begin
			if(counter < 32'd80)
				counter <= counter + 1;
			else 
				counter <= counter;
		end
		else begin
			counter <= 0;
		end
		
		time_up <= (counter == 32'd80);
	end
end

endmodule
