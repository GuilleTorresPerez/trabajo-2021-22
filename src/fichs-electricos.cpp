


#include <iostream>
#include <iomanip>
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

        if (ignore.empty()) { // Evitar la última línea en blanco
            return false;
        }

        getline(f, ignore, ';');
        getline(f, ignore, ';');
        getline(f, ignore, ';');

        getline(f, precioS, ';');
        
        getline(f, fechaS);

        fecha.agno = stoi(fechaS.substr(0, 10));
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

    string ignore;

    getline(archivo, ignore);

    GastoDiario aux;
    unsigned horaAux;
    double precioAux;

    Fecha primerDia = {1, 1, 2021};
    Fecha primerMes = {1, mesInicial, 2021};

    for (unsigned i = 0; i < MAX_DIAS; i++) {
        for (unsigned j = 0; j < NUM_HORAS; j++) {
            if (leerPrecioHorario(archivo, aux.fecha, horaAux, precioAux)) {
                if (aux.fecha.mes >= mesInicial && aux.fecha.mes <= mesFinal) {
                    
                    int index = diasTranscurridos(primerDia, aux.fecha) - diasTranscurridos(primerDia, primerMes);

                    registros[index].fecha.agno = aux.fecha.agno;
                    registros[index].fecha.mes = aux.fecha.mes;
                    registros[index].fecha.dia = aux.fecha.dia;
                    registros[index].precio[j] = precioAux;

                }
            }
        }
    }

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

        if (ignore.empty()) { // Evita la ultima línea del archivo (línea en el archivo)
            return false;
        }
        
        getline(f, fechaS, ';');
        getline(f, horaS, ';');
        getline(f, consumoS, ';');

        getline(f, ignore);

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
    
    if (nombreCliente != "a" && nombreCliente != "b") {
        return false;
    }

    unsigned totalIndex = 0;
    unsigned horaAux;

    string mesDatosRuta = RUTA_DATOS + nombreCliente + "-2021-";
    string ignore;

    for (unsigned i = mesInicial; i < mesFinal+1; i++) {

        horaAux = 0;

        ifstream archivo;
        string nuevoMesDatosRuta = mesDatosRuta;

        if (i < 10) {
            nuevoMesDatosRuta = mesDatosRuta + "0";
        }

        nuevoMesDatosRuta = nuevoMesDatosRuta + to_string(i) + ".csv";

        archivo.open(nuevoMesDatosRuta, ios::in);

        if (archivo.fail()) {
            cout << "No se ha podido leer el archivo " << nuevoMesDatosRuta << endl;
            return false;
        }

        getline(archivo, ignore); // Evitar primera linea del archivo

        double auxiliar;

        while(leerConsumoHorario(archivo, registros[totalIndex].fecha, horaAux, auxiliar)) {

            registros[totalIndex].consumo[horaAux-1] = auxiliar;

            if (horaAux == 24) {
                totalIndex++;
            }
        }

        archivo.close();

    }

    return true;

}
