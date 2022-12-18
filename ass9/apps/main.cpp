#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Point
{

private:
    int x;
    int y;

public:
    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(const int &x, const int &y)
    {
        this->x = x;
        this->y = y;
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    void setX(const int &x)
    {
        this->x = x;
    }

    void setY(const int &y)
    {
        this->y = y;
    }

    bool PointsTouching(const Point &otherPoint) const
    {
        return (abs(x - otherPoint.getX()) <= 1 & abs(y - otherPoint.getY()) <= 1);
    }

    void makePointTouching(const Point &headPoint)
    {
        int diffX = abs(headPoint.getX() - x);
        int diffY = abs(headPoint.getY() - y);

        double scaleX, scaleY;
        if (diffX > 0 & diffY > 0) // if not in same row and same column
        {
            scaleX = (diffX == 1) ? (1) : (0.5);
            scaleY = (diffY == 1) ? (1) : (0.5);
        }
        else
        {
            scaleX = 0.25 * diffX; // Make the scale equal to 0.5 in case of delta 2 or 0 incase of 0 delta
            scaleY = 0.25 * diffY;
        }
        setX(getX() + scaleX * (headPoint.getX() - x));
        setY(getY() + scaleY * (headPoint.getY() - y));
    }

    friend bool operator<(const Point &p1, const Point &p2);
};

bool operator<(const Point &p1, const Point &p2)
{
    if (p1.getX() < p2.getX())
    {
        return true;
    }
    else if (p1.getX() > p2.getX())
    {
        return false;
    }
    return p1.getY() < p2.getY();
}

int main(int, char **)

{
    int tailSize = 9;
    std::vector<Point> tailVector;
    Point Head;

    for (int i = 0; i < tailSize; i++)
    {
        tailVector.push_back(Point());
    }

    std::map<Point, int> visitCounter;
    visitCounter[tailVector[tailSize - 1]]++;

    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);

    while (std::getline(fin, line))

    {
        int stepsToMake = std::stoi(line.substr(2));
        char direction = line[0];

        for (int i = 0; i < stepsToMake; i++)
        {
            switch (direction)
            {
            case 'D':
                Head.setY(Head.getY() + 1);
                break;
            case 'U':
                Head.setY(Head.getY() - 1);
                break;
            case 'L':
                Head.setX(Head.getX() - 1);
                break;
            case 'R':
                Head.setX(Head.getX() + 1);
                break;
            }
            if (!tailVector[0].PointsTouching(Head))
            {
                tailVector[0].makePointTouching(Head);

                for (int i = 1; i < tailSize; i++)
                {
                    if (!tailVector[i].PointsTouching(tailVector[i - 1]))
                    {

                        tailVector[i].makePointTouching(tailVector[i - 1]);
                    }
                }
            }
            visitCounter[tailVector[tailSize - 1]]++;
        }
    }
    std::cout << visitCounter.size() << std::endl;
};
