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
void SQEnQueue(struct symrec * scope, char* prefix){
    struct scopeQueue* newOne = (struct scopeQueue* ) malloc(sizeof(struct scopeQueue));
    newOne->scope = scope;
    newOne->prefix = (char *) malloc(strlen(prefix) + 1);
    strcpy(newOne->prefix, prefix);
    newOne->next = (struct scopeQueue*) 0;
    SQbottom->next = newOne;
    SQbottom = SQbottom->next;
}

int SQIsEmpty(){
    return SQbottom == SQtop;
}

struct symrec * SQDeQueue(){
    if(SQIsEmpty()) return 0;
    struct symrec * tempScope = SQtop->next->scope;
    struct scopeQueue* temp = SQtop->next;
    if(temp != SQbottom) SQtop->next = temp->next;
    else SQbottom = SQtop;
    free(temp);
    return tempScope;
}

char* getPrefixFromTop(){
    if(SQIsEmpty()) return 0;
    return SQtop->next->prefix;
}

void initSQ(){
    // the first node is useless!
    SQtop = (struct scopeQueue* ) malloc(sizeof(struct scopeQueue));
    SQtop->next = (struct scopeQueue*) 0;
    SQbottom = SQtop;
}



/************************** End scopeQueue code **************************/