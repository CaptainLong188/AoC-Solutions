#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2) { return EXIT_FAILURE; }

    std::ifstream inputFile {argv[1]};

    if (!inputFile.is_open())
    {
        std::cerr << "Could not open " << argv[1] << '\n';
        return EXIT_FAILURE;
    }
    
    int ans {};
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::string str1 {line.substr(0, 7)};
        std::string str2 {line.substr(7)};
        // std::cout << str1 << "  " << str2 << '\n';
        
        
        // Calculate the row
        int lo {0}, hi {127};

        for (const auto &ch : str1)
        {
            int mid {(lo + hi) / 2};

            if (ch == 'F') // Take the lower half
            {
                hi = mid;
            }
            else // Take the upper half
            {
                lo = mid + 1;    
            }
        }
        assert(lo == hi);
        int row {lo};

        // Calculate the column
        lo = 0, hi = 7;
        for (const auto &ch : str2)
        {
            int mid {(lo + hi) / 2};

            if (ch == 'L') // Take the lower half
            {
                hi = mid;
            }
            else // Take the upper half
            {
                lo = mid + 1;    
            }
        }
        assert(lo == hi);
        int col {lo};

        ans = std::max(ans, (row * 8 + col));
    }

    std::cout << ans << '\n';
    
    return EXIT_SUCCESS;
}