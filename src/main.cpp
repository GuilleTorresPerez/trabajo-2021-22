/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Pablo Teres y Guillermo Torres  
 * Ultima revisión: ¡¡¡!!!
 * Resumen: ¡¡¡!!!
 * Nota: El código de este programa está repartido en varios módulos.
 *       Para compilarlo, hay que ejecutar el comando
 *           make all
 *       o, en Windows,
 *           mingw32-make all
 *       o ejecutar la tarea "Compilar «electricidad»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/electricidad
 *       o, en Windows,
 *           bin\electricidad.exe
 *       o ejecutar la tarea "Ejecutar «electricidad»" de VSC.
\******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
#include "vector-gastos.hpp"
#include "tarifas-comerciales.hpp"

using namespace std;


/*
 * Pre:  «f» es «cout» o un flujo de la clase «ofstream» asociado con un fichero
 *       externo abierto para escritura. Las «numRegs» primeras componentes
 *       del vector «regDiarios» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: Ha escrito en el flujo «f» el informe sobre consumo eléctrico indicado
 *       en el enunciado de este trabajo.
 */


void escribirInforme(ostream& f,
                     const GastoDiario regDiarios[], const unsigned numRegs,
                     const string nombreCliente, 
                     const unsigned mesInicial, const unsigned mesFinal) {
}


void pedirInformacion (char usuario, unsigned mesInicial, unsigned mesFinal) {
    cout << "Escriba el nombre del usuario: ";
    cin >> usuario;

    do {
        cout << endl << "Escriba el mes inicial y el final: ";
        cin >> mesInicial >> mesFinal;
        
        if (mesInicial < 1 || mesInicial > 12) {
            cout << "El mes inicial tiene que estar entre 1 y 11." << endl;
        }
        if (mesFinal < 1 || mesInicial > 12) {
            cout << "El mes final tiene que estar entre 1 y 11." << endl;
        }
        if (mesInicial > mesFinal) {
            cout << "El mes inicial tiene que ser menor o igual que el mes final." << endl;
        }

    } while (mesInicial > mesFinal || 
           mesInicial < 1 || mesInicial > 12 || 
           mesFinal < 1 || mesFinal > 12); 
}

/*
 * ¡ESCRIBID LA ESPECIFICACIÓN DE ESTA FUNCIÓN!
 */
int main() {
    char usuario;
    unsigned mesInicial, mesFinal;

    pedirInformacion(usuario, mesInicial, mesFinal);
    return 0;
}