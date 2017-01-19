/***************************************************************************
Quad code Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
Quad code RECORD
-------------------------------------------------------------------------*/

enum Opcode {
    bnot, add, addi, sub, subi, mul, muli, opdiv, opdivi, lwi, swi, jmp, call, ret, li, lw, sw, jgt, jgti, end, param, write, read, label, rem, remi, shl, shli, shr, shri, jge, jgei, jlt, jlti, jle, jlei, je, jei, jne, jnei, band, bandi, bxor, bxori, bor, bori, neg
};

char* Opstr[47] = {
    "bnot",
    "add",
    "addi",
    "sub",
    "subi",
    "mul",
    "muli",
    "div",
    "divi",
    "lwi",
    "swi",
    "jmp",
    "call",
    "ret",
    "li",
    "lw",
    "sw",
    "jgt",
    "jgti",
    "end",
    "param",
    "write",
    "read",
    "label",
    "rem",
    "remi",
    "shl",
    "shli",
    "shr",
    "shri",
    "jge",
    "jgei",
    "jlt",
    "jlti",
    "jle",
    "jlei",
    "je",
    "jei",
    "jne",
    "jnei",
    "band",
    "bandi",
    "bxor",
    "bxori",
    "bor",
    "bori",
    "neg"
};

union var {
     //虽然我也想用int 但是这样会导致我无法区分temp和id
    int TIA; // stand for temp, immediate number and address.
    char* id; //或者干脆就不要用id了,或者只在lwsw处用id
    struct Quad* addr; //用于jmp
};

// 一条IR指令
struct Quad {
    // 四元组
    int order;
    enum Opcode op;
    union var   src1; // 直接使用别的指令作为operand
    union var   src2;
    union var   dest;

    int basicBlockFlag;

    struct Quad* prev;
    struct Quad* next; // 双向链
};

struct IntermediaRepresentation{
    struct Quad* head;
    struct Quad* tail;
};

// // 一个基本块
// class BasicBlock {
//   Quad head; // 用一个线性链表来表示整个基本块的逻辑；末尾必须是控制流指令；中间不包括phi
//   ArrayList<Quad> phis; // 记录该基本块开头所需的phi指令

//   // ArrayList<BasicBlock> successors;
//   // 后继基本块；该信息可以从该基本块末尾的控制流指令提取，不需要显式用字段记录

//   // ??? flags;
//   // 可选的额外信息，可以用来记录诸如按reverse post-order（RPO）遍历CFG的序号，是否是循环开头（loop header），等等
// }

// class IR {
//   BasicBlock start; // 起始基本块

//   // List<BasicBlock> blocks; // 所有基本块
//   // 虽然从start肯定能顺着CFG遍历到所有活着的基本块，但也有些实现为方便而在一个列表里记录下所有基本块的引用；
//   // 有时候（例如要处理异常的话）有可能有活着的基本块会无法直接从start到达，此时也最好显式记录所有block。
// }

/*-------------------------------------------------------------------------
Quad code ENTRY
-------------------------------------------------------------------------*/
struct IntermediaRepresentation * IR = (struct IntermediaRepresentation*) 0;
struct IntermediaRepresentation* InterR = (struct IntermediaRepresentation*) 0;
struct IntermediaRepresentation* InitR = (struct IntermediaRepresentation*) 0;
/*-------------------------------------------------------------------------
Quad code
Implementation: a chain of records.
------------------------------------------------------------------------*/
// struct Quad *sym_table = (Quad *) 0; /* The pointer to the Quad code */

/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
// IR->head = IR->tail = (Quad *) 0;
int tempCount = 0;
/*========================================================================
Operations: genIR
========================================================================*/
struct Quad * genIR(enum Opcode op, int s1, int s2, int d) {
    struct Quad *ptr;
    struct Quad *next;
    next = (struct Quad *) malloc(sizeof(struct Quad));
    ptr = IR->tail->next;
    next->order = ptr->order+1;
    next->basicBlockFlag = 0;
    ptr->op = op;
    ptr->src1.TIA = s1; // this may cause some problem
    ptr->src2.TIA = s2;
    ptr->dest.TIA = d;
    ptr->next = next;
    next->prev = ptr;
    next->next = 0;
    IR->tail = ptr;
    return ptr;
}

struct Quad * genIRForLS(enum Opcode op, int s1, int s2, char* d) {
    struct Quad *ptr;
    struct Quad *next;
    next = (struct Quad *) malloc(sizeof(struct Quad));
    ptr = IR->tail->next;
    next->order = ptr->order+1;
    next->basicBlockFlag = 0;
    ptr->op = op;
    ptr->src1.TIA = s1; // this may cause some problem
    ptr->src2.TIA = s2;
    ptr->dest.id = d;
    ptr->next = next;
    next->prev = ptr;
    next->next = 0;
    IR->tail = ptr;
    return ptr;
}

