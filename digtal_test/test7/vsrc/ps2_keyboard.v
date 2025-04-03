module ps2_keyboard(//添加计数器
    input clk,clrn,ps2_clk,ps2_data,
    input nextdata_n,
    output [7:0] data,
    output reg ready,   // 队列中是否存在元素
    output reg overflow,     // 队列是否溢出
    output reg[7:0]key_count // 键盘计数
);
    reg [9:0] buffer;        // 输入缓冲区
    reg [7:0] fifo[7:0];     // 数据队列
    reg [2:0] w_ptr,r_ptr;   // 队列读写指针
    reg [3:0] count;  // 输入位数总数
    reg [2:0] ps2_clk_sync; //记录ps2时钟信号

    always @(posedge clk) begin
        ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};//打拍

    end

    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];//下降沿采样

    always @(posedge clk) begin
        if (clrn == 1) begin // 修改复位条件
            count <= 0; w_ptr <= 0; r_ptr <= 0; overflow <= 0; ready<= 0;key_count<=0;
        end
        else begin
            if ( ready ) begin // read to output next data
                if(nextdata_n == 1'b0) //read next data
                begin
                    r_ptr <= r_ptr + 3'b1;
                    if(w_ptr==(r_ptr+1'b1)) //empty
                        ready <= 1'b0;
                end
            end
            if (sampling) begin
              if (count == 4'd10) begin
                if ((buffer[0] == 0) &&  // 开始符
                    (ps2_data)       &&  // 结束符
                    (^buffer[9:1])) begin      // 奇偶校验
                    if(buffer[8:1]==8'hf0)  
                       key_count<=key_count+1;//判断是否为断码，是的话就加一

                    fifo[w_ptr] <= buffer[8:1];  // kbd scan code
                    w_ptr <= w_ptr+3'b1;
                    ready <= 1'b1;
                    overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
                    $display("receive %x", buffer[8:1]);
                end
                count <= 0;     // for next
              end else begin
                buffer[count] <= ps2_data;  // store ps2_data
                count <= count + 3'b1;
              end
            end
        end
    end
    assign data = fifo[r_ptr]; //always set output data

    always @(posedge clk) begin
        $display("count=%d", count);
    end
endmodule
