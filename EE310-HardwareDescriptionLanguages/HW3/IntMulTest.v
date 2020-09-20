`timescale 1ns / 1ps

module IntMulTest;

	// Inputs
	reg clk;
	reg rst;
	reg len_valid;
	reg [3:0] len_in;
	reg in_valid;
	reg [15:0] data_in;

	// Outputs
	wire busy;
	wire out_valid;
	wire [15:0] data_out;

	// Instantiate the Unit Under Test (UUT)
	IntMul uut (
		.clk(clk), 
		.rst(rst), 
		.len_valid(len_valid),
		.len_in(len_in), 
		.in_valid(in_valid), 
		.data_in(data_in), 
		.busy(busy), 
		.out_valid(out_valid), 
		.data_out(data_out)
	);
	
	reg [127:0] A_array [24:0];
	reg [127:0] B_array [24:0];
	reg [255:0] C_array [24:0];
	reg [3:0] lens_array [24:0];
	integer k,i, length;

	initial begin
		$readmemb("A.txt", A_array);
		$readmemb("B.txt", B_array);
		$readmemb("C.txt", C_array);
		$readmemb("lens.txt", lens_array);
		clk = 0;
		forever #5 clk = ~clk;
	end
		
	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 0;
		len_valid = 0;
		len_in = 0;
		in_valid = 0;
		data_in = 0;

		// Wait 100 ns for global reset to finish
		#105;
		// Add stimulus here
		rst = 1;
		#10;
		rst = 0;
		#10;
		
		for(k=0; k < 25; k=k+1)
		begin
			len_valid = 1;
			#10;
			len_valid = 0;
			$display("length: %d", lens_array[k]);
			len_in = lens_array[k];
			#10;
			length = len_in;
			len_in = 0;
			
			in_valid = 1;
			#10;
			in_valid = 0;
			
			for(i=1; i <= length; i=i+1)
			begin
				data_in = A_array[k][(i-1)*16 +: 16];
				#10;
			end
			
			for(i=1; i <= length; i=i+1)
			begin
				data_in = B_array[k][(i-1)*16 +: 16];
				#10;
			end
			
			if(length == 1)
				#180;
			else if(length == 2)
				#530;
			else if(length == 3)
				#1080;
			else if(length == 4)
				#1830;
			else if(length == 5)
				#2780;
			else if(length == 6)
				#3930;
			else if(length == 7)
				#5280;
			else if(length == 8)
				#6830;
			
			for(i=1; i <= 2*length; i=i+1)
			begin
				if(data_out != C_array[k][(i-1)*16 +: 16])
				begin
					//$display("Data_out: %d", data_out);
					//$display("C_array[k]: %d", C_array[k][(i-1)*16 +: 16]);
					$display("Test case %0d, C%0d is wrong", k+1, i-1);
				end
				else
				begin
					//$display("Data_out: %d", data_out);
					//$display("C_array[k]: %d", C_array[k][(i-1)*16 +: 16]);
					$display("Test case %0d, C%0d is correct", k+1, i-1);
				end
				#10;
			end
			#10;
		end
	end
      
endmodule
