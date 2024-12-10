module top (
  input clk,clrn,ps2_clk,ps2_data,
  output reg [7:0] seg0,seg1,seg2,seg3,seg4,seg5,seg6=8'hff,seg7=8'hff//seg7,sen6不用
);
  reg nextdata_n = 1'b0;
  reg overflow;
  reg [7:0] data,tmp_data,out_data;
  reg [7:0] key_count;
  reg [7:0] ascii;
  reg ready;

  reg [7:0] tmp_seg0,tmp_seg1,tmp_seg2,tmp_seg3;
  //四个状态
  reg [2:0] a=3'b000;//初始状态，等待输入
  reg [2:0] b=3'b001;//这个状态，是out_data写入
  reg [2:0] c=3'b010;//将out_data的数据显示在数码管上
  reg [2:0] d=3'b011;//将out_data的数据显示在数码管上

  reg [2:0] state=a,next_state;
	//输出ready，overflow，tmp_data，key_count
  ps2_keyboard my_keyboard(
    .clk(clk),
    .clrn(clrn),
    .ps2_clk(ps2_clk),
    .ps2_data(ps2_data),
    .nextdata_n(nextdata_n),
    .data(tmp_data),
    .ready(ready),
    .overflow(overflow),
    .key_count(key_count)
  );
  ps2_to_ascii my_ps2_to_ascii(
    .x(data),
    .y(ascii)
  );
  bcd7seg my_seg1 (
    .b(data[3:0]),
    .h(tmp_seg0)
  );
  bcd7seg my_seg2 (
    .b(data[7:4]),
    .h(tmp_seg1)
  );
  bcd7seg my_seg3 (
    .b(ascii[3:0]),
    .h(tmp_seg2)
  );
  bcd7seg my_seg4 (
    .b(ascii[7:4]),
    .h(tmp_seg3)
  );
  bcd7seg my_seg5 (
    .b(key_count[3:0]),
    .h(seg4)
  );
  bcd7seg my_seg6 (
    .b(key_count[7:4]),
    .h(seg5)
  );
  always @(posedge clk) begin//状态转移逻辑
    if (clrn == 1) state<=a;
    else  state<=next_state;
  end
  always @(*) begin//下一状态逻辑
    if(ready) begin
      case (state)
        a:next_state=b;
        b:next_state=(tmp_data==8'hf0)?c:b;//tmp_data==8'hf0表示松开了按键
        c:next_state=(tmp_data!=8'hf0)?d:c;//状态不为0的时候尽快到状态b更新数据
        d:next_state=(tmp_data!=8'hf0)?b:d;//状态不为0的时候尽快到状态b更新数据
        default:next_state=a;
      endcase
      out_data=tmp_data;
    end
    else begin
      next_state=state;
    end
  end

  always @(posedge clk) begin
      // $display("tmp_data=%x\n",tmp_data);
      //$display("state=%d\n",state);
      if(state != b)begin
        seg0<=8'hff;
        seg1<=8'hff;
        seg2<=8'hff;
        seg3<=8'hff;
      end
      else begin
        if(state == b)begin
          seg0<=tmp_seg0;
          seg1<=tmp_seg1;
          seg2<=tmp_seg2;
          seg3<=tmp_seg3;
        end
        else begin
          seg0<=8'hff;
          seg1<=8'hff;
          seg2<=8'hff;
          seg3<=8'hff;
        end
      end
  end

  assign data=(state==b)?out_data:8'b0;
endmodule
