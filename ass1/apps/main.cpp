#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class Elf
{

private:
    int calories;

public:
    Elf()
    {
        this->calories = 0;
    }

    void addCalories(const int additionalCalories)
    {
        this->calories = this->calories + additionalCalories;
    }

    const int getTotalCalories() const
    {
        return this->calories;
    }
};

bool compareElfCalories(Elf *a, Elf *b)
{
    return (a->getTotalCalories() < b->getTotalCalories());
}

int main(int, char **)

{
    Elf *elf = new Elf();
    std::vector<Elf *> VectorOfElfs;

    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);
    while (std::getline(fin, line))

    {
        if (line.empty())
        {
            VectorOfElfs.push_back(elf);
            elf = new Elf();
        }
        else
        {
            elf->addCalories(std::stoi(line));
        }
    }

    std::sort(VectorOfElfs.rbegin(), VectorOfElfs.rend(), compareElfCalories);

    // part 1
    // std::cout << VectorOfElfs[0]->getTotalCalories();

    // part 2
    int topN = 3; // find top n Elfs
    int summedCalories = 0;

    for (int i = 0; i < topN; ++i)
    {
        summedCalories = summedCalories + VectorOfElfs[i]->getTotalCalories();
    }
    std::cout << summedCalories << std::endl;

    // Clearing pointers to avoid memoy leaks
    for (auto p : VectorOfElfs)
    {
        delete p;
    }
    VectorOfElfs.clear();
}