#pragma once
#include "scriptable_AI.hpp"
#include "types.hpp"
#include "assets/scripts/player_controller.hpp"

class scriptable_enemy : public scriptable_AI
{
public:
    /*void on_interact(brown::event &e)
    {
        if (e.get_param<entity_id>(Events::Entity::Interact::ID) == m_entity.get_id() && is_player_in_range(6))
        {
           m_health--;
        }
    }
    */
    bool check_collision(int dir)
    {
        chtype chars[4] = {
            mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x + 2) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 2, ts->position.x + 1) & A_CHARTEXT,
            mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT};

        // return !(chars[dir - 1] == ' ' || (chars[dir - 1] <= 'z' && chars[dir - 1] >= 'a'));
        return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x';
    }
    void on_create()
    {
        ts = &get_component<transform>();
        m_healthbar = &get_component<ui>();
        m_state->add_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, scriptable_enemy::on_interact));
        t.start();
        damage_t.start();
        t_move.start();
        m_health = 3;

        m_player = static_cast<player_controller*>(m_state->find_entity("player").get_component<native_script>().instance);
    };
    void on_update()
    {
        auto pl= m_state->find_entity("player").get_component<transform>();
        player_controller* pl_h = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        std::string hearts = "";
        for (int i = 0; i < m_health; i++)
            hearts += "❤ ";
        m_healthbar->text = hearts;
        
        if (is_player_in_range(15)&& t_move.elapsed() >=0.5){
            t_move.start();
            if (ts->position.x != pl.position.x)
            {
                if(ts->position.x>pl.position.x ){
                    ts->direction = 3;
                    if(!check_collision(3))
                        ts->position.x--;              
                }else {
                    ts->direction = 1;
                    if(!check_collision(1))
                        ts->position.x++;
                }  
            }
            else if (ts->position.y!=pl.position.y)
            {
                if(ts->position.y>pl.position.y){
                    ts->direction = 4;
                    if (!check_collision(4)) 
                        ts->position.y--;

                }else{
                    ts->direction = 2;
                    if (!check_collision(2))
                        ts->position.y++;
                
                }
            }
        }

        if(t.elapsed() >= rand() % 4 + 1 && pl.position.x==ts->position.x&& pl.position.y==ts->position.y){
            pl_h->set_health(--pl_h->health);
            t.start();
        }
        char e_dmg = mvwinch(m_state->get_win(), ts->position.y,ts->position.x);
        if((e_dmg=='R'||e_dmg=='O'||e_dmg=='L'||e_dmg=='x')&& damage_t.elapsed() >= 1){
            m_health--;
            damage_t.start();
        }
        if(m_health <= 0) {
            delete_self();
        }
        
    }
    void on_destroy()
    {
        m_state->remove_event_listener(METHOD_LISTENER(Events::Entity::Interact::ID, scriptable_enemy::on_interact));
    }
    
private:
    int m_health;
    ui *m_healthbar;
    brown::Timer t;
    brown::Timer damage_t;
    brown::Timer t_move;
    player_controller *m_player;
};
