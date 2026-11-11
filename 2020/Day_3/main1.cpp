#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc < 2) { return EXIT_FAILURE; }

    int ans {};
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
    
    // Slope: Right 3 Down 1
    int pos_x {};
    int rows = (int) area.size();
    int cols = area[0].size();

    for (int i = 0; i < rows; i++)
    {
        if (area[i][pos_x] == '#') { ans++; }
        pos_x = (pos_x + 3) % cols;
    }

    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}