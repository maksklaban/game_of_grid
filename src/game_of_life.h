#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

struct point
{
    int x;
    int y;

    point() : x(0), y(0) {}
};

class game_of_life
{
private:
    std::vector< std::vector<bool> > m_grid_curr;
    size_t m_grid_cols;
    size_t m_grid_rows;
    bool m_debug;

public:
    game_of_life(size_t grid_cols, size_t grid_rows);
    virtual ~game_of_life();

    void init(const std::vector<point>& cells_cord);
    void start();
    void stop();
};

#endif // GAME_OF_LIFE_H
