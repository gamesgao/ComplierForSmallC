/***************************************************************************
Code Generator
***************************************************************************/
#include "scopeQueue.h" /*scopeQueue Code*/
#include "dataSeg.h" /*dataSeg Code*/
/*-------------------------------------------------------------------------
Data Segment
-------------------------------------------------------------------------*/
char *prefix;

void genDatawithinScope(struct symrec * symPoint){
    struct symrec *ptr;

    for (ptr = symPoint; ptr != (struct symrec *)0 && ptr->name != 0; ptr = (struct symrec *)ptr->next){
        if(strcmp(ptr->type, "int") == 0){
            DSPush(ptr->name, prefix);
        } else if(strcmp(ptr->type, "func") == 0){
            SQEnQueue(ptr->scope, ptr->name);
        } else if(strcmp(ptr->type, "struct") != 0){
            struct symrec *base = getsym(ptr->type);
            int i;
            for(i = 0; i < base->width / 4-1 ;i++){
                DSPush("", "");
            }
            DSPush(ptr->name, prefix);
        }
    }
}

void genData(){
    initSQ();
    SQEnQueue(sym_table, "");
    while(!SQIsEmpty()){
        prefix = getPrefixFromTop();
        genDatawithinScope(SQDeQueue());
    }
    printDS();
}

void patchData(){
    // InitR
}
/*-------------------------------------------------------------------------
Code Segment
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Print Code to stdio
-------------------------------------------------------------------------*/

/************************** End Code Generator **************************/