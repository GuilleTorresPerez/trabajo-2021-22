

#include "gasto-diario.hpp"
#include "fecha.hpp"


/*
 * Pre:  ---
 * Post: Devuelve la hora en la que el precio de la electricidad según los datos
 *       de precios horarios del registro «gasto» fue más cara.
 */
unsigned horaMasCara(const GastoDiario& gasto) {
    
    unsigned maxPrecio = 0;

    for (int i = 0; i < NUM_HORAS; i++) {
        if (maxPrecio < gasto.precio[i]) {
            maxPrecio = gasto.precio[i];
        }
    }

    return maxPrecio;

}

/*
 * Pre:  ---
 * Post: Devuelve el precio medio de la electricidad según los datos de precios
 *       horarios del registro «gasto».
 */
double costeMedio(const GastoDiario& gasto) {
    
    double suma = 0;

    for (int i = 0; i < NUM_HORAS; i++) {
        suma += gasto.precio[i];
    }

    suma /= NUM_HORAS;

    return suma;

}

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario& gasto) {
    
    double suma = 0;

    for (int i = 0; i < NUM_HORAS; i++) {
        suma += gasto.precio[i] * gasto.consumo[i];
    }

    return suma;

}

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que todo el 
 *       consumo eléctrico reflejado en el registro «gasto» hubiera tenido lugar
 *       en la hora con el precio más barato del registro «gasto».
 */
double costeDiarioMinimo(const GastoDiario& gasto) {
    
    double masBaratoGasto = 999;
    double masBaratoPrecio = 999;

    for (int i = 0; i < NUM_HORAS; i++) {
        if (masBaratoPrecio > gasto.precio[i]) {
            masBaratoPrecio = gasto.precio[i];
        }
    }

    for (int i = 0; i < NUM_HORAS; i++) {
        double nuevoPrecio = gasto.consumo[i] * masBaratoPrecio;
        if (masBaratoGasto > nuevoPrecio) {
            masBaratoGasto = nuevoPrecio;
        }
    }

    return masBaratoGasto;

}