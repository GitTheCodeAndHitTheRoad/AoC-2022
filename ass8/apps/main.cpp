#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Tree
{

private:
    int x;
    int y;

public:
    Tree()
    {
        this->x = 0;
        this->y = 0;
    }

    Tree(const int &x, const int &y)
    {
        this->x = x;
        this->y = y;
    }

    int getX() const
    {
        return this->x;
    }

    int getY() const
    {
        return this->y;
    }

    void setX(const int &x)
    {
        this->x = x;
    }

    void setY(const int &y)
    {
        this->y = y;
    }
};

class TreePatch
{

private:
    int dimension;
    int numberOfTrees;
    std::vector<int> grid;

public:
    TreePatch()
    {
        this->dimension = 0;
        this->numberOfTrees = 0;
    }

    void Initialize(const int &dimension)
    {
        this->dimension = dimension;
        this->numberOfTrees = dimension * dimension;
        grid.resize(numberOfTrees);
        for (int i = 0; i < numberOfTrees; i++)
        {
            grid[i] = 0; // set trees as zero height for default
        }
    }

    void setTreeHeight(const Tree &tree, const int &height)
    {
        grid[(dimension * tree.getX()) + tree.getY()] = height;
    }

    int getTreeHeight(const Tree &tree) const
    {
        return grid[(dimension * tree.getX()) + tree.getY()];
    }

    int getVisibileTrees() const
    {
        int visibleTrees = 4 * dimension - 4; // outside trees are always visible
        for (int i = 1; i < dimension - 1; i++)
        {
            for (int j = 1; j < dimension - 1; j++)
            {
                visibleTrees += isTreeVisible(Tree(i, j));
            }
        }
        return visibleTrees;
    }

    bool isTreeVisible(const Tree &tree) const
    {
        return (isVisibleHorizontal(tree) | isVisibleVertical(tree));
    }

    bool isVisibleHorizontal(const Tree &tree) const
    {
        bool visibleFromLeft = true;
        bool visibleFromRight = true;
        for (int i = 0; i < dimension; i++)
        {
            Tree compareTree(i, tree.getY());
            if (getTreeHeight(compareTree) >= getTreeHeight(tree))
            {
                if (compareTree.getX() < tree.getX())
                {
                    visibleFromLeft = false;
                }
                else if (compareTree.getX() > tree.getX())
                {
                    visibleFromRight = false;
                }
            }
        }
        return (visibleFromLeft | visibleFromRight);
    }

    bool isVisibleVertical(const Tree &tree) const
    {
        bool visibleFromTop = true;
        bool visibleFromBottom = true;
        for (int i = 0; i < dimension; i++)
        {
            Tree compareTree(tree.getX(), i);
            if (getTreeHeight(compareTree) >= getTreeHeight(tree))
            {
                if (compareTree.getY() < tree.getY())
                {
                    visibleFromBottom = false;
                }
                else if (compareTree.getY() > tree.getY())
                {
                    visibleFromTop = false;
                }
            }
        }
        return (visibleFromTop | visibleFromBottom);
    }

    int getHighestScenicScore() const
    {
        int highestScenicScore = 0;
        for (int i = 1; i < dimension - 1; i++)
        {
            for (int j = 1; j < dimension - 1; j++)
            {
                int treeScore = getTreeScenicScore(Tree(i, j));
                if (treeScore > highestScenicScore)
                {
                    highestScenicScore = treeScore;
                }
            }
        }
        return highestScenicScore;
    }

    int getTreeScenicScore(const Tree &tree) const
    {

         return (scenicScoreHorizontals(tree, "left") * scenicScoreHorizontals(tree, "right") *
                scenicScoreVerticals(tree, "top") * scenicScoreVerticals(tree, "bottom"));
    }

    int scenicScoreHorizontals(const Tree &tree, const std::string &side) const
    {
        int sign = (side == "right") ? 1 : -1;
        Tree blockingTree(tree.getX(), tree.getY());
        int x = tree.getX();

        while (x > 0 & x < dimension - 1)
        {
            x = sign + x;
            blockingTree.setX(x);
            if (getTreeHeight(blockingTree) >= getTreeHeight(tree))
            {
                break;
            }
        }
        return abs(blockingTree.getX() - tree.getX());
    }

    int scenicScoreVerticals(const Tree &tree, const std::string &side) const
    {
        int sign = (side == "bottom") ? 1 : -1;
        Tree blockingTree(tree.getX(), tree.getY());
        int y = tree.getY();

        while (y > 0 & y < dimension - 1)
        {
            y = sign + y;
            blockingTree.setY(y);
            if (getTreeHeight(blockingTree) >= getTreeHeight(tree))
            {
                break;
            }
        }
        return abs(blockingTree.getY() - tree.getY());
    }
};

int main(int, char **)

{
    int lineCount = 0;
    TreePatch treePatch;

    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);

    while (std::getline(fin, line))

    {
        if (lineCount == 0)
        {
            treePatch.Initialize(line.length());
        }

        for (int i = 0; i < line.length(); i++)
        {
            treePatch.setTreeHeight(Tree(i, lineCount), line[i] - '0');
        }

        ++lineCount;
    }
    std::cout << treePatch.getHighestScenicScore() << std::endl;
    //  std::cout << treePatch.getVisibileTrees();
};
