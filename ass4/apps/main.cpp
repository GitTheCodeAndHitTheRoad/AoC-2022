#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

class SectionRange
{

private:
    int p_start;
    int p_end;

public:
    SectionRange()
    {
        this->p_start = 0;
        this->p_end = 0;
    }
    SectionRange(const int &p_start, const int &p_end)
    {
        this->p_start = p_start;
        this->p_end = p_end;
    }

    int GetStart() const
    {
        return this->p_start;
    }

    int GetEnd() const
    {
        return this->p_end;
    }
};

class SectionPairs

{
private:
    SectionRange RangeElf1;
    SectionRange RangeElf2;

public:
    SectionPairs(const SectionRange &RangeElf1, const SectionRange &RangeElf2)
    {
        this->RangeElf1 = RangeElf1;
        this->RangeElf2 = RangeElf2;
    }

    bool AreRangesContained()
    {
        bool RangeElf1Contained = RangeElf1.GetStart() >= RangeElf2.GetStart() & RangeElf1.GetEnd() <= RangeElf2.GetEnd();
        bool RangeElf2Contained = RangeElf2.GetStart() >= RangeElf1.GetStart() & RangeElf2.GetEnd() <= RangeElf1.GetEnd();
        return (RangeElf1Contained | RangeElf2Contained);
    }

    bool DoSectionsOverlap()
    {
        return !(RangeElf1.GetEnd() < RangeElf2.GetStart() | RangeElf2.GetEnd() < RangeElf1.GetStart());
    }
};

int main(int, char **)

{
    int fullyContainedCount = 0;
    int overlappingPairsCount = 0;

    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);
    while (std::getline(fin, line))

    {
        int commaPos = line.find(",");
        int firstDashPos = line.find("-");
        int secondDashPos = line.find("-", firstDashPos + 1);

        SectionRange RangeElf1(std::stoi(line.substr(0, firstDashPos)), std::stoi(line.substr(firstDashPos + 1, commaPos - firstDashPos - 1)));
        SectionRange RangeElf2(std::stoi(line.substr(commaPos + 1, firstDashPos - commaPos - 1)), std::stoi(line.substr(secondDashPos + 1)));

        SectionPairs sectionPairs(RangeElf1, RangeElf2);

        // part 1
        // if (sectionPairs.AreRangesContained())
        // {
        //     ++fullyContainedCount;
        // }

        if (sectionPairs.DoSectionsOverlap())
        {
            ++overlappingPairsCount;
        }
    }

    // std::cout << fullyContainedCount << std::endl;
    std::cout << overlappingPairsCount << std::endl;
}