#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

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

    std::string line;

    while (std::getline(inputFile, line))
    {
        int lo, hi;
        char ch, password[64];

        if (std::sscanf(line.c_str(), "%d-%d %c: %63s", &lo, &hi, &ch, password) != 4)
        {
            continue;
        }

        if (password[lo - 1] == ch ^ password[hi - 1] == ch) { ans++; }
    }
    
    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}