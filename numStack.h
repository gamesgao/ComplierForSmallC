/***************************************************************************
numStack code Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
numStack code RECORD
-------------------------------------------------------------------------*/
struct NSData{
    int valType; /*can be 0:empty, 1:int, 2:temp*/
    // int intval;
    int temp;
    char* id;
    int offset;
    struct branchList* trueList;
    struct branchList* falseList;
    struct branchList* nextList;
};

struct numStack {
    struct NSData* data;
    struct numStack* next; 
};
/*-------------------------------------------------------------------------
numStack code ENTRY
-------------------------------------------------------------------------*/
struct numStack* NStop = (struct numStack*) 0;
/*-------------------------------------------------------------------------
numStack code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
Operations: push, pop, isEmpty.
========================================================================*/
void NSPush(struct NSData* data){
    struct numStack* newTop = (struct numStack* ) malloc(sizeof(struct numStack));
    newTop->data = (struct NSData*) malloc(sizeof(struct NSData));
    newTop->data->valType = data->valType;
    newTop->data->temp = data->temp;
    newTop->data->id = data->id;
    newTop->data->offset = data->offset;
    newTop->next = NStop;
    NStop = newTop;
}

int NSIsEmpty(){
    return NStop == (struct numStack*) 0;
}

struct NSData* NSPop(){
    if(NSIsEmpty()) return 0;
    struct NSData* temp = NStop->data;
    struct numStack* tempTop = NStop->next;
    free(NStop);
    NStop = tempTop;
    return temp;
}

struct NSData* getNSFromBottom(){
    struct numStack*ptr = NStop;
    struct numStack*ptrPrev;
    if(ptr->next == (struct numStack*) 0){
        NStop = (struct numStack*) 0;
        struct NSData* temp = ptr->data;
        free(ptr);
        return temp;
    }
    while(ptr->next != (struct numStack*) 0){
        ptrPrev = ptr;
        ptr = ptr->next;
    }
    ptrPrev->next = (struct numStack*) 0;
    struct NSData* temp = ptr->data;
    free(ptr);
    return temp;
}





/************************** End numStack code **************************/