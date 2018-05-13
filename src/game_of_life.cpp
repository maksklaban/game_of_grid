#include "game_of_life.h"

using namespace std;

namespace conway_game
{
    game_of_life::game_of_life(const string& conf_filename/*="conf.ini"*/, const string& log_filename/*="app_log.txt"*/)
        : m_conf_filename(conf_filename),
          m_log_filename(log_filename),
          m_grid_cols(20),
          m_grid_rows(20),
          m_flag_done(true)
          {}

    game_of_life::~game_of_life()
    {
        stop();
    }

    bool game_of_life::load_settings()
    {
        ofstream f;
        string buffer;
        stringstream sstr;
        bool result = true;

        f.open(m_conf_filename, ofstream::out);

        if (!f.is_open())
            return false;

        while (getline(f, buffer))
        {
            if (buffer.find("[grid_rows]") != string::npos)
            {
                for( getline(f, buffer); f.good() && buff[0] == '#'; getline(f, buff) )
                {
                    // skip comments in config file
                }

                if (buffer.size() == 0)
                    result = false;

                sstr.str(buffer);
                sstr >> m_grid_rows;
                sstr.clear();
            }
            else if (buffer.find("[grid_cols]") != string::npos)
            {
                for( getline(f, buffer); f.good() && buff[0] == '#'; getline(f, buff) )
                {
                    // skip comments in config file
                }

                if (buffer.size() == 0)
                    result = false;

                sstr.str(buffer);
                sstr >> m_grid_cols;
                sstr.clear();
            }
            else if (buffer.find("[init_cell_cords]") != string::npos)
            {
                for( getline(f, buff); f.good() && !buff.empty(); getline(f, buff) )
                {
                    if (buff[0] == '#')
                        continue;

                    int x = 0, y = 0;

                    sstr.str(buffer);
                    sstr >> x;
                    sstr >> y;
                    sstr.clear();
                    m_init_cells.push_back(point(x, y));
                }
            }
        }
        return result;
    }

    bool game_of_life::init()
    {
        if (!load_settings())
            return false;

        m_grid_states.push_back(game_grid(m_grid_cols, m_grid_rows, m_init_cells));
    }

    void game_of_life::stop()
    {
        m_flag_done = true;

        unique_lock<mutex> data_mtx(m_states_mtx);
        data_mtx.unlock();

        unique_lock<mutex> cons_mtx(m_cons_mtx);
        unique_lock<mutex> prod_mtx(m_prod_mtx);
    }

    void game_of_life::run()
    {
        m_flag_done = false;

        m_producer = thread([this]()
        {
            unique_lock<mutex> prod_lck(m_prod_mtx);

            while (!m_flag_done)
            {
                this_thread::sleep_for(milliseconds(1000));
                unique_lock<mutex> m_states_mtx;

                game_grid temp(m_grid_states.back());
                temp.determine_state();
                m_grid_states.push_back();
            }
        });
    }
}
