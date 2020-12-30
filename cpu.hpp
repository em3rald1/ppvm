#ifndef _PPVM_CPU_H_
#define _PPVM_CPU_H_

#include <iostream>
#include <vector>

#include "instr-set.hpp"

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long uint64;
typedef signed long int64;
using std::vector;

class c_ppvm_cpu_core {      
    vector<uint8> ram;
    uint64 r1 = 0;
    uint64 r2 = 0;
    uint64 r3 = 0;
    uint64 r4 = 0;

    uint64 r5 = 0;
    uint64 r6 = 0;
    uint64 r7 = 0;
    uint64 r8 = 0;

    uint64 sp = 0;
    uint64 ip = 0;
    uint64 acc = 0;
    uint16 toUint16(uint8 x, uint8 y);
    uint32 toUint32(uint16 x, uint16 y);
    uint64 toUint64(uint32 x, uint32 y);

    int16 toInt16(int8 x, int8 y);
    int32 toInt32(int16 x, int16 y);
    int64 toInt64(int32 x, int32 y);

    uint32* toUint32(uint64 x);
    uint16* toUint16(uint32 x);
    uint8* toUint8(uint16 x);

    int32* toInt32(int64 x);
    int16* toInt16(int32 x);
    int8* toInt8(int16 x);
    public:
        c_ppvm_cpu_core(long long size);
        uint8 fetch();
        uint16 fetch16();
        uint32 fetch32();
        uint64 fetch64();
        void push(uint8 data);
        void push(uint16 data);
        void push(uint32 data);
        void push(uint64 data);
        uint8 pop();
        uint16 pop16();
        uint32 pop32();
        uint64 pop64();

        uint64& getRegister(uint8 registerIndex);

        void debug();
        void loadBytes(vector<uint8> data, uint64 position);
        void executeInstruction(uint8 instruction);

        //void viewMemoryAt(uint64 pos, uint64 n);
};

#endif