function func_hello(langue)
	if langue=="english" then
		print("LUA - Hello World")
		return 0
	else
		if langue=="francais" then
			print("LUA - Bonjour le Monde !")
			return 0
		else
			print("LUA - euh...")
			return 1
		end
	end
end

function retours_multiples(a)
	 return a-1,a+1
end