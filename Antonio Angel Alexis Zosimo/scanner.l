%option c++
%option yyclass="scanner"
%option noyywrap

%{
#include <iostream>
#include <cstring>
#include <cstdlib>
%}

%x ERROR

%%
"tellme"|"all_sat"|"true"|"false"|"and"|"or"|"not"|"if"|"then"  { lexema = yytext; return _reservada; }

[a-zA-Z][a-zA-Z0-9]*_?[a-zA-Z0-9]+'*     { lexema = yytext; return _id; }
[a-zA-Z][a-zA-Z0-9]*'*                  { lexema = yytext; return _id; }

0[0-7]+                                 { lexema = yytext; return _oct; }
0[xX][0-9a-fA-F]+                       { lexema = yytext; return _hexa; }
[1-9][0-9]*\.[0-9]+                     { lexema = yytext; return _real; }
0\.[0-9]+                               { lexema = yytext; return _real; }
[1-9][0-9]*                             { lexema = yytext; return _int; }

"("                                     { return _lpar; }
")"                                     { return _rpar; }
";"                                     { return _scolon; }
"?"                                     { return _selector; }
":"                                     { return _def; }
"&"                                     { return _and; }
"|"                                     { return _or; }
"!"                                     { return _not; }
"->"                                    { return _impl; }

[0-9][a-zA-Z_]+                         { return _err; }

[ \t\r]+                                { }
\n                                      { lineas++; }

"#"[^\n]*                               { }

.                                       { return _err; }
<<EOF>>                                 { return _eof; }
%%

#include "scanner.hpp"

scanner::scanner(const string& fname) : lineas(1) {
    archivo.open(fname.c_str());
    if (archivo.is_open()) {
        switch_streams(&archivo, &cout);
    }
}

scanner::~scanner() {
    if (archivo.is_open()) archivo.close();
}

scanner::token scanner::next() {
    return (scanner::token) yylex();
}