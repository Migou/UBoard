
 --for de base
 for i=1,9 do
    print(i)
 end
 print("\n")

days = {"Sunday", "Monday", "Tuesday", "Wednesday",
            "Thursday", "Friday", "Saturday"}


  -- itérer juste les clés.
for k in pairs(days) do 
    print(k) 
    print(days[k])
end
print("\n")

  -- itérer les paires (key, value)
for k,v in ipairs(days) do print(k,v) end
print("\n")

-- créer son propre itérateur
  function myiterator ()
      local i = 1;
      return function ()      -- iterator function
        if i<10 then
	  i=i+1
	  return string.format("%c",64 + i-1) --string.format génère les chaines "A", "B", ...
	else	
          return nil  -- no more lines: end of traversal
        end
      end
   end

for v in myiterator()
do
    print(v)
end


-- http://www.lua.org/manual/5.1/manual.html
