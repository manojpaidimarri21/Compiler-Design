%{
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
extern int yylineno;
struct hash_node
{
    char token_string[20];
    int tokenid;
    int typee;   //0 for real 1 for INTEGER
    struct hash_node * next_hash_node;
};

struct node {
    char * str;
    struct node * next_node;
};

struct node * newList(){
    struct node * newNode = malloc(sizeof(struct node));
    newNode->str = "dummy";
    newNode->next_node=0;
    return newNode;
}

void insert_right(struct node * headNode,char * str){
  struct node *newNode = malloc(sizeof(struct node));
  newNode->str = str;
  newNode->next_node=0;
  struct node * iterator=headNode;
  while(iterator->next_node)
  {
    iterator=iterator->next_node;
  }
  iterator->next_node=newNode;
}


int called=0;
struct hash_node * list[10];

int yylex(void);
int yyerror(char * msg);

unsigned long djb2(const char *s);
int search_symtab(char * token,int id);
int insert_symtab(char * token,int id);
void iDTypeSetter(struct node * , char * );
int typecheckerInHash(char * );
%}

%union{
  char * IDstring;
    struct node * head;
    int id_val;

}

%start prog
%token <IDstring> PROGRAMtoken VARtoken BEGINtoken ENDtoken ENDDOTtoken INTEGERtoken REALDectoken FORtoken READtoken WRITEtoken TOtoken DOtoken SEMICOLONtoken COLONtoken REALtoken
%token <IDstring> COMMAtoken COLEQUALtoken PLUStoken MINUStoken ASTERISKtoken DIVtoken LEFTPARENTHESIStoken RIGHTPARENTHESIStoken  INTtoken
%token <IDstring> IDtoken


%type <IDstring> prog progName decList dec idType   stmt stmtList assign exp term factor read write index_exp for body
%type <IDstring> id beg var enddot do
%type <head> idList

%%

prog        : PROGRAMtoken progName var decList beg stmtList enddot { printf("Program %s end is reached\n",$2);  }
progName    : id { printf("Progname is %s \n",$$);}
            ;
decList     : dec
            | decList SEMICOLONtoken dec
            | error dec
            {
                printf("In Line Number %d : Syntax Error : Expected ' ; ' \n",yylineno-4);
                yyerror("");yyerrok;
            }
            ;
dec         : idList COLONtoken idType { iDTypeSetter($1, $3) ;}
            | error idType
            {
                printf("In Line Number %d : Syntax Error : Expected ' : ' \n",yylineno-3);
                yyerror("");yyerrok;
            }
            ;
idType      : INTEGERtoken
            | REALDectoken
            ;
idList      : id { insert_right($$ = newList() , $1); }
            | idList COMMAtoken id { insert_right($$ = $1, $3); }
            ;
stmtList    : stmt
            | stmtList SEMICOLONtoken stmt
            |error stmt
            {
                printf("In Line Number %d : Syntax Error : Expected ' ; ' \n",yylineno);
                yyerror("");yyerrok;
            }
            ;
stmt        : assign
            | read
            | write
            | for
            ;
assign      : id COLEQUALtoken exp {

                if( typecheckerInHash($1)!= typecheckerInHash($3))
                {
                    printf("Semantic error : type mismatch between %s and %s\n",$1,$3);
                }
             }
            | error exp
            {
                printf("In Line Number %d : Syntax Error : Expected ' := ' \n",yylineno-13);

                yyerror("");yyerrok;
            }
            ;
exp         : term
            | exp PLUStoken term {
                            if( typecheckerInHash($1)!= typecheckerInHash($3))
                            {
                                printf("Semantic error : type mismatch between %s and %s\n",$1,$3);
                            }
                         }
            | exp MINUStoken term {
                            if( typecheckerInHash($1)!= typecheckerInHash($3))
                            {
                                printf(" Semantic error : type mismatch  between %s and %s\n",$1,$3);
                            }
                         }
            ;
term        : factor
            | term ASTERISKtoken factor{
                            if( typecheckerInHash($1)!= typecheckerInHash($3))
                            {
                                printf("Semantic error : type mismatch between %s and %s\n",$1,$3);
                            }
                         }
            | term DIVtoken factor{
                            if( typecheckerInHash($1)!= typecheckerInHash($3))
                            {
                                printf("Semantic error : type mismatch between %s and %s\n",$1,$3);
                            }
                         }
            ;
