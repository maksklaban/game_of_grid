#include "game_grid.h"

using namespace std;

namespace conway_game
{
    game_grid::game_grid(size_t grid_cols, size_t grid_rows, const vector<point>& points)
        : m_grid_cols(grid_cols), m_grid_rows(grid_rows), m_is_loged(false)
    {
        m_grid_curr.resize(m_grid_cols, vector<bool>(m_grid_rows, 0));

        if (points.empty())
        {
            m_is_over = true;
        }
        else
        {
            for (auto& point: points)
            {
                if (point.x > -1 &&
                    point.y > -1 &&
                    point.x < m_grid_cols &&
                    point.y < m_grid_rows)
                 {
                    m_grid_curr[point.x][point.y] = true;
                 }
            }
            m_is_over = false;
        }

    }

    game_grid::game_grid(const game_grid& another)
    {
        if (this != &another)
        {
//            m_grid_curr = another.m_grid_curr;
            m_grid_cols = another.m_grid_cols;
            m_grid_rows = another.m_grid_rows;
            m_is_over = another.m_is_over;

            m_grid_curr.resize(m_grid_cols + 2, vector<bool>(m_grid_rows, 0));

            for(size_t a = 0; a < m_grid_cols; a++)
            {
                for(size_t b = 0; b < m_grid_rows; b++)
                {
                    m_grid_curr[a][b] = another.m_grid_curr[a][b];
                }
            }
//            memcpy(this, &another, sizeof(game_grid));
        }
    }

    game_grid::~game_grid() {}

    game_grid& game_grid::operator=(const game_grid& another)
    {
        if (this != &another)
        {
            m_grid_cols = another.m_grid_cols;
            m_grid_rows = another.m_grid_rows;
            m_is_over = another.m_is_over;

            m_grid_curr.resize(m_grid_cols + 2, vector<bool>(m_grid_rows, 0));

            for(size_t y = 0; y < m_grid_cols; y++)
            {
                for(size_t x = 0; x < m_grid_rows; x++)
                {
                    m_grid_curr[y][x] = another.m_grid_curr[y][x];
                }
            }
        }
        return *this;
    }

    bool game_grid::operator==(const game_grid& another)
    {
        for(size_t y = 0; y < m_grid_cols; y++)
        {
            for(size_t x = 0; x < m_grid_rows; x++)
            {
                if (m_grid_curr[y][x] != another.m_grid_curr[y][x])
                    return false;
            }
        }
        return true;
    }

    size_t game_grid::get_cols_count() const
    {
        return m_grid_cols;
    }

    size_t game_grid::get_rows_count() const
    {
        return m_grid_rows;
    }

    const bool_matrix& game_grid::get_grid() const
    {
        return m_grid_curr;
    }

    bool game_grid::is_over() const
    {
        return m_is_over;
    }

    bool game_grid::is_loged() const
    {
        return m_is_loged;
    }

    void game_grid::set_log_flag()
    {
        m_is_loged = true;
    }

    bool game_grid::determine_state()
    {
        game_grid temp(*this);
        auto& temp_grid = temp.get_grid();

//        m_is_over = true;
        for(int y = 0; y < m_grid_cols; y++)
        {
            for(int x = 0; x < m_grid_rows; x++)
            {
                int alive = 0;
                for(int c = y - 1; c <= y + 1; c++)
                {
                    for(int d = x - 1; d <= x + 1; d++)
                    {
                        if (c == y && d == x)
                            continue;

                        if(c > -1 && c < m_grid_cols && d > -1 && d < m_grid_rows)
                        {
                            if(temp_grid[c][d])
                            {
                                ++alive;
                            }
                        }
                    }
                }
                if(alive < 2)
                {
                    m_grid_curr[y][x] = false;
                }
                else if(alive == 3)
                {
                    m_is_over = false;
                    m_grid_curr[y][x] = true;
                }
                else if(alive > 3)
                {
                    m_grid_curr[y][x] = false;
                }
            }
        }
        m_is_over = *this == temp;
        return m_is_over;
    }

    ostream& operator<<(ostream& stream, const game_grid& grid)
    {
        size_t cols_count = grid.get_cols_count();
        size_t rows_count = grid.get_rows_count();
        auto& grid_matrix = grid.get_grid();
        for(size_t a = 0; a < cols_count; a++)
        {
            for(size_t b = 0; b < rows_count; b++)
            {
                if(grid_matrix[a][b] == true)
                {
                    stream << " O ";
                }
                else
                {
                    stream << " . ";
                }
                if(b == rows_count-1)
                {
                    stream << endl;
                }
            }
        }
        return stream;
    }
}
