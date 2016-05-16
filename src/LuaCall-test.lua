function func_int_noarg()
	 return 666;
end

function func_int_fois_deux(v)
	 return v*2;
end

function strlen(s)
	 return string.len(s);
end

function defaultstring()
	 return "Je suis une loutre!";
end

function makelogin(s,i)
	 return s..i;
end

function second_hand_main()
	 i, s = appel_au_c(5)
	 print("recu int="..i.."; s="..s)
	 return 0
end