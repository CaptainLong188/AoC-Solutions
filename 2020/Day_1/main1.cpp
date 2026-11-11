#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

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

    std::unordered_set<int> uset;
    std::string line;
    int num {};

    while (std::getline(inputFile, line))
    {
        num = std::stoi(line);

        if (uset.count(2020 - num) > 0)
        {
            ans = num * (2020 - num);
            std::cout << ans << '\n';
            return EXIT_SUCCESS;
        }

        uset.insert(num);
    }  

    std::cout << "No pair found";

    return EXIT_SUCCESS;
}