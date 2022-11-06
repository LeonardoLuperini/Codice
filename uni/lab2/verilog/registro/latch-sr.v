module latchSR (output q, output nq, input s, input r);
	assign q = ~(nq | r);
	assign nq = ~(q | s);
endmodule
