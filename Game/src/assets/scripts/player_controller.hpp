#pragma once
#include "engine/brown.hpp"
#include "assets/scripts/projectile.hpp"

class player_controller : public brown::scriptable_entity
{
public:
    void on_create()
    {
        health = 100;
        ts = &get_component<transform>();
        anim = &get_component<animator_controller>();
        anim->add_anim("play", {3, false, 0, false, 20, 3, "anim_3"});
    }

    void on_update()
    {
        if (brown::KEY_PRESSED == 'a')
        {
            ts->direction = 4;
            ts->position.x--;
        }
        else if (brown::KEY_PRESSED == 'd')
        {
            ts->direction = 2;
            ts->position.x++;
        }
        
        if (brown::KEY_PRESSED == 'w')
        {
            ts->direction = 1;
            ts->position.y--;
        }
        else if (brown::KEY_PRESSED == 's')
        {
            ts->direction = 3;
            ts->position.y++;
        }

        if (brown::KEY_PRESSED == 'h')
        {
            anim->play("idle");
        }

        else if (brown::KEY_PRESSED == 'g')
        {
            anim->play("play");
        }

        else if (brown::KEY_PRESSED == 't')
        {
            brown::entity proj = m_state->create_entity();
            proj.add_component<transform>({ts->position, ts->direction});
            proj.add_component<sprite>({{2, 2}, "sprite2"});
            proj.add_component<animator_controller>({}).add_anim("explode", {5, false, 0, false, 5, {2, 2}, "animated1", true});
            proj.add_component<native_script>({}).bind<projectile>();
        }
    }

private:
    transform *ts = nullptr;
    animator_controller *anim = nullptr;
    int health;
};
