/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Pablo Teres y Guillermo Torres  
 * Ultima revisión: 14 de enero de 2022
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

    f << endl << "INFORME DEL CLIENTE '" << usuarioMayusucla << "' ENTRE LOS MESES " << mesInicial << " Y " << mesFinal << " DE 2021" << endl;
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

    horaMasCara(regDiarios, numRegs, diaHoraCara, horaCara, precioMasCaro);

    f << "La hora más cara tuvo lugar el ";
    mostrar(f, diaHoraCara); 
    f << " a las " << horaCara << ":00. Precio: " << precioMasCaro / 1000 << " €/kwh" << endl << endl;

    f << setprecision(2);

    // Calculo del importe minimo y total, así como del porcentaje de diferencia entre los dos
    double importeTotal = costeTerminoVariable(regDiarios, numRegs);
    double importeMinimo = costeMinimoPosible(regDiarios, numRegs);
    double porcentajeDiferencia = (1 - (importeMinimo / importeTotal)) * 100;

    f << "El importe del consumo eléctrico en el periodo considerado ha sido de " << importeTotal << " €." << endl;

    f << "El importe mínimo concentrando todo el consumo diario en la hora más barata" << endl << "habría sido de " << importeMinimo << " € (un " 
    << porcentajeDiferencia << " % menor)" << endl << endl;


    // Calculo del precio del consumo aplicando las tarifas respectivas
    f << "COSTE CON TARIFAS COMERCIALES" << endl;
    f << "   Coste           Nombre de la tarifa" << endl;
    f << "-----------------------------------------------" << endl;
    for (unsigned i = 0; i < NUM_TARIFAS_COMERCIALES; i++) {
        f << setw(10) << costeTarifaPlanaTramos(regDiarios, numRegs, TARIFAS_COMERCIALES[i]) << " €       " << TARIFAS_COMERCIALES[i].nombre << endl;
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
void pedirInformacion (string& usuario, unsigned& mesInicial, unsigned& mesFinal) {
    
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
        if (mesFinal < 1 || mesFinal > 12) {
            cout << "El mes final tiene que estar entre 1 y 11." << endl;
            fechaCorrecta = false;
        }
        if (mesInicial > mesFinal) {
            cout << "El mes inicial tiene que ser menor o igual que el mes final." << endl;
            fechaCorrecta = false;
        }

        cout << endl;

    } while (!fechaCorrecta); 

    

}

void pedirNombreFichero(string& rutaArchivo) {

    cout << "Escriba el nombre del fichero del informe" << endl << "(presione solo ENTRAR para escribirlo en la pantalla): ";
    cin.ignore(1, '\n');
    getline(cin, rutaArchivo);
}

/*
 * Función principal del programa. Se inicializan las variables necesarias para el programa en pedirInformacion a través
 * de los requisitos del usuario para posteriormente la lectura de datos necesarios de los ficheros en leerConsumos y leerPrecios.
 * Por último, se operan con dichos datos y se escribe en pantalla o en un archivo especificado los datos que se buscan en
 * la función escribir informe. Estas operaciones son hayar el dia con el coste medio más barato, así como su precio medio;
 * hayar la hora más cara, así como su fecha y su precio; hayar el importe del consumo eléctrico en el periodo dado y el 
 * importe asumiendo que todos los calculos se realizan con la hora mas barata, así como el porcentaje de diferencia entre estos dos valores.
 * Por último se calcula el precio considerando diversas tarifas.
 * 
 * !!! Aviso:
 * 
 * Sobre posible error en el programa: Cuando se trata con archivos del usuario A algunos resultados pueden resultar en 
 * valer un par de centimos más de aquellos mostrados en las trazas en el pdf del trabajo, sin embargo, parece funcionar
 * correctamente con aquellos resultados obtenidos del usuario B y comparados con las trazas del pdf. El motivo de este suceso
 * puede ser resultado debido a que el compilador asume que los doubles almacenados en los struct "tarifas" tienen valores periodicos,
 * arrastrando un valor muy pequeño a lo largo de las multiplicaciones, o que haya algun cambio en los propios ficheros del usuario A
 * descargados desde github, muy posiblemente entre los meses 1 y 5 dado a que la diferencia de centimos es la misma en las trazas
 * 1 y 5 (que tratan los meses del 1 a 11 y 1 a 5 del usuario A respectivamente).
 * 
 */
int main() {

    string rutaArchivo;
    string usuario;
    unsigned mesInicial, mesFinal;
    GastoDiario registro[MAX_DIAS];
    int numRegistro = 0;
    const string nombreFicheroTarifas = "datos/tarifas-2021-ene-nov.csv";

    
    pedirInformacion(usuario, mesInicial, mesFinal);

    // Si hay algun fallo leyendo los archivos el programa finaliza.
    if (!leerConsumos(usuario, mesInicial, mesFinal, registro)) {
        return 1;
    }
    if (!leerPrecios(nombreFicheroTarifas, mesInicial, mesFinal, registro)){
        return 1;
    }

    pedirNombreFichero(rutaArchivo);

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
            cout << "No se ha podido escribir en el fichero" << rutaArchivo << endl;
            return 0;
        }

        escribirInforme(archivo, registro, numRegistro, usuario[0], mesInicial, mesFinal);
        cout << "Informe '" << rutaArchivo << "' creado correctamente.";
    }
    return 0;
}