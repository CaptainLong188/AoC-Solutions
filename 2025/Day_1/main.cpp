#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2) { return EXIT_FAILURE;}

    int ans {};
    std::string filename {argv[1]};
    
    std::ifstream inputFile;
    inputFile.open(filename);

    if (inputFile.is_open())
    {
        // Parse the input
        std::string line {};
        char direction {};
        int num {};
        int currentPosition {50};

        while (std::getline(inputFile, line))
        {            
            direction = line[0];
            num = std::stoi(line.substr(1));
            
            if (direction == 'L')
            {
                if (currentPosition - num % 100 < 0)
                {
                    currentPosition = (currentPosition + 100 - num % 100);
                }
                else { currentPosition -= num % 100; }
            }
            else
            {
                if (currentPosition + num % 100 > 99)
                {
                    currentPosition = (currentPosition - 100 + num % 100);
                }
                else { currentPosition += num % 100; }
            }
            
            if (currentPosition == 0) { ans++; }
        }
        
        std::cout << ans << '\n';
    }

    return EXIT_SUCCESS;
}