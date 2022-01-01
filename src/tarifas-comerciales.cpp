#include <string>
#include "gasto-diario.hpp"
#include "tarifas-comerciales.hpp"
#pragma once
using namespace std;

double costeDiarioTarifaPlanaTramos(const GastoDiario& gasto, 
                                    const TarifaPlanaTramos tarifa) {
    double suma = 0;
    for (unsigned i = 0; i < NUM_HORAS; i++) {
        if ((i > 10 && i < 14) || (i > 18 && i < 22)) {
            suma += gasto.consumo[i] * tarifa.punta;
        } else if ((i > 8 && i < 10) || (i > 14 && i < 18) || (i > 22 && i < 0)) {
            suma += gasto.consumo[i] * tarifa.llano;
        } else if (i >  0 && i < 8) {
            suma += gasto.consumo[i] * tarifa.valle;
        }
    }
    return suma;
}

double costeTarifaPlanaTramos(const GastoDiario regDiario[],
                              const unsigned numRegs, const TarifaPlanaTramos tarifa) {
    double suma = 0;
    for (unsigned i = 0; i < numRegs; i++) {
        suma += costeDiarioTarifaPlanaTramos(regDiario[i], tarifa);
    }
    return suma;
    
}
