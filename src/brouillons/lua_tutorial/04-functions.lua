function syracuse(x)
  print(x)
  if x == 1 then
        return
  elseif x % 2 == 0 then
	return syracuse(x/2)
  else
	return syracuse(3*x+1)
  end
end


syracuse(math.random(1000))
