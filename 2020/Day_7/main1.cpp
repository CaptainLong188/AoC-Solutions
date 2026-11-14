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
    std::unordered_map<std::string, std::vector<std::string>> edges;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss {line};
        std::string token;
        std::vector<std::string> words;
        
        while (iss >> token) { words.push_back(token); }
        
        // Extract the outer color
        std::string outer_color {words[0] + ' ' + words[1]};
        
        if (words[4] == "no") { continue;}

        // Extract the inner color and build the directed acyclic graph
        for (int i = 5; i < (int) words.size(); i+= 4)
        {
            std::string inner_color {words[i] + ' ' + words[i + 1]};
            edges[inner_color].push_back(outer_color);
        }
    }
    
    // for (const auto& node: edges)
    // {
    //     std::cout << node.first << " : ";
    //     for (const auto& e : node.second) { std::cout << e << " "; }
    //     std::cout << '\n';
    // }

    // BFS
    std::unordered_map<std::string, bool> visited;
    // for (const auto& e: edges) { visited[e.first] = false; }
    std::queue<std::string> q;
    q.push("shiny gold");
   
    while (!q.empty())
    {
        std::string node {q.front()};
        q.pop();

        for (const auto& neighbour: edges[node])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
    
    std::cout << visited.size() << '\n';

    return EXIT_SUCCESS;
}