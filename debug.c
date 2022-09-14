//
// Created by fan on 9/13/22.
//

#include "debug.h"
#include <stdio.h>


void disassembleChunk(Chunk *chunk, const char *name) {
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }

}

static int constantInstruction(const char *name, Chunk *chunk, int offset) {
    uint8_t constant = chunk->code[offset+1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset+2;
}
static int simpleInstruction(const char *name,int offset){
    printf("%s\n", name);
    return offset+1;

}
int getLine(Chunk *chunk, int offset){
    int start =0;
    int end = chunk->lineCount-1;
    for(;;){
        int mid = (start+end)/2;
        LineStart *line=&chunk->lines[mid];
        if(offset < line->offset){
            end = mid-1;
        } else if(mid == chunk->lineCount-1 || offset < chunk->lines[mid+1].offset){
            return line->line;
    } else{
            start=mid+1;
        }
    }

}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);
    if(offset>0 && getLine(chunk,offset)== getLine(chunk,offset-1)){
        printf("   | ");
    } else{
        printf("%4d ", getLine(chunk,offset));
    }
    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        default:
            printf("Unknow opcode %d\n", instruction);
            return offset + 1;

    }
}



