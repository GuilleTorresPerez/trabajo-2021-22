
/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Guillermo Torres y Pablo Terés
 * Ultima revisión: 14-01-2022
 * Resumen: Fichero con funciones para la lectura de datos respecto a los ficheros almacenados en la carpeta datos.
\******************************************************************************/


#include <string>
#include "gasto-diario.hpp"
#include "tarifas-comerciales.hpp"

using namespace std;

double costeDiarioTarifaPlanaTramos(const GastoDiario& gasto, const TarifaPlanaTramos tarifa) {
    double suma = 0;
    for (unsigned i = 0; i < NUM_HORAS; i++) {
        if ((i >= 10 && i < 14) || (i >= 18 && i < 22)) {
            suma += gasto.consumo[i] * tarifa.punta;
        } else if ((i >= 8 && i < 10) || (i >= 14 && i < 18) || i >= 22) {
            suma += gasto.consumo[i] * tarifa.llano;
        } else {
            suma += gasto.consumo[i] * tarifa.valle;
        }
    }
    return suma;
}

double costeTarifaPlanaTramos(const GastoDiario regDiario[], const unsigned numRegs, const TarifaPlanaTramos tarifa) {
    double suma = 0;
    for (unsigned i = 0; i < numRegs; i++) {
        suma += costeDiarioTarifaPlanaTramos(regDiario[i], tarifa);
    }
    return suma;
    
}