factor      : id
            | INTtoken
            | REALtoken
            | LEFTPARENTHESIStoken exp RIGHTPARENTHESIStoken
            ;
read        : READtoken LEFTPARENTHESIStoken idList RIGHTPARENTHESIStoken
            ;
write       : WRITEtoken LEFTPARENTHESIStoken idList RIGHTPARENTHESIStoken
            ;
for         : FORtoken index_exp DOtoken body
            ;
index_exp   : id COLEQUALtoken exp TOtoken exp
            | error do
            {
                printf("In Line Number %d : Syntax Error : Expected correct index expression \n",yylineno);

                yyerror("");yyerrok;
            }
            ;
body        : stmt
            | beg stmtList ENDtoken
            ;
id          : IDtoken ;

var         :    VARtoken    ;
beg         :    BEGINtoken  ;
enddot      :    ENDDOTtoken  ;
do          :    DOtoken     ;


%%

unsigned long djb2(const char *a)
  {
      unsigned const char *str;
      str=(unsigned const char *) a;
      unsigned long h = 5381;
      int c;

      while (c = *str++)
          h = ((h << 5) + h) + c;
      h=h%10;
      return h;
  }

  int search_symtab(char * token,int id)
  {
      int key = djb2(token) % 10;
      struct hash_node *iterator = list[key];
      int z=-1;
      while(iterator)
      {   z++;
          if((strcmp(iterator->token_string, token)==0) && iterator->tokenid == id)
              return z;
          iterator = iterator->next_hash_node;

      }
      return -1;
  }
  int typecheckerInHash(char * token)
  {
        int key = djb2(token) % 10;
        struct hash_node *iterator = list[key];
        int z=-1;
        while(iterator)
        {   z++;
            if((strcmp(iterator->token_string, token)==0))
            {
                return  iterator->typee;
            }
            iterator = iterator->next_hash_node;

        }
        return 0;
  }
  void typeSetterInHash(char * token,char * idType)
  {
        int key = djb2(token) % 10;
        struct hash_node *iterator = list[key];
        int z=-1;
        while(iterator)
        {   z++;
            if((strcmp(iterator->token_string, token)==0))
            {
            if(strcmp(idType,"INTEGER")==0)
               iterator->typee=1;
            else
              iterator->typee=0;
            }
            iterator = iterator->next_hash_node;

        }
  }
int insert_symtab(char * token,int id)
{
    int p=search_symtab(token,id);
    if(p!=-1) return p;
    else
    {

        struct hash_node *newhash_node =  (struct hash_node *)malloc(sizeof(struct hash_node));
        strcpy(newhash_node->token_string,token);
        newhash_node->tokenid=id;
        newhash_node->typee=1;
        newhash_node->next_hash_node = NULL;
         int k=0;
        //calculate hash key
        int key = djb2(token) % 10;
        //check if list[key] is empty
        if(list[key] == NULL)
          {
            list[key] = newhash_node;
            k=0;
          }
        //else collision
        else
        {
            //add the hash_node at the end of list[key].
            struct hash_node *iterator = list[key];
            while(iterator->next_hash_node)
            {
                iterator = iterator->next_hash_node;
                k++;
            }
            k++;
            iterator->next_hash_node = newhash_node;
        }
        return k;
    }
}

int install_id(char * yytext)
{
    return insert_symtab(yytext,IDtoken);
}
// inserts number into the symbol table and returns index in the symbol table.
int install_num(char * yytext)
{
    return insert_symtab(yytext,INTtoken);
}
int install_real(char * yytext)
{
    return insert_symtab(yytext,REALtoken);
}
void iDTypeSetter(struct node * list_head,char *idType)
{

      struct node * iterator = list_head;
      while(iterator)
      {
          typeSetterInHash(iterator->str,idType);
          iterator=iterator->next_node;
      }


}

int main(int argc, char **argv)
{
    extern FILE *yyin;
    yyin = fopen(argv[1],"r");
    yyparse();
    if(called==0)
    	printf(" Successfully Parsed\n");

      printf("------------SYMTAB------------------\n");
       for(int i = 0; i < 10; i++)
       {
           struct hash_node *temp = list[i];
         printf("list[%d]-->",i);
           while(temp)
           {
            printf("(%s ::",temp->token_string);
            printf(" %d :: ",temp->typee);

             printf(" %d )---> ",temp->tokenid);
               temp = temp->next_hash_node;

           }
         printf("NULL\n");
       }
    return 0;
}

int yyerror(char *msg)
{
	called = 1;
	return 0;
}
