`timescale 1ns / 1ps

module PingPongTest;

	// Inputs
	reg clk;
	reg rst;
	reg BTN_West;
	reg BTN_North;
	reg BTN_East;
	reg [3:0] SW;

	// Outputs
	wire [7:0] LED;
	wire [3:0] Data_Out;
	wire [3:0] LCD_Control;

	// Instantiate the Unit Under Test (UUT)
	PingPongTop uut (.clk(clk), .rst(rst), .BTN_West(BTN_West), .BTN_North(BTN_North), .BTN_East(BTN_East), .SW(SW), .LED(LED), .Data_Out(Data_Out), .LCD_Control(LCD_Control));
	
	initial begin
		clk = 0;
		forever #10 clk = ~clk;		
	end
	
	
	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 0;
		BTN_West = 0;
		BTN_North = 0;
		BTN_East = 0;
		SW = 0;

		// Wait 100 ns for global reset to finish
		#100;
      
		// Add stimulus here
		
		//First player enters a name
		BTN_North = 1;
		#10;
		BTN_North = 0;
		#10;
		//letter "a"
		SW[3] = 0; SW[2] = 1; SW[1] = 1; SW[0] = 0;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		#10;
		SW[3] = 0; SW[2] = 0; SW[1] = 0; SW[0] = 1;
		
		BTN_North = 1;
		#10;
		BTN_North = 0;		
		//letter "a"
		#10;
		SW[3] = 0; SW[2] = 1; SW[1] = 1; SW[0] = 0;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		#10;
		SW[3] = 0; SW[2] = 0; SW[1] = 0; SW[0] = 1;
		
		BTN_North = 1;
		#10;
		BTN_North = 0;		
		#10;
		//letter "a"
		SW[3] = 0; SW[2] = 1; SW[1] = 1; SW[0] = 0;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		#10;
		SW[3] = 0; SW[2] = 0; SW[1] = 0; SW[0] = 1;
		
		//Second player enters a name
		BTN_North = 1;
		#10;
		BTN_North = 0;		
		#10;
		//letter "b"
		SW[3] = 0; SW[2] = 1; SW[1] = 1; SW[0] = 0;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		#10;
		SW[3] = 0; SW[2] = 0; SW[1] = 1; SW[0] = 0;

		BTN_North = 1;
		#10;
		BTN_North = 0;		
		#10;
		//letter "b"
		SW[3] = 0; SW[2] = 1; SW[1] = 1; SW[0] = 0;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		#10;
		SW[3] = 0; SW[2] = 0; SW[1] = 1; SW[0] = 0;
		
		BTN_North = 1;
		#10;
		BTN_North = 0;		
		#10;
		//letter "b"
		SW[3] = 0; SW[2] = 1; SW[1] = 1; SW[0] = 0;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		#10;
		SW[3] = 0; SW[2] = 0; SW[1] = 1; SW[0] = 0;
		
		//Game starts
		BTN_North = 1;
		#10;
		BTN_North = 0;
		
		
		//East serves
		#1000001000;
		BTN_East = 1;
		#10;
		BTN_East = 0;
		
		//West serves
		#1500001000;
		BTN_West = 1;
		#10;
		BTN_West = 0;
		
		//East loses
		#250000000;
		BTN_East = 1;
		#10;
		BTN_East = 0;
		
		#10;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		
		//West loses
		#250000000;
		BTN_West = 1;
		#10;
		BTN_West = 0;
		
		#10;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		
		//East loses
		#1250001000;
		
		#10;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		
		//East serves
		#1000001000;
		BTN_East = 1;
		#10;
		BTN_East = 0;
		
		//West loses
		#1750001000;
		
		#10;
		BTN_North = 1;
		#10;
		BTN_North = 0;
		
		//East serves
		#1000001000;
		BTN_East = 1;
		#10;
		BTN_East = 0;
		
		//West loses
		#250000000;
		BTN_West = 1;
		#10;
		BTN_West = 0;
		
		//Score: 2-3		
	end
      
endmodule