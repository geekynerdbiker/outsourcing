`timescale 1ns / 1ps

module pfa(A, B, Cin, G, P, sum);
   input A;
   input B;
   input Cin;

   output G;
   output P;
   output sum;

   wire P_int;
      
   assign G = A & B;
   assign P = P_int;
   assign P_int = A ^ B;
   assign sum = P_int ^ Cin;
endmodule