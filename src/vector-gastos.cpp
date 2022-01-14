
/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Guillermo Torres y Pablo Terés
 * Ultima revisión: 14-01-2022
 * Resumen: Fichero que contiene funciones para la gestion de los datos
 *          almacenados en un registro que contiene información sobre todos los dias
 *          entre dos determinadas fechas.
\******************************************************************************/

#include "gasto-diario.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, double& precioMedioMinimo) {

    double precioMedio = costeMedio(regsDiarios[0]);
    double aux; // Variable auxiliar para comparar precios
    int index = 0; // Variable auxiliar para indicar que dia tiene el precio más bajo
    
    for (unsigned i = 1; i < numRegs; i++) {
        
        aux = costeMedio(regsDiarios[i]);
        
        if (precioMedio > aux) {
            precioMedio = aux;
            index = i;
        }
    }

    dia = regsDiarios[index].fecha;
    precioMedioMinimo = precioMedio;

}

void horaMasCara(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, unsigned& hora, double& precioMaximo) {

    precioMaximo = regsDiarios[0].precio[horaMasCara(regsDiarios[0])];
    double aux; // Variable auxiliar para comparar precios

    for (unsigned i = 1; i < numRegs; i++) {
        
        aux = regsDiarios[i].precio[horaMasCara(regsDiarios[i])];

        if (precioMaximo < aux) {
            
            precioMaximo = aux;
            dia = regsDiarios[i].fecha;
            hora = horaMasCara(regsDiarios[i]);

        }     
    }
}

double costeTerminoVariable(const GastoDiario regsDiarios[], const unsigned numRegs) {
    
    double suma = 0;

    for (unsigned i = 0; i < numRegs; i++) {
        suma += costeDiario(regsDiarios[i]);
    }

    return suma;

}

double costeMinimoPosible(const GastoDiario regsDiarios[], const unsigned numRegs) {
    double suma = 0;
    for (unsigned i = 0; i < numRegs; i++) {
        suma += costeDiarioMinimo(regsDiarios[i]);
    }
    return suma;
}