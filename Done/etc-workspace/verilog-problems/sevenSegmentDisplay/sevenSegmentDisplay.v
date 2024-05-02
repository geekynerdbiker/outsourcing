input [3:0] numeral_bit;

output a;
output b;
output c;
output d;
output e;
output f;
output g;


wire a_maxterm_01;
wire a_maxterm_02;
wire a_3_or_1;
wire a_2_and_0;
wire a_not_2_and_not_0;


wire b_maxterm_01;
wire b_maxterm_02;
wire b_not_0_and_not_1;
wire b_not_2_and_not_3;
wire b_0_and_1;


wire c_maxterm_02;
wire c_3_or_2;
wire c_1_and_0;



wire d_maxterm_01;
wire d_maxterm_02;
wire d_maxterm_03;
wire d_maxterm_04;
wire d_not_0_and_1;
wire d_not_0_and_not_2;
wire d_not_2_and_not_3;
wire d_not_2_and_not_0;
wire d_not_2_and_1;
wire d_1_and_not_0;
wire d_2_and_not_1;
wire d_0_and_2;
wire d_combine_01;
wire d_combine_02;

wire d_combine;

wire minterm_00;
wire minterm_02;
wire minterm_06;
wire minterm_08;

wire minterm_00_or_minterm_02;
wire minterm_06_or_minterm_08;

wire 1_and_not_0;
wire 3_and_not_2;
wire not_3_and_2;
wire not_1_and_not_0;
wire not_3_and_not_2;
wire not_3_and_2;


wire f_maxterm_01;
wire f_maxterm_02;
wire f_maxterm_03;

wire f_combine;
wire f_0_and_1;

wire g_maxterm_00;
wire g_maxterm_01;
wire g_maxterm_07;
wire g_combine;
wire 2_and_not_1;
wire not_3_and_not_2;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];



assign a_3_or_1 = numeral_bit[3] | numeral_bit[1];
assign a_2_and_0 = numeral_bit[2] & numeral_bit[0];
assign a_maxterm_01 = a_3_or_1 | a_2_and_0;
assign a_not_2_and_not_0 = not_numeral_bit_2 & not_numeral_bit_0;
assign a_maxterm_02 = a_not_2_and_not_0 & not_numeral_bit_3;
assign a = a_maxterm_01 | a_maxterm_02;


assign b_not_0_and_not_1 = not_numeral_bit_0 & not_numeral_bit_1;
assign b_maxterm_01 = numeral_bit[3] | b_not_0_and_not_1;
assign b_0_and_1 = numeral_bit[0] & numeral_bit[1];
assign b_not_2_and_not_3 = not_numeral_bit_2 & not_numeral_bit_3;
assign b_maxterm_02 = b_0_and_1 | b_not_2_and_not_3;
assign b = b_maxterm_01 | b_maxterm_02;



assign c_1_and_0 = not_numeral_bit_1 | numeral_bit[0];
assign c_3_or_2 = numeral_bit[3] | numeral_bit[2];
assign c_maxterm_02 = c_1_and_0 | c_3_or_2;
assign c = c_maxterm_02;


assign d_not_2_and_not_0 = not_numeral_bit_2 & not_numeral_bit_0;

assign d_not_2_and_1 = not_numeral_bit_2 & numeral_bit[1];

assign d_1_and_not_0 = numeral_bit[1] & not_numeral_bit_0;

assign d_maxterm_02 = d_not_2_and_1 | d_1_and_not_0;

assign d_2_and_not_1 = numeral_bit[2] & not_numeral_bit_1;

assign d_maxterm_03 = d_2_and_not_1 & numeral_bit[0];

assign d_combine_01 = d_not_2_and_not_0 | d_maxterm_02;

assign d = d_combine_01 | d_maxterm_03;



assign not_3_and_not_2 = not_numeral_bit_3 & not_numeral_bit_2;
assign not_1_and_not_0 = not_numeral_bit_1 & not_numeral_bit_0;

assign 1_and_not_0 = numeral_bit[1] & not_numeral_bit_0;

assign not_3_and_2 = not_numeral_bit_3 & numeral_bit[2];

assign 3_and_not_2 = numeral_bit[3] & not_numeral_bit_2;



assign minterm_00 = not_3_and_not_2 & not_1_and_not_0;

assign minterm_02 = not_3_and_not_2 & 1_and_not_0;

assign minterm_06 = not_3_and_2 & 1_and_not_0;

assign minterm_08 = 3_and_not_2 & not_1_and_not_0;



assign minterm_00_or_minterm_02 = minterm_00 | minterm_02;
assign minterm_06_or_minterm_08 = minterm_06 | minterm_08

assign e = minterm_00_or_minterm_02 | minterm_06_or_minterm_08;


assign f_maxterm_01 = numeral_bit[3] | b_not_0_and_not_1;
assign f_maxterm_02 = d_maxterm_03;
assign f_0_and_1 = not_numeral_bit_0 & numeral_bit[1];
assign f_maxterm_03 = f_0_and_1 & numeral_bit[2];
assign f_combine = f_maxterm_02 | f_maxterm_03;
assign f = f_combine | f_maxterm_01;


assign 2_and_not_1 = numeral_bit[2] & not_numeral_bit_1
assign g_maxterm_00 = numeral_bit[3] | 2_and_not_1;

assign g_maxterm_01 = numeral_bit[1] & not_numeral_bit_0;

assign not_3_and_not_2 = not_numeral_bit_3 & not_numeral_bit_2;
assign g_maxterm_07 = not_3_and_not_2 & numeral_bit[1];

assign g_combine = g_maxterm_00 | g_maxterm_01;

assign g = g_combine | g_maxterm_07;