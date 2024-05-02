`timescale 1ns / 1ps

module adder16(
	input [15:0] A,
    input [15:0] B,
    input Cin,
    
    output [15:0] sum,
    output Cout
    );
	 
	
    wire C1, C2, C3;

	adder4 add4_1 (.A(A[3:0]) , .B(B[3:0]), .Cin(Cin), .sum(sum[3:0]), .Cout(C1));
	adder4 add4_2 (.A(A[7:4]) , .B(B[7:4]), .Cin(C1), .sum(sum[7:4]), .Cout(C2));
	adder4 add4_3 (.A(A[11:8]) , .B(B[11:8]), .Cin(C2), .sum(sum[11:8]), .Cout(C3));
	adder4 add4_4 (.A(A[15:12]) , .B(B[15:12]), .Cin(C3), .sum(sum[15:12]), .Cout(Cout));
endmodule

module adder4(
    input [3:0] A,
    input [3:0] B,
    input Cin,

    output [3:0] sum,
    output Cout
    );
	 
	wire C1, C2, C3;

	full_adder FA1 (.A(A[0]) , .B(B[0]), .Cin(Cin), .sum(sum[0]), .Cout(C1));
	full_adder FA2 (.A(A[1]) , .B(B[1]), .Cin(C1), .sum(sum[1]), .Cout(C2));
	full_adder FA3 (.A(A[2]) , .B(B[2]), .Cin(C2), .sum(sum[2]), .Cout(C3));
	full_adder FA4 (.A(A[3]) , .B(B[3]), .Cin(C3), .sum(sum[3]), .Cout(Cout));
endmodule

module full_adder(
    input A,
    input B,
    input Cin,

    output sum,
    output Cout
    );
	 
	assign sum = (A ^ B) ^ Cin;
	assign Cout = (A & B) | (A & Cin) | (B & Cin); 
endmodule	 