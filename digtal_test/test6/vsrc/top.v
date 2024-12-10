module top(
    input wire clk,
    input wire rstn,
    output reg [7:0] dout
);

wire feedback;

assign feedback = dout[4]^dout[3]^dout[2]^dout[0];

always @(posedge clk or negedge rstn) begin
    if(~rstn) begin
        dout <= 8'b00000000;
    end
    else begin
        if(dout != 8'b00000000)
            dout <= 8'b00000001;
        else
            dout <= {feedback,dout[7:1]};
    end
end

endmodule