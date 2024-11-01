`timescale 1ns / 1ps

module adder16_tb;
	reg [15:0] A;
	reg [15:0] B;
	reg Cin;

	wire [15:0] sum;
	wire Cout;
	wire Cout2;

	adder16 unit_adder (
		.A(A), 
		.B(B), 
		.Cin(Cin), 
		.sum(sum), 
		.Cout(Cout)
	);

	cla16 unit_cla (
		.A(A), 
		.B(B), 
		.Cin(Cin), 
		.sum(sum),
		.Cout(Cout2)
	);

	initial begin
		A = 16'b1111111100000000;
		B = 16'b0000000011111111;
		Cin = 1'b0;
		#50;
		A = 16'b1111111100000000;
		B = 16'b0000000011111111;
		Cin = 1'b1;
		#50
		A = 16'b0000001111000011;
		B = 16'b0000000011001111;
		Cin = 1'b1;
	end
endmodule

