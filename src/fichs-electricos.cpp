


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
    string fechaS, horaS, precioS;

    while(!f.eof()) {
        getline(f, ignore, ';');
        getline(f, fechaS, ';');

        fecha.dia = stoi(fechaS.substr(0, 1));
        fecha.mes = stoi(fechaS.substr(3, 4));
        fecha.agno = stoi(fechaS.substr(6, 9));

        getline(f, horaS, ';');

        hora = stoi(horaS);

        getline(f, precioS, ';');

        precio = stoi(precioS);

        getline(f, ignore);

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
    return true;
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