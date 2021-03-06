 -- This is a test file

teal_monster =
{
    texture = ":/game/char/villager",
    size = { x = 113, y = 99 },
    offset = { x = -25, y = -66 },

    animations =
    {
     -- Only one animation per type, syntax:
     -- { "type", "animation_codename" }
        { "walk", "villager_walking" },
     -- { "run", "villager_running" }
    },

    maxhealth = 100,
    name = "VillagerMonster",
    family = "Villagers",
    
    fight =
    {
        autoAttack = false,
        movementPoints = 3,
        actionPoints = 6
    }
}
