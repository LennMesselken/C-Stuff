
typedef enum {
    ADD, SUB, MUl,
    AND, OR, NOT, XOR, 
    PUSH, POP, SET,
    JMP, JMPZ, JMPOF, HLT
} Instructions;

typedef enum {
    A, B, C, D, E, F, G, H,
    IP, SP, FLAGS
} Registers;


int main (){
    int program[] = {SET, A, 1, SET, B, 2, ADD, A, B};
}