`timescale 1ns / 1ps

module tb_cla4;
	reg [15:0] A;
	reg [15:0] B;
	reg Cin;

	wire [3:0] sum;

	cla4 unit (
		.A(A), 
		.B(B), 
		.Cin(Cin), 
		.sum(sum),
		.Cout(Cout)
	);

	initial begin
		A = 4'b1100;
		B = 4'b0011;
		Cin = 1'b0;
		#50;
		A = 4'b1100;
		B = 4'b0011;
		Cin = 1'b1;
		#50;
		A = 4'b0011;
		B = 4'b1111;
		Cin = 1'b1;
		#50;
	end
endmodule