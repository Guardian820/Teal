-- Some utility functions

require "luautil.lua"

function HasCharacterPlayed(character)
    return teal_fight_data.character.index > character.index
end

Character = Class()

function Character:MoveToward(character)
    self:MoveTo(character.x, character.y)
end

function Character:MoveTo(x, y)
    Teal_MoveCharacter(x, y)
end

function Character:MoveAwayFrom(x, y)
    Teal_MoveCharacterAwayFrom(x, y)
end

function Character:Attack(characterIndex, skillCodename)
    Teal_AttackCharacter(characterIndex, skillCodename)
end