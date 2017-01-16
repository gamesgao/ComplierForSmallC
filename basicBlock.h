/***************************************************************************
basicBlock code Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
basicBlock code RECORD
-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
basicBlock code ENTRY
-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
basicBlock code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
Operations: markBasicBlock.
========================================================================*/
void markBasicBlock(struct IntermediaRepresentation* IR){
    struct Quad *ptr = IR->head;
    while(ptr->next != (struct Quad *) 0){
        ptr = ptr->next;
        if(ptr->op == jmp || ptr->op == jgt || ptr->op == call || ptr->op == jgti){
            ptr->dest.addr->basicBlockFlag = 1;
            ptr->next->basicBlockFlag = 1;
        }
        else if(ptr->op == ret){
            ptr->next->basicBlockFlag = 1;
        }
    }
    ptr = IR->head;
    while(ptr->next != (struct Quad *) 0){
        ptr = ptr->next;
        if(ptr->op == label){
            ptr->basicBlockFlag = 0;
            ptr->next->basicBlockFlag = 1;
        }
    }
}

/************************** End basicBlock code **************************/