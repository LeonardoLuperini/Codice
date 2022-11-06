module fa (output newcarry, output z, input a, input b, input carry);
	assign {newcarry, z} = a + b + carry; //somme in complemento a due, fa la somma di a + b + carry e cattura in newcarry il bit in più mentre in z il bit normale della somma
	// ^ è scritto in modo behavioral
endmodule

module faN (output carryout, output [N-1:0] z, input [N-1:0] a, input [N-1:0] b, input carryin);
	parameter N = 32;
	wire [N-2:0] tempcarry;
	
	fa fa0(tempcarry[0], a[0], b[0], carryin);
	
	genvar i;
	generate
		for (i=1; i<N-1; i=1+1) begin
			fa fai(tempcarry[i], a[i], b[i], tempcarry[i-1]);
		end
	endgenerate

	fa faN(tempcarry[N-2], a[N-1], b[N-1], carryout);
endmodule
