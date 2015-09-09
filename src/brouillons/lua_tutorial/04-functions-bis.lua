local top=0;
local nbloops=0;

function syracuse(x)
  print(x)
  nbloops = nbloops+1
  top = math.max(top,x)
  if x == 1 then
        return
  elseif x % 2 == 0 then
	return syracuse(x/2)
  else
	return syracuse(3*x+1)
  end
end


math.randomseed(os.time())
syracuse(math.random(1000))
print("TOP=",top)
print("NB ITERATIONS=",nbloops)
