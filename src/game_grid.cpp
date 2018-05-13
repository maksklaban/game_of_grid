#include "game_grid.h"

using namespace std;

namespace conway_game
{
    game_grid::game_grid(size_t grid_cols, size_t grid_rows, const vector<point>& points)
        : m_grid_cols(grid_cols), m_grid_rows(grid_rows)
    {
        m_grid_curr.resize(m_grid_cols, vector<bool>(m_grid_rows, 0));

        for (auto& point: points)
        {
            m_grid_curr[x][y] = true;
        }
    }

    game_grid::game_grid(const game_grid& another)
    {
        memcpy(this, *another, sizeof(game_grid));
    }

    game_grid::~game_grid() {}

    void game_grid::determine_state()
    {
        for(int a = 1; a < grid_cols; a++)
        {
            for(int b = 1; b < grid_rows; b++)
            {
                int alive = 0;
                for(int c = -1; c < 2; c++)
                {
                    for(int d = -1; d < 2; d++)
                    {
                        if(!(c == 0 && d == 0))
                        {
                            if(m_grid_curr[a+c][b+d])
                            {
                                ++alive;
                            }
                        }
                    }
                }
                if(alive < 2)
                {
                    m_grid_curr[a][b] = false;
                }
                else if(alive == 3)
                {
                    m_grid_curr[a][b] = true;
                }
                else if(alive > 3)
                {
                    m_grid_curr[a][b] = false;
                }
            }
        }
    }

    ostream& operator<<(ostream& stream, const game_grid& grid)
    {
        for(int a = 1; a < grid_cols; a++)
            {
            for(int b = 1; b < grid_rows; b++)
            {
                if(m_grid_curr[a][b] == true)
                {
                    stream << " O ";
                }
                else
                {
                    stream << " . ";
                }
                if(b == grid_rows-1)
                {
                    stream << endl;
                }
            }
        }
        return stream;
    }
}
