#include "game_of_life.h"

using namespace std;
using namespace chrono;

namespace conway_game
{
    game_of_life::game_of_life(const string& conf_filename/*="conf.ini"*/, const string& log_filename/*="app_log.txt"*/)
        : m_conf_filename(conf_filename),
          m_log_filename(log_filename),
          m_grid_cols(20),
          m_grid_rows(20)
          {}

    game_of_life::~game_of_life()
    {
        stop();
    }

    void game_of_life::log_state(const game_grid& state)
    {
        time_t rawtime;
        struct tm* timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        cout <<"State:\n" << state << ": timestamp " << asctime(timeinfo) << endl;
    }

    bool game_of_life::load_settings()
    {
        fstream f;
        string buffer;
        stringstream sstr;
        bool result = true;

        f.open(m_conf_filename, ofstream::in);

        if (!f.is_open())
            return false;

        while (getline(f, buffer))
        {
            if (buffer.find("[grid_rows]") != string::npos)
            {
                for( getline(f, buffer); f.good() && buffer[0] == '#'; getline(f, buffer) )
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
                for( getline(f, buffer); f.good() && buffer[0] == '#'; getline(f, buffer) )
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
                for( getline(f, buffer); f.good() && !buffer.empty(); getline(f, buffer) )
                {
                    if (buffer[0] == '#')
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

        m_log.open(m_log_filename, ofstream::ate);
        m_grid_states.push_back(game_grid(m_grid_cols, m_grid_rows, m_init_cells));
        return true;
    }

    void game_of_life::stop()
    {
        unique_lock<mutex> data_mtx(m_states_mtx);
        data_mtx.unlock();

        unique_lock<mutex> cons_mtx(m_cons_mtx);
        unique_lock<mutex> prod_mtx(m_prod_mtx);
    }

    void game_of_life::run()
    {
        m_producer = thread([this]()
        {
            unique_lock<mutex> prod_lck(m_prod_mtx);
            bool result = false;

            while (true)
            {
                this_thread::sleep_for(milliseconds(10));
                unique_lock<mutex> queue_lck(m_states_mtx);

                game_grid temp = m_grid_states.back();
                result = temp.determine_state();
                m_grid_states.push_back(temp);

                if (result)
                    break;
            }
        });

        m_consumer = thread([this]()
        {
            unique_lock<mutex> cons_lck(m_cons_mtx);
            bool result = false;

            while (true)
            {
                this_thread::sleep_for(milliseconds(1000));
                unique_lock<mutex> queue_lck(m_states_mtx);

                auto _it     = m_grid_states.begin();
                auto _it_end = m_grid_states.end();

                while (_it != _it_end)
                {
                    auto& grid_ref = *_it;
                    if (!grid_ref.is_loged())
                    {
                        log_state(grid_ref);
                        grid_ref.set_log_flag();
                    }
                    result = grid_ref.is_over();

                    if (m_grid_states.size() > 1)
                    {
                        _it = m_grid_states.erase(_it);
                    }
                    else
                    {
                        break;
                    }
                }
                if (result)
                    break;
            }
        });

        m_producer.join();
        m_consumer.join();
    }
}
