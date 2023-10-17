`timescale 1ns / 1ps

module cla16(A, B, Cin, sum, Cout, P1, G1);
    input [15:0] A;
    input [15:0] B;
    input Cin;

    output [15:0] sum;
    output Cout;
    output G1;
    output P1;

    wire Cin;
    wire [3:0] G;
    wire [3:0] P;
    wire [3:1] C;
    
    cla_logic CarryLogic2 (G[3:0], P[3:0], Cin, C[3:1], Cout, P1, G1);
    cla4 u0 (A[3:0], B[3:0], Cin, sum[3:0], P[0], G[0]);
    cla4 u1 (A[7:4], B[7:4], C[1],  sum[7:4], P[1], G[1]);
    cla4 u2 (A[11:8], B[11:8], C[2], sum[11:8], P[2], G[2]);
    cla4 u3 (A[15:12], B[15:12], C[3], sum[15:12], P[3], G[3]);
endmodule