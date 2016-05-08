-- penser à éventuellement importer lua_ldj_bind.lua, qui définit une fonction pour renvoyer des vecteurs en résultat de fonction vers le C++
local typeActionAllumettes=0;
local typeAjout=1;
local typeChangementEtat=2;
local typeDeplacement=3;
local typePrise=4;
local p_coupvector;
--TODO
-- sudo apt-get install luarocks 
-- sudo luarocks install inspect
-- luarocks is configured by default fos lua 5.1, by chance, -- ``cd sudo cp 5.1/inspect.lua  5.2`` does the trick!


--We will need to call from lua C++ accessors to the model.
-- that way, the model can me writen only in C++.
-- http://gamedevgeek.com/tutorials/calling-c-functions-from-lua/
-- CF la fonction LuaCall::make_callable_from_lua()

local inspect = require('inspect')

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

function Tile:add(v) --très bizarre cette syntaxe . pour les instanciations et : pour le cas où on doit utiliser self.
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
   self.type = "priseGenerique"
   self.piece = piece
   self.prise = emplacementPrise
   self.dest = emplacementDest
   return self
end
 
function Action.newDeplacement(piece,emplacement)
   local self = setmetatable({}, Action)
   self.type = "deplacement"
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
print("yo")
   self.type = "changementEtat"
   self.piece = piece
   self.attr = stringAttr
   self.val = valeur
print("yi")
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


function ChangementEtat(piece,attr,val) 
  print("aaa");
  print("attr="..attr..",val="..val);
  action = Action.newChangementEtat(piece,attr,val) 
  print("yu")


  -- verification de la variable globale curListeAction
  if curListeAction == nil then
     -- version objet lua
     coup = {}
     table.insert(coup,action) 
     table.insert(listeCoups,coup)
     -- version liaison directe C++
print("yv cpp_add_coup("..p_coupvector..")")
 
     cpp_add_coup(p_coupvector)
     print("yw add_action("..p_coupvector..","..typeActionAllumettes..","..val)
     cpp_add_action(p_coupvector,typeActionAllumettes,val) -- en attendant une gestion plus générique du modèle avec un ChangementEtat(piece,attr,val) transmis à C++
print("yx")

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
	print("yo")
  	 self.valeur = 14
	 self.valeur_min = 0
	 self.valeur_max = 14
	 print(inspect(self))
	 return self
end

tile1 = Tile.new()  --ldj= Tile tile1
_lua_mainboard=tile1 -- default board : code généré automatiquement après la première déclaration d'un plateau/case/etc...

--print("tile1="..inspect(tile1))
--print("tile1=" .. tile1.pieces[0].valeur)
--initialisation
piece1 = Pallumettes.new() --default board as none is declared
tile1.add(piece1) -- default destination

function CoupsPossibles(pv,nballumettes)
	 -- on la stocke dans une variable globale
	 p_coupvector = pv 
	 --print("start pointeur="..pv);
	-- if piece1.valeur > 0 then ChangementEtat(piece1,"valeur",piece1.valeur-1) end
	   if nballumettes > 0 then ChangementEtat(piece1,"valeur",1) end		
	-- if piece1.valeur > 1 then ChangementEtat(piece1,"valeur",piece1.valeur-2) end
	   if nballumettes > 1 then ChangementEtat(piece1,"valeur",2) end
	 -- if piece1.valeur > 2 then ChangementEtat(piece1,"valeur",valeur-3) end
	   if nballumettes > 2 then ChangementEtat(piece1,"valeur",3) end
print("end");

end

function Evaluation()
	 return 0
end




------- TEST --------------

print( "valeur = " .. piece1.valeur)

--print(inspect(CoupsPossibles()))