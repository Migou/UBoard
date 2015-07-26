 -- ouf oh putain j'ai réussi!

function f(a,b,...)
  print("a="..a)
  print("b="..b)
  print("suite=")
  length=select("#",...)
  print(length.." more arguments")
  x=select(1,...)
  y=select(2,...)
  print("x="..x)
  print("y="..y)
end

f("je","suis","un","chat")