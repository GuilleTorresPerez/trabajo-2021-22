

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
    
    return costeDiario(gasto) / NUM_HORAS;

}

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario& gasto) {
    
    double suma = 0;

    for (int i = 0; i < NUM_HORAS; i++) {
        suma += gasto.precio[i];
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
    
    double masBarato = 999;

    for (int i = 0; i < NUM_HORAS; i++) {
        if (masBarato > gasto.precio[i]) {
            masBarato = gasto.precio[i];
        }
    }

    // TODO: No entiendo que es lo que hay que hacer en este, igual es que soy retramonger :V

}