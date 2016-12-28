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
  add, sub, mul, div, load, store, mov, jmp, call
};

union var {
    int line;
    int reg;
    int num;
    char* variable;
};

// 一条IR指令
struct Quad {
  // 四元组
  Opcode op;
  var   src1; // 直接使用别的指令作为operand
  var   src2;
  var   dest;

  struct Quad* prev, next; // 双向链
}

struct IntermediaRepresentation{
    struct Quad* head;
    struct Quad* tail;
}

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
/*========================================================================
Operations: genIR
========================================================================*/
void genIR(Opcode op, var s1, var s2, var d) {
  if(IR == (struct IntermediaRepresentation*)0){
    IR = (struct IntermediaRepresentation *) malloc(sizeof(struct IntermediaRepresentation));
    IR->head = (struct Quad *) malloc(sizeof(struct Quad));
    IR->head->next = (Quad *)0;
    IR->head->prev = (Quad *)0;
    IR->tail = IR->head;
  }// the first node is useless
  struct Quad *ptr;
  ptr = (struct Quad *) malloc(sizeof(struct Quad));
  ptr->op = op;
  ptr->src1 = s1; // this may cause some problem
  ptr->src2 = s2;
  ptr->dest = d;
  IR->tail->next = ptr;
  ptr->prev = IR->tail;
  IR->tail = ptr;
  // return ptr;
}
/************************** End Quad code **************************/