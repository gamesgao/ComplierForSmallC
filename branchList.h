/***************************************************************************
branchList code Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
branchList code RECORD
-------------------------------------------------------------------------*/

struct branchList {
    struct Quad* inst;
    struct branchList* next; 
};
/*-------------------------------------------------------------------------
branchList code ENTRY
-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
branchList code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
Operations: makelist, merge, backpatch.
========================================================================*/
struct branchList * makelist(struct Quad* inst){
    struct branchList *temp = malloc(sizeof(struct branchList));
    temp->inst = inst;
    temp->next = (struct branchList *) 0;
    return temp;
}

struct branchList * merge(struct branchList * L1, struct branchList * L2){
    struct branchList * temp = L1;
    if(L1 == (struct branchList *) 0){
        if(L2 == (struct branchList *) 0) return 0;
        else{
            temp = L2;
            L2 = L1;
            L1 = temp;
        }
    }
    while(temp->next != 0){
        temp = temp->next;
    }
    temp->next = L2;
    return L1;
}

void backpatch(struct branchList * L, struct Quad* inst){
    struct branchList * temp = L;
    if(L == (struct branchList *) 0) return;
    while(temp->next != 0){
        temp->inst->dest.addr = inst;
        temp = temp->next;
    }
}


/************************** End branchList code **************************/