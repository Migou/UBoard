------------------------------------------------
-- Les pieces sont définies dans le LDJ, comment les récupère-t-on?
------------------------------------------------
--// implicite  Piece : { position|pioche|NULL }
--Dame : Piece
--Tour : Piece
--...
--Pion : Piece
--Pion2048_ : Piece { valeur = int }
--Lettre : Piece { const valeur = [a-z]|[:espace:] ; const points=[0-10] }



------------------------------------------------
-- Classe Action
------------------------------------------------
local Action = {} -- la table représentant la classe, qui sera duppliquée dans chaque instance
Action.__index = Action -- ??failed table lookups on the instances should fallback to the class table, to get methods
   -- en d'autres termes : si on tente d'acceder à moninstance.mafonction et que mafonction n'existe pas dans la structure moninstance :
   -- lua lit moninstance.__index, et recherche la fonction dans ce qu'elle contient. Or, on sait que la table de la classe a été recopiée dans la métatable de l'instance, donc la métatable contient __index = Action
   -- Action est une variable comme tout le monde...
   -- il recherche aloes Action.mafonction
 
--function State.execute(action) 
--
--end
 
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
   if 


   self.piece = Piece.new(xxx)
   self.dest = emplacement
   return self
end

 






########################
# ce bout de code est à placer au début du code ldj
#
#

global listeCoups = {}
global curListeAction // une liste d'action représente un coup

// permet au scripteur de démarrer un coup composite
function StartActionList()
  curListeAction = {}
end

// permet au scripteur de terminer un coup composite
function EndActionList()
  // verification de la variable globale curListeAction
  if curListeAction = nil
  then
     print("ERROR : EndActionList rencontré mais aucune ActionList n'est ouverte") 
  else 
     table.insert(listeCoups;curListeAction)
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

  // verification de la variable globale curListeAction
  if curListeAction == nil then
     coup = {}
     table.insert(coup,action)
     table.insert(listeCoups,coup)
  else
     table.insert(curListeAction,action)
  end
end 

function Prise( cible ,  ) // todo voir comment on code en lua des arguments facultatifs 
                                 // ou comment on surcharge une fonction 
   ....
end





// autres Directives de coups