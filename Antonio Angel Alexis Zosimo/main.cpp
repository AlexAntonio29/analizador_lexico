#include <iostream>
#include <iomanip> // Para setw
#include "scanner.hpp"
#include <fstream>

using namespace std;

ifstream* archivo_actual = nullptr;

int main(int argc, const char * argv[]){
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;

    scanner s(nombreArchivo);
    
    archivo_actual = new ifstream(nombreArchivo.c_str());

    scanner::token t;

    do{
        t = s.next();

        switch(t){
            case scanner::_id:
                cout << left << setw(12) << "id" << s.getLexema() << "\n";
                break;
            case scanner::_int:
                cout << left << setw(12) << "integer" << s.getLexema() << "\n";
                break;
            case scanner::_oct:
                cout << left << setw(12) << "octal" << s.getLexema() << "\n";
                break;
            case scanner::_hexa:
                cout << left << setw(12) << "hexa" << s.getLexema() << "\n";
                break;
            case scanner::_real:
                cout << left << setw(12) << "real" << s.getLexema() << "\n";
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

    delete archivo_actual;
    return 0;
}