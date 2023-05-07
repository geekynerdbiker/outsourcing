input  [1:0] read_address;

input        line_0_valid;
input  [1:0] line_0_tag;
input  [7:0] line_0_block;

input        line_1_valid;
input  [1:0] line_1_tag;
input  [7:0] line_1_block;

output       read_hit;
output [7:0] read_byte;

wire line_0_match_1;
wire line_0_match_0;
wire line_0_match;
wire line_0_valid_match;

wire line_1_match_1;
wire line_1_match_0;
wire line_1_match;
wire line_1_valid_match;

wire line_0_block_07_match;
wire line_0_block_06_match;
wire line_0_block_05_match;
wire line_0_block_04_match;
wire line_0_block_03_match;
wire line_0_block_02_match;
wire line_0_block_01_match;
wire line_0_block_00_match;

wire line_1_block_07_match;
wire line_1_block_06_match;
wire line_1_block_05_match;
wire line_1_block_04_match;
wire line_1_block_03_match;
wire line_1_block_02_match;
wire line_1_block_01_match;
wire line_1_block_00_match;

wire read_hit;
wire read_byte;
wire tag;
wire match;

wire block_07;
wire block_06;
wire block_05;
wire block_04;
wire block_03;
wire block_02;
wire block_01;
wire block_00;

assign line_0_match_1 = read_address[1] ~^ line_0_tag[1];
assign line_0_match_0 = read_address[0] ~^ line_0_tag[0];
assign line_0_match = line_0_match_1 & line_0_match_0;
assign line_0_valid_match = line_0_valid & line_0_match;

assign line_1_match_1 = read_address[1] ~^ line_1_tag[1];
assign line_1_match_0 = read_address[0] ~^ line_1_tag[0];
assign line_1_match = line_1_match_1 & line_1_match_0;
assign line_1_valid_match = line_1_valid & line_1_match;

assign read_hit = line_0_valid_match | line_1_valid_match;

assign line_0_block_07_match = line_0_match & line_0_block[7];
assign line_0_block_06_match = line_0_match & line_0_block[6];
assign line_0_block_05_match = line_0_match & line_0_block[5];
assign line_0_block_04_match = line_0_match & line_0_block[4];
assign line_0_block_03_match = line_0_match & line_0_block[3];
assign line_0_block_02_match = line_0_match & line_0_block[2];
assign line_0_block_01_match = line_0_match & line_0_block[1];
assign line_0_block_00_match = line_0_match & line_0_block[0];

assign line_1_block_07_match = line_1_match & line_1_block[7];
assign line_1_block_06_match = line_1_match & line_1_block[6];
assign line_1_block_05_match = line_1_match & line_1_block[5];
assign line_1_block_04_match = line_1_match & line_1_block[4];
assign line_1_block_03_match = line_1_match & line_1_block[3];
assign line_1_block_02_match = line_1_match & line_1_block[2];
assign line_1_block_01_match = line_1_match & line_1_block[1];
assign line_1_block_00_match = line_1_match & line_1_block[0];

assign block_07 = line_0_block_07_match | line_1_block_07_match;
assign block_06 = line_0_block_06_match | line_1_block_06_match;
assign block_05 = line_0_block_05_match | line_1_block_05_match;
assign block_04 = line_0_block_04_match | line_1_block_04_match;
assign block_03 = line_0_block_03_match | line_1_block_03_match;
assign block_02 = line_0_block_02_match | line_1_block_02_match;
assign block_01 = line_0_block_01_match | line_1_block_01_match;
assign block_00 = line_0_block_00_match | line_1_block_00_match;

assign read_byte[7] = read_hit & block_07;
assign read_byte[6] = read_hit & block_06;
assign read_byte[5] = read_hit & block_05;
assign read_byte[4] = read_hit & block_04;
assign read_byte[3] = read_hit & block_03;
assign read_byte[2] = read_hit & block_02;
assign read_byte[1] = read_hit & block_01;
assign read_byte[0] = read_hit & block_00;