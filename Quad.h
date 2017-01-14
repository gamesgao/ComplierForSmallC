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
    add, addi, sub, subi, mul, muli, opdiv, opdivi, lwi, swi, jmp, call, li, lw, sw, jgt, jgti
};

char* Opstr[15] = {
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
    "li",
    "lw",
    "sw",
    "jgt",
    "jgti"
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
struct IntermediaRepresentation* IR = (struct IntermediaRepresentation*) 0;
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
    if(IR == (struct IntermediaRepresentation*)0){
        IR = (struct IntermediaRepresentation *) malloc(sizeof(struct IntermediaRepresentation));
        IR->head = (struct Quad *) malloc(sizeof(struct Quad));
        IR->head->order = 0;
        IR->head->next = (struct Quad *)0;
        IR->head->prev = (struct Quad *)0;
        IR->tail = IR->head;
    }// the first node is useless
    struct Quad *ptr;
    ptr = (struct Quad *) malloc(sizeof(struct Quad));
    ptr->order = IR->tail->order+1;
    ptr->op = op;
    ptr->src1.TIA = s1; // this may cause some problem
    ptr->src2.TIA = s2;
    ptr->dest.TIA = d;
    IR->tail->next = ptr;
    ptr->prev = IR->tail;
    ptr->next = 0;
    IR->tail = ptr;
    return ptr;
}

struct Quad * genIRForLS(enum Opcode op, int s1, int s2, char* d) {
    if(IR == (struct IntermediaRepresentation*)0){
        IR = (struct IntermediaRepresentation *) malloc(sizeof(struct IntermediaRepresentation));
        IR->head = (struct Quad *) malloc(sizeof(struct Quad));
        IR->head->order = 0;
        IR->head->next = (struct Quad *)0;
        IR->head->prev = (struct Quad *)0;
        IR->tail = IR->head;
    }// the first node is useless
    struct Quad *ptr;
    ptr = (struct Quad *) malloc(sizeof(struct Quad));
    ptr->order = IR->tail->order+1;
    ptr->op = op;
    ptr->src1.TIA = s1; // this may cause some problem
    ptr->src2.TIA = s2;
    ptr->dest.id = d;
    IR->tail->next = ptr;
    ptr->prev = IR->tail;
    ptr->next = (struct Quad *)0;
    IR->tail = ptr;
    return ptr;
}

struct Quad * genIRForBranch(enum Opcode op, int s1, int s2, struct Quad* d) {
    if(IR == (struct IntermediaRepresentation*)0){
        IR = (struct IntermediaRepresentation *) malloc(sizeof(struct IntermediaRepresentation));
        IR->head = (struct Quad *) malloc(sizeof(struct Quad));
        IR->head->order = 0;
        IR->head->next = (struct Quad *)0;
        IR->head->prev = (struct Quad *)0;
        IR->tail = IR->head;
    }// the first node is useless
    struct Quad *ptr;
    ptr = (struct Quad *) malloc(sizeof(struct Quad));
    ptr->order = IR->tail->order+1;
    ptr->op = op;
    ptr->src1.TIA = s1; // this may cause some problem
    ptr->src2.TIA = s2;
    ptr->dest.addr = d;
    IR->tail->next = ptr;
    ptr->prev = IR->tail;
    ptr->next = (struct Quad *)0;
    IR->tail = ptr;
    return ptr;
}

int newTemp(){
    return tempCount++;
}

void printIR(){
    if(IR == (struct IntermediaRepresentation*)0) return;
    struct Quad* ptr = IR->head;
    while(ptr->next != (struct Quad *)0){
        ptr = ptr->next;
        if(ptr->op==lw || ptr->op==sw) printf("%d\t%s\t%d\t%d\t%s\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.id);
        else if(ptr->op == jmp || ptr->op == jgt) printf("%d\t%s\t%d\t%d\tinst%d\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.addr->order);
        else printf("%d\t%s\t%d\t%d\t%d\n", ptr->order, Opstr[ptr->op], ptr->src1.TIA, ptr->src2.TIA, ptr->dest.TIA);
    }
}
/************************** End Quad code **************************/