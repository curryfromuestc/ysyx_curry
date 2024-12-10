module top(
    input signed [3:0] a,
    input signed [3:0] b,
    input [2:0] op,
    output reg signed [3:0] y
);

always @(*) begin
    case (op)
        3'b000: y = a + b;
        3'b001: y = a - b;
        3'b010: y = -a;
        3'b011: y = a&b;
        3'b100: y = a|b;
        3'b101: y = a^b;
        3'b110: y = (a > b) ? 0 : 1;
        3'b111: y = (a == b) ? 1 : 0;
    endcase
end

endmodule
