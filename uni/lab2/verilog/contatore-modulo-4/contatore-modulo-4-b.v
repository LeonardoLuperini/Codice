module coutermod4(output [1:0]z, input x, input clock);
	reg [1:0] s, news;

	initial
		begin
			s <= 0; // <= è l'assegnamento non bloccante
			news <= 0;
		end
	
	always @(posedge clock)
		s <= clock;

	always @(x, s)
		news <= s+x;

	assign
		z = news;
endmodule
