#include "cpu.hpp"

c_ppvm_cpu_core::c_ppvm_cpu_core(long long size) {
    this->ram.reserve(size);
}

uint16 c_ppvm_cpu_core::toUint16(uint8 x, uint8 y) {
    uint16 out = 0;
    out |= (uint16)x << 8;
    out |= (uint16)y << 0;
    return out;
}

uint32 c_ppvm_cpu_core::toUint32(uint16 x, uint16 y) {
    uint32 out = 0;
    out |= (uint32)x << 16;
    out |= (uint32)y << 0;
    return out;
}

uint64 c_ppvm_cpu_core::toUint64(uint32 x, uint32 y) {
    uint64 out = 0;
    out |= (uint64)x << 32;
    out |= (uint64)y << 0;
    return out;
}

int16 c_ppvm_cpu_core::toInt16(int8 x, int8 y) {
    int16 out = 0;
    out |= (int16)x << 8;
    out |= (int16)y << 0;
    return out;
}

int32 c_ppvm_cpu_core::toInt32(int16 x, int16 y) {
    uint32 out = 0;
    out |= (int32)x << 16;
    out |= (int32)y << 0;
    return out;
}

int64 c_ppvm_cpu_core::toInt64(int32 x, int32 y) {
    uint64 out = 0;
    out |= (int64)x << 32;
    out |= (int64)y << 0;
    return out;
}

uint32* c_ppvm_cpu_core::toUint32(uint64 x) {
    uint32 i[2];
    i[0] = (uint32)(x);
    i[1] = (uint32)(x>>64);
    return i;
}
uint16* c_ppvm_cpu_core::toUint16(uint32 x) {
    uint16 i[2];
    i[0] = (uint16)(x);
    i[1] = (uint16)(x>>32);
    return i;
}
uint8* c_ppvm_cpu_core::toUint8(uint16 x){
    uint8 i[2];
    i[0] = (uint8)x;
    i[1] = (uint8)(x>>8);
    return i;
}

int32* c_ppvm_cpu_core::toInt32(int64 x) {
    int32 i[2];
    i[0] = (int32)(x);
    i[1] = (int32)(x>>64);
    return i;
}
int16* c_ppvm_cpu_core::toInt16(int32 x) {
    int16 i[2];
    i[0] = (int16)(x);
    i[1] = (int16)(x>>32);
    return i;
}
int8* c_ppvm_cpu_core::toInt8(int16 x){
    int8 i[2];
    i[0] = (int8)x;
    i[1] = (int8)(x>>8);
    return i;
}

uint8 c_ppvm_cpu_core::fetch() {
    uint8 data = this->ram[this->ip];
    this->ip++;
    return data;
}

uint16 c_ppvm_cpu_core::fetch16() {
    uint8 data1 = this->ram[this->ip];
    uint8 data2 = this->ram[this->ip+1];
    uint16 data = toUint16(data1, data2);
    this->ip+=2;
    return data;
}

uint32 c_ppvm_cpu_core::fetch32() {
    uint16 data1 = fetch16();
    uint16 data2 = fetch16();
    uint32 data = toUint32(data1, data2);  
    return data;
}

uint64 c_ppvm_cpu_core::fetch64() {
    uint32 data1 = fetch32();
    uint32 data2 = fetch32();
    uint64 data = toUint64(data1, data2);
    return data;
}

void c_ppvm_cpu_core::push(uint8 data) {
    this->ram[this->sp] = data;
    this->sp--;
}

void c_ppvm_cpu_core::push(uint16 data) { 
    uint8 data1 = this->toUint8(data)[0];
    uint8 data2 = toUint8(data)[1];
    push(data1);
    push(data2);
}

void c_ppvm_cpu_core::push(uint32 data) {
    uint16 data1 = toUint16(data)[0];
    uint16 data2 = toUint16(data)[1];
    push(data1);
    push(data2);
}

void c_ppvm_cpu_core::push(uint64 data) {
    uint32 data1 = toUint32(data)[0];
    uint32 data2 = toUint32(data)[1];
    push(data1);
    push(data2);
}

uint8 c_ppvm_cpu_core::pop() {
    this->sp++;
    return this->ram[this->sp];
}

uint16 c_ppvm_cpu_core::pop16() {
    uint8 data1 = pop();
    uint8 data2 = pop();
    return toUint16(data1, data2);
}

uint32 c_ppvm_cpu_core::pop32() {
    uint16 data1 = pop16();
    uint16 data2 = pop16();
    return toUint32(data1, data2);
}

uint64 c_ppvm_cpu_core::pop64() {
    uint32 data1 = pop32();
    uint32 data2 = pop32();
    return toUint64(data1, data2);
}

void c_ppvm_cpu_core::debug() {
    std::cout << "R1: " << (long)r1 << std::endl;
    std::cout << "R2: " << (long)r2 << std::endl;
    std::cout << "R3: " << (long)r3 << std::endl;
    std::cout << "R4: " << (long)r4 << std::endl;
    std::cout << "R5: " << (long)r5 << std::endl;
    std::cout << "R6: " << (long)r6 << std::endl;
    std::cout << "R7: " << (long)r7 << std::endl;
    std::cout << "R8: " << (long)r8 << std::endl;
    std::cout << "IP: " << (long)ip << std::endl;
    std::cout << "SP: " << (long)sp << std::endl;
    std::cout << "ACC: " << (long)acc << std::endl;
}
void c_ppvm_cpu_core::loadBytes(vector<uint8> data, uint64 pos) {
    for(uint64 i = pos; i < data.size()+pos; i++) {
        this->ram[i] = data[i-pos];
    }
}

uint64& c_ppvm_cpu_core::getRegister(uint8 registerIndex) {
    switch (registerIndex)
    {
        case 1: {
            return r1;
        }
        case 2: {
            return r2;
        }
        case 3: {
            return r3;
        }
        case 4: {
            return r4;
        }
        case 5: {
            return r5;
        }
        case 6: {
            return r6;
        }
        case 7: {
            return r7;
        }
        case 8: {
            return r8;
        }
        case 9: {
            return acc;
        }
    }
}

void c_ppvm_cpu_core::executeInstruction(uint8 instruction) {
    switch(instruction) {
        case MOV_LIT_REG: {
            uint64 literal = fetch64();
            getRegister(fetch()) = literal;
            break;
        }
        case MOV_REG_REG: {
            getRegister(fetch()) = getRegister(fetch());
            break;
        }
        case MOV_LIT_MEM: {
            uint32 literal = fetch32();
            uint32 addr = fetch32();
            uint16 addr0 = toUint16 (addr)[0];
            uint16 addr1 = toUint16 (addr)[1];

            uint8 addr_0 = toUint8 (addr0)[0];
            uint8 addr_1 = toUint8 (addr0)[1];
            uint8 addr_2 = toUint8 (addr1)[0];
            uint8 addr_3 = toUint8 (addr1)[1];

            uint16 data0 = toUint16 (literal)[0];
            uint16 data1 = toUint16 (literal)[1];

            uint8 data_0 = toUint8(data0)[0];
            uint8 data_1 = toUint8(data0)[1];
            uint8 data_2 = toUint8(data1)[0];
            uint8 data_3 = toUint8(data1)[1];

            this->ram[addr_0] = data_0;
            this->ram[addr_1] = data_1;
            this->ram[addr_2] = data_2;
            this->ram[addr_3] = data_3;
            break;
        }
        case MOV_REG_MEM: {
            
        }
    }
}