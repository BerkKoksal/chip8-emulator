#pragma once

#include <array>
#include <cstdint>
#include <string>

class Chip8{
    private:
    
        uint8_t memory[4096]{};
        
        std::array<uint8_t, 16> V{}; //16 general purpose registers
        uint16_t VI{}; //index register

        std::array<std::array<uint8_t, 64>, 32> display{}; //2D aray for now

        //timers
        uint8_t delayTimer{};
        uint8_t soundTimer{};

        uint16_t PC{0x200}; //programs begin at 0x200


    public:
        bool loadIntoMem(const std::string &fileName);
        uint16_t fetchNextInstruction();
};
