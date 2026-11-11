#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <unordered_map>

typedef long long ll;
const int numberOfDays = 256; // works for part 1 and part 2

template <typename T>
void printVector (std::vector<T> v)
{
    for (const auto& e : v)
    {
        std::cout << e << " ";
    }
}

void updateFishes (std::unordered_map<ll, ll>& mapFishes)
{
    std::unordered_map<ll, ll> n_mapFishes;

    for (const auto& e : mapFishes)
    {
        if (e.first == 0)
        {
            n_mapFishes[8] += e.second;
            n_mapFishes[6] += e.second;
        }
        else
        {
            n_mapFishes[e.first - 1] += e.second;
        }
        
    }

    mapFishes = n_mapFishes;
    n_mapFishes.clear();
}


int main(int argc, char const *argv[])
{
    if (argc < 2) return 0;

    ll ans;
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {   
        // Parse the input
        std::string line;
        std::getline(inputFile, line);
        std::vector<int> timer;

        for (int i = 0; i < (int) line.size(); i += 2)
        {
            timer.push_back(line[i] - '0');
        }

        std::unordered_map<ll, ll> mapTimers;

        for (const auto& e : timer) mapTimers[e]++;

        for (int i = 0; i < numberOfDays; ++i)
        {
            updateFishes(mapTimers);
        }

        for (const auto& e : mapTimers) std::cout << e.first << " " << e.second << std::endl;

        ans = std::accumulate(mapTimers.begin(), mapTimers.end(), (ll)0, 
        [] (ll value, const auto& p)
        {
            return value + p.second;
        }
        );
    }

    std::cout << ans << std::endl;
    inputFile.close();

    return 0;
}
