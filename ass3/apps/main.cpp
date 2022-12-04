#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

// part 1

class BackPack
{

private:
    std::string content;
    int contentLength;

    std::string compartement1;
    std::string compartement2;

public:
    BackPack(const std::string &content)
    {
        this->content = content;
        this->contentLength = content.size();
    }

    int getBackpackPriority()
    {
        splitIntoCompartements();
        auto commonItems = findCommonItems();
        return calculateBackPackPriority(commonItems);
    }

    void splitIntoCompartements()
    {
        compartement1 = content.substr(0, contentLength / 2);
        compartement2 = content.substr(contentLength / 2, contentLength / 2);
    }

    std::set<char> findCommonItems()
    {
        std::string commonItems = "";
        for (char ch : compartement1)
        {
            if (compartement2.find(ch) != std::string::npos)
            {
                commonItems = commonItems + ch;
            }
        }
        std::set<char> commonSet(commonItems.begin(), commonItems.end());
        return commonSet;
    }

    int calculateBackPackPriority(const std::set<char> &commonItems)
    {
        int backPackPriority = 0;
        for (const char &ch : commonItems)
        {
            backPackPriority = backPackPriority + getItemPriority(ch);
        }
        return backPackPriority;
    }

    int getItemPriority(const char &ch) const
    {
        if (std::isupper(ch))
        {
            return ch - 'A' + 27;
        }
        return ch - 'a' + 1;
    }
};

// part 2
class ElfGroup
{

private:
    std::string setOfBackpacks[3];

public:
    void setBackPackByNumber(const int &backPacknr, const std::string backPackContent)
    {
        setOfBackpacks[backPacknr] = backPackContent;
    }

    int getGroupPriority()
    {
        char commonItem = getCommonItem();
        return getItemPriority(commonItem);
    }

    char getCommonItem()
    {
        char commonItem;
        std::set<char> backPack1(setOfBackpacks[0].begin(), setOfBackpacks[0].end());
        std::set<char> backPack2(setOfBackpacks[1].begin(), setOfBackpacks[1].end());
        std::set<char> backPack3(setOfBackpacks[2].begin(), setOfBackpacks[2].end());

        for (char ch : backPack1)
        {
            if (backPack2.count(ch) > 0)
            {
                if (backPack3.count(ch) > 0)
                {
                    commonItem = ch;
                    break;
                }
            }
        }
        return commonItem;
    }

    int getItemPriority(const char &ch) const
    {
        if (std::isupper(ch))
        {
            return ch - 'A' + 27;
        }
        return ch - 'a' + 1;
    }
};

int main(int, char **)

{
    ElfGroup ElfGroup;
    int lineCounter = 0;
    int totalPriority = 0;
    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);
    while (std::getline(fin, line))

    {
        // part 1
        // BackPack backPack(line);
        // totalPriority = totalPriority + backPack.getBackpackPriority();

        // part2

        int backPackNumber = lineCounter % 3;
        ElfGroup.setBackPackByNumber(backPackNumber, line);
        if (backPackNumber == 2)
        {
            totalPriority = totalPriority + ElfGroup.getGroupPriority();
        }

        ++lineCounter;
    }

    std::cout << totalPriority << std::endl;
}