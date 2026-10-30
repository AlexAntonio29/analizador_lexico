#ifndef scanner_hpp
#define scanner_hpp

#include <fstream>
#include <string>
#include <cctype>
#include <ios>

using namespace std;

extern int yylineno;

class scanner {

    static int udef;

public:
    typedef enum { 
        _id, _int, _oct, _hexa, _real, 
        _reservada, 
        _lpar, _rpar, _scolon, _selector, _def, 
        _and, _or, _not, _impl, 
        _eof, _err 
    } token;

private:
    int lineas;
    string lexema;
    ifstream archivo;

public:
    scanner(const string& fname);
    ~scanner();

    token next();
    string getLexema() const { return lexema; }
    int getLineas() const { return lineas; }
    
    friend int yylex();
};

#endif