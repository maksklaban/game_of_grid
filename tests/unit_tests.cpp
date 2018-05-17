#include <vector>
#include <algorithm>

#include "../src/game_of_life.h"
#include "catch.hpp"

using namespace conway_game;

TEST_CASE("game_of_life test(conf_test.ini)", "[Game of life test]")
{
    game_of_life test_app("conf_test.ini");
    test_app.init();
    auto& grid_cols = test_app.get_grid_cols();
    auto& grid_rows = test_app.get_grid_rows();
    auto& points_ref = test_app.get_init_cells();    
    
    SECTION("Game of life init")
    {
        REQUIRE(grid_cols == 12);
        REQUIRE(grid_rows == 33);

        auto _it = points_ref.begin();
        auto _it_end = points_ref.end();
        auto _find1 = std::find(_it, _it_end, point(2, 0));
        auto _find2 = std::find(_it, _it_end, point(-1, 2));
        auto _find3 = std::find(_it, _it_end, point(11, 0));

        REQUIRE(points_ref.size() == 8);
        REQUIRE(_find1 != _it_end);
        REQUIRE(_find2 != _it_end);
        REQUIRE(_find3 == _it_end);
    }

    SECTION("Game grid tests")
    {
        game_grid test_grid(grid_cols, grid_rows, points_ref);
        auto& grid_points_ref = test_grid.get_grid();

        std::vector<point> init_point_values1;
        init_point_values1.push_back(point(0,1));
        init_point_values1.push_back(point(1,2));
        init_point_values1.push_back(point(2,0));
        init_point_values1.push_back(point(2,1));
        init_point_values1.push_back(point(2,2));
        init_point_values1.push_back(point(111,233));
        init_point_values1.push_back(point(0,22222));
        init_point_values1.push_back(point(-1,2));

        std::vector<point> init_point_values2;
        init_point_values2.push_back(point(3,4));
        init_point_values2.push_back(point(4,5));
        init_point_values2.push_back(point(4,3));
        init_point_values2.push_back(point(1,4));
        init_point_values2.push_back(point(5,3));

        std::vector<point> init_point_values3;
        init_point_values3.push_back(point(3,4));
        init_point_values3.push_back(point(4,3));
        init_point_values3.push_back(point(5,4));


        game_grid test_grid2(12, 33, init_point_values1);
        game_grid test_grid3(20, 20, std::vector<point>());
        test_grid3.set_log_flag();
        game_grid test_grid4(test_grid3);
        game_grid test_grid5(10, 10, init_point_values2);
        test_grid5.determine_state();
        game_grid test_grid6(10, 10, init_point_values3);


        REQUIRE(grid_points_ref[0][2] == true);
        REQUIRE(grid_points_ref[11][0] == false);
        REQUIRE(grid_points_ref[2][2] == true);
        REQUIRE(grid_points_ref[1][2] == true);

        REQUIRE(grid_points_ref.size() == test_grid.get_cols_count() + 1);
        REQUIRE(grid_points_ref[0].size() == test_grid.get_rows_count() + 1);
        REQUIRE(test_grid.is_over()  == false);
        REQUIRE(test_grid.is_loged() == false);

        REQUIRE(test_grid == test_grid2);

        REQUIRE(!(test_grid == test_grid3));
        REQUIRE(test_grid3.is_over() == true);
        REQUIRE(test_grid3.is_loged() == true);

        REQUIRE(test_grid4 == test_grid3);
        REQUIRE(test_grid4.is_over() == true);
        REQUIRE(test_grid4.is_loged() == false);

        REQUIRE(test_grid5 == test_grid6);
        REQUIRE(test_grid5.is_over() == false);
    }
}