//
// Created by fan on 9/13/22.
//
#include <stdlib.h>
#include "chunk.h"
#include "memory.h"
void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->lines=NULL;
    chunk->lineCapacity=0;
    chunk->lineCount=0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
}
void freeChunk(Chunk* chunk){
    FREE_ARRAY(uint8_t,chunk->code,chunk->capacity);
    FREE_ARRAY(LineStart ,chunk->lines,chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}
void writeChunk(Chunk* chunk, uint8_t byte,int line){
    if(chunk->capacity < chunk->count+1){
        int oldCapacity = chunk->capacity;
        chunk->capacity=GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,oldCapacity,chunk->capacity);
    }

    chunk->code[chunk->count]=byte;
    chunk->count++;

    // RLE line num
    if(chunk->lineCount >0  &&line == chunk->lines[chunk->lineCount-1].line){
        return;
    }
    if(chunk->lineCapacity < chunk->lineCount+1){
        int oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity=GROW_CAPACITY(oldCapacity);
        chunk->lines= GROW_ARRAY(LineStart , chunk->lines,oldCapacity,chunk->lineCapacity);
    }
    LineStart *lineStart = &chunk->lines[chunk->lineCount++];
    lineStart->offset=chunk->count-1;
    lineStart->line=line;

}
int addConstant(Chunk* chunk, Value value){
    writeValueArray(&chunk->constants,value);
    return chunk->constants.count-1;
}
void writeConstant(Chunk* chunk,Value value,int line){

}