`timescale 1ns/1ps

module ram (
    input  wire       clk,
    input  wire       we,
    input  wire [3:0] addr,
    input  wire [7:0] din,
    output reg  [7:0] dout
);

reg [7:0] mem [0:15];
integer i;

initial begin
    for (i = 0; i < 16; i = i + 1)
        mem[i] = 8'h00;
end

always @(posedge clk) begin
    if (we)
        mem[addr] <= din;
    dout <= mem[addr];
end

endmodule


module tb;

reg clk;
reg we;
reg [3:0] addr;
reg [7:0] din;
wire [7:0] dout;

ram uut (
    .clk(clk),
    .we(we),
    .addr(addr),
    .din(din),
    .dout(dout)
);

// 时钟：10ns 周期
initial begin
    clk = 0;
    forever #5 clk = ~clk;
end

// 波形和测试流程
initial begin
    $dumpfile("ram.vcd");
    $dumpvars(0, tb);

    // 也可以加监视，方便看变化
    $monitor("t=%0t clk=%b we=%b addr=%0d din=%h dout=%h",
             $time, clk, we, addr, din, dout);

    we   = 0;
    addr = 0;
    din  = 0;

    // 在下降沿之后再改输入，避免和 posedge 打架
    @(negedge clk);
    we   = 1;
    addr = 4'h3;
    din  = 8'hAA;

    @(negedge clk);
    addr = 4'h5;
    din  = 8'h55;

    @(negedge clk);
    we   = 0;
    addr = 4'h3;

    @(negedge clk);
    addr = 4'h5;

    @(negedge clk);
    $finish;
end

endmodule












