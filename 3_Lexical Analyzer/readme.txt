command to run the lex file :: lex 180101054_Assign03.l
C program will be generated i.e lex.yy.c
Command to compile c program :: g++ lex.yy.c
Command to run               :: ./a.out

input should be kept in file input.txt
output will be stored in output.txt file



I have used open hashing method
open hashing  is a collision avoidence method which uses array of linked list to resolve the collision.

It is also known as the separate chaining method (each linked list is considered as a chain).

so to specity the token there are two numbers.First is the index of the chain in which the element is present and the second is the index of element in that chain.
