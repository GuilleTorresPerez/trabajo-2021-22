
/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Guillermo Torres y Pablo Terés
 * Ultima revisión: 14-01-2022
 * Resumen: Fichero que contiene funciones para la extracción de los
 *          datos relevantes de los ficheros de precios y consumo eléctrico.
\******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "fecha.hpp"
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"

using namespace std;


bool leerPrecioHorario(istream& f, Fecha& fecha, unsigned& hora, double& precio) {

    string ignore;
    string fechaS, precioS;

    while(!f.eof()) {
        getline(f, ignore, ';');

        if (ignore.empty()) { // Evita la ultima línea del archivo (línea vacía)
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


bool leerPrecios(const string nombreFichero, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {
    
    ifstream archivo;

    archivo.open(nombreFichero, ios::in);

    if (archivo.fail()) {
        cout << "No se ha podido leer el archivo con la ruta especificada (tarifas)." << endl;
        return false;
    }

    string ignore;

    getline(archivo, ignore); // Evitar la primera linea del archivo

    Fecha fechaAux; // Variable auxiliar para leer la fecha
    unsigned horaAux; // Variable auxiliar para leer la hora
    double precioAux; // Variable auxiliar para leer el precio

    Fecha primerDia = {1, mesInicial, 2021};

    for (unsigned i = 0; i < MAX_DIAS; i++) {
        for (unsigned j = 0; j < NUM_HORAS; j++) {
            if (leerPrecioHorario(archivo, fechaAux, horaAux, precioAux)) {
                if (fechaAux.mes >= mesInicial && fechaAux.mes <= mesFinal) {
                    
                    int index = diasTranscurridos(primerDia, fechaAux); // Variable para almacenar la información en el registro

                    registros[index].fecha = fechaAux;
                    registros[index].precio[horaAux] = precioAux; // También se podría usar la variable local j para indexar la hora

                }
            }
        }
    }

    return true;

}

bool leerConsumoHorario(istream& f, Fecha& fecha, unsigned& hora, double& consumo) {
    

    // No es necesario sobreescribir el valor de fecha, ya que se lee en la función leerPrecioHora


    string ignore;
    string fechaS, consumoS, horaS;

    while(!f.eof()) {
        getline(f, ignore, ';');

        if (ignore.empty()) { // Evita la ultima línea del archivo (línea vacía)
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


bool leerConsumos(const string nombreCliente, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {

    unsigned totalIndex = 0; // Indice para tener en cuenta el numero de dias pasados
    unsigned horaAux; // Indice para tener en cuenta la proxima hora a leer del archivo y guardarla en el registro

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

        double auxiliar; // Variable auxiliar para almacenar el consumo en el registro

        while(leerConsumoHorario(archivo, registros[totalIndex].fecha, horaAux, auxiliar)) {

            registros[totalIndex].consumo[horaAux-1] = auxiliar;

            if (horaAux == 24) { // Cuando la hora llega a 24, la próxima línea del fichero pertenece al siguiente dia
                totalIndex++;
            }
        }

        archivo.close();

    }

    return true;

}
