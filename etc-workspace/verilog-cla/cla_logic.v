`timescale 1ns / 1ps

module cla_logic (G, P, Cin, C, Cout, P0, G0);
   input [3:0] G;
   input [3:0] P;
   input Cin;

   output [3:1] C;
   output Cout;
   output G0;
   output P0;
   
   wire G_temp;
   wire P_temp;
   
   assign C[1] = G[0] | (P[0] & Cin);
   assign C[2] = G[1] | (P[1] & G[0])| (P[1] & P[0] & Cin);
   assign C[3] = G[2] | (P[2] & G[1]) | (P[2] & P[1] & G[0])| (P[2] & P[1] & P[0] & Cin);
   assign P_temp = P[3] & P[2] & P[1] & P[0];
   assign G_temp = G[3] | (P[3] & G[2]) | (P[3] & P[2] & G[1]) | (P[3] & P[2] & P[1] & G[0]);
   assign Cout = G_temp | (P_temp & Cin);
   assign P0 = P_temp;
   assign G0 = G_temp;
endmodule