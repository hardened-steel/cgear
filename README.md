# CGear
Compiler object-oriented programming language. Written in C++ with boost::spirit and llvm.

This is an attempt to create a programming language compiler. It is based on LLVM framework, and use boost library.
The parser is implemented using boost::spirit library, specifically, spirit::lex - for lexer analysis and spirit::qi for parser.
LLVM used as backend code generator.
