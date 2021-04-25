Commands to compile the lex and yacc files and generate all output files :
chmod +x compile_files.sh
./compile_files.sh

To run the specific input file and generate its y.output use commands ::

./a.out input.txt > output.txt
./a.out syntaxError1.txt > outputsyntaxError1.txt
./a.out syntaxError2.txt > outputsyntaxError2.txt
./a.out syntaxError3.txt > outputsyntaxError3.txt
./a.out semanticError1.txt > outputsemanticError1.txt
./a.out semanticError2.txt > outputsemanticError2.txt
./a.out semanticError3.txt > outputsemanticError3.txt
