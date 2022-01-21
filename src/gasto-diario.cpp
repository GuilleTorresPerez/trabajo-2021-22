/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Guillermo Torres y Pablo Terés
 * Ultima revisión: 14-01-2022
 * Resumen: Fichero que contiene funciones para la
 *          gestión de datos de horarios de consumo y precios de un día concreto.
\******************************************************************************/

#include "gasto-diario.hpp"
#include "fecha.hpp"


unsigned horaMasCara(const GastoDiario& gasto) {
    
    double maxPrecio = gasto.precio[0];
    unsigned hora = 0;

    for (unsigned i = 1; i < NUM_HORAS; i++) {
        if (maxPrecio < gasto.precio[i]) {
            maxPrecio = gasto.precio[i];
            hora = i;
        }
    }

    return hora;
}

double costeMedio(const GastoDiario& gasto) {
    
    double suma = 0;

    for (unsigned i = 0; i < NUM_HORAS; i++) {
        suma += gasto.precio[i];
    }

    suma /= NUM_HORAS;

    return suma;

}

double costeDiario(const GastoDiario& gasto) {
    
    double suma = 0;

    for (unsigned i = 0; i < NUM_HORAS; i++) {
        suma += gasto.precio[i] * gasto.consumo[i] / 1000;
    }

    return suma;

}

double costeDiarioMinimo(const GastoDiario& gasto) {
    
    double masBaratoPrecio = gasto.precio[0];
    for (unsigned i = 1; i < NUM_HORAS; i++) {
        if (masBaratoPrecio > gasto.precio[i]) {
            masBaratoPrecio = gasto.precio[i];
        }
    }

    double suma = 0;
    for (unsigned i = 0; i < NUM_HORAS; i++) {
        suma += gasto.consumo[i] * masBaratoPrecio / 1000;
    }

    return suma;

}