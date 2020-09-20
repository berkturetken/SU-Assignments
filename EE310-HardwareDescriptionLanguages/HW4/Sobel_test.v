`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:06:59 05/10/2020
// Design Name:   Sobel
// Module Name:   C:/Users/dogan/Alpobaba/Alpobaba/School/2019-2020 Spring/EE 310/Labs/Lab4/Lab4_alperend_berkturetken/Sobel_test.v
// Project Name:  Lab4_alperend_berkturetken
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Sobel
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Sobel_test;

	// Inputs
	reg clk;
	reg rst;
	reg start;
	reg [7:0] pixel_in;

	// Outputs
	wire busy;
	wire finish;
	wire [7:0] pixel_out;

	// Instantiate the Unit Under Test (UUT)
	Sobel uut (
		.clk(clk), 
		.rst(rst), 
		.start(start), 
		.pixel_in(pixel_in), 
		.busy(busy), 
		.finish(finish), 
		.pixel_out(pixel_out)
	);
	
	reg [7:0] baboon_array [65535:0];
	reg [7:0] cameraman_array [65535:0];
	reg [7:0] egg_array [65535:0];
	reg [7:0] lena_array [65535:0];
	reg [7:0] puppy_array [65535:0];
	integer k;
	integer f1, f2, f3, f4, f5;
	
	initial begin
		$readmemb("baboon.txt", baboon_array);
		$readmemb("cameraman.txt", cameraman_array);
		$readmemb("egg.txt", egg_array);
		$readmemb("lena.txt", lena_array);
		$readmemb("puppy.txt", puppy_array);
		f1 = $fopen("baboon_out.txt");
		f2 = $fopen("cameraman_out.txt");
		f3 = $fopen("egg_out.txt");
		f4 = $fopen("lena_out.txt");
		f5 = $fopen("puppy_out.txt");
		forever #5 clk = ~clk;
	end
	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 0;
		start = 0;
		pixel_in = 0;
		// Wait 100 ns for global reset to finish
		#5;
		rst = 1;
		#50;
		rst = 0;
		#10;
		
		start = 1;
		#10;
		start = 0;
		
		for(k = 0; k < 65536; k = k + 1)
		begin
			pixel_in = baboon_array[k];
			#10;
		end
		
		while(finish == 0) //it will pass time until the operations finish
		begin
			#10;
		end
		//when the finish is 1, we will print the output
		#10;
		
		for(k = 0 ; k < 65536; k = k + 1)
		begin
			$fwrite(f1, "%b", pixel_out, "\n");
			#10;
		end
		
		#50;
		
		start = 1;
		#10;
		start = 0;
		
		for(k = 0; k < 65536; k = k + 1)
		begin
			pixel_in = cameraman_array[k];
			#10;
		end
		
		while(finish == 0) //it will pass time until the operations finish
		begin
			#10;
		end
		//when the finish is 1, we will print the output
		#10;
		
		for(k = 0 ; k < 65536; k = k + 1)
		begin
			$fwrite(f2, "%b", pixel_out, "\n");
			#10;
		end
		
		#50;
		
		start = 1;
		#10;
		start = 0;
		
		for(k = 0; k < 65536; k = k + 1)
		begin
			pixel_in = egg_array[k];
			#10;
		end
		
		while(finish == 0) //it will pass time until the operations finish
		begin
			#10;
		end
		//when the finish is 1, we will print the output
		#10;
		
		for(k = 0 ; k < 65536; k = k + 1)
		begin
			$fwrite(f3, "%b", pixel_out, "\n");
			#10;
		end
		
		#50;
		
		start = 1;
		#10;
		start = 0;
		
		for(k = 0; k < 65536; k = k + 1)
		begin
			pixel_in = lena_array[k];
			#10;
		end
		
		while(finish == 0) //it will pass time until the operations finish
		begin
			#10;
		end
		//when the finish is 1, we will print the output
		#10;
		
		for(k = 0 ; k < 65536; k = k + 1)
		begin
			$fwrite(f4, "%b", pixel_out, "\n");
			#10;
		end
		
		#50;
		
		start = 1;
		#10;
		start = 0;
		
		for(k = 0; k < 65536; k = k + 1)
		begin
			pixel_in = puppy_array[k];
			#10;
		end
		
		while(finish == 0) //it will pass time until the operations finish
		begin
			#10;
		end
		//when the finish is 1, we will print the output
		#10;
		
		for(k = 0 ; k < 65536; k = k + 1)
		begin
			$fwrite(f5, "%b", pixel_out, "\n");
			#10;
		end
		#50;		
		// Add stimulus here
		
		$fclose(f1);
		$fclose(f2);
		$fclose(f3);
		$fclose(f4);
		$fclose(f5);
		$stop;

	end
      
endmodule

