#include <cstdlib>
#include <bitset>
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
    std::bitset<26> mask, person;
    mask.set();
    bool has_people {false}; 

    while (std::getline(inputFile, line))
    {
        if (line.empty()) 
        { 
            if (has_people) { ans += mask.count(); }
            mask.set();
            has_people = false;
            continue;
        }

        for (const auto& ch: line) { person.set(ch - 'a'); }
        has_people = true;
        mask &= person;
        person.reset();
    }

    // Evaluate last line
    if (has_people) { ans += mask.count(); }

    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}