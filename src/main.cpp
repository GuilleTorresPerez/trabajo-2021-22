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
#include <iomanip>
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


void escribirInforme(ostream& f, const GastoDiario regDiarios[], const unsigned numRegs, const char nombreCliente, const unsigned mesInicial, const unsigned mesFinal) {

    f << "INFORME DEL CLIENTE \"" << nombreCliente - 32 << "\" ENTRE LOS MESES " << mesInicial << " Y " << mesFinal << " DE 2021" << endl;
    f << "-------------------------------------------------------------------------------------" << endl << endl;

// por qué nombreCliente - 32?? 

    double precioMedioMinimo = 0;
    Fecha diaMin;

    diaMasBarato(regDiarios, numRegs, diaMin, precioMedioMinimo);

    f << "El día completo más barato fue el "; 
    mostrar(f, diaMin); 
    f << ". Precio medio: " << precioMedioMinimo << " €/kwh" << endl;
    
    //////////////////////////

    Fecha diaMax;
    unsigned horaMax;
    double precioMax;
    horaMasCara(regDiarios, numRegs, diaMax, horaMax, precioMax);

    f << "La hora más cara tuvo lugar el ";
    mostrar(f, diaMax); 
    f << " a las " << horaMax << ":00. Precio: " << precioMax << " €/kwh" << endl << endl;

    ///////////////////////////////

    f << "El importe del consumo eléctrico en el periodo considerado ha sido de " << "// importe" << " €." << endl;
    f << "El importe mínimo concentrando todo el consumo diario en la hora más barata" << endl << "habría sido de " << "// importe mínimo conc." << " € (un " << "// porcentaje mejor" << " % menor)" << endl << endl;

    f << "COSTE CON TARIFAS COMERCIALES" << endl;
    f << "Coste              Nombre de la tarifa" << endl;
    f << "-----------------------------------------------" << endl;
    for (int i = 0; i < NUM_TARIFAS_COMERCIALES; i++) {
        f << setw(8) << "// coste con tarifa" << setw(24) << TARIFAS_COMERCIALES[i].nombre;
    }

}


/*
 * Pre:  «usuario» es el char al que se refiere el tipo de usuario y sus datos respectivos
 *       «mesInicial» y «mesFinal» se refieren al primer y al último mes del intervalo
 *       de meses del que se quiere conseguir los datos y «rutaArchivo» es el posible
 *       archivo que se puede crear para almacenar los datos
 * Post: Se han insertado los datos necesarios en las posibles variables y se ha detectado
 *       si se ha producido un error (como un intervalo de meses mal introducido, por ejemplo)
 */
void pedirInformacion (char& usuario, unsigned& mesInicial, unsigned& mesFinal, string& rutaArchivo) {
    
    bool fechaCorrecta = true;

    cout << "Escriba el nombre del usuario: ";
    cin >> usuario;

    do {
        cout << endl << "Escriba el mes inicial y el final: ";
        cin >> mesInicial >> mesFinal;
        fechaCorrecta = true;
        
        if (mesInicial < 1 || mesInicial > 12) {
            cout << "El mes inicial tiene que estar entre 1 y 11." << endl;
            fechaCorrecta = false;
        }
        else if (mesFinal < 1 || mesInicial > 12) {
            cout << "El mes final tiene que estar entre 1 y 11." << endl;
            fechaCorrecta = false;
        }
        else if (mesInicial > mesFinal) {
            cout << "El mes inicial tiene que ser menor o igual que el mes final." << endl;
            fechaCorrecta = false;
        }

        cout << endl;

    } while (!fechaCorrecta); 

    cout << "Escriba el nombre del fichero del informe" << endl << "(presione solo ENTRAR para escribirlo en la pantalla): ";

    cin >> rutaArchivo;

}

/*
 * ¡ESCRIBID LA ESPECIFICACIÓN DE ESTA FUNCIÓN!
 */
int main() {

    string rutaArchivo;
    char usuario;
    unsigned mesInicial, mesFinal;
    GastoDiario registro[999];
    int numRegistro = 0;

    pedirInformacion(usuario, mesInicial, mesFinal, rutaArchivo);

    string usuarioString(1, usuario);

    while (leerConsumos(usuarioString, mesInicial, mesFinal, registro))
    {
        numRegistro++;
    }

    if (rutaArchivo.empty()) {
        escribirInforme(cout, registro, numRegistro, usuario, mesInicial, mesFinal);
    } else {

        ofstream archivo;

        archivo.open(rutaArchivo, ios::out);

        if (archivo.fail()) {
            cout << "No se ha podido crear el archivo " << rutaArchivo << endl;
            return 0;
        }

        escribirInforme(archivo, registro, numRegistro, usuario, mesInicial, mesFinal);
    }

    

    return 0;
}