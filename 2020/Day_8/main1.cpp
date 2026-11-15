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
    std::vector<std::pair<std::string, int>> instructions;

    while (std::getline(inputFile, line))
    {
        char instruction[4];
        int val;
        
        if (std::sscanf(line.c_str(), "%s %d", instruction, &val) != 2) { continue; }
        instructions.push_back({instruction, val});
    }
    
    int idx {}, accumulator {};
    std::vector<bool> visited((int) instructions.size());

    while (true)
    {
        // Check if we already have visited this instruction
        if (visited[idx]) { break; }
        visited[idx] = true;

        std::string instruction { instructions[idx].first };
        
        if (instruction == "nop") { idx++; }
        else if (instruction == "acc")
        {
            accumulator += instructions[idx].second;
            idx++;
        }
        else { idx += instructions[idx].second; }
    }
    
    std::cout << accumulator << '\n';

    return EXIT_SUCCESS;
}