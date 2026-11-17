#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#define ll long long

bool check(const std::vector<ll>& nums, int start, int end)
{
    ll target {nums[end]};
    std::unordered_set<ll> set;

    for (int i = start; i < end; i++)
    {
        if (target != nums[i] * 2 && set.count(target - nums[i]) > 0) { return true; }
        set.insert(nums[i]);
    }

    return false;
}

int main(int argc, char *argv[])
{
    if (argc < 2) { return EXIT_FAILURE;}

    std::ifstream inputFile {argv[1]};

    if (!inputFile.is_open())
    {
        std::cerr << "Could not open " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    std::string line; 
    std::vector<ll> nums;

    while (std::getline(inputFile, line))
    {
        if (line.empty()) continue;
        nums.push_back(std::stoll(line));
    }
    
    int window {25}, len {(int) nums.size()};
    ll target {};

    for (int i = window; i < len; i++)
    {
        if (!check(nums, i - window, i))
        {
            target = nums[i];
            break;
        }
    }

    // Find a contiguous set of at least to numbers which sum is target
    // Sliding Window Technique
    // Expand 
    // Shrink until valid again
    
    int left {};
    ll sum {};

    for (int right = 0; right < len; right++)
    {
        sum += nums[right]; // Expand

        while (sum > target)
        {
            sum -= nums[left++]; // Shrink until valid again
        }
        
        if (sum == target && right - left >= 1)
        {
            ll min {*std::min_element(nums.begin() + left, nums.begin() + right + 1)};
            ll max {*std::max_element(nums.begin() + left, nums.begin() + right + 1)};
            std::cout << min + max << '\n';
            return EXIT_SUCCESS;
        }
    }
    
    return EXIT_SUCCESS;
}