`timescale 1ns / 1ps

module comb_test;
	//Inputs
	reg [7:0] A3, A2, A1, A0, B3, B2, B1, B0; 
	// Output
	wire [7:0] C3, C2, C1, C0;

	// Instantiate the Unit Under Test (UUT)
	comb uut (A3, A2, A1, A0, B3, B2, B1, B0, C3, C2, C1, C0);
	
	//Arrays to keep the test data for each inputa nd output
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
	
	//reading txt files to get inputs
	initial begin
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
	end
	
	integer k;
	
	initial begin
	
		//initialize inputs
		A3 = 0;
		A2 = 0;
		A1 = 0;
		A0 = 0;
		B3 = 0;
		B2 = 0;
		B1 = 0;
		B0 = 0;
		
		#100;
		
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
			#10;
			
			if((C3 == C3_array[k]) && (C2 == C2_array[k]) && (C1 == C1_array[k]) && (C0 == C0_array[k]))
			begin
				$display("Test case %d is correct", k);
				$display("%d, %d", C3, C3_array[k]);
			end
			else
			begin
				$display("Test case %d is wrong", k);
				$display("%d, %d", C3, C3_array[k]);
			end
			
		end	
		
		//$finish;
		
	end
      
endmodule

