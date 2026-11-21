#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::vector<std::pair<int, int>> dirs = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

bool inside(int rows, int cols, int x, int y)
{
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int countOccupied(const std::vector<std::string>& grid, int r, int c)
{
    int rows {(int) grid.size()}, cols {(int) grid[0].size()};
    int cnt {};

    for (const auto& dir: dirs)
    {
        int nr {r + dir.first}, nc {c + dir.second};
        if (inside(rows, cols, nr, nc) && grid[nr][nc] == '#') { cnt++; }
    }

    return cnt;
}

bool process(std::vector<std::string>& grid)
{
    int rows {(int) grid.size()}, cols {(int) grid[0].size()};
    const std::vector<std::string> prev {grid};
    bool changed {false};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int seat {prev[i][j]};

            if (seat == '.') continue;

            int occupied {countOccupied(prev, i, j)};

            // If the seat is empty and there are no occupied seats adjacent to it
            // it becomes occupied
            if (seat == 'L' && occupied == 0)
            {
                grid[i][j] = '#';
                changed = true;
            }
            // If the seat is occupied and four or more seats adjacent to it are also occupied 
            // the seat becomes empty
            else if (seat == '#' && occupied >= 4)
            {
                grid[i][j] = 'L';
                changed = true;
            }
        }
    }

    return changed;
}

int main(int argc, char *argv[])
{
    if (argc < 2) { return EXIT_FAILURE; }

    std::ifstream inputFile {argv[1]};

    if (!inputFile.is_open())
    {
        std::cerr << "Could not open " << argv[1] << '\n';
        return EXIT_FAILURE;
    }
    std::string line;
    std::vector<std::string> seats;

    while (std::getline(inputFile, line)) { seats.push_back(line); }

    while (process(seats)) {} // it will break when the seats remain the same

    int cnt {};
    for (const auto& row: seats)
    {
        cnt += std::count(row.begin(), row.end(), '#');
    }

    std::cout << cnt << '\n';

    return EXIT_SUCCESS;
}