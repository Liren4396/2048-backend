#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <iomanip> 

template <std::size_t SIZE>
void print_out(std::array<std::array<std::string, SIZE>, SIZE> map) {
    std::size_t max_width = 0;
    for (const auto& row : map) {
        for (const auto& col : row) {
            if (col != ".") {
                max_width = std::max(max_width, col.length());
            }
        }
    }

    for (const auto& row : map) {
        for (const auto& col : row) {
            if (col == ".") {
                std::cout << std::setw(max_width) << ".";
            } else {
                std::cout << std::setw(max_width) << col;
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

class game_2048 {
public:

    enum class Move { Up, Down, Left, Right };
    game_2048() {
        std::srand(static_cast<unsigned>(std::time(0)));
    }

    template <std::size_t SIZE>
    void start(std::array<std::array<std::string, SIZE>, SIZE>& map) {
        add_random_tile(map);
    }

    std::string merge_point(std::string point) {
        if ("2" == point) return "4";
        else if ("4" == point) return "8";
        else if ("8" == point) return "16";
        else if ("16" == point) return "32";
        else if ("32" == point) return "64";
        else if ("64" == point) return "128";
        else if ("128" == point) return "256";
        else if ("256" == point) return "512";
        else if ("512" == point) return "1024";
        else if ("1024" == point) {
            game_win = true;
            return "2048";
        }
        return point;
    }

    template <std::size_t SIZE>
    void Up_move(std::array<std::array<std::string, SIZE>, SIZE>& map, int n) {
        for (int j = 0; j < n; ++j) {
            for (int i = 1; i < n; ++i) {
                if (map[i][j] == ".") continue;
                int z = i-1;

                while (z > 0 && map[z][j] == ".") --z;
                if (map[z][j] == map[i][j]) {
                    map[z][j] = merge_point(map[z][j]);
                    map[i][j] = ".";
                } else if (z == 0 && map[z][j] == ".") {
                    map[z][j] = map[i][j];
                    map[i][j] = ".";
                } else {
                    map[z+1][j] = map[i][j];
                    if (z+1 != i) map[i][j] = ".";
                }
            }
        }
    }
    template <std::size_t SIZE>
    void Down_move(std::array<std::array<std::string, SIZE>, SIZE>& map, int n) {
        for (int j = n-1; j >= 0; --j) {
            for (int i = n-2; i >= 0; --i) {
                if (map[i][j] == ".") continue;
                int z = i+1;
                while (z <= n-1 && map[z][j] == ".") ++z;
                if (map[z][j] == map[i][j]) {
                    map[z][j] = merge_point(map[z][j]);
                    map[i][j] = ".";
                } else if (z == n-1 && map[z][j] == ".") {
                    map[z][j] = map[i][j];
                    map[i][j] = ".";
                } else {
                    map[z-1][j] = map[i][j];
                    if (z-1 != i) map[i][j] = ".";
                }
                
            }
        }
    }
    template <std::size_t SIZE>
    void Left_move(std::array<std::array<std::string, SIZE>, SIZE>& map, int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                if (map[i][j] == ".") continue;
                int z = j-1;
                while (z > 0 && map[i][z] == ".") --z;
                if (map[i][z] == map[i][j]) {
                    map[i][z] = merge_point(map[i][z]);
                    map[i][j] = ".";
                } else if (z == 0 && map[i][z] == ".") {
                    map[i][z] = map[i][j];
                    map[i][j] = ".";
                } else {
                    map[i][z+1] = map[i][j];
                    if (z+1 != j) map[i][j] = ".";
                }
            }
        }
    }
    template <std::size_t SIZE>
    void Right_move(std::array<std::array<std::string, SIZE>, SIZE>& map, int n) {
        for (int i = n-1; i >= 0; --i) {
            for (int j = n-2; j >= 0; --j) {
                if (map[i][j] == ".") continue;
                int z = j+1;
                while (z <= n-1 && map[i][z] == ".") ++z;
                if (map[i][z] == map[i][j]) {
                    map[i][z] = merge_point(map[i][z]);
                    map[i][j] = ".";
                } else if (z == n-1 && map[i][z] == ".") {
                    map[i][z] = map[i][j];
                    map[i][j] = ".";
                } else {
                    map[i][z-1] = map[i][j];
                    if (z-1 != j) map[i][j] = ".";
                }
            }
        }
    }
    template <std::size_t SIZE>
    void game_move(std::array<std::array<std::string, SIZE>, SIZE>& map, Move direction) {
        std::array<std::array<std::string, SIZE>, SIZE> original_map = map;
        int n = map.size();
        if (Move::Up == direction) {
            Up_move(map, n);
        } else if (Move::Down == direction) {
            Down_move(map, n);
        } else if (Move::Right == direction) {
            Right_move(map, n);
        } else if (Move::Left == direction) {
            Left_move(map, n);
        }
        if (original_map != map) {
            add_random_tile(map);
        } else {
            std::cout << "No tiles moved" << std::endl;
        }
        
    }
    template <std::size_t SIZE>
    void add_random_tile(std::array<std::array<std::string, SIZE>, SIZE>& map) {
        std::vector<std::pair<int, int>> empty_list;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (map[i][j] == ".") {
                    empty_list.push_back({i, j});
                }
            }
        }
        if (!empty_list.empty()) {
            int index = std::rand() % empty_list.size();
            int i = empty_list[index].first;
            int j = empty_list[index].second;
            map[i][j] = (std::rand() % 2 == 0) ? "2" : "4";
        }
        std::cout << "produced ramdom new points" << std::endl;
        print_out(map);
    }
    template <std::size_t SIZE>
    void check_game_fail(std::array<std::array<std::string, SIZE>, SIZE>& map) {
        bool flag = true;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (map[i][j] == ".") {
                    flag = false;
                } else if (j > 0 && map[i][j-1] == map[i][j]) {
                    flag = false;
                } else if (i > 0 && map[i-1][j] == map[i][j]) {
                    flag = false;
                }
            }
        }
        game_lose = flag;
    }
    bool get_game_win_status() {
        return game_win;
    }

    bool get_game_lose_status() {
        return game_lose;
    }
private:
    bool game_win = false;
    bool game_lose = false;
};


int main() {
    game_2048 game;
    std::array<std::array<std::string, 4>, 4> map = {{{ ".", ".", ".", "." },
                   { ".", ".", ".", "." },
                   { ".", ".", ".", "." },
                   { ".", ".", ".", "." }}};
    game.start(map);
    while (true) {
        
        std::string curr_dir;
        std::cout << "input an direction: ";
        std::cin >> curr_dir;
        if (game.get_game_win_status() == true) {
            std::cout << "you win!" << std::endl;
            break;
        }
        if (game.get_game_lose_status() == true) {
            std::cout << "you lose." << std::endl;
            break;
        }
        if (curr_dir == "w") {
            game.game_move(map, game_2048::Move::Up);
        } else if (curr_dir == "a") {
            game.game_move(map, game_2048::Move::Left);
        } else if (curr_dir == "s") {
            game.game_move(map, game_2048::Move::Down);
        } else if (curr_dir == "d") {
            game.game_move(map, game_2048::Move::Right);
        }
        game.check_game_fail(map);
        if (game.get_game_win_status() == true) {
            std::cout << "you win!" << std::endl;
            break;
        }
        
        if (game.get_game_lose_status() == true) {
            std::cout << "you lose." << std::endl;
            break;
        }
    }
}