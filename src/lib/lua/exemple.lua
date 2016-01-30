--local inspect = require('inspect')

--header

local Action = {}
Action.__index = Action

local Tile = {}
Tile.__index = Tile

-- ajout d'une piece dans la tile
function Tile.new()
	 local self = setmetatable({}, Tile)
	 self.pieces={}
	 return self
end

function Tile.add(v) 
    self.pieces = { v } -- faudra ajouter un push plus tard mais tant qu'on n'a qu'une piece, c'est bon...
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

function Action.newAjout(typePiece,emplacement)
   local self = setmetatable({}, Action)
   self.type = "ajout"

   -- il va falloir créer une piece en fonction de son type, 
   -- sachant que la liste est définie dans un bloc LDJ
    

   self.piece = Piece.new(typePiece);
   self.dest = emplacement
   return self
end

function Action.newChangementEtat(piece,stringAttr,valeur)
   local self = setmetatable({}, Action)
   self.type = "prise"
   self.piece = piece
   self.attr = stringAttr
   self.val = valeur
   return self
end
  






--########################
--# ce bout de code est à placer au début du code ldj
--#
--#

--global variables do not need declaration
listeCoups = {}
--global --curListeAction -- une liste d'action représente un coup

-- permet au scripteur de démarrer un coup composite
function StartActionList()
  curListeAction = {}
end

-- permet au scripteur de terminer un coup composite
function EndActionList()
  -- verification de la variable globale curListeAction
  if curListeAction == nil then
     print("ERROR : EndActionList rencontré mais aucune ActionList n'est ouverte") 
  else 
     table.insert(listeCoups,curListeAction)
     curListeAction = nil
  end
end

----------------------------------------
-- La liste des Mouvements possibles
----------------------------------------
--
--
--

function Ajout(pos)
  action = Action.newAjout(pos) 

  -- verification de la variable globale curListeAction
  if curListeAction == nil then
     coup = {}
     table.insert(coup,action)
     table.insert(listeCoups,coup)
  else
     table.insert(curListeAction,action)
  end
end 


function ChangementEtat(piece,attr,val) -- ? attr, 'attr'
  action = Action.newChangementEtat(piece,attr,val) 

  -- verification de la variable globale curListeAction
  if curListeAction == nil then
     coup = {}
     table.insert(coup,action)
     table.insert(listeCoups,coup)
  else
     table.insert(curListeAction,action)
  end
end 


-- autres Directives de coups

--definition

nbJoueurs = 2


Pallumettes={}
Pallumettes.__index = Piece

function Pallumettes.new()
	 local self = setmetatable({}, Pallumettes)
	
  	 self.valeur = 14
	 self.valeur_min = 0
	 self.valeur_max = 14
	 return self
end

tile1 = Tile.new()  --ldj= Tile tile1
_lua_mainboard=tile1 -- default board : code généré automatiquement après la première déclaration d'un plateau/case/etc...

--print("tile1="..inspect(tile1))
print("tile1=" .. tile1.pieces[0].valeur)
--initialisation
piece1 = Pallumettes.new() --default board as none is declared
tile1.add(piece1) -- default destination

function CoupsPossibles()
   -- default start

  --end
	   if piece1.valeur > 0 then ChangementEtat(piece1,valeur,piece1.valeur-1) end
	   if piece1.valeur > 1 then ChangementEtat(piece1,valeur,piece1.valeur-2) end
	   if piece1.valeur > 2 then ChangementEtat(piece1,valeur,piece1.valeur-3) end

-- default fuction ending
   return listeCoups
end

function Evaluation()
	 return 0
end




------- TEST --------------

print( "valeur = " .. piece1.valeur)