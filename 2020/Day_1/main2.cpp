#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
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

    std::string line;
    std::unordered_set<int> uset;
    std::vector<int> nums;

    while (std::getline(inputFile, line))
    {
        nums.push_back(std::stoi(line));
    }  

    std::sort(nums.begin(), nums.end());

    // Three Pointers
    for (int i = 0, n = (int) nums.size(); i < n - 2; i++)
    {
        int j {i + 1};
        int k {n - 1};

        while (j < k)
        {
            int sum {nums[i] + nums[j] + nums[k]};

            if (sum == 2020)
            {
                ans = nums[i] * nums[j] * nums[k];
                std::cout << ans << '\n';
                return EXIT_SUCCESS;
            }
            else if (sum < 2020) { j++; }
            else {k--; }
        }
    }

    std::cout << "No pair found";

    return EXIT_SUCCESS;
}