/*****************************************
    
    Team XX : 
        2024000000    Kim Mina
        2024000001    Lee Minho
*****************************************/



////////////////////////////////////
//  TOP MODULE
////////////////////////////////////
module macarray (
    input     wire              CLK,
    input     wire              RSTN,
	input	  wire	  [11:0]	MNT,
	input	  wire				START,
	
    output    wire              EN_I,
    output    wire    [2:0]     ADDR_I,
    input     wire    [63:0]    RDATA_I,
	output    wire              EN_W,
    output    wire    [2:0]     ADDR_W,
    input     wire    [63:0]    RDATA_W,
	
    output    wire              EN_O,
    output    wire              RW_O,
    output    wire    [3:0]     ADDR_O,
    output    wire    [63:0]    WDATA_O,
    input     wire    [63:0]    RDATA_O
);


    // WRITE YOUR CONTROL SYSTEM CODE
    
    reg [63:0] input_reg [3:0];
    reg [63:0] weight_reg [3:0];
    reg [127:0] mac_result [3:0];
    reg [3:0] state;
    reg [3:0] output_counter;

    localparam IDLE         = 4'd0,
               LOAD_INPUT    = 4'd1,
               LOAD_WEIGHT   = 4'd2,
               COMPUTE       = 4'd3,
               WRITE_OUTPUT  = 4'd4;

    wire [3:0] M = MNT[11:8];
    wire [3:0] N = MNT[7:4];
    wire [3:0] T = MNT[3:0];

    always @(posedge CLK or negedge RSTN) begin
        if (!RSTN) begin
            state <= IDLE;
            output_counter <= 4'b0;
        end else begin
            case (state)
                IDLE:
                    if (START) state <= LOAD_INPUT;
                LOAD_INPUT:
                    state <= LOAD_WEIGHT;
                LOAD_WEIGHT:
                    state <= COMPUTE;
                COMPUTE:
                    state <= WRITE_OUTPUT;
                WRITE_OUTPUT:
                    if (output_counter == (T * M) / 4) state <= IDLE;
                    else state <= LOAD_INPUT;
            endcase
        end
    end

    assign EN_I = (state == LOAD_INPUT);
    assign ADDR_I = (state == LOAD_INPUT) ? output_counter[2:0] : 3'b0;
    always @(posedge CLK) begin
        if (state == LOAD_INPUT) begin
            input_reg[0] <= RDATA_I[63:0];
            input_reg[1] <= RDATA_I[63:0];
            input_reg[2] <= RDATA_I[63:0];
            input_reg[3] <= RDATA_I[63:0];
        end
    end

    assign EN_W = (state == LOAD_WEIGHT);
    assign ADDR_W = (state == LOAD_WEIGHT) ? output_counter[2:0] : 3'b0;
    always @(posedge CLK) begin
        if (state == LOAD_WEIGHT) begin
            weight_reg[0] <= RDATA_W[63:0];
            weight_reg[1] <= RDATA_W[63:0];
            weight_reg[2] <= RDATA_W[63:0];
            weight_reg[3] <= RDATA_W[63:0];
        end
    end

    always @(posedge CLK) begin
        if (state == COMPUTE) begin
            mac_result[0] <= input_reg[0] * weight_reg[0] + mac_result[0];
            mac_result[1] <= input_reg[1] * weight_reg[1] + mac_result[1];
            mac_result[2] <= input_reg[2] * weight_reg[2] + mac_result[2];
            mac_result[3] <= input_reg[3] * weight_reg[3] + mac_result[3];
        end
    end

    assign EN_O = (state == WRITE_OUTPUT);
    assign RW_O = (state == WRITE_OUTPUT);
    assign ADDR_O = output_counter[3:0];
    assign WDATA_O = (state == WRITE_OUTPUT) ? {mac_result[3][63:0], mac_result[2][63:0], mac_result[1][63:0], mac_result[0][63:0]} : 64'b0;

    always @(posedge CLK) begin
        if (state == WRITE_OUTPUT) begin
            output_counter <= output_counter + 1;
        end
    end

    // WRITE YOUR MAC_ARRAY DATAPATH CODE



endmodule
