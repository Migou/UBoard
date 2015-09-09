function syracuse(x)
  print(x)
  if x == 1 then
        return 0,x
  elseif x % 2 == 0 then
	top, nbloop = syracuse(x/2)
  else
	top, nbloop = syracuse(3*x+1)
  end
  return math.max(top,x), nbloop+1
end

math.randomseed(os.time())
top,nbloop = syracuse(math.random(1000))
print("TOP=",top)
print("NBLOOP=",nbloop)

