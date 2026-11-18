#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
    
    nums.push_back(0); // Charging outlet
    std::sort(nums.begin(), nums.end());
    int cnt_1 {}, cnt_3 {1};

    for (int i = 1; i < (int) nums.size(); i++)
    {
        int diff {nums[i] - nums[i - 1]};
        if (diff  == 1) { cnt_1++; }
        else if (diff == 3) { cnt_3++; }
    }

    std::cout << cnt_1 * cnt_3 << '\n';

    return EXIT_SUCCESS;
}