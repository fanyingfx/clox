//
// Created by fan on 9/16/22.
//

#include <stdio.h>
#include "compile.h"
#include "scanner.h"
void compile(const char *source,Chunk *chunk){
    initScanner(source);
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");

}

//static void advance(){
//    parser.previous = parser.current;
//for(;;){
//    parser.current=scanToken();
//    if(parser.current.type!= TOKEN_ERROR) break;
//
//    errorAtCurrent(parser.current.start);
//}
//}
//bool compile(const char* source, Chunk *chunk ){
//    initScanner(source);
//
//    advance();
//    expression();
//    consume(TOKEN_EOF, "Expect end of expression.");
//}
