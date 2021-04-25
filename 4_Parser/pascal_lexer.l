%option yylineno
%{
#include "y.tab.h"

int yyval;
int install_id(char * yytext);
int install_num(char * yytext);
int install_real(char * yytext);

%}


%%
"\n"                        {/*increase line number*/yylineno++;}
[ \t]+                          {/*no action and no return*/;}
"PROGRAM"                   {yylval.IDstring=strdup(yytext);return PROGRAMtoken;}
"VAR"                       {yylval.IDstring=strdup(yytext);return VARtoken;}
"BEGIN"                     {yylval.IDstring=strdup(yytext);return BEGINtoken;}
"END."                      {yylval.IDstring=strdup(yytext);return ENDDOTtoken;}
"END"                       {yylval.IDstring=strdup(yytext);return ENDtoken;}
"INTEGER"  		              {yylval.IDstring=strdup(yytext);return INTEGERtoken;}
"FOR"                       {yylval.IDstring=strdup(yytext);return FORtoken;}
"READ"                      {yylval.IDstring=strdup(yytext);return READtoken;}
"WRITE"                     {yylval.IDstring=strdup(yytext);return WRITEtoken;}
"TO"                        {yylval.IDstring=strdup(yytext);return TOtoken;}
"DO"                        {yylval.IDstring=strdup(yytext);return DOtoken;}
";"                         {yylval.IDstring=strdup(yytext);return SEMICOLONtoken;}
":"                         {yylval.IDstring=strdup(yytext);return COLONtoken;}
","                         {yylval.IDstring=strdup(yytext);return COMMAtoken;}
":="                        {yylval.IDstring=strdup(yytext);return COLEQUALtoken;}
"+"                         {yylval.IDstring=strdup(yytext);return PLUStoken;}
"-"                         {yylval.IDstring=strdup(yytext);return MINUStoken;}
"*"                         {yylval.IDstring=strdup(yytext);return ASTERISKtoken;}
"DIV"                       {yylval.IDstring=strdup(yytext);return DIVtoken;}
"("                         {yylval.IDstring=strdup(yytext);return LEFTPARENTHESIStoken;}
")"                         {yylval.IDstring=strdup(yytext);return RIGHTPARENTHESIStoken;}
"REAL"                      {yylval.IDstring = strdup(yytext);return REALDectoken;}
[A-Za-z][A-Za-z0-9]*        {yylval.IDstring=strdup(yytext);yyval = install_id(yytext);return IDtoken;}
[0-9]+"."[0-9]+             {yylval.IDstring = strdup(yytext);yyval = install_real(yytext); return REALtoken;}
[0-9]+                      {yylval.IDstring=strdup(yytext);yyval = install_num(yytext);return INTtoken;}
%%
int yywrap(void)
{
    return 1;
}
