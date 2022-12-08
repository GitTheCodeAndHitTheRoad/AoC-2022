#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

class Stack
{

private:
    std::vector<char> crates;

public:
    void PushIntoStackTop(const char &crate)
    {
        crates.push_back(crate);
    }

    void PushIntoStackBottom(const char &crate)
    {
        crates.insert(crates.begin(), crate);
    }

    void MoveToOtherStack(Stack &destinationStack, const int &numberOfCrates)
    {
        for (int i = 0; i < numberOfCrates; i++)
        {
            destinationStack.PushIntoStackTop(crates.back());
            crates.pop_back();
        }
    }

    void MoveBatchToOtherStack(Stack &destinationStack, const int &numberOfCrates)
    {
        int cratesSize = GetCratesSize();
        int indexToMove = cratesSize - numberOfCrates;

        for (int i = 0; i < numberOfCrates; i++)
        {
            char crate = crates[indexToMove];
            destinationStack.PushIntoStackTop(crate);
            crates.erase(crates.begin() + indexToMove);
        }
    }

    char GetBottomCrate() const
    {
        return crates.front();
    }

    char GetTopCrate() const
    {
        return crates.back();
    }

    int GetCratesSize() const
    {
        return crates.size();
    }

    void PrintCrate(const int &index) const
    {
        std::cout << crates[index];
    }
};

std::vector<Stack> CreateStackVector(std::fstream &fin)
{
    int numberOfStacks;
    int lineLength;
    bool firstLine = true;
    std::vector<Stack> stackVector;
    std::string line;
    while (std::getline(fin, line))
    {
        if (firstLine)
        {
            lineLength = line.length();
            numberOfStacks = (lineLength + 1) / 4;
            for (int i = 0; i < numberOfStacks; i++)
            {
                Stack stack;
                stackVector.push_back(stack);
            }
            firstLine = false;
        }

        if (line.find('[') != std::string::npos) // defintion of stacks ends at line with numbers
        {
            for (int i = 0; i < numberOfStacks; i++)
            {
                char crate = line[1 + i * 4];
                if (crate != ' ')
                {
                    stackVector[i].PushIntoStackBottom(crate);
                }
            }
        }
        else
        {
            break;
        }
    }

    return stackVector;
}

std::string ObtainMessage(const std::vector<Stack> stackVector)
{
    std::string message;

    for (int i = 0; i < stackVector.size(); i++)
    {
        message += stackVector[i].GetTopCrate();
    }

    return message;
}

int main(int, char **)

{
    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);

    auto stackVector = CreateStackVector(fin);

    while (std::getline(fin, line))

    {
        if (line != "")
        {
            int comma1Pos = line.find(' ');
            int comma2Pos = line.find(' ', comma1Pos + 1);
            int comma3Pos = line.find(' ', comma2Pos + 1);
            int comma4Pos = line.find(' ', comma3Pos + 1);
            int comma5Pos = line.find(' ', comma4Pos + 1);

            int cratesToMove = std::stoi(line.substr(comma1Pos + 1, comma2Pos - comma1Pos - 1));
            int moveFromStack = std::stoi(line.substr(comma3Pos + 1, comma4Pos - comma3Pos - 1)) - 1;
            int moveToStack = std::stoi(line.substr(comma5Pos + 1)) - 1;

            stackVector[moveFromStack].MoveBatchToOtherStack(stackVector[moveToStack], cratesToMove);
        }
    }

    std::cout << ObtainMessage(stackVector);
}