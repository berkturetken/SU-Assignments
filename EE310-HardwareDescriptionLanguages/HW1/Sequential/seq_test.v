`timescale 1ns / 1ps

module seq_test;

	// Inputs
	reg clk;
	reg rst;
	reg start;
	reg [7:0] A3;
	reg [7:0] A2;
	reg [7:0] A1;
	reg [7:0] A0;
	reg [7:0] B3;
	reg [7:0] B2;
	reg [7:0] B1;
	reg [7:0] B0;

	// Outputs
	wire finish;
	wire [7:0] C3;
	wire [7:0] C2;
	wire [7:0] C1;
	wire [7:0] C0;

	// Instantiate the Unit Under Test (UUT)
	seq uut (.clk(clk), .rst(rst), .start(start), .A3(A3), .A2(A2), .A1(A1), .A0(A0), .B3(B3), .B2(B2), .B1(B1), .B0(B0), .finish(finish), .C3(C3), .C2(C2), .C1(C1), .C0(C0));
	
	reg [7:0] A3_array [0:49];
	reg [7:0] A2_array [0:49];
	reg [7:0] A1_array [0:49];
	reg [7:0] A0_array [0:49];
	reg [7:0] B3_array [0:49];
	reg [7:0] B2_array [0:49];
	reg [7:0] B1_array [0:49];
	reg [7:0] B0_array [0:49];
	reg [7:0] C3_array [0:49];
	reg [7:0] C2_array [0:49];
	reg [7:0] C1_array [0:49];
	reg [7:0] C0_array [0:49];
	
	initial begin
		// Initialize Inputs
		$readmemb("A3.txt", A3_array);
		$readmemb("A2.txt", A2_array);
		$readmemb("A1.txt", A1_array);
		$readmemb("A0.txt", A0_array);
		$readmemb("B3.txt", B3_array);
		$readmemb("B2.txt", B2_array);
		$readmemb("B1.txt", B1_array);
		$readmemb("B0.txt", B0_array);
		$readmemb("C3.txt", C3_array);
		$readmemb("C2.txt", C2_array);
		$readmemb("C1.txt", C1_array);
		$readmemb("C0.txt", C0_array);
		clk = 0;
		forever #5 clk = ~clk;
	end
	
	integer k;
	
	initial begin
	
		//initialize inputs
		rst = 1;
		#10;
		rst = 0;
		start = 1;
	
		A3 = 0;
		A2 = 0;
		A1 = 0;
		A0 = 0;
		B3 = 0;
		B2 = 0;
		B1 = 0;
		B0 = 0;
		
		//test with for loop
		for(k=0; k<50; k=k+1)
		begin
			A3 = A3_array[k];
			A2 = A2_array[k];
			A1 = A1_array[k];
			A0 = A0_array[k];
			B3 = B3_array[k];
			B2 = B2_array[k];
			B1 = B1_array[k];
			B0 = B0_array[k];
			#300;
			
			if((C3 == C3_array[k]) && (C2 == C2_array[k]) && (C1 == C1_array[k]) && (C0 == C0_array[k]))
			begin
				$display("Test case %d is correct", k);
			end
			else
			begin
				$display("Test case %d is wrong", k);
			end
			rst = 1;
			#10;
			rst = 0;
		end
	end
endmodule

