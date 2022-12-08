#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <list>

int main(int, char **)

{
    char currentChar;
    int charCounter = 1;
    std::list<char> chars;

    std::fstream fin("../../apps/test.txt", std::fstream::in);

    while (fin >> currentChar)

    {
        chars.push_back(currentChar);
        if (chars.size() > 14)
        {
            chars.pop_front();
        }

        std::set<char> uniqueChars(chars.begin(), chars.end());
        if (uniqueChars.size() >= 14)
        {
            std::cout << charCounter << std::endl;
            break;
        }
        ++charCounter;
    }
};