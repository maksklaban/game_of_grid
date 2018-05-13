#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

namespace conway_game
{
    struct point
    {
        int x;
        int y;

        point() : x(0), y(0) {}
    };

    class game_of_life
    {
    private:
        std::vector<point> m_init_cells;
        std::list<game_grid> m_grid_states;
        size_t m_grid_cols;
        size_t m_grid_rows;
        std::string m_conf_filename;
        std::string m_log_filename;
        std::ofstream m_log;
        std::thread m_producer;
        std::thread m_consumer;
        std::mutex m_prod_mtx;
        std::mutex m_cons_mtx;
        bool m_debug;

    public:
        game_of_life(const std::string& conf_filename="conf.ini", const std::string& log_filename="app_log.txt");
        virtual ~game_of_life();

        void init();
        void run();
        void stop();
    };
}

#endif // GAME_OF_LIFE_H
