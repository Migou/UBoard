function power(x)
	 local y=1
	 while((x/y)%2==0)
	 do
		y=y*2
	 end   
return y
end

function tobinary(x)
	 if x==0 then
	   return ""
	 elseif x%2==0 then
	    return tobinary(x/2).."0"
	 else
	    return tobinary((x-1)/2).."1"
	 end   
end


function syracuse(x)
  print(x,tobinary(x),power(x))
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

