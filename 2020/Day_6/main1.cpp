#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

void count(int (&cnt)[26], int& ans)
{
    int aux{};

    for (int i = 0; i < 26; i++)
    {
        if (cnt[i] > 0) { aux++; }
        cnt[i] = 0;
    }

    ans += aux;
}

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
    int cnt[26] = {};

    while (std::getline(inputFile, line))
    {
        if (line.empty()) { count(cnt, ans); }

        for (const auto& ch: line) { cnt[ch - 'a']++; }
    }

    // Evaluate last line
    count(cnt, ans);

    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}