local Action = {} -- la table représentant la classe, qui sera duppliquée dans chaque instance
MyClass.__index = Action -- ??failed table lookups on the instances should fallback to the class table, to get methods
                         -- en d'autres termes : si on tente d'acceder à moninstance.mafonction et que mafonction n'existe pas dans la structure moninstance :
                         -- lua lit moninstance.__index, et recherche la fonction dans ce qu'elle contient. Or, on sait que la table de la classe a été recopiée dans la métatable de l'instance, donc la métatable contient __index = Action
  -- Action est une variable comme tout le monde...
  -- il recherche aloes Action.mafonction

-- 

function State.execute(action) 

end

function Action.newPrise(piece,emplacement)
  local self = setmetatable({}, Action)
  self.type = "prise"
  self.piece = piece
  self.dest = emplacement
  return self
end

function Action.newPriseGenerique(piece,emplacementPris,emplacementDest)
  local self = setmetatable({}, Action)
  self.type = "prise"
  self.piece = piece
  self.prise = emplacementPrise
  self.dest = emplacementDest
  return self
end

function Action.newDeplacement(piece,emplacement)
  local self = setmetatable({}, Action)
  self.type = "prise"
  self.piece = piece
  self.dest = emplacement
  return self
end


function MyClass.set_value(self, newval)
  self.value = newval
end

function MyClass.get_value(self)
  return self.value
end

local i = MyClass.new(5)
-- tbl:name(arg) is a shortcut for tbl.name(tbl, arg), except tbl is evaluated only once
print(i:get_value()) --> 5
i:set_value(6)
print(i:get_value()) --> 6
