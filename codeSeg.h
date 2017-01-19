/***************************************************************************
codeSeg code Module
***************************************************************************/
/*=========================================================================
DECLARATIOCS
=========================================================================*/
/*-------------------------------------------------------------------------
codeSeg code RECORD
-------------------------------------------------------------------------*/
struct codeSeg {
    char* label;
    char* op;
    char* p1;
    char* p2;
    char* p3;
    char* prefix;
    struct codeSeg* next; 
};
/*-------------------------------------------------------------------------
codeSeg code ENTRY
-------------------------------------------------------------------------*/
struct codeSeg* CStop = (struct codeSeg*) 0;
struct codeSeg* CSbottom = (struct codeSeg*) 0;
/*-------------------------------------------------------------------------
codeSeg code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
Operations: push, pop, isEmpty.
========================================================================*/
void CSPush(char* label, char* op, char* p1, char* p2, char* p3, char* prefix){
    struct codeSeg* newBottom = (struct codeSeg* ) malloc(sizeof(struct codeSeg));
    newBottom->label = (char *) malloc(strlen(label) + 1);
    strcpy(newBottom->label, label);
    newBottom->op = (char *) malloc(strlen(op) + 1);
    strcpy(newBottom->op, op);
    newBottom->p1 = (char *) malloc(strlen(p1) + 1);
    strcpy(newBottom->p1, p1);
    newBottom->p2 = (char *) malloc(strlen(p2) + 1);
    strcpy(newBottom->p2, p2);
    newBottom->p3 = (char *) malloc(strlen(p3) + 1);
    strcpy(newBottom->p3, p3);
    newBottom->prefix = (char *) malloc(strlen(prefix) + 1);
    strcpy(newBottom->prefix, prefix);
    if(CSbottom == (struct codeSeg*) 0){
        CSbottom = newBottom;
        CStop = CSbottom;
    }
    else{
        CSbottom->next = newBottom;
    }
    newBottom->next = (struct codeSeg*) 0;
    CSbottom = newBottom;
}

int CSIsEmpty(){
    return CStop == (struct codeSeg*) 0;
}

void printCS(){
    struct codeSeg* ptr = CStop;
    printf(".text\n");
    while(ptr != (struct codeSeg*) 0){
        if(strcmp(ptr->label, "") != 0 && strcmp(ptr->prefix, "") != 0) printf("%s:\t%s\t%s\t%s\t%s.%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        else if(strcmp(ptr->label, "") != 0) printf("%s:\t%s\t%s\t%s\t%s%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        else if(strcmp(ptr->prefix, "") != 0) printf("%s\t%s\t%s\t%s\t%s.%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        else printf("%s\t%s\t%s\t%s\t%s%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        ptr = ptr->next;
    }
}

void outputCS(){
    struct codeSeg* ptr = CStop;
    printf(".text\n");
    while(ptr != (struct codeSeg*) 0){
        if(strcmp(ptr->label, "") != 0 && strcmp(ptr->prefix, "") != 0) printf("%s:\t%s\t%s\t%s\t%s.%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        else if(strcmp(ptr->label, "") != 0) printf("%s:\t%s\t%s\t%s\t%s%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        else if(strcmp(ptr->prefix, "") != 0) printf("%s\t%s\t%s\t%s\t%s.%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        else printf("%s\t%s\t%s\t%s\t%s%s\t\n", ptr->label, ptr->op, ptr->p1, ptr->p2, ptr->prefix, ptr->p3);
        ptr = ptr->next;
    }
}

// struct codeSeg* findCodeInst(char *id, char *prefix){
//     struct codeSeg* ptr = CStop;
//     while(ptr != (struct codeSeg*) 0){
//         if(strcmp(ptr->id, id) == 0 && strcmp(ptr->prefix, prefix) == 0){
//             return ptr;
//         }
//         ptr = ptr->next;
//     }
//     return 0;
// }
// struct CSData* CSPop(){
//     if(CSIsEmpty()) return 0;
//     struct CSData* temp = CStop->data;
//     struct codeSeg* tempTop = CStop->next;
//     // free(CStop);
//     CStop = tempTop;
//     return temp;
// }





/************************** End codeSeg code **************************/