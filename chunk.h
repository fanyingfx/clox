//
// Created by fan on 9/13/22.
//

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;
typedef struct {
    /*
     * the number of elements in the array we have allocated (“capacity”)
     * and how many of those allocated entries are actually in use (“count”).
     */
    int count;
    int capacity;
    uint8_t *code;
    int *lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);

void freeChunk(Chunk *chunk);

void writeChunk(Chunk *chunk, uint8_t byte,int line);

int addConstant(Chunk *chunk, Value value);

#endif //CLOX_CHUNK_H
