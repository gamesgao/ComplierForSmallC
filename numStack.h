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
    // char* id;
}

struct numStack {
    struct NSData* data;
    struct numStack* next; 
};
/*-------------------------------------------------------------------------
numStack code ENTRY
-------------------------------------------------------------------------*/
struct numStack* top = (struct numStack*) 0;
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
    newTop->next = top;
    top = newTop;
}

struct NSData* NSPop(){
    if(isEmpty()) return -409;
    struct NSData* temp = top->data;
    struct numStack* tempTop = top->next;
    free(top);
    top = tempTop;
    return temp;
}

bool NSIsEmpty(){
    return top == (struct numStack*) 0;
}



/************************** End numStack code **************************/