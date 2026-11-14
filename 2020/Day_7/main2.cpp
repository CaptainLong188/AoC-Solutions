#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
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
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> edges;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss {line};
        std::string token;
        std::vector<std::string> words;
        
        while (iss >> token) { words.push_back(token); }
        
        // Extract the outer color
        std::string outer_color {words[0] + ' ' + words[1]};
        
        if (words[4] == "no") { continue;}

        // Extract the inner color and building the directed acyclic graph
        for (int i = 4; i < (int) words.size(); i+= 4)
        {
            std::string inner_color { words[i + 1] + ' ' + words[i + 2] };
            int cnt { std::stoi(words[i]) };
            edges[outer_color].push_back({cnt, inner_color});
        }
    }
    
    // for (const auto& node: edges)
    // {
    //     std::cout << node.first << " : ";
    //     for (const auto& e : node.second)
    //     {
    //         std::cout << e.first << " " << e.second << " "; 
    //     }
    //     std::cout << '\n';
    // }

    // BFS
    std::queue<std::pair<int, std::string>> q;
    q.push({1, "shiny gold"});
    int ans {};

    while (!q.empty())
    {
        auto node = q.front(); q.pop();
        int mul {node.first};
        std::string color {node.second};

        for (const auto& neighbour: edges[color])
        {
            ans += mul * neighbour.first;
            q.push({mul * neighbour.first, neighbour.second});
        }
    }
    
    
    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}