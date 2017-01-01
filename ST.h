/***************************************************************************
Symbol Table Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
SYMBOL TABLE RECORD
-------------------------------------------------------------------------*/
struct symrec {
    char *name;          /* name of symbol */
    int offset;          /* data offset */
    char* type; /*fun struct ID int*/
    struct symrec *scope; /*为了struct ID*/
    int width; /*为了struct type*/
    struct symrec *next; /* link field */
    struct Quad* entry; /*为了func*/
};
typedef struct symrec symrec;
/*-------------------------------------------------------------------------
SYMBOL TABLE ENTRY
-------------------------------------------------------------------------*/
struct symrec *identifier;
/*-------------------------------------------------------------------------
SYMBOL TABLE
Implementation: a chain of records.
------------------------------------------------------------------------*/
struct symrec *sym_table = (struct symrec *) 0; /* The pointer to the Symbol Table */
int totalOffset = 0;
/*========================================================================
Operations: Putsym, Getsym
========================================================================*/
struct symrec *getsym(char *sym_name);
void addLevel(){
    struct symrec *ptr;

    ptr = (struct symrec *) malloc(sizeof(struct symrec));
    ptr->name = (char *) 0;
    // ptr->offset = data_location();
    ptr->next = (struct symrec *) sym_table;
    ptr->offset = totalOffset;
    sym_table = ptr;
    totalOffset = 0;
    // return ptr;
}

struct symrec * subLevel(){
    struct symrec *scope = sym_table;
    struct symrec *ptr;
    for (ptr = sym_table; ptr != (struct symrec *)0; ptr = (struct symrec *)ptr->next){
        if (ptr->name == (char *) 0){
            totalOffset = ptr->offset;
            sym_table = ptr->next;
            break;
        }
    }
    return scope;
}

struct symrec *putsym(char *sym_name, char* type, int width, struct symrec * scope, struct Quad* entry) {
    struct symrec *ptr;
    ptr = (struct symrec *) malloc(sizeof(struct symrec));
    ptr->name = (char *) malloc(strlen(sym_name) + 1);
    strcpy(ptr->name, sym_name);
    ptr->type = (char *) malloc(strlen(type) + 1);
    strcpy(ptr->type, type);

    ptr->next = (struct symrec *) sym_table;
    if(strcmp(ptr->type, "int")){
        ptr->offset = totalOffset;
        totalOffset += width;
    } else if(strcmp(ptr->type, "func")){
        ptr->scope = scope;
        ptr->entry = entry;

    } else if(strcmp(ptr->type, "struct")){
        ptr->offset = totalOffset;
        ptr->width = width;
        ptr->scope = scope;
    }
    else{
        struct symrec *typeID = getsym(type);
        if(typeID == 0){
//            errors++;
            printf("%s is not defined\n", type);
            free(ptr);
            return 0;
        } else{
            ptr->offset = totalOffset;
            totalOffset += typeID->width;
        }
    }
    sym_table = ptr;
    return ptr;
}

struct symrec *getsym(char *sym_name) {
    struct symrec *ptr;
    for (ptr = sym_table; ptr != (struct symrec *)0; ptr = (struct symrec *)ptr->next)
        if(ptr->name != 0)
            if (strcmp(ptr->name, sym_name) == 0)
                return ptr;
    return 0;
}

struct symrec *getsymInScope(char *sym_name) {
    struct symrec *ptr;
    for (ptr = sym_table; ptr != (struct symrec *)0 && ptr->name != 0; ptr = (struct symrec *)ptr->next)
        if (strcmp(ptr->name, sym_name) == 0)
            return ptr;
    return 0;
}

struct symrec *getsymWithScope(char *sym_name, struct symrec * symPoint) {
    struct symrec *ptr;
    for (ptr = symPoint; ptr != (struct symrec *)0; ptr = (struct symrec *)ptr->next)
        if(ptr->name != 0)
            if (strcmp(ptr->name, sym_name) == 0)
                return ptr;
    return 0;
}

struct symrec *getsymWithinScope(char *sym_name, struct symrec * symPoint) {
    struct symrec *ptr;
    for (ptr = symPoint; ptr != (struct symrec *)0 && ptr->name != 0; ptr = (struct symrec *)ptr->next)
        if (strcmp(ptr->name, sym_name) == 0)
            return ptr;
    return 0;
}
/************************** End Symbol Table **************************/