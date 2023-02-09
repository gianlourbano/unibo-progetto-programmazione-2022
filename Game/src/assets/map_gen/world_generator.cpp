#include "world_generator.hpp"
#include "assets/states/room_state.hpp"

void world_generator::generate_new_world()
{
    m_generators.push_back(level_generator());
    m_generators.back().generate();

    m_floorplans.push_back(m_generators.back().get_floorplan());

    rooms new_world = rooms(10, 10);
    m_worlds.push_back(new_world);

    m_worlds.back()[this->m_room_center] = new room_state(room_data(45, 10, 10, nullptr, this, 0));

    m_current_world++;
};

void world_generator::generate_neighbouring_rooms(int index) {
    floorplan fp = m_floorplans[m_current_world];

    if (fp[index - 1]) {
        m_worlds[m_current_world][index - 1] = new room_state(room_data(index-1, 10, 10, nullptr, this, 2));   
    }
    if (fp[index + 1]) {
        m_worlds[m_current_world][index + 1] = new room_state(room_data(index+1, 10, 10, nullptr, this, 4));   
    }
    if (fp[index - 10]) {
        m_worlds[m_current_world][index - 10] = new room_state(room_data(index-10, 10, 10, nullptr, this, 3));   
    }
    if (fp[index + 10]) {
        m_worlds[m_current_world][index + 10] = new room_state(room_data(index+10, 10, 10, nullptr, this, 1));   
    }
}