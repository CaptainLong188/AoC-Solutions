#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using Passport = std::map<std::string, std::string>;
const std::vector<std::string> eye_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

bool yearInRange(const std::string& str, int lo, int hi)
{
    if (str.size() != 4 || str.find_first_not_of("0123456789") != std::string::npos) { return false; }
    int year {std::stoi(str)};
    return year >= lo && year <= hi;
}

bool isValid(const Passport& p)
{
    // Check if all required fields are present in the passport
    for (const std::string& key : {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"})
    {
        if (p.find(key) == p.end()) { return false; }
    } 

    // Birth Year
    if (!yearInRange(p.at("byr"), 1920, 2002)) { return false; }

    // Issue Year
    if (!yearInRange(p.at("iyr"), 2010, 2020)) { return false; }

    // Expiration year
    if (!yearInRange(p.at("eyr"), 2020, 2030)) { return false; }

    // Height
    int height {}, idx {};
    std::string hgt {p.at("hgt")};

    while (hgt[idx] >= '0' && hgt[idx] <= '9')
    {
        height = (height * 10 + (hgt[idx++] - '0'));
    }
    std::string unit {hgt.substr(idx)};

    if (unit == "cm")
    {
        if (height < 150 || height > 193) { return false; }
    }
    else if (unit == "in")
    {
        if (height < 59 || height > 76) { return false; }
    }
    else { return false; }

    // Hair color
    std::string hcl {p.at("hcl")};

    if (hcl.size() != 7 || hcl[0] != '#') { return false; }

    for (int i = 1; i < 7; i++)
    {
        if (!(hcl[i] >= '0' && hcl[i] <= '9') && !(hcl[i] >= 'a' && hcl[i] <= 'f')) { return false; }
    }   

    // Eye color
    if (std::find(eye_colors.begin(), eye_colors.end(), p.at("ecl")) == eye_colors.end()) { return false; }

    // Passport ID
    std::string pid {p.at("pid")};
    if (pid.size() != 9) { return false; }
    
    for (const auto& ch: pid)
    {
        if (ch < '0' || ch > '9') { return false; }
    }

    return true;
}

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
    std::map<std::string, std::string> map;

    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            if (isValid(map)) { ans++; }
            map.clear();
            continue;
        }

        std::istringstream ss{line};
        std::string token;

        while (ss >> token)
        {
            map[token.substr(0, 3)] = token.substr(4);
        }
    }
    
    if (isValid(map)) { ans++; }

    std::cout << ans << '\n';

    return EXIT_SUCCESS;
}