## Lexeme Tokenizer/Parser  
   
To compile on Linux / macOS:  
`gcc -std=c99 -o Analyzer.out Givens.c Parser.c Tokenizer.c Analyzer.c`  
  
Then run: ./Analyzer.out <TokenTest0.txt>  
to run test given test file.  
  
### How it works  
Output will show whether the program file input is valid given an EBNF grammar. It does this by tokenizing the program into an array of lexemes, which is passed to the parser to  determine if valid. A series of passing and failing test programs are avaoilable, but welcome to try your own code file. (may not work)
