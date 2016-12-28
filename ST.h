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
  // int offset;          /* data offset */
  char* type;
  // int level;
  struct symrec *next; /* link field */
};
// typedef struct symrec symrec;
/*-------------------------------------------------------------------------
SYMBOL TABLE ENTRY
-------------------------------------------------------------------------*/
struct symrec *identifier;
/*-------------------------------------------------------------------------
SYMBOL TABLE
Implementation: a chain of records.
------------------------------------------------------------------------*/
struct symrec *sym_table = (struct symrec *) 0; /* The pointer to the Symbol Table */
/*========================================================================
Operations: Putsym, Getsym
========================================================================*/
void addLevel(){
  struct symrec *ptr;
  ptr = (struct symrec *) malloc(sizeof(struct symrec));
  ptr->name = (char *) 0;
  // ptr->offset = data_location();
  ptr->next = (struct symrec *) sym_table;
  sym_table = ptr;
  // return ptr;
}

struct symrec * subLevel(){
  struct symrec *scope = sym_table;
  struct symrec *ptr;
  for (ptr = sym_table; ptr != (struct symrec *)0; ptr = (struct symrec *)ptr->next)
    if (ptr->name == (char *) 0)
      sym_table = ptr->next;
      break;
  return scope;
}

struct symrec *putsym(char *sym_name, char* type) {
  struct symrec *ptr;
  ptr = (struct symrec *) malloc(sizeof(struct symrec));
  ptr->name = (char *) malloc(strlen(sym_name) + 1);
  strcpy(ptr->name, sym_name);
  ptr->type = (char *) malloc(strlen(type) + 1);
  strcpy(ptr->type, type);
  // ptr->offset = data_location();
  ptr->next = (struct symrec *) sym_table;
  sym_table = ptr;
  return ptr;
}

struct symrec *getsym(char *sym_name) {
  struct symrec *ptr;
  for (ptr = sym_table; ptr != (struct symrec *)0; ptr = (struct symrec *)ptr->next)
    if (strcmp(ptr->name, sym_name) == 0)
      return ptr;
  return 0;
}
/************************** End Symbol Table **************************/