


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "fecha.hpp"
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"

using namespace std;

/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-precios> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <precio-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «precio»,
 *       respectivamente, los datos sobre la fecha, hora y precio horario
 *       correspondientes a la línea que se ha extraído del flujo «f».
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
bool leerPrecioHorario(istream& f, Fecha& fecha, unsigned& hora, double& precio) {

    string ignore;
    string fechaS, precioS;

    while(!f.eof()) {
        getline(f, ignore, ';');
        getline(f, ignore, ';');
        getline(f, ignore, ';');
        getline(f, ignore, ';');

        getline(f, precioS, ';');
        
        getline(f, fechaS);

        fecha.agno = stoi(fechaS.substr(0, 3));
        fecha.mes = stoi(fechaS.substr(5,6));
        fecha.dia = stoi(fechaS.substr(8,9));

        hora = stoi(fechaS.substr(11,12));

        precio = stod(precioS);

        return true;

    }

    return false;

}

/*
 * Pre:  «nombreFichero» es el nombre de un fichero externo que cumple con la
 *       sintaxis de la regla <fichero-precios> establecida en el enunciado; 
 *       «mesInicial» y «mesFinal» están ambos entre «PRIMER_MES» y «ULTIMO_MES»
 *       y mesInicial < mesFinal.
 * Post: Ha copiado los datos de precios horarios correspondientes a fechas 
 *       entre «mesInicial» y «mesFinal» presentes en «nombreFichero» en las 
 *       componentes correspondientes a la hora del precio del campo «precios»
 *       en las primeras componentes del vector «registros», cuyos campos
 *       «fecha» se han actualizado y han quedado en orden cronológico (tal y
 *       como aparecían en el fichero). LOS DATOS DEL VECTOR CORRESPONDIENTE AL
 *       CAMPO «CONSUMO» NO SE HAN MODIFICADO.
 *       La función ha devuelto «true» si ha podido leer del fichero de nombre 
 *       «nombreFichero» correctamente, y «false» en caso contrario.
 */
bool leerPrecios(const string nombreFichero, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {
    
    ifstream archivo;

    archivo.open(nombreFichero, ios::in);

    if (archivo.fail()) {
        cout << "No se ha podido leer el archivo con la ruta especificada." << endl;
        return false;
    }

    GastoDiario aux;
    unsigned horaAux;
    double precioAux;

    unsigned index = 0;

    for (int i = 0; i < MAX_DIAS; i++) {
        for (int j = 0; j < NUM_HORAS; j++) {
            if (leerPrecioHorario(archivo, aux.fecha, horaAux, precioAux)) {
                if (aux.fecha.mes >= mesInicial && aux.fecha.mes <= mesFinal) {
                    registros[i].fecha = aux.fecha;
                    registros[i].precio[j] = precioAux;
                }
            }
        }
    }

    // TODO: Esto es una pedazo de chapuza, si encuentras una mejor manera de hacer esto arreglalo :)

    return true;

}

/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-consumos> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <consumo-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «consumo»,
 *       respectivamente, los datos sobre la fecha, hora y consumo horario
 *       correspondientes a la línea que se ha extraído del flujo «f». 
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
bool leerConsumoHorario(istream& f, Fecha& fecha, unsigned& hora, double& consumo) {
    
    string ignore;
    string fechaS, consumoS, horaS;

    while(!f.eof()) {
        getline(f, ignore, ';');
        
        getline(f, fechaS, ';');
        getline(f, horaS, ';');
        getline(f, consumoS, ';');

        getline(f, ignore);

        fecha.agno = stoi(fechaS.substr(6, 9));
        fecha.mes = stoi(fechaS.substr(3,4));
        fecha.dia = stoi(fechaS.substr(0,1));

        hora = stoi(horaS);

        consumo = stod(consumoS);

        return true;

    }

    return false;
}

/*
 * Pre:  «mesInicial» y «mesFinal» están ambos entre «PRIMER_MES» y «ULTIMO_MES»
 *       y mesInicial < mesFinal; si para cada mes entre «mesInicial» y
 *       «mesFinal» existe un fichero con nombre de la forma
 *       "datos/" + nombreCliente + "-2021-" + mes-con-dos-cifras + ".csv", este
 *       cumple con la sintaxis de la regla <fichero-consumos> establecida en el
 *       enunciado.
 * Post: Ha copiado los datos de precios horarios correspondientes a fechas 
 *       entre «mesInicial» y «mesFinal» presentes en los ficheros mencionados
 *       en la precondición en las componentes correspondientes a la hora del
 *       consumo del campo «consumo» en las primeras componentes del vector
 *       «registros». LOS DATOS DEL VECTOR CORRESPONDIENTE AL CAMPO «PRECIOS» NO
 *       SE HAN MODIFICADO.
 *       La función ha devuelto «true» si ha podido leer de todos los ficheros 
 *       referidos en la precondición correctamente, y «false» en caso contrario.
 */
bool leerConsumos(const string nombreCliente, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {
    return true;
}