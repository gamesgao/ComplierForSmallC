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
    struct Quad* ptr = InitR->head;
    int result = 0;
    prefix = "";
    while(ptr->next != (struct Quad *)0){
        ptr1 = ptr->next;
        if(ptr->op == label) prefix = ptr->dest.id;
        else if(ptr->op == swi){
            struct dataSeg* target = findDataInst(ptr->dest.id, prefix);
            if(target != (struct dataSeg*) 0) target->data = result;
            else{
                printf("wrong while do patchData!\n");
            }
            result = 0;
        }
        else if(ptr->op == li){
            result = ptr->src2;
        }
        else{
            printf("the remain one need to do more!\n");
        }
    }
}
/*-------------------------------------------------------------------------
Code Segment
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Print Code to stdio
-------------------------------------------------------------------------*/

/************************** End Code Generator **************************/