function player_regenerate_mana()
    -- At this point there is no condition which prevents mana regeneration 
    if player_get_mana() < player_get_max_mana() then
        increment = (player_get_power() * player_get_max_mana()) / 1000 + player_get_level()
        player_set_mana(min(player_get_max_mana(), player_get_mana() + increment))
    end
end
