`timescale 1ns / 1ps
/*
module timer(clk, rst, t_start, t_end);

input clk, rst, t_start;
output reg t_end;
reg[100:0] cnt;

always @ (posedge clk or posedge rst)
begin
	if(rst)
	begin
		t_end <= 0;
		cnt <= 0;
	end
	else
	begin
		if(t_start)
		begin
			if(cnt < 125000000)
			begin
				cnt <= cnt + 1;
			end
			else
			begin
				cnt <= cnt;
			end
		end
		else
		begin
			cnt <= 0;
		end
		
		t_end <= (cnt == 125000000);
	end
end

endmodule*/

module timer(clk, rst, t_end);

input clk, rst;
output reg t_end;
reg[100:0] cnt;

always @ (posedge clk or posedge rst)
begin
	if(rst)
	begin
		t_end <= 0;
		cnt <= 0;
	end
	else
	begin
		if(cnt < 12500000)
		begin
			cnt <= cnt + 1;
			t_end <= 0;
		end
		else
		begin
			cnt <= 0;
			t_end <= 1;
		end
	end
end

endmodule
