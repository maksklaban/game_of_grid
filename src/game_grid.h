#ifndef GAME_GRID_H
#define GAME_GRID_H

#include "defines.h"

namespace conway_game
{
    struct point;

    typedef std::vector< std::vector<bool> > bool_matrix;

    class game_grid
    {
    private:
        bool_matrix m_grid_curr;
        size_t m_grid_cols;
        size_t m_grid_rows;
        bool m_is_over;
        bool m_is_loged;

    public:
        game_grid(size_t grid_cols, size_t grid_rows, const std::vector<point>& points);
        game_grid(const game_grid& another);
        ~game_grid();

        game_grid& operator=(const game_grid& another);
        bool operator==(const game_grid& another) const;

        const bool_matrix& get_grid() const;
        size_t get_cols_count() const;
        size_t get_rows_count() const;
        bool is_over() const;
        bool is_loged() const;

        void set_log_flag();

        bool determine_state();
    };

    std::ostream& operator<< (std::ostream& stream, const game_grid& grid);
}

#endif // GAME_GRID_H
