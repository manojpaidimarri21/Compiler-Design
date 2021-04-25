%{
#include<stdio.h>
#include<stdlib.h>
#include "token.h"


int yyval;
int install_id();
int install_num();

struct node
{
    char str[20];
    int tokenid;
    struct node *next;
};

struct node * list[10];
unsigned long djb2(const char *s);
int insert_symtab(char * token,int id);


%}

letter  [a-zA-Z]
digit   [0-9]
id      { letter }( { letter } | { digit } )*
number  [1-9]({ digit }+)


%%
"\n"                        {/*increase line number*/yylineno++;}
[ \t]+                          {/*no action and no return*/;}
"PROGRAM"                   {return PROGRAMnumber;}
"VAR"                       {return VARnumber;}
"BEGIN"                     {return BEGINnumber;}
"END."                      {return ENDDOTnumber;}
"END"                       {return ENDnumber;}
"INTEGER"  		    {return INTEGERnumber;}
"FOR"                       {return FORnumber;}
"READ"                      {return READnumber;}
"WRITE"                     {return WRITEnumber;}
"TO"                        {return TOnumber;}
"DO"                        {return DOnumber;}
";"                         {return SEMICOLONnumber;}
":"                         {return COLONnumber;}
","                         {return COMMAnumber;}
":="                        {return COLEQUALnumber;}
"+"                         {return PLUSnumber;}
"-"                         {return MINUSnumber;}
"*"                         {return ASTERISKnumber;}
"DIV"                       {return DIVnumber;}
"("                         {return LEFTPARENTHESISnumber;}
")"                         {return RIGHTPARENTHESISnumber;}
[A-Za-z][A-Za-z0-9]*  {yyval = install_id();return 22;}
[0-9]+      {yyval = install_num();return 23;}
%%

int yywrap(void)
{
    return 1;
}

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
      struct node *temp = list[key];
      int z=-1;
      while(temp)
      {   z++;
          if((strcmp(temp->str, token)==0) && temp->tokenid == id)
              return z;
          temp = temp->next;

      }
      return -1;
  }
int insert_symtab(char * token,int id)
{
    int p=search_symtab(token,id);
    if(p!=-1) return p;
    else
    {

        struct node *newNode =  (struct node *)malloc(sizeof(struct node));
        strcpy(newNode->str,token);
        newNode->tokenid=id;
        newNode->next = NULL;
         int k=0;
        //calculate hash key
        int key = djb2(token) % 10;
        //check if list[key] is empty
        if(list[key] == NULL)
          {
            list[key] = newNode;
            k=0;
          }
        //else collision
        else
        {
            //add the node at the end of list[key].
            struct node *temp = list[key];
            while(temp->next)
            {
                temp = temp->next;
                k++;
            }
            k++;
            temp->next = newNode;
        }
        return k;
    }
}

int install_id()
{
    return insert_symtab(yytext,22);
}

int install_num()
{
    return insert_symtab(yytext,23);
}




int main(void)
{
    int token_number;
      FILE *fp;
      fp = fopen("output.txt", "w+");
    for(int i = 0; i < 10; i++)
        list[i] = NULL;
    yyin = fopen("input.txt","r");
    token_number= yylex();
    int present_line_number = 0;
    fprintf(fp,"Line\tToken type\t\tToken specifier\t\n");
    while (token_number!=0)
    {
        if(present_line_number !=yylineno)
        {
            fprintf(fp,"%d",yylineno);
            present_line_number = yylineno;
        }
        if(token_number==22||token_number==23)
        {
            fprintf(fp,"\t%d\t\t%s\t\t%lu,%d\n",token_number,yytext,djb2(yytext),yyval);
        }else{
            fprintf(fp,"\t%d\n",token_number);
        }
        token_number =yylex();
    }

    fprintf(fp,"------------SYMTAB------------------\n");
     for(int i = 0; i < 10; i++)
     {
         struct node *temp = list[i];
         fprintf(fp,"list[%d]-->",i);
         while(temp)
         {
            fprintf(fp,"(%s ::",temp->str);
             fprintf(fp," %d )---> ",temp->tokenid);
             temp = temp->next;

         }
         fprintf(fp,"NULL\n");
     }
     fclose(fp);
    return 0;
}
