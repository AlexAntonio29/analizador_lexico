#include <iostream>
#include "scanner.hpp"

using namespace std;

int main(int argc, const char * argv[]){
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;

    scanner s(nombreArchivo);
    scanner::token t;

    do{
        t = s.next();

        switch(t){
            case scanner::_id:
                cout << "id\t\t" << s.getLexema() << "\n";
                break;
            case scanner::_int:
                cout << "integer\t\t" << s.getLexema() << "\n";
                break;
            case scanner::_oct:
                cout << "octal\t\t" << s.getLexema() << "\n";
                break;
            case scanner::_hexa:
                cout << "hexa\t\t" << s.getLexema() << "\n";
                break;
            case scanner::_real:
                cout << "real\t\t" << s.getLexema() << "\n";
                break;
            case scanner::_reservada:
                cout << s.getLexema() << "\n";
                break;
            case scanner::_lpar:
                cout << "lpar\n";
                break;
            case scanner::_rpar:
                cout << "rpar\n";
                break;
            case scanner::_scolon:
                cout << "scolon\n";
                break;
            case scanner::_selector:
                cout << "selector\n";
                break;
            case scanner::_def:
                cout << "def\n";
                break;
            case scanner::_and:
                cout << "and\n";
                break;
            case scanner::_or:
                cout << "or\n";
                break;
            case scanner::_not:
                cout << "not\n";
                break;
            case scanner::_impl:
                cout << "impl\n";
                break;
            case scanner::_eof:
                cout << "eof\n\n";
                cout << "Fin del analisis\n";
                cout << "se leyeron " << s.getLineas() << " lineas\n";
                break;
            case scanner::_err:
                cout << "Error en la linea " << s.getLineas() << "\n";
                break;
            default:
                cout << "WTF\n";
        }

    }while(t != scanner::_eof && t != scanner::_err);

    return 0;
}