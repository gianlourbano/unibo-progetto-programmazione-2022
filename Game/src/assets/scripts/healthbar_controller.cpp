#include "healthbar_controller.hpp"


    void healtbar_controller::health_changed(brown::event &e)
    {
        m_health = e.get_param<player_data>(Events::Player::Data::DATA).health;
    }

    void healtbar_controller::on_create()
    {
        m_state->add_event_listener(METHOD_LISTENER(Events::Player::DATA, "healthbar", healtbar_controller::health_changed));
        m_healthbar = &get_component<ui>();
        pl = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
        m_health = pl->get_health();
    }
    void healtbar_controller::on_update()
    {
        std::string hearts;
        for (int i = 0; i < m_health / 10; i++)
            hearts += "❤ ";
        m_healthbar->text = "Health (" + std::to_string(m_health) + "/" + std::to_string(pl->get_data().max_health) + "): " + hearts;
    }

    void healtbar_controller::set_health(int health)
    {
        m_health = health;
    }
