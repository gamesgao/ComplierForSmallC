/***************************************************************************
Code Generator
***************************************************************************/
#include "scopeQueue.h" /*scopeQueue Code*/
#include "dataSeg.h" /*dataSeg Code*/
#include "codeSeg.h" /*codeSeg Code*/
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
    char* noneStr = "";
    char *instLabel = (char *)malloc(sizeof(char)*80);
    char *op = (char *)malloc(sizeof(char)*80);
    char *p1 = (char *)malloc(sizeof(char)*80);
    char *p2 = (char *)malloc(sizeof(char)*80);
    char *p3 = (char *)malloc(sizeof(char)*80);
    char *prefix = (char *)malloc(sizeof(char)*80);
    sprintf(prefix, "%s", noneStr);
    sprintf(instLabel, "%s", noneStr);
    while(ptr->next != (struct Quad *)0){
        ptr = ptr->next;
        switch(ptr->op){
            case mul:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "mul");
                sprintf(p1, "$t%d", getTR(ptr, ptr->dest.TIA));
                sprintf(p2, "$t%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p3, "$t%d", getTemp(ptr, ptr->src2.TIA));        
                CSPush(instLabel, op, p1, p2, p3, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case muli:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "mul");
                sprintf(p1, "$t%d", getTR(ptr, ptr->dest.TIA));
                sprintf(p2, "$t%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p3, "%d", ptr->src2.TIA);
                CSPush(instLabel, op, p1, p2, p3, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case label:{
                scope = getsym(ptr->dest.id)->scope;
                sprintf(prefix, "%s", ptr->dest.id);
                sprintf(instLabel, "%s", ptr->dest.id);
                CSPush(instLabel, "sw", "$ra", noneStr, "0($sp)", noneStr);
                CSPush(noneStr, "add", "$sp", "$sp", "-4", noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case lwi:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "lw");
                sprintf(p1, "$t%d", getTR(ptr, ptr->src1.TIA));
                sprintf(p2, "%s", noneStr);
                sprintf(p3, "%s+%d", ptr->dest.id, ptr->src2.TIA);
                if(getsymWithinScope(ptr->dest.id, scope) != (struct symrec *) 0) CSPush(instLabel, op, p1, p2, p3, prefix);
                else CSPush(instLabel, op, p1, p2, p3, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case li:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "li");
                sprintf(p1, "$t%d", getTR(ptr, ptr->dest.TIA));
                sprintf(p2, "%s", noneStr);
                sprintf(p3, "%d", ptr->src2.TIA);
                CSPush(instLabel, op, p1, p2, p3, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case swi:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "sw");
                sprintf(p1, "$t%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p2, "%s", noneStr);
                sprintf(p3, "%s+%d", ptr->dest.id, ptr->src2.TIA);
                if(getsymWithinScope(ptr->dest.id, scope) != (struct symrec *) 0) CSPush(instLabel, op, p1, p2, p3, prefix);
                else CSPush(instLabel, op, p1, p2, p3, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case jgti:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "bgt");
                sprintf(p1, "$t%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p2, "%d", ptr->src2.TIA);
                sprintf(p3, "l%d", ptr->dest.addr->order);        
                CSPush(instLabel, op, p1, p2, p3, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case jmp:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "j");
                sprintf(p1, "%s", noneStr);
                sprintf(p2, "%s", noneStr);
                sprintf(p3, "l%d", ptr->dest.addr->order);        
                CSPush(instLabel, op, p1, p2, p3, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case write:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "move");
                sprintf(p1, "$a0");
                sprintf(p2, "$t%d", getTemp(ptr, ptr->dest.TIA));
                sprintf(p3, "%s", noneStr);        
                CSPush(instLabel, op, p1, p2, p3, noneStr);       
                CSPush(noneStr, "li", "$v0", "1", noneStr, noneStr);
                CSPush(noneStr, "syscall", noneStr, noneStr, noneStr, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case ret:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                if(strcmp(prefix, "main") == 0){
                    CSPush(instLabel, "li", "$v0", "10", noneStr, noneStr);
                    CSPush(noneStr, "syscall", noneStr, noneStr, noneStr, noneStr);
                    break;
                }
                sprintf(op, "move");
                sprintf(p1, "$v0");
                sprintf(p2, "$t%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p3, "%s", noneStr);        
                CSPush(instLabel, op, p1, p2, p3, noneStr);
                CSPush(noneStr, "add", "$sp", "$sp", "4", noneStr);
                CSPush(noneStr, "lw", "$ra", noneStr, "0($sp)", noneStr);
                CSPush(noneStr, "jr", "$ra", noneStr, noneStr, noneStr);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case param:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                // this is an part that are not very smooth in this part!
                struct Quad* fun = ptr;
                while(fun->op != call) fun = fun->next;
                sprintf(op, "sw");
                sprintf(p1, "$t%d", getTemp(ptr, ptr->src1.TIA));
                sprintf(p2, "%s", noneStr);
                sprintf(p3, "%s", ptr->dest.id);
                CSPush(instLabel, op, p1, p2, p3, fun->dest.addr->dest.id);
                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case call:{
                if(ptr->basicBlockFlag == 1 && strcmp(instLabel, noneStr) == 0) sprintf(instLabel, "l%d", ptr->order);
                sprintf(op, "jal");
                sprintf(p1, "%s", noneStr);
                sprintf(p2, "%s", noneStr);
                sprintf(p3, "%s", ptr->dest.addr->dest.id);        
                CSPush(instLabel, op, p1, p2, p3, noneStr);

                sprintf(instLabel, "%s", noneStr);
                break;
            }
            case end:break;
            default:printf("wrong while CG\n");
        }

    }

    printCS();
}


/*-------------------------------------------------------------------------
Print Code to stdio
-------------------------------------------------------------------------*/

/************************** End Code Generator **************************/