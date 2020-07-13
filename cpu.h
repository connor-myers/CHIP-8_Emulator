#ifndef CPU_H
#define CPU_H

typedef struct CPU {
    unsigned int memory[];
    unsigned int registers[];
    unsigned short stack[];            
} CPU;

#endif 