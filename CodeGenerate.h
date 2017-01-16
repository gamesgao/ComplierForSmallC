/***************************************************************************
Code Generator
***************************************************************************/
#include "scopeQueue.h" /*scopeQueue Code*/
/*-------------------------------------------------------------------------
Data Segment
-------------------------------------------------------------------------*/
char *prefix;

void genDatawithinScope(struct symrec * symPoint){
    struct symrec *ptr;
    for (ptr = symPoint; ptr != (struct symrec *)0 && ptr->name != 0; ptr = (struct symrec *)ptr->next){
        if(strcmp(ptr->type, "int") == 0){
        } else if(strcmp(ptr->type, "func") == 0){
            printSTwithinScope(ptr->scope);
        } else if(strcmp(ptr->type, "struct") == 0){
            printSTwithinScope(ptr->scope);
        }
        else{
        }
    }
}

void genData(){
    initSQ();
    SQEnQueue(sym_table);
    prefix = "";
    while(!SQIsEmpty()){
        genDatawithinScope(SQDeQueue());
    }
}
/*-------------------------------------------------------------------------
Code Segment
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Print Code to stdio
-------------------------------------------------------------------------*/
void print_code() {
    int i = 0;
    while (i < code_offset) {
        printf("%3ld: %-10s%4ld\n", i, op_name[(int)code[i].op], code[i].arg);
        i++;
    }
}
/************************** End Code Generator **************************/