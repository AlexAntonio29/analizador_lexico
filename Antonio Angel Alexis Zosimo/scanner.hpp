#ifndef scanner_hpp
#define scanner_hpp

#include <fstream>
#include <string>
#include <cctype>
#include <ios>

using namespace std;

class scanner{

    static int udef;

public:
    typedef enum { _id, _int, _oct, _eof, _err } token;

private:
    ifstream file;
    long pos;

    int read(){ //char
        return file.get();
    }

    void failure(){
    
        file.seekg(pos);
    }

    void success(){
    	long p=file.tellg();
    	if(p>=0)
        pos =p;
    }

    void fallback(){
    	
        file.seekg(-1, ios::cur);
    }

    bool id();
    token num();

    void wsp();
    bool eof();

public:
    scanner(const string& fname) : file(fname.c_str()), pos(0) {}

    ~scanner(){
        file.close();
    }

    token next();
};

#endif
