`timescale 1ns / 1ps

module IntMul(clk, rst, len_valid, len_in, in_valid, data_in, busy, out_valid, data_out);
	
	input clk, rst;
	input len_valid, in_valid;
	input [3:0] len_in;
	input [15:0] data_in;
	output reg busy, out_valid;
	output reg [15:0] data_out;

	reg [2:0] curr_state;	//total: 8 states, we need 5 states
	reg [2:0] next_state;	//total: 8 states, we need 5 states
	reg [3:0] k;				//temp input length
	reg [4:0] inp_cntr;
	reg [3:0] itr_cntr;
	reg [3:0] itr_cntr2;
	reg [4:0] itr_cntr3;
	reg [3:0] opr_cntr;
	reg [18:0] p;
	reg carry;
	reg [17:0] t_h;
	reg [15:0] t_l;
	
	// DSP1 interface
	reg [16:0] dsp_a_in;
	reg [16:0] dsp_b_in;
	reg [18:0] dsp_p_in;
	reg dsp_carry_in;
	wire [34:0] dsp_out;
	
	// DSP2 interface
	reg [18:0] dsp2_a_in;
	reg [16:0] dsp2_d_in;
	wire [18:0] dsp2_out;
	
	//BRAM Interface
	reg [3:0] waddr;
	reg wea;
	reg [15:0] a_in;
	reg [3:0] raddr;
	wire [15:0] a_out;
	
	//BRAM2 Interface
	reg [3:0] waddr2;
	reg wea2;
	reg [15:0] b_in;
	reg [3:0] raddr2;
	wire [15:0] b_out;
	
	//BRAM3 Interface
	reg [3:0] waddr3;
	reg wea3;
	reg [15:0] c_in;
	reg [3:0] raddr3;
	wire [15:0] c_out;
	
	//Reset
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
		0: begin
			if(busy == 0)
				begin
				if(len_valid)
					next_state = 1;
				else
					next_state = 0;
			end
			else
				if(in_valid)
					next_state = 2;
				else
					next_state = 0;
		end
		1: begin
			next_state = 0;
		end
		2: begin
			if(inp_cntr == k*2)
				next_state = 3;
			else
				next_state = 2;
		end
		3: begin
			if((itr_cntr == k-1) && (itr_cntr2 == k) && (opr_cntr == 14))
			begin
				next_state = 4;
			end
			else
				next_state = 3;
		end
		4: begin
			//itr_cntr3 = 0;		//previously, it is uncommented...
			if(busy == 1)
				next_state = 4;
			else
				next_state = 0;
		end
		endcase
	end
	
	//Length
	always @ (posedge clk or posedge rst) begin
		if(rst)
		begin
			k <= 0;
			busy <= 0;
			data_out <= 0;
			itr_cntr <= 0;
			itr_cntr2 <= 0;
			itr_cntr3 <= 0;
			opr_cntr <= 0;
			out_valid <= 0;
		end
		else 
		begin
			if(curr_state == 1)
			begin
				k <= len_in;
				busy <= 1;
			end
			else if(curr_state == 3) 
			begin
				itr_cntr3 <= itr_cntr + itr_cntr2;
				if(itr_cntr2 < k)
				begin
					if(opr_cntr == 9)
					begin
						itr_cntr2 <= itr_cntr2 + 1;
						if(itr_cntr2 == k-1)
							opr_cntr <= opr_cntr + 1;
						else
							opr_cntr <= 0;
					end
					else
						opr_cntr <= opr_cntr + 1;	
				end
				else if((itr_cntr == k-1) && (itr_cntr2 == k) && (opr_cntr == 14))
				begin
					out_valid <= 1;
					itr_cntr3 <= 0;
				end
				else
				begin
					if(opr_cntr == 14)
					begin
						itr_cntr2 <= 0;
						itr_cntr <= itr_cntr + 1;
						opr_cntr <= 0;
					end
					else
						opr_cntr <= opr_cntr + 1;
				end
			end
			else if(curr_state == 4 && busy)
			begin
				out_valid <= 0;
				data_out <= c_out;
				itr_cntr3 <= itr_cntr3 + 1;
				if(itr_cntr3 == 2*k + 1)
				begin
					busy <= 0;
					data_out <= 0;
				end
			end
			else
			begin
				itr_cntr <= 0;
				itr_cntr2 <= 0;
				itr_cntr3 <= itr_cntr3;
				opr_cntr <= 0;
			end
		end
	end
	
	//inp_cntr control
	always @(posedge clk or posedge rst) begin
		if(rst) begin
			inp_cntr <= 0;
		end
		else begin
			if(curr_state == 2)
				inp_cntr <= inp_cntr + 1;
			else
				inp_cntr <= 0;
		end
	end
	
	//BRAM write
	always @(posedge clk or posedge rst) begin
		if(rst) begin
			a_in <= 0;
			wea <= 0;
			waddr <= 0;
			b_in <= 0;
			wea2 <= 0;
			waddr2 <= 0;
			c_in <= 0;
			wea3 <= 0;
			waddr3 <= 0;
			carry <= 0;
			c_in <= 0;
		end
		else begin
			if(curr_state == 2)
			begin
				wea3 <= 1;
				waddr3 <= inp_cntr;
				c_in <= 0;
				if(inp_cntr < k)
				begin
					a_in <= data_in;
					wea <= 1;
					waddr <= inp_cntr;
				end
				else
				begin
					b_in <= data_in;
					wea2 <= 1;
					waddr2 <= inp_cntr-k;
				end
			end
			else if(curr_state == 3)
			begin
				waddr3 <= itr_cntr3;
				if(opr_cntr == 9)
				begin
					wea3 <= 1;
					{carry, c_in} <= dsp2_out[16:0];
				end
				else if(opr_cntr == 14)
				begin
					wea3 <= 1;
					c_in <= dsp2_out[15:0];
					carry <= 0;
				end
				else
				begin
					wea3 <= 0;
					carry <= carry;
				end
			end
			else 
			begin
				a_in <= 0;
				wea <= 0;
				waddr <= 0;
				b_in <= 0;
				wea2 <= 0;
				waddr2 <= 0;
			end	
		end
	end
	/*
	//Operation
	always @ (posedge clk or posedge rst) begin
		if(rst) 
		begin
			itr_cntr <= 0;
			itr_cntr2 <= 0;
			itr_cntr3 <= 0;
			opr_cntr <= 0;
		end
		else 
		begin
			if(curr_state == 3) 
			begin
				itr_cntr3 <= itr_cntr + itr_cntr2;
				if(itr_cntr2 < k)
				begin
					if(opr_cntr == 9)
					begin
						itr_cntr2 <= itr_cntr2 + 1;
						if(itr_cntr2 == k-1)
							opr_cntr <= opr_cntr + 1;
						else
							opr_cntr <= 0;
					end
					else
						opr_cntr <= opr_cntr + 1;	
				end
				else
				begin
					if(opr_cntr == 14)
					begin
						itr_cntr2 <= 0;
						itr_cntr <= itr_cntr + 1;
						opr_cntr <= 0;
					end
					else
						opr_cntr <= opr_cntr + 1;
				end
			end
			else
			begin
				itr_cntr <= 0;
				itr_cntr2 <= 0;
				itr_cntr3 <= itr_cntr3;
				opr_cntr <= 0;
			end
		end
	end
	*/
	//BRAM read (opr_cntr == 0)
	//output is available at (opr_cntr == 1)
	always @ (*) begin
		raddr = itr_cntr;
		raddr2 = itr_cntr2;
		raddr3 = itr_cntr3;
	end	
	
	// DSP1 input
	always @ (posedge clk or posedge rst) begin
	   if(rst) 
		begin
			dsp_a_in <= 0;
			dsp_b_in <= 0;
			dsp_p_in <= 0;
			dsp_carry_in <= 0;
		end
		else 
		begin
			if(opr_cntr == 1)
			begin
				dsp_a_in <= a_out;
				dsp_b_in <= b_out;
				dsp_p_in <= p;
				dsp_carry_in <= carry;
			end
		end
	end

	// DSP1 output
	always @ (posedge clk or posedge rst) begin
	   if(rst) 
		begin
			p <= 0;
			t_h <= 0;
			t_l <= 0;
		end
		else 
		begin
			if(curr_state == 3)
			begin
				if(opr_cntr == 4 && itr_cntr2 < k)
				begin
					t_h <= dsp_out[33:16];
					t_l <= dsp_out[15:0];
					p <= dsp_out[33:16];
				end
				else if(opr_cntr == 14)
				begin
					p <= 0;
				end
				else
				begin
					t_h <= t_h;
					t_l <= t_l;
				end
			end
		end
	end
	
	//DSP2 input
	always @ (posedge clk or posedge rst) begin
		if(rst)
		begin
			dsp2_a_in <= 0;
			dsp2_d_in <= 0;
		end
		else
		begin
			if(opr_cntr == 6)
			begin
				dsp2_a_in <= t_l;
				dsp2_d_in <= c_out;
			end
			else if(opr_cntr == 11)
			begin
				dsp2_a_in <= p;
				dsp2_d_in <= carry;	
			end
		end
	end
	/*
	//DSP2 output (?)
	always @ (posedge clk or posedge rst) begin
		if(rst)
		begin
			carry <= 0;
			c_in <= 0;
			p <= 0;
		end
		else
		begin
			if(curr_state == 3)
			begin
				if(opr_cntr == 9)
				begin
					wea3 <= 1;
					{carry, c_in} <= dsp2_out[16:0];
				end
				else if(opr_cntr == 14)
				begin
					wea3 <= 1;
					c_in <= dsp2_out[15:0];
					carry <= 0;
					p <= 0;
				end
				else
				begin
					wea3 <= 0;
					carry <= carry;
				end
			end
		end
	end
	
	//Valid output (not sure?)
	always @ (posedge clk or posedge rst) begin
		if(rst)
		begin
			out_valid <= 0;
		end
		else
		begin
			if((curr_state == 3) && (itr_cntr == k-1) && (itr_cntr2 == k) && (opr_cntr == 14))
			begin
				out_valid <= 1;
				itr_cntr3 <= 0;
			end
			else
				out_valid <= 0;
		end
	end
	*/
	/*
	//BRAM read for output
	always @ (posedge clk or posedge rst) begin
		if(rst)
		begin
			data_out <= 0;
			itr_cntr3 <= 0;
		end
		else
		begin
			if(curr_state == 4 && busy)
			begin
				data_out <= c_out;
				itr_cntr3 <= itr_cntr3 + 1;
				if(itr_cntr3 == 2*k + 1)
				begin
					busy <= 0;
					data_out <= 0;
					c_in <= 0;
				end
			end
		end
	end
	*/
	//Module Instantiations
	BRAM_unit b0(.clka(clk),
					 .wea(wea),
					 .addra(waddr),
					 .dina(a_in),
					 .clkb(clk),
					 .addrb(raddr),
					 .doutb(a_out)
					);
					
	BRAM_unit b1(.clka(clk),
					 .wea(wea2),
					 .addra(waddr2),
					 .dina(b_in),
					 .clkb(clk),
					 .addrb(raddr2),
					 .doutb(b_out)
					);
				
	BRAM_unit b2(.clka(clk),
					 .wea(wea3),
					 .addra(waddr3),
					 .dina(c_in),
					 .clkb(clk),
					 .addrb(raddr3),
					 .doutb(c_out)
					);
	
	DSP_unit d1(.clk(clk),
					.a(dsp_a_in),
					.b(dsp_b_in),
					.c(dsp_p_in),
					.carryin(dsp_carry_in),
					.p(dsp_out));
	
	dsp48_macro d2(.clk(clk),
					.a(dsp2_a_in),
					.d(dsp2_d_in),
					.p(dsp2_out));
	
endmodule
