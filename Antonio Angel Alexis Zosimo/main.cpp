#include <iostream>
#include "scanner.hpp"

using namespace std;

int main(int argc, const char * argv[]){
    scanner s("prueba.txt");

	//	if(s.next()==scanner::_id) cout<<"Soy feliz";
	//	else cout << "vete a gastro";
    scanner::token t;

    do{
        t = s.next();

        switch(t){
            case scanner::_id:
                cout << "identificador\n";
                break;

            case scanner::_int:
                cout << "Entero\n";
                break;

            case scanner::_oct:
                cout << "Octal\n";
                break;

            case scanner::_eof:
                cout << "End of file\n";
                break;

            default:
                cout << "WTF\n";
        }

    }while(t != scanner::_eof && t != scanner::_err);

    cout << "Bye\n";

    return 0;
}
