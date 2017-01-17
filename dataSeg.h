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
    char* prefix;
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
    newTop->id = (char *) malloc(strlen(id) + 1);
    newTop->prefix = (char *) malloc(strlen(prefix) + 1);
    strcpy(newTop->id, id);
    strcpy(newTop->prefix, prefix);
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
        if(strcmp(ptr->id, "") != 0 && strcmp(ptr->prefix, "") != 0)printf("%s.%s:\t.word\t%d\n", ptr->prefix, ptr->id, ptr->data);
        else if(strcmp(ptr->id, "") != 0) printf("%s%s:\t.word\t%d\n", ptr->prefix, ptr->id, ptr->data);
        else printf("\t.word\t%d\n", ptr->data);
        ptr = ptr->next;
    }
}

struct dataSeg* findDataInst(char *id, char *prefix){
    struct dataSeg* ptr = DStop;
    while(ptr != (struct dataSeg*) 0){
        if(strcmp(ptr->id, id) == 0 && strcmp(ptr->prefix, prefix) == 0){
            return ptr;
        }
        ptr = ptr->next;
    }
    return 0;
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