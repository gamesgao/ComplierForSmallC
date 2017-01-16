/***************************************************************************
dataSeg code Module
***************************************************************************/
/*=========================================================================
DECLARATIODS
=========================================================================*/
/*-------------------------------------------------------------------------
dataSeg code RECORD
-------------------------------------------------------------------------*/
struct dataSeg {
    char* id;
    int data;
    struct dataSeg* next; 
};
/*-------------------------------------------------------------------------
dataSeg code ENTRY
-------------------------------------------------------------------------*/
struct dataSeg* DStop = (struct dataSeg*) 0;
/*-------------------------------------------------------------------------
dataSeg code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
OperatioDS: push, pop, isEmpty.
========================================================================*/
void DSPush(char* id, char* prefix){
    struct dataSeg* newTop = (struct dataSeg* ) malloc(sizeof(struct dataSeg));
    newTop->id = (char *) malloc(strlen(id) + strlen(prefix) + 3);
    strcpy(newTop->id, id);
    if(strcmp(prefix, "") != 0) strcat(newTop->id, ".");
    if(strcmp(id, "") != 0) strcat(newTop->id, ":");
    strcat(newTop->id, prefix);
    newTop->data = 0;
    newTop->next = DStop;
    DStop = newTop;
}

int DSIsEmpty(){
    return DStop == (struct dataSeg*) 0;
}

void printDS(){
    struct dataSeg* ptr = DStop;
    printf(".data\n");
    while(ptr != (struct dataSeg*) 0){
        printf("%s\t.word\t%d\n", ptr->id, ptr->data);
        ptr = ptr->next;
    }
}
// struct DSData* DSPop(){
//     if(DSIsEmpty()) return 0;
//     struct DSData* temp = DStop->data;
//     struct dataSeg* tempTop = DStop->next;
//     // free(DStop);
//     DStop = tempTop;
//     return temp;
// }





/************************** End dataSeg code **************************/