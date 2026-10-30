#include "scanner.hpp"
#include <iostream>

int scanner::udef = -1;

bool scanner::id(){
    int actual = 0, prior = udef;
    int c;

    while (actual != udef){
        prior = actual;
        c = read();

        switch(actual){
          
            case 0:
            	//actual = (c=='_'?1:(isapha(c)) ?2:udef; ternario
                if(c == '_') actual = 1;
                else if(isalpha(c)) actual = 2;
                else actual = udef;
                break;

            
            case 1:
            	//	actual=(isdigit(c)or c=='_')?1:(isalpha(c))?2:udef ternario
                if(isdigit(c) || c == '_') actual = 1;
                else if(isalpha(c)) actual = 2;
                else actual = udef;
                break;

            // error
            case 2:
            	//	actual = (isalnum(c)or c=='_')2:udef; meteodo ternario
                if(isalnum(c) || c == '_') actual = 2;
                else actual = udef;
                break;
        }
    }

    if(prior == 2){
        
		fallback();
        success();
        return true;
    }

    failure();
    return false;
}


scanner::token scanner::num(){
    int actual = 0, prior = udef;
    int c;

    while (actual != udef){
        prior = actual;
        c = read();

        switch(actual){
            case 0:
                actual = (c == '0') ? 2 : isdigit(c) ? 1 : udef;
                break;

            case 1:  // decimal
                if(!isdigit(c)) actual = udef;
                break;

            case 2:  // octal
                actual = ('0' <= c && c <= '7') ? 3 : udef;
                break;

            case 3:  // octal
                actual =
                    ('0' <= c && c <= '7') ? 3 :
                    (c == '8' || c == '9') ? 4 : udef;
                break;

            case 4:  
                actual = udef;
                break;
        }
    }

    // estados de aceptacion
    if(prior == 1 || prior == 2 || prior == 3){
       fallback();
        success();
        return (prior == 3) ? _oct : _int;
    }

    failure();
    return _err;
}


void scanner::wsp(){
    while(isspace(file.peek())){
        file.get();
    }
    success();
}


bool scanner::eof(){
    return file.eof();//es fin de archivo
}


scanner::token scanner::next(){
    token t;

    wsp();

	if(eof()) return _eof;
    if(id()) return _id;
    if((t = num()) != _err) return t;

	if(file.get() == EOF) return _eof;
    return _err;
}