struct Quad * genIRForLabel(char* l) {
    struct Quad *ptr;
    struct Quad *next;
    next = (struct Quad *) malloc(sizeof(struct Quad));
    ptr = IR->tail->next;
    next->order = ptr->order+1;
    next->basicBlockFlag = 0; // this may cause some problem
    ptr->op = label;
    ptr->src1.TIA = 0; 
    ptr->src2.TIA = 0;
    ptr->dest.id = l;
    ptr->next = next;
    next->prev = ptr;
    next->next = 0;
    IR->tail = ptr;
    return ptr;
}

struct Quad * genIRForBranch(enum Opcode op, int s1, int s2, struct Quad* d) {
    struct Quad *ptr;
    struct Quad *next;
    next = (struct Quad *) malloc(sizeof(struct Quad));
    ptr = IR->tail->next;
    next->order = ptr->order+1;
    next->basicBlockFlag = 0;
    ptr->op = op;
    ptr->src1.TIA = s1; // this may cause some problem
    ptr->src2.TIA = s2;
    ptr->dest.addr = d;
    ptr->next = next;
    next->prev = ptr;
    next->next = 0;
    IR->tail = ptr;
    return ptr;
}

int newTemp(){
    return tempCount++;
}

void printIR(struct IntermediaRepresentation * ir){
    if(ir == (struct IntermediaRepresentation*)0) return;
    struct Quad* ptr = ir->head;
    while(ptr->next != (struct Quad *)0){
        ptr = ptr->next;
        if(ptr->basicBlockFlag == 1) printf("###");
        if(ptr->op==lw || ptr->op==sw || ptr->op==swi || ptr->op==lwi || ptr->op==param) printf("%d\t%s\t%d\t%d\t%s\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.id);
        else if(ptr->op == jmp || ptr->op == jgt || ptr->op == jgti || ptr->op == call || ptr->op == jge || ptr->op == jgei || ptr->op == jlt || ptr->op == jlti || ptr->op == jle || ptr->op == jlei || ptr->op == je || ptr->op == jei || ptr->op == jne || ptr->op == jnei) printf("%d\t%s\t%d\t%d\tinst%d\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.addr->order);
        else if(ptr->op == label) printf("%s:\n", ptr->dest.id);
        else printf("%d\t%s\t%d\t%d\t%d\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.TIA);
    }
}

void initInitR(){
    InitR = (struct IntermediaRepresentation *) malloc(sizeof(struct IntermediaRepresentation));
    InitR->head = (struct Quad *) malloc(sizeof(struct Quad));
    InitR->tail = (struct Quad *) malloc(sizeof(struct Quad));
    InitR->head->order = 0;
    InitR->head->basicBlockFlag = 0;
    InitR->tail->order = 1;
    InitR->tail->basicBlockFlag = 1;
    InitR->head->next = InitR->tail;
    InitR->head->prev = (struct Quad *)0;
    InitR->tail->prev = InitR->head;
    InitR->tail->next = (struct Quad *)0;
    InitR->tail = InitR->head;
}

void initInterR(){
    InterR = (struct IntermediaRepresentation *) malloc(sizeof(struct IntermediaRepresentation));
    InterR->head = (struct Quad *) malloc(sizeof(struct Quad));
    InterR->tail = (struct Quad *) malloc(sizeof(struct Quad));
    InterR->head->order = 0;
    InterR->head->basicBlockFlag = 0;
    InterR->tail->order = 1;
    InterR->tail->basicBlockFlag = 1;
    InterR->head->next = InterR->tail;
    InterR->head->prev = (struct Quad *)0;
    InterR->tail->prev = InterR->head;
    InterR->tail->next = (struct Quad *)0;
    InterR->tail = InterR->head;


}

void endIR(struct IntermediaRepresentation * ir){
    ir->tail = ir->tail->next;
    ir->tail->op = end;
    ir->tail->src1.TIA = 0; // this may cause some problem
    ir->tail->src2.TIA = 0;
    ir->tail->dest.TIA = 0;
}

    


void outputIR(struct IntermediaRepresentation * ir){
    if(ir == (struct IntermediaRepresentation*)0) return;
    struct Quad* ptr = ir->head;
    while(ptr->next != (struct Quad *)0){
        ptr = ptr->next;
        if(ptr->basicBlockFlag == 1) fprintf(yyout,"###");
        if(ptr->op==lw || ptr->op==sw || ptr->op==swi || ptr->op==lwi || ptr->op==param) fprintf(yyout,"%d\t%s\t%d\t%d\t%s\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.id);
        else if(ptr->op == jmp || ptr->op == jgt || ptr->op == jgti || ptr->op == call || ptr->op == jge || ptr->op == jgei || ptr->op == jlt || ptr->op == jlti || ptr->op == jle || ptr->op == jlei || ptr->op == je || ptr->op == jei || ptr->op == jne || ptr->op == jnei) fprintf(yyout,"%d\t%s\t%d\t%d\tinst%d\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.addr->order);
        else if(ptr->op == label) fprintf(yyout,"%s:\n", ptr->dest.id);
        else fprintf(yyout,"%d\t%s\t%d\t%d\t%d\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.TIA);
    }
}
/************************** End Quad code **************************/