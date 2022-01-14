/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Pablo Teres y Guillermo Torres  
 * Ultima revisión: 13 de enero de 2022
 * Resumen: El fichero main es el archivo principal del proyecto "electricidad"
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

const unsigned ESPACIO = 2;

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

    char usuarioMayusucla = nombreCliente - 32;

    f << "INFORME DEL CLIENTE '" << usuarioMayusucla << "' ENTRE LOS MESES " << mesInicial << " Y " << mesFinal << " DE 2021" << endl;
    f << "--------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << fixed << setprecision(5);

    // Calculo del dia mas barato entre los meses introducidos
    Fecha costeMinimoFecha;
    double costeMed;

    diaMasBarato(regDiarios, numRegs, costeMinimoFecha, costeMed);
    f << "El día completo más barato fue el "; 
    mostrar(f, costeMinimoFecha); 
    f << ". Precio medio: " << fixed << setprecision(5) << costeMed / 1000 << " €/kwh" << endl;
    

    // Calculo de la hora, junto con precio, mas cara entre los meses introducidos
    unsigned horaCara;
    double precioMasCaro;
    Fecha diaHoraCara;

    cout << setprecision(2);

    horaMasCara(regDiarios, numRegs, diaHoraCara, horaCara, precioMasCaro);

    f << "La hora más cara tuvo lugar el ";
    mostrar(f, diaHoraCara); 
    f << " a las " << horaCara << ":00. Precio: " << precioMasCaro / 1000 << " €/kwh" << endl << endl;


    // Calculo del importe minimo y total, así como del porcentaje de diferencia entre los dos
    double importeTotal = costeTerminoVariable(regDiarios, numRegs);
    double importeMinimo = costeMinimoPosible(regDiarios, numRegs);
    double porcentajeDiferencia = (1 - (importeMinimo / importeTotal)) * 100;

    f << "El importe del consumo eléctrico en el periodo considerado ha sido de " 
      << fixed << setprecision(ESPACIO) << importeTotal << " €." << endl;

    f << "El importe mínimo concentrando todo el consumo diario en la hora más barata" << endl << "habría sido de " 
      << fixed << setprecision(ESPACIO) << importeMinimo << " € (un " 
      << fixed << setprecision(ESPACIO) << porcentajeDiferencia << " % menor)" << endl << endl;


    // Calculo del precio del consumo aplicando las tarifas respectivas
    f << "COSTE CON TARIFAS COMERCIALES" << endl;
    f << "   Coste           Nombre de la tarifa" << endl;
    f << "-----------------------------------------------" << endl;
    for (unsigned i = 0; i < NUM_TARIFAS_COMERCIALES; i++) {
        f << setw(10) << fixed << setprecision(ESPACIO) << costeTarifaPlanaTramos(regDiarios, numRegs, TARIFAS_COMERCIALES[i]) << " €       " << TARIFAS_COMERCIALES[i].nombre << endl;
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
void pedirInformacion (string& usuario, unsigned& mesInicial, unsigned& mesFinal, string& rutaArchivo) {
    
    bool fechaCorrecta; // Variable auxiliar para verificar que los datos introducidos son correctos

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
    cin.ignore(1, '\n');
    getline(cin, rutaArchivo);
    cout << rutaArchivo;

    if (rutaArchivo.find('\\') != std::string::npos || rutaArchivo.find('/') != std::string::npos || 
        rutaArchivo.find(':') != std::string::npos || rutaArchivo.find('*') != std::string::npos ||
        rutaArchivo.find('?') != std::string::npos || rutaArchivo.find('\"') != std::string::npos ||
        rutaArchivo.find('<') != std::string::npos || rutaArchivo.find('>') != std::string::npos ||
        rutaArchivo.find('|') != std::string::npos) 
        {
            cout << "No se ha podido escribir en el fichero \"" << rutaArchivo << "\".";
        }

    cout << endl;

}

/*
 * Función principal del programa. Se inicializan las variables necesarias para el programa en pedirInformacion
 * para posteriormente leer los datos necesarios de los ficheros en leerConsumos y leerPrecios.
 * Por último, se operan con dichos datos y se escribe en pantalla o en un archivo especificado los datos que se buscan.
 */
int main() {

    string rutaArchivo;
    string usuario;
    unsigned mesInicial, mesFinal;
    GastoDiario registro[MAX_DIAS];
    int numRegistro = 0;
    const string nombreFicheroTarifas = "datos/tarifas-2021-ene-nov.csv";

    
    pedirInformacion(usuario, mesInicial, mesFinal, rutaArchivo);

    // Si hay algun fallo leyendo los archivos el programa finaliza.
    if (!leerConsumos(usuario, mesInicial, mesFinal, registro)) {
        return 1;
    }
    if (!leerPrecios(nombreFicheroTarifas, mesInicial, mesFinal, registro)){
        return 1;
    }

    // Calculo del total de dias con datos que hay en el registro
    Fecha primerDia = {1, mesInicial, 2021};
    Fecha ultimoDia = {1, mesFinal+1, 2021};

    numRegistro = diasTranscurridos(primerDia, ultimoDia);
    
    if (rutaArchivo.empty()) {

        escribirInforme(cout, registro, numRegistro, usuario[0], mesInicial, mesFinal);

    } else {

        ofstream archivo;

        archivo.open(rutaArchivo, ios::out);

        if (archivo.fail()) {
            cout << "No se ha podido crear el archivo." << rutaArchivo << endl;
            return 0;
        }

        escribirInforme(archivo, registro, numRegistro, usuario[0], mesInicial, mesFinal);
    }
    return 0;
}