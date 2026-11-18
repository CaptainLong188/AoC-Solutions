#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

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
    std::vector<int> nums {};
    while (std::getline(inputFile, line))
    {
        nums.push_back(std::stoi(line));
    }
    
    std::sort(nums.begin(), nums.end());

    std::vector<ll> ways(nums.back() + 1);
    ways[0] = 1;

    for (const auto& num: nums)
    {
        if (num == 1) { ways[1] = 1; }
        else if (num == 2) { ways[2] = ways[1] + ways[0];}
        else { ways[num] = ways[num - 1] + ways[num - 2] + ways[num - 3]; }
    }

    std::cout << ways[nums.back()] << '\n';

    return EXIT_SUCCESS;
}