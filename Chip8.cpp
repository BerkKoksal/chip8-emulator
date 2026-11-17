#include "Chip8.h"
#include <fstream>
#include <stdexcept>

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

uint16_t Chip8::fetchNextInstruction(){
    
    if(PC + 1 > 0xFFF){
        throw std::out_of_range("Invalid memory address");
    }
    uint16_t instruction = (memory[PC] << 8) | memory[PC + 1];
    
    //Send PC to next instruction
    PC +=2;

    return instruction;
}