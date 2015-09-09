--VB : code repompé ici : http://lua-users.org/wiki/InheritanceTutorial

-- Create a new class that inherits from a base class
-- VB : Crée la classe (une variable en lua) et pas l'instance.
function inheritsFrom( baseClass )

    -- The following lines are equivalent to the SimpleClass example:

    -- Create the table and metatable representing the class.
    local new_class = {}
    local class_mt = { __index = new_class }

    -- Note that this function uses class_mt as an upvalue, so every instance
    -- of the class will share the same metatable.
    --
    function new_class:create()
        local newinst = {}
        setmetatable( newinst, class_mt )
        return newinst
    end

    -- The following is the key to implementing inheritance:

    -- The __index member of the new class's metatable references the
    -- base class.  This implies that all methods of the base class will
    -- be exposed to the sub-class, and that the sub-class can override
    -- any of these methods.
    --
    if baseClass then
        setmetatable( new_class, { __index = baseClass } )
    end

    return new_class
end

--[[ ca doit fonctionner ainsi :

> -- Create a new class that inherits from SimpleClass
> SubClass = inheritsFrom( SimpleClass )
>
> -- override className() function
> function SubClass:className() print( "SubClass" ) end
>
> -- Create an instance of SimpleClass
> simple = SimpleClass:create()
> 
> simple:className()
SimpleClass

]]--

