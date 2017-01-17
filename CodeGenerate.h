/***************************************************************************
Code Generator
***************************************************************************/
#include "scopeQueue.h" /*scopeQueue Code*/
#include "dataSeg.h" /*dataSeg Code*/
#include "RegAllocation.h" /*RegAllocation Code*/
/*-------------------------------------------------------------------------
Data Segment
-------------------------------------------------------------------------*/
char *prefix;

void genDatawithinScope(struct symrec * symPoint){
    struct symrec *ptr;

    for (ptr = symPoint; ptr != (struct symrec *)0 && ptr->name != 0; ptr = (struct symrec *)ptr->next){
        if(strcmp(ptr->type, "int") == 0){
            int i;
            for(i = 0; i<ptr->width * ptr->height -1;i++){
                DSPush("", "");
            }
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
        ptr = ptr->next;
        if(ptr->op == label) prefix = ptr->dest.id;
        else if(ptr->op == swi){
            struct dataSeg* target = findDataInst(ptr->dest.id, prefix);
            int i;
            for(i=0;i<ptr->src2.TIA/4;i++) target = target->next;
            if(target != (struct dataSeg*) 0) target->data = result;
            else{
                printf("wrong while do patchData!\n");
            }
            result = 0;
        }
        else if(ptr->op == li){
            result = ptr->src2.TIA;
        }
        else if(ptr->op == end){
            break;
        }
        else{
            printf("the remain one need to do more!\n");
        }
    }
    printDS();
}
/*-------------------------------------------------------------------------
Code Segment
-------------------------------------------------------------------------*/
void CodeGenerate(){
    struct Quad* ptr = InterR->head;
    struct symrec *scope=sym_table;
    char *label = (char *)malloc(sizeof(char)*80);
    char *op = (char *)malloc(sizeof(char)*80);
    char *p1 = (char *)malloc(sizeof(char)*80);
    char *p2 = (char *)malloc(sizeof(char)*80);
    char *p3 = (char *)malloc(sizeof(char)*80);
    char *prefix = (char *)malloc(sizeof(char)*80);
    sprintf(prefix, "");
    while(ptr->next != (struct Quad *)0){
        ptr = ptr->next;
        switch(ptr->op){
            case mul:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "mul");
                sprintf(p1, "$%d", getTR(ptr, ptr->dest.TIA));
                sprintf(p2, "$%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p3, "$%d", getTemp(ptr, ptr->src2.TIA));        
                CSPush(label, op, p1, p2, p3, "");
                sprintf(label, "");
                break;
            }
            case muli:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "mul");
                sprintf(p1, "$%d", getTR(ptr, ptr->dest.TIA));
                sprintf(p2, "$%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p3, "%d", gptr->src2.TIA);
                CSPush(label, op, p1, p2, p3, "");
                sprintf(label, "");
                break;
            }
            case label:{
                sprintf(label, "%s", ptr->dest.id);
                scope = getsym(ptr->dest.id)->scope;
                sprintf(prefix, ptr->dest.id);


                break;
            }
            case lwi:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "lw");
                sprintf(p1, "$%d", getTR(ptr, ptr->src1.TIA));
                sprintf(p2, "", );
                sprintf(p3, "%s+%d", ptr->dest.id, ptr->src2.TIA);
                if(getsymWithinScope(ptr->dest.id, scope) != (struct symrec *) 0) CSPush(label, op, p1, p2, p3, prefix);
                else CSPush(label, op, p1, p2, p3, "");
                sprintf(label, "");
                break;
            }
            case li:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "li");
                sprintf(p1, "$%d", getTR(ptr, ptr->dest.TIA));
                sprintf(p2, "");
                sprintf(p3, "%d", ptr->src2.TIA);
                CSPush(label, op, p1, p2, p3, "");
                sprintf(label, "");
                break;
            }
            case swi:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "sw");
                sprintf(p1, "$%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p2, "");
                sprintf(p3, "%s+%d", ptr->dest.id, ptr->src2.TIA);
                if(getsymWithinScope(ptr->dest.id, scope) != (struct symrec *) 0) CSPush(label, op, p1, p2, p3, prefix);
                else CSPush(label, op, p1, p2, p3, "");
                sprintf(label, "");
                break;
            }
            case jgti:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "bgt");
                sprintf(p1, "$%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p2, "%d", gptr->src2.TIA);
                sprintf(p3, "l%d", ptr->dest.addr->order);        
                CSPush(label, op, p1, p2, p3, "");
                sprintf(label, "");
                break;
            }
            case jmp:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "j");
                sprintf(p1, "");
                sprintf(p2, "");
                sprintf(p3, "l%d", ptr->dest.addr->order);        
                CSPush(label, op, p1, p2, p3, "");
                sprintf(label, "");
                break;
            }
            case write:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                sprintf(op, "move");
                sprintf(p1, "$a0");
                sprintf(p2, "$%d", ptr->dest.TIA);
                sprintf(p3, "");        
                CSPush(label, op, p1, p2, p3, "");       
                CSPush("", "li", "$v0", "1", "", "");
                CSPush("", "syscall", "", "", "", "");
                sprintf(label, "");
                break;
            }
            case ret:{
                if(ptr->basicBlockFlag == 1 && strcmp(label, "") == 0) sprintf(label, "l%d", ptr->order);
                if(strcmp(prefix, "main") == 0){
                    CSPush(label, "li", "$v0", "10", "", "");
                    CSPush("", "syscall", "", "", "", "");
                    break;
                }
                sprintf(op, "move");
                sprintf(p1, "$v0");
                sprintf(p2, "$%d", ptr->src1.TIA);
                sprintf(p3, "");        
                CSPush(label, op, p1, p2, p3, "");
                CSPush("", "lw", "$ra", "0($sp)", "", "");
                CSPush("", "jr", "$ra", "", "", "");
                sprintf(label, "");
                break;
            }
            default:printf("wrong while CG\n");
        }

    }
}


/*-------------------------------------------------------------------------
Print Code to stdio
-------------------------------------------------------------------------*/

/************************** End Code Generator **************************/