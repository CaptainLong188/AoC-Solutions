#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Result
{
    bool terminated;
    int accumulator;
};


Result check(const std::vector<std::pair<std::string, int>>& instructions, const int len)
{    
    int idx {}, cnt {};
    std::vector<bool> visited(len);

    while (true)
    {
        if (idx == len) { break; } // If we reach instruction "len" program terminates
        if (idx < 0 || idx > len) { return {false, cnt}; } // jumped outside the program

        // Check if we already have visited this instruction
        if (visited[idx]) { return {false, cnt}; }  
        visited[idx] = true;

        std::string instruction { instructions[idx].first };
        
        if (instruction == "nop") { idx++; }
        else if (instruction == "acc")
        {
            cnt += instructions[idx].second;
            idx++;
        }
        else { idx += instructions[idx].second; }
    }

    return {true, cnt};
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

    std::string line;
    std::vector<std::pair<std::string, int>> instructions;

    while (std::getline(inputFile, line))
    {
        char instruction[4];
        int val;
        
        if (std::sscanf(line.c_str(), "%3s %d", instruction, &val) != 2) { continue; }
        instructions.push_back({instruction, val});
    }
    
    int len {(int) instructions.size()}, ans {};

    for (int i = 0; i < len; i++)
    {
        std::string& op {instructions[i].first};
        if (op == "acc") { continue; }

        const std::string original {op};
        op = (original == "nop") ? "jump" : "nop"; // Flip the operation

        Result result = check(instructions, len);
        op = original; // Restore the operation

        if (result.terminated)
        {
            ans = result.accumulator;
            break;
        }
    }

    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}