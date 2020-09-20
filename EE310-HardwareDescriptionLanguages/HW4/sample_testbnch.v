`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:56:34 05/01/2020
// Design Name:   try_1
// Module Name:   D:/Users/suuser/Desktop/try/try_1/t3.v
// Project Name:  try_1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: try_1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module t3;
parameter PERIOD = 10;
parameter HALFPERIOD = PERIOD/2;
	// Inputs
	reg [7:0] A;
	reg clk;

	reg [7:0] img[1:101376];	//Adjust size of this reg regarding size of your input image
	// Outputs
	wire [7:0] B;

	// Instantiate the Unit Under Test (UUT)
	try_1 uut (
		.A(A),
		.clk(clk), 
		.B(B)
	);
	integer i;
	integer f1;	//Integer for keeping the output file
	
	initial
	begin
		clk = 0;
		#PERIOD forever #HALFPERIOD clk= ~clk;
	end
	
	initial begin
		// Initialize Inputs
		A = 0;
		clk = 0;
		f1 = $fopen("img_out.txt");//Open your output file
		$readmemh("frame1.txt",img); //Read your input file(Use readmemb for binary files)
		
		// Wait 100 ns for global reset to finish
		#100;
      for(i=1; i<101375; i=i+1) begin
			A[7:0] = img[i];
			#PERIOD;
			$display("i =",i , "img =", img[i]);
			/*
			if(i%352 == 0)
				$fwrite(f1,"%h", B, "\n");
			else
				$fwrite(f1,"%h", B, " ");
				*/
			$fwrite(f1,"%b", B, "\n"); //Write B(your output) to your file in f1.		"%b" for binary, "\n" for writing one result in each row
		end
		// Add stimulus here
		$fclose(f1);//Close your output file
		$stop;//Stop your simulation when operation is fibished
	end
      
endmodule

