%option noyywrap
%option yylineno

%{
#include "scanner.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>

extern ifstream* archivo_actual;
scanner* scanner_actual = nullptr;

#define YY_INPUT(buf, result, max_size) \
    { \
        archivo_actual->read(buf, max_size); \
        result = archivo_actual->gcount(); \
    }
%}

%x ERROR

%%
"tellme"|"all_sat"|"true"|"false"|"and"|"or"|"not"|"if"|"then"  { scanner_actual->lexema = yytext; return scanner::_reservada; }

[a-zA-Z][a-zA-Z0-9]*_?[a-zA-Z0-9]+'*     { scanner_actual->lexema = yytext; return scanner::_id; }
[a-zA-Z][a-zA-Z0-9]*'*                  { scanner_actual->lexema = yytext; return scanner::_id; }

0[0-7]+                                 { scanner_actual->lexema = yytext; return scanner::_oct; }
0                                       { scanner_actual->lexema = yytext; return scanner::_oct; }
0[xX][0-9a-fA-F]+                       { scanner_actual->lexema = yytext; return scanner::_hexa; }
[1-9][0-9]*\.[0-9]+                     { scanner_actual->lexema = yytext; return scanner::_real; }
0\.[0-9]+                               { scanner_actual->lexema = yytext; return scanner::_real; }
[1-9][0-9]*                             { scanner_actual->lexema = yytext; return scanner::_int; }

"("                                     { return scanner::_lpar; }
")"                                     { return scanner::_rpar; }
";"                                     { return scanner::_scolon; }
"?"                                     { return scanner::_selector; }
":"                                     { return scanner::_def; }
"&"                                     { return scanner::_and; }
"|"                                     { return scanner::_or; }
"!"                                     { return scanner::_not; }
"->"                                    { return scanner::_impl; }

[0-9][a-zA-Z_]+                         { return scanner::_err; }

[ \t\r]+                                { }
\n                                      { /* yylineno lo maneja solo */ }

"#"[^\n]*                               { }

.                                       { return scanner::_err; }
<<EOF>>                                 { 
                                            scanner_actual->lineas = yylineno - 1; 
                                            return scanner::_eof; 
                                        }
%%

scanner::scanner(const string& fname) : lineas(1), archivo(fname.c_str()) {
    scanner_actual = this;
}

scanner::~scanner() {
    archivo.close();
    scanner_actual = nullptr;
}

scanner::token scanner::next() {
    return (scanner::token) yylex();
}