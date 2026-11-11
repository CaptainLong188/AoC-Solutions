#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc < 2) { return EXIT_FAILURE; }

    int ans {1};
    std::ifstream inputFile {argv[1]};

    if (!inputFile.is_open())
    {
        std::cerr << "Could not open " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    std::string row;
    std::vector<std::string> area;

    while (std::getline(inputFile, row))
    {
        area.push_back(row);
    }
    
    int rows = (int) area.size();
    int cols = area[0].size();
    int slopes[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

    for (int i = 0; i < 5; i++)
    {
        int cnt {}, pos_x {};

        for (int j = 0; j < rows; (slopes[i][1] == 1 ? j++ : j+=2))
        {
            if (area[j][pos_x] == '#') { cnt++; }
            pos_x = (pos_x + slopes[i][0]) % cols;
        }

        ans *= cnt;
    }

    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}