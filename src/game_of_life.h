#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "defines.h"

namespace conway_game
{
    class game_grid;

    struct point
    {
        int x;
        int y;

        point(int x, int y) : x(x), y(y) {}

        bool operator==(const point& other) const
        {
            return this->x == other.x && this->y == other.y;
        }
    };

    class game_of_life
    {
    private:
        std::vector<point> m_init_cells;
        std::list<game_grid> m_grid_states;
        std::string m_conf_filename;
        std::string m_log_filename;
        size_t m_grid_cols;
        size_t m_grid_rows;
        std::ofstream m_log;
        std::thread m_producer;
        std::thread m_consumer;
        std::mutex m_prod_mtx;
        std::mutex m_cons_mtx;
        std::mutex m_states_mtx;
        bool m_flag_done;

        bool load_settings();
        void log_state(game_grid& state);
    public:
        game_of_life(const std::string& conf_filename="conf.ini", const std::string& log_filename="game_log.txt");
        virtual ~game_of_life();

        const std::vector<point>& get_init_cells() const;
        const size_t& get_grid_cols() const;
        const size_t& get_grid_rows() const;

        bool init();
        void run();
        void stop();
    };
}

#endif // GAME_OF_LIFE_H
