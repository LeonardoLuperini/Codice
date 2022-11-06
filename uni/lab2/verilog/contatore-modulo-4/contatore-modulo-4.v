module statouscita (output [1:0]z, input [1:0]s, input x);
	assign z[0] = (~s[0] & x) | (s[0] & ~x);
	assign z[1] = (~s[1] & s[0] & x) | (s[1] & ~s[0]) | (s[1] & s[0] & ~x);
endmodule

module registro (output [N-1:0]z, input [N-1:0]inval, input we, input clock);
	parameter N = 32;

	reg [N-1:0] S;

	initial // viene eseguito solo una volta all'inizio della simulazione
		begin
			S = 2'b00;
		end
	
	always @(posedge clock) 
		begin
			if (we==1) S = inval;
		end

	assign
		z = S;
endmodule

module coutermod4 (output [N-1:0]z, input x, input clock);
	parameter N = 2;

	wire [N-1:0] rin;
	wire [N-1:0] rout;

	registro #(N) regs(rout, rin, 1'b1, clock);
	statouscita newst(rin, rout, x);
	
	assign z = rin;
endmodule

module test();
	parameter N = 2;

	reg x;
	reg clock;
	wire [N-1:0]z;
	
	coutermod4 #(N) cnt(z, x, clock);

	initial
		begin
			$dumpfile("test.vcd");
			$dumpvars;
			//$monitor("clock: %b x: %b z: %d",clock, x , z);
			clock = 1'b0;
			x = 1'b0;
			forever #2 clock = ~clock; //simile a always, da ora in poi ogni 2t il clock cambia segno quindi il ciclo di clock dura 4t
		end
	
	initial
		begin
			#1 x = 1'b1;
			#1 x = 1'b1;
			#1 x = 1'b1;
			#1 x = 1'b1;
			#1 x = 1'b1;
			#1 x = 1'b1;
			#1 x = 1'b0;
			#1 x = 1'b1;
			#1 x = 1'b0;
			#1 x = 1'b1;
			#1 x = 1'b0;
			#1 x = 1'b1;
			#5 $finish;
		end
endmodule
