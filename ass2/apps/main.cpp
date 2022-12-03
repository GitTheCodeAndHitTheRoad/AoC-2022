#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class WinningStrategy
{

private:
    int myPoints = 0;

    enum Play
    {
        rock = 1,
        paper = 2,
        scissors = 3
    };

    enum PlayResult
    {
        win = 6,
        draw = 3,
        loss = 0
    };

public:
    void procesLineInput(const std::string &line)
    {
        // part 1
        // Play OpponentPlay = FromCharToPlay(line[0]);
        // Play MyPlay = FromCharToPlay(line[2]);
        // addPoints(PointsPerPlay(MyPlay, OpponentPlay));

        // part 2
        Play OpponentPlay = FromCharToPlay(line[0]);
        PlayResult outcome = FromCharToOutcome(line[2]);
        Play MyPlay = FromGameOutcomeToPlay(OpponentPlay, outcome);
        addPoints(PointsPerPlay(MyPlay, OpponentPlay));
    }

    Play FromCharToPlay(const char &c)
    {
        if (c == 'A' | c == 'X')
        {
            return Play::rock;
        }
        else if (c == 'B' | c == 'Y')
        {
            return Play::paper;
        }
        else if (c == 'C' | c == 'Z')
        {
            return Play::scissors;
        }
    }

    PlayResult FromCharToOutcome(const char &c)
    {
        if (c == 'X')
        {
            return PlayResult::loss;
        }
        else if (c == 'Y')
        {
            return PlayResult::draw;
        }
        else if (c == 'Z')
        {
            return PlayResult::win;
        }
    }

    Play FromGameOutcomeToPlay(const Play &OpponentPlay, const PlayResult &PlayResult)
    {
        if (PlayResult == PlayResult::win)
        {
            return GetWinningPlay(OpponentPlay);
        }
        else if (PlayResult == PlayResult::draw)
        {
            return OpponentPlay;
        }
        else if (PlayResult == PlayResult::loss)
        {
            return GetLosingPlay(OpponentPlay);
        }
    }

    Play GetWinningPlay(const Play &OpponentPlay)
    {
        if (OpponentPlay == Play::scissors)
        {
            return static_cast<Play>(OpponentPlay - 2);
        }
        return static_cast<Play>(OpponentPlay + 1);
    }

    Play GetLosingPlay(const Play &OpponentPlay)
    {
        if (OpponentPlay == Play::rock)
        {
            return static_cast<Play>(OpponentPlay + 2);
        }
        return static_cast<Play>(OpponentPlay - 1);
    }

    int PointsPerPlay(const Play &MyPlay, const Play &OpponentPlay)
    {
        int delta = MyPlay - OpponentPlay;
        if (delta == 1 | delta == -2)
        {
            return PlayResult::win + MyPlay;
        }
        else if (delta == 0)
        {
            return PlayResult::draw + MyPlay;
        }
        else
        {
            return PlayResult::loss + MyPlay;
        }
    }

    void addPoints(const int &points)
    {
        myPoints = myPoints + points;
    }

    int getMyPoints() const
    {
        return myPoints;
    }
};

int main(int, char **)

{
    WinningStrategy wgst;

    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);
    while (std::getline(fin, line))

    {
        wgst.procesLineInput(line);
    }

    std::cout << wgst.getMyPoints() << std::endl;
}