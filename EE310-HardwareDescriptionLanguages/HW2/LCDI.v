
//////////////////////////////////////////////////////////////////////////////////
// 
// Developed by: Toma H. Sacco, Ph.D. 
// Updated by  : Ahmet C. Mert, Sabanci University
// 
// For details, check pg.53 of https://www.xilinx.com/support/documentation/boards_and_kits/ug230.pdf
//
// This module can display 120 different characters
// For character encoding, check pg.47 of https://www.xilinx.com/support/documentation/boards_and_kits/ug230.pdf
//
//////////////////////////////////////////////////////////////////////////////////

module LCDI(clk, first_line, second_line, dataout, control);
    input clk;
    input [127:0] first_line;
    input [127:0] second_line;
    output [3:0] dataout;
    output [2:0] control;
    
    // --> [127:120]: Left-most digit on lCD line
    // --> [7:0]    : Right-most digit on LCD line
	
    reg [5:0]  sel=0;
    reg [25:0] delay=0;  
    reg [5:0]  state=0;
    reg [3:0]  dataout=0;
    reg [2:0]  control=0; // [E,D/C' , R/W'] 
    reg [7:0]  DR=0;
    reg [7:0]  MUX=0;

    always @(sel or first_line or second_line) begin
        case(sel)
        // second line
        0 :MUX = second_line[7:0]    ;
        1 :MUX = second_line[15:8]   ;
        2 :MUX = second_line[23:16]  ;
        3 :MUX = second_line[31:24]  ;
        4 :MUX = second_line[39:32]  ;
        5 :MUX = second_line[47:40]  ;
        6 :MUX = second_line[55:48]  ;
        7 :MUX = second_line[63:56]  ;
        8 :MUX = second_line[71:64]  ;
        9 :MUX = second_line[79:72]  ;
        10:MUX = second_line[87:80]  ;
        11:MUX = second_line[95:88]  ;
        12:MUX = second_line[103:96] ;
        13:MUX = second_line[111:104];
        14:MUX = second_line[119:112];
        15:MUX = second_line[127:120];
        // first line
        40:MUX = first_line[7:0]    ;
        41:MUX = first_line[15:8]   ;
        42:MUX = first_line[23:16]  ;
        43:MUX = first_line[31:24]  ;
        44:MUX = first_line[39:32]  ;
        45:MUX = first_line[47:40]  ;
        46:MUX = first_line[55:48]  ;
        47:MUX = first_line[63:56]  ;
        48:MUX = first_line[71:64]  ;
        49:MUX = first_line[79:72]  ;
        50:MUX = first_line[87:80]  ;
        51:MUX = first_line[95:88]  ;
        52:MUX = first_line[103:96] ;
        53:MUX = first_line[111:104];
        54:MUX = first_line[119:112];
        55:MUX = first_line[127:120];
        endcase
    end
	 
    always @ (posedge clk)
    begin
        case(state)
        //Power-On Initialization
        0:begin delay <= 750_000; state<= 1;control <= 0;    end
        1:begin 
            if(delay==0)begin state <= 2; delay<=12; dataout<= 4'h3; control<=3'h4; end
            else delay <= delay -1; 
        end
        2:begin 
            if(delay==0)begin delay <= 205_000; state<= 3;control <= 0; end
            else delay <= delay -1 ; 
        end
        3:begin 
            if(delay==0)begin state <= 4; delay<=12; dataout<= 4'h3; control<=3'h4; end
            else delay <= delay -1; 
        end
        4:begin 
            if(delay==0)begin delay <= 5_000; state<= 5;control <= 0; end
            else delay <= delay -1 ; 
        end
        5:begin 
            if(delay==0)begin state <= 6; delay<=12; dataout<= 4'h3; control<=3'h4; end
            else delay <= delay -1; 
        end
        6:begin 
            if(delay==0)begin delay <= 2_000; state<= 7;control <= 0; end
            else delay <= delay -1 ; 
        end
        7:begin 
            if(delay==0)begin state <= 8; delay<=12; dataout<= 4'h2; control<=3'h4; end
            else delay <= delay -1; 
        end
        8:begin 
            if(delay==0)begin delay <= 2_000; state<= 9;control <= 0; end
            else delay <= delay -1 ; 
        end
        9:begin 
            if(delay==0)begin state <= 10;sel <= 4; end
            else delay <= delay -1; 
        end
		
        // Display Configuration
        10:begin  
            case(sel)
            0: begin state <= 20; delay <= 82_000; end
            1: begin state <= 11; DR <= 8'h01; end
            2: begin state <= 11; DR <= 8'h0C; end
            3: begin state <= 11; DR <= 8'h06; end
            4: begin state <= 11; DR <= 8'h28; end 		 
            default: state <= 0 ;
            endcase 
        end
        11:begin state <= 12; control <= 0; dataout <= DR[7:4]; delay <= 2; sel <= sel -1; end
        12:begin 
            if(delay==0)begin delay <= 12; state<= 13; control<=3'h4; end
            else delay <= delay -1 ;
        end
        13:begin 
            if(delay==0)begin delay <= 2; state<= 14; control<=0; end
            else delay <= delay -1 ; 
        end
        14:begin 
            if(delay==0)begin delay <= 50 ; state<= 15; end
            else delay <= delay -1 ; 
        end
        15:begin 
            if(delay==0)begin state <= 16; control <= 0; dataout <=DR[3:0]; delay <= 2;end
            else delay <= delay -1 ; 
        end
        16:begin 
            if(delay==0)begin delay <= 12; state<= 17; control<=3'h4; end
            else delay <= delay -1 ; 
        end
        17:begin 
            if(delay==0)begin delay <= 2; state<= 18; control<=0; end
            else delay <= delay -1 ; 
        end
        18:begin 
            if(delay==0)begin delay <= 2_000 ; state<= 19; end
            else delay <= delay -1 ; 
        end
        19:begin 
            if(delay==0)begin state<= 10; end
            else delay <= delay -1 ; 
        end
        20:begin 
            if(delay==0)begin state<= 21; end
            else delay <= delay -1 ; 
        end
        
        // Displaying
        21:begin state <= 22;sel <= 56; end // 'sel' is set here
        
        // Setting the starting address
        22:begin state <= 23; DR <=8'h80; end // -> This is starting address
        
        23:begin state <= 24; control <= 0; dataout <= DR[7:4]; delay <= 2; sel <= sel -1; end
        24:begin if(delay==0)begin delay <= 12; state<= 25; control<=3'h4; end
                 else delay <= delay -1 ;end
        25:begin if(delay==0)begin delay <= 2; state<= 26; control<=0; end
                 else delay <= delay -1 ; end
        26:begin if(delay==0)begin delay <= 50 ; state<= 27; end
                 else delay <= delay -1 ; end
        27:begin if(delay==0)begin state <= 28; control <= 0; dataout <=DR[3:0]; delay <= 2;end
                 else delay <= delay -1 ; end
        28:begin if(delay==0)begin delay <= 12; state<= 29; control<=3'h4; end
                 else delay <= delay -1 ; end
        29:begin if(delay==0)begin delay <= 2; state<= 30; control<=0; end
                 else delay <= delay -1 ; end
        30:begin if(delay==0)begin delay <= 2_000 ; state<= 31; end
                 else delay <= delay -1 ; end
        31:begin if(delay==0)begin state<= 32; end
                 else delay <= delay -1 ; end
        
        // Writing data to the display
        32:begin state <= 33; DR <= MUX; end
        33:begin state <= 34; control <= 3'b010; dataout <= DR[7:4]; delay <= 2; end
        34:begin 
            if(delay==0)begin delay <= 12; state<= 35; control<=3'b110; end
            else delay <= delay -1 ;
        end
        35:begin 
            if(delay==0)begin delay <= 2; state<= 36; control<=3'b010; end
            else delay <= delay -1 ; 
        end
        36:begin 
            if(delay==0)begin delay <= 50 ; state<= 37;control<=0; end
            else delay <= delay -1 ; 
        end
        37:begin 
            if(delay==0)begin state <= 38; control <= 3'b010; dataout <=DR[3:0]; delay <= 2;end
            else delay <= delay -1 ; 
        end
        38:begin 
            if(delay==0)begin delay <= 12; state<= 39; control<=3'b110; end
            else delay <= delay -1 ; 
        end
        39:begin 
            if(delay==0)begin delay <= 2; state<= 40; control<=3'b010; end
            else delay <= delay -1 ;
        end
        40:begin 
            if(delay==0)begin delay <= 2_000 ; state<= 41;control<=0; end
            else delay <= delay -1 ; 
        end
        41:begin 
            if(delay==0)begin if(sel==0)state<= 42;else begin state<= 32; sel<=sel - 1; end end
            else delay <= delay -1 ; 
        end
        
        // Delay between displaying
        42:begin state <= 43; delay <= 40_000_000; end
        43:begin 
            if(delay==0)begin state<= 21; end
            else delay <= delay -1 ; 
        end	
        default: state <= 0;
        endcase
    end

endmodule
