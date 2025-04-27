module Ebreak (
    input [31:0] instruction
);
    import "DPI-C" function void halt();
    always @(*) begin
        if (instruction == 32'b00000000000100000000000001110011) begin
            halt();
        end
    end
endmodule 