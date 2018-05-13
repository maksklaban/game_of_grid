#ifndef GAME_GRID_H
#define GAME_GRID_H

namespace conway_game
{
    class game_grid
    {
    private:
        std::vector< std::vector<bool> > m_grid_curr;
        size_t m_grid_cols;
        size_t m_grid_rows;

    public:
        game_grid(size_t grid_cols, size_t grid_rows);
        game_grid(const game_grid& another);
        ~game_grid();

        void determine_state();
    };

    std::ostream& operator<< (std::ostream& stream, const game_grid& grid);
}

#endif // GAME_GRID_H
