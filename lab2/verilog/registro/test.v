module test();
	wire q;
	wire nq;	
	reg s;
	reg r;

	latchSR lsr(q, nq, s, r);

	initial
		begin
			$dumpfile("test.vcd");
			$dumpvars;
			s = 1'b0;
			r = 1'b1;
		end

	initial
		begin
			#1 r = 1'b0;  	
			#1 s = 1'b1;
			#1 s = 1'b0;
			#2 r = 1'b1;
			#1 s = 1'b1;
			#2 $finish;
		end
endmodule
