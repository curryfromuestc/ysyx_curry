module ps2_to_ascii (
  input [7:0]x, 
  output [7:0]y
);
  reg [7:0] tmp;

  always @(*) begin
    case (x)
    8'h1c:tmp=8'h61;
    8'h32:tmp=8'h62;
    8'h21:tmp=8'h63;
    8'h23:tmp=8'h64;
    8'h24:tmp=8'h65;
    8'h2b:tmp=8'h66;
    8'h34:tmp=8'h67;
    8'h33:tmp=8'h68;
    8'h43:tmp=8'h69;
    8'h3b:tmp=8'h6a;
    8'h42:tmp=8'h6b;
    8'h4b:tmp=8'h6c;
    8'h3a:tmp=8'h6d;
    8'h31:tmp=8'h6e;
    8'h44:tmp=8'h6f;
    8'h4d:tmp=8'h70;
    8'h15:tmp=8'h71;
    8'h2d:tmp=8'h72;
    8'h1b:tmp=8'h73;
    8'h2c:tmp=8'h74;
    8'h3c:tmp=8'h75;
    8'h2a:tmp=8'h76;
    8'h1d:tmp=8'h77;
    8'h22:tmp=8'h78;
    8'h35:tmp=8'h79;
    8'h1a:tmp=8'h7a;
    8'hf0:tmp=0;
    8'h45:tmp=8'h30;
    8'h16:tmp=8'h31;
    8'h1e:tmp=8'h32;
    8'h26:tmp=8'h33;
    8'h25:tmp=8'h34;
    8'h2e:tmp=8'h35;
    8'h36:tmp=8'h36;
    8'h3d:tmp=8'h37;
    8'h3e:tmp=8'h38;
    8'h46:tmp=8'h39;
    default:tmp=0;
    endcase
  end

  assign y=tmp;
endmodule
