#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

bool isValid(const char* str)
{
    int len {(int) std::strlen(str)};
    return len == 8 || (len == 7 && std::count(str, str + 8, 'c') == 0);
}

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
    char first[9] = {}; // This holds 8 characters
    int idx {};

    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            // Check if the passport is valid
            if (isValid(first)) { ans++; }

            idx = 0;
            std::fill(first, first + 8, '\0');
            continue;
        }

        if (idx < 8) { first[idx++] = line[0] ;}
        
        for (int i = 1;  i + 1 < (int) line.size(); i++)
        {
            if (line[i] == ' ') { first[idx++] = line[i + 1]; }
        }
    }   

    // Check last passport
    if (isValid(first)) { ans++; }

    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}