#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <sstream>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Image.h"
#include "Root.h"

std::vector<std::string> split_cmd_line(std::istream& is) {
    std::string commandline;
    std::vector<std::string> parsed_command;
    std::getline(is, commandline);
    std::stringstream ss(commandline);
    std::string word;
    while (ss >> word) {
        parsed_command.push_back(word);
    }
    return parsed_command;
}

using std::cout;
using std::endl;
using std::string;



int main(int argc, char *argv[])
{
    int ExitKEY = 0;
    std::vector<std::string> DataFromConsol;
    for (int i = 1; i < argc; ++i) {
        DataFromConsol.emplace_back(argv[i]);
    }
    std::string filename ="../" + DataFromConsol[0];
    while(ExitKEY == 0){
        std::cout<<"Please enter the information, has your file MBR or not(Y/N)?: ";
        auto VectorOfMBR = split_cmd_line(std::cin);
        if(VectorOfMBR[0] == "Y" || VectorOfMBR[0] == "y"){
            ExitKEY = 1;
        }
        else if(VectorOfMBR[0] == "N" || VectorOfMBR[0] == "n"){
            ExitKEY = 2;
        }
    }
    long beas = 0;

    if(ExitKEY == 2){
        beas = 0;
    }
    else{
        beas = 512*17;
    }

    Image mainImage = Image(filename,beas);
    std::cout << "Bytes per sector: " << mainImage.getBootData().bytesPerSector << std::endl;
    std::cout << "Sectors per claster: " << (int) mainImage.getBootData().sectorPerCluster << std::endl;
    std::cout << "# of FATs: " << (int) mainImage.getBootData().numberOfFATS << std::endl;
    std::cout << "FAT size: " << mainImage.getBootData().sectorsPerFAT << std::endl;
    std::cout << "Root directory entires: " << mainImage.getBootData().rootEntries / 32 << ". Its size: "
              << mainImage.getBootData().rootEntries << std::endl;
    std::cout << "Reserved Sectors: " << mainImage.getBootData().reservedSectors << std::endl;
    std::cout << "Signature: " << (int) mainImage.getBootData().signature << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout<<"Ls of root catalog"<<std::endl;
    Root root = Root(mainImage);
    std::cout<<"Please enter the name of file: ";
    auto Vector = split_cmd_line(std::cin);

    std::string needed = Vector[0];
    auto res = root.find_file(needed);

    if (res == -1) {
        std::cout << "File not found" << std::endl;
    }

    else {
        std::cout << "File found" << std::endl;
    }

    auto file = root.getFile(res);
    root.describe_file(file);
}
