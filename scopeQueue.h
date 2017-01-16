/***************************************************************************
scopeQueue code Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
scopeQueue code RECORD
-------------------------------------------------------------------------*/
struct scopeQueue {
    char* prefix;
    struct symrec * scope;
    struct scopeQueue* next; 
};
/*-------------------------------------------------------------------------
scopeQueue code ENTRY
-------------------------------------------------------------------------*/
struct scopeQueue* SQtop = (struct scopeQueue*) 0;
struct scopeQueue* SQbottom = (struct scopeQueue*) 0;
/*-------------------------------------------------------------------------
scopeQueue code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
Operations: enQueue, deQueue, isEmpty.
========================================================================*/
void SQEnQueue(struct symrec * scope){
    struct scopeQueue* newOne = (struct scopeQueue* ) malloc(sizeof(struct scopeQueue));
    newOne->scope = scope;
    SQbottom->next = newOne;
    SQbottom = SQbottom->next;
}

int SQIsEmpty(){
    return SQbottom == SQtop;
}

struct symrec * SQDeQueue(){
    if(NSIsEmpty()) return 0;
    struct symrec * temp = top->next->scope;
    struct scopeQueue* temp = top->next;
    top->next = temp->next;
    free(temp);
    return temp;
}

void initSQ(){
    // the first node is useless!
    SQtop = (struct scopeQueue* ) malloc(sizeof(struct scopeQueue));
    SQtop->next = (struct scopeQueue*) 0;
    SQbottom = SQtop;
}



/************************** End scopeQueue code **************************/