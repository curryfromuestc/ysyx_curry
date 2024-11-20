module top(
  input clk,
  input rst,
  output reg [15:0] led
 );
reg [31:0] count;
always @(posedge clk) begin
    if (rst) begin 
        led <= 1; count <= 0; 
    end //复位 设置第0位的灯亮起
    else begin
        if (count == 0) led <= {led[14:0], led[15]}; //等的状态循环移动
        count <= (count >= 5000000 ? 32'b0 : count + 1);//循环5000001次对count置零
    end
end
endmodule
