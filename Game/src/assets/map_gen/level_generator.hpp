#pragma once
#include <random>
#include "engine/std/queue.hpp"
#include "engine/std/vector.hpp"
#include "engine/math/math.hpp"

enum ROOM_TYPE {
    EMPTY = 0,
    NORMAL_UNDISCOVERED = 1,
    NORMAL = 2,
    BOSS_UNDISCOVERED = 3,
    BOSS = 4,
    KEY_ROOM_UNDISCOVERED = 5,
    KEY_ROOM = 6,
};

class level_generator{
    private:
        brown::dt::queue<int> m_endrooms;     // Stack con l'ultima stanza visitata
        brown::dt::queue<int> m_rooms;        // Stack con tutte le stanze

        brown::dt::vector<int> m_floorplan;   // Vettore con le stanze

        int m_room_count = 0;           

        bool placed_special = false;    
        int max_rooms = 20;             // massimo stanze
        int min_rooms = int((random_int(1, 3)) + 5 + depth * 2.6);             // minimo stanze

        int depth = 1;

        std::mt19937 rng;
        std::uniform_real_distribution<double> rand;

        bool is_key_picked_up = false;

    private:
        

        int pop_endroom();
        void pick_secretroom();

        int neighbour_count(int);

    public:
        void key_picked_up() { is_key_picked_up = true;}
        bool is_unlocked() { return is_key_picked_up; }

        level_generator(int depth): depth(depth + 1)
        {
            for (int i = 0; i < 100; i++)
            {
                this->m_floorplan.push_back(0);
            }
            rng = std::mt19937(time(NULL));
            rand = std::uniform_real_distribution<double>(0, 1);

            min_rooms = (int)(1.8 * depth + 6);
        }

        int room_count()
        {
            return this->m_room_count;
        }

        bool visit(int);

        void start();

        void generate();

        brown::dt::vector<int> get_floorplan()
        {
            return this->m_floorplan;
        }
};