#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class File
{

private:
    std::string name;
    int fileSize;

public:
    File(const std::string &name, const int &fileSize)
    {
        this->name = name;
        this->fileSize = fileSize;
    }

    int getSize() const
    {
        return fileSize;
    }
};

class Dir
{

private:
    std::string name;
    std::vector<Dir *> subDirs;
    std::vector<File *> files;

public:
    Dir()
    {
        this->name = "";
    }
    Dir(const std::string &name)
    {
        this->name = name;
    }

    void setDirName(const std::string &name)
    {
        this->name = name;
    }

    std::string getDirName() const
    {
        return this->name;
    }

    void addSubDir(Dir *subDir)
    {
        subDirs.push_back(subDir);
    }

    void addFile(File *file)
    {
        files.push_back(file);
    }
    int getSize() const
    {
        int totalSize = 0;
        for (auto file : files)
        {
            totalSize += file->getSize();
        }
        for (auto subDir : subDirs)
        {
            totalSize += subDir->getSize();
        }
        return totalSize;
    }

    ~Dir()
    {
        for (auto dir : subDirs)
        {
            delete dir;
            dir = nullptr;
        }
        for (auto file : files)
        {
            delete file;
            file = nullptr;
        }
    }
};

bool isDirAlreadyAdded(std::string name, std::vector<Dir *> &vectorOfDirs)
{
    for (auto dir : vectorOfDirs)
    {
        if (dir->getDirName() == name)
        {
            return true;
        }
    }
    return false;
}

Dir *getPointerToDir(std::string name, std::vector<Dir *> &vectorOfDirs)
{
    for (auto dir : vectorOfDirs)
    {
        if (dir->getDirName() == name)
        {
            return dir;
        }
    }
    std::cout << "returning nullptr for :" << name << std::endl;
    return nullptr;
}

int main(int, char **)

{

    std::vector<Dir *> vectorOfDirs;

    std::string currentDir = "";
    Dir *currentDirPointer;

    std::string line;
    std::fstream fin("../../apps/test.txt", std::fstream::in);

    while (std::getline(fin, line))

    {
        if (line.find('$') != std::string::npos) // $ indictaes input
        {
            if (line.find("cd") != std::string::npos & line.find("..") == std::string::npos)
            {
                std::string moveToDir = line.substr(5);
                currentDir += "-";
                currentDir += moveToDir;

                if (isDirAlreadyAdded(currentDir, vectorOfDirs))
                {
                    currentDirPointer = getPointerToDir(currentDir, vectorOfDirs);
                }
                else
                {
                    currentDirPointer = new Dir(currentDir);
                    vectorOfDirs.push_back(currentDirPointer);
                }
            }
            else if (line.find("cd ..") != std::string::npos)
            {
                int deepestSubDir = currentDir.rfind("-");
                currentDir = currentDir.substr(0, deepestSubDir); // move back 1 die
            }
        }
        else // otherwise it is output (list of dirs and /or files)
        {
            if (line.find("dir") != std::string::npos)
            {
                std::string moveToDir = line.substr(4);
                std::string dirNameComplete = currentDir + "-" + moveToDir;

                Dir *subdir = new Dir(dirNameComplete);

                currentDirPointer->addSubDir(subdir);
                vectorOfDirs.push_back(subdir);
            }
            else
            {
                // line contains filename
                int spacePos = line.find(" ");
                std::string fileName = line.substr(spacePos + 1);
                int fileSize = std::stoi(line.substr(0, spacePos));
                File *file = new File(fileName, fileSize);
                currentDirPointer->addFile(file);
            }
        }
    }

    int totalSize = 70000000;
    int totalSizeNeeded = 30000000;
    int totalSizeTaken = getPointerToDir("-/", vectorOfDirs)->getSize();
    int totalSizeAvailable = totalSize - totalSizeTaken;
    int totalSizeToDelete = totalSizeNeeded - totalSizeAvailable;

    int smallestSize = totalSizeTaken;

    for (auto dir : vectorOfDirs)
    {
        // std::cout << "Dir Name: " << dir->getDirName() << ", size: " << dir->getSize() << std::endl;
        if (dir->getSize() < smallestSize & dir->getSize() >= totalSizeToDelete)
        {
            smallestSize = dir->getSize();
        }
    }
    std::cout << smallestSize;
};
