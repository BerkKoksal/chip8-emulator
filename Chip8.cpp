#include "Chip8.h"
#include <fstream>

bool Chip8::loadIntoMem(const std::string &fileName){
    //open file
    std::ifstream fileToLoad;
    fileToLoad.open(fileName, std::ios::in | std::ios::binary);
    //check if file was opened
    if (!fileToLoad.is_open()) {
        return false;
    }
    //check size of file
    fileToLoad.seekg(0, std::ios::end);
    std::streampos fileSize = fileToLoad.tellg();
    fileToLoad.seekg(0, std::ios::beg);

    if (fileSize == std::streampos{-1}){
        return false; // Check if tellg failed
    }
    if(fileSize > std::streampos{3584}){ //3584 because programs in CHIP-8 start at 0x200
        return false;
    }
    //get mem adress
    uint8_t* ptr = &memory[0x200];

    char* buf = reinterpret_cast<char*>(ptr);

    //write into mem
    fileToLoad.read(buf,static_cast<std::streamsize>(fileSize));

    if (!fileToLoad){
        return false;
    }

    return true;
}