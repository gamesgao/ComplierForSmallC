/***************************************************************************
scopeStack code Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
scopeStack code RECORD
-------------------------------------------------------------------------*/
struct scopeStack {
    struct symrec * scope;
    struct scopeStack* next; 
};
/*-------------------------------------------------------------------------
scopeStack code ENTRY
-------------------------------------------------------------------------*/
struct scopeStack* SStop = (struct scopeStack*) 0;
/*-------------------------------------------------------------------------
scopeStack code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
Operations: enQueue, deQueue, isEmpty.
========================================================================*/
void SSPush(struct symrec * scope){
    struct scopeStack* newOne = (struct scopeStack* ) malloc(sizeof(struct scopeStack));
    newOne->scope = scope;
    newOne->next = SStop;
    SStop= newOne;
}

int SSIsEmpty(){
    return SStop == (struct scopeStack*) 0;
}

struct symrec * SSPop(){
    if(SSIsEmpty()) return 0;
    struct symrec * tempScope = SStop->scope;
    struct scopeStack* temp = SStop;
    SStop = temp->next;
    free(temp);
    return tempScope;
}
/************************** End scopeStack code **************************/