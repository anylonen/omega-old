require("log")

player = {}
status = {}

status["ACCURACY"]      = {["id"] =  0, ["value"] = 0}
status["BLINDED"]       = {["id"] =  1, ["value"] = 0}
status["SLOWED"]        = {["id"] =  2, ["value"] = 0}
status["DISPLACED"]     = {["id"] =  3, ["value"] = 0}
status["SLEPT"]         = {["id"] =  4, ["value"] = 0}
status["DISEASED"]      = {["id"] =  5, ["value"] = 0}
status["POISONED"]      = {["id"] =  6, ["value"] = 0}
status["HASTED"]        = {["id"] =  7, ["value"] = 0}
status["BREATHING"]     = {["id"] =  8, ["value"] = 0}
status["INVISIBLE"]     = {["id"] =  9, ["value"] = 0}
status["REGENERATING"]  = {["id"] = 10, ["value"] = 0}
status["VULNERABLE"]    = {["id"] = 11, ["value"] = 0}
status["BERSERK"]       = {["id"] = 12, ["value"] = 0}
status["IMMOBILE"]      = {["id"] = 13, ["value"] = 0}
status["ALERT"]         = {["id"] = 14, ["value"] = 0}
status["AFRAID"]        = {["id"] = 15, ["value"] = 0}
status["HERO"]          = {["id"] = 16, ["value"] = 0}
status["LEVITATING"]    = {["id"] = 17, ["value"] = 0}
status["ACCURATE"]      = {["id"] = 18, ["value"] = 0}
status["TRUESIGHT"]     = {["id"] = 19, ["value"] = 0}
status["SHADOWFORM"]    = {["id"] = 20, ["value"] = 0}
status["ILLUMINATION"]  = {["id"] = 21, ["value"] = 0}
status["DEFLECTION"]    = {["id"] = 22, ["value"] = 0}
status["PROTECTION"]    = {["id"] = 23, ["value"] = 0}
status["RETURNING"]     = {["id"] = 24, ["value"] = 0}
status["NUMSTATI"]      = {["id"] = 25, ["value"] = 0}

player["status"] = status 

function player_get_status_id(status_name)
    local status_value = player_get_status(status_name)
    return player.status[status_name].id
end

function player_regenerate_mana()
    -- At this point there is no condition which prevents mana regeneration 
    if player_get_mana() < player_get_max_mana() then
        local increment = (player_get_power() * player_get_max_mana()) / 1000 + player_get_level()
        player_set_mana(min(player_get_max_mana(), player_get_mana() + increment))
    end
end

function player_calculate_mana()
    local amount = player_get_power() * player_get_level() + 1
    return amount
end
