/***************************************************************************
regAllocation code Module
***************************************************************************/
/*=========================================================================
DECLARATIODS
=========================================================================*/
/*-------------------------------------------------------------------------
regAllocation code RECORD
-------------------------------------------------------------------------*/
struct regStack {
    int temp;
    struct regStack* next; 
};


struct RegType{
    int flag;
    int temp;
};
/*-------------------------------------------------------------------------
regAllocation code ENTRY
-------------------------------------------------------------------------*/
struct regStack* RStop = (struct regStack*) 0;
struct RegType tempReg[10]; 
/*-------------------------------------------------------------------------
regAllocation code
Implementation: a chain of records.
------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
initialization
------------------------------------------------------------------------*/
/*========================================================================
OperatioDS: push, pop, isEmpty.
========================================================================*/
void initTR(){
    int i;
    for(i=0;i<10;i++){
        tempReg[i].flag = 0;
    }
}

void RSPush(int temp){
    struct regStack* newTop = (struct regStack*) malloc(sizeof(struct regStack));
    newTop->temp = temp;
    newTop->next = RStop;
    RStop = newTop;
}



struct regStack* findTempInStack(int temp){
    struct regStack* ptr=RStop;
    while(ptr != (struct regStack*) 0){
        if(ptr->temp == temp){
            return ptr;
        }
        ptr = ptr->next;
    }
    return 0;
}

int findTemp(int temp){
    int i;
    for(i=0;i<10;i++){
        if(tempReg[i].temp == temp){
            return i;
        }
    }
    return 10;
}

int GC(struct Quad * ptr){
    int flag[10]={0};
    int posi = 0;
    while(ptr->basicBlockFlag != 1 && ptr != 0){
        posi += 1;
        if(ptr->op == mul){
            int regPosi;
            regPosi = findTemp(ptr->src1.TIA);
            if(regPosi < 10 && flag[regPosi] == 0) flag[regPosi] = posi;
            regPosi = findTemp(ptr->src2.TIA);
            if(regPosi < 10 && flag[regPosi] == 0) flag[regPosi] = posi;
        }
        else if(ptr->op == muli || ptr->op == ret || ptr->op == swi || ptr->op == jgti ){
            int regPosi;
            regPosi = findTemp(ptr->src1.TIA);
            if(regPosi < 10 && flag[regPosi] == 0) flag[regPosi] = posi;
        }
        else if(ptr->op == write){
            int regPosi;
            regPosi = findTemp(ptr->dest.TIA);
            if(regPosi < 10 && flag[regPosi] == 0) flag[regPosi] = posi;
        }
        ptr = ptr->next;
    }
    int i;
    int result = 0;
    int max = 0;
    int maxReg = -1;
    for(i=0;i<10;i++){
        if(flag[i]==0){
            tempReg[i].flag = 0;
            result++;
        }
        else{
            if(flag[i]>max){
                max = flag[i];
                maxReg = i;
            }
        }
    }
    if(result != 0){
        return 10;
    }
    else{
        return maxReg;
    }
}

int getTR(struct Quad * ptr, int temp){
    int i;
    for(i=0;i<10;i++){
        if(tempReg[i].flag == 0){
            tempReg[i].flag = 1;
            tempReg[i].temp = temp;
            return i;
        }
    }
    int maxReg = GC(ptr);
    if(maxReg == 10){
        for(i=0;i<10;i++){
            if(tempReg[i].flag == 0){
                tempReg[i].flag = 1;
                tempReg[i].temp = temp;
                return i;
            }
        }
    }
    else{
        // push maxReg
        RSPush(tempReg[maxReg].temp);
        tempReg[maxReg].flag = 1;
        tempReg[maxReg].temp = temp;
        return maxReg;
    }
}

int getTemp(struct Quad * ptr, int temp){
    int regPosi = findTemp(temp);
    if(regPosi < 10) return regPosi;
    struct regStack* reg = findTempInStack(temp);
    struct regStack* tempRS;
    if(reg != (struct regStack*) 0){
        while(RStop != reg->next){
            tempRS = RStop;
            RStop = RStop->next;
            regPosi = getTR(ptr, tempRS->temp);
            //pop regPosi
            tempReg[regPosi].flag = 1;
            tempReg[regPosi].temp = tempRS->temp;
            free(tempRS);
        }
    }
    else{
        printf("wrong while do the reg allocation!\n");
    }
}


/************************** End regAllocation code **************************/