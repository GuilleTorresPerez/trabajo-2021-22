

#include "gasto-diario.hpp"
#include "fecha.hpp"


/*
 * Pre:  ---
 * Post: Devuelve la hora en la que el precio de la electricidad según los datos
 *       de precios horarios del registro «gasto» fue más cara.
 */
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

//Me imagino que las horas las tenemos en cuenta desde la hora 0 a la hora 23, en caso de que no habría que sumarle 1 al return.

/*
 * Pre:  ---
 * Post: Devuelve el precio medio de la electricidad según los datos de precios
 *       horarios del registro «gasto».
 */
double costeMedio(const GastoDiario& gasto) {
    
    double suma = 0;

    for (unsigned i = 0; i < NUM_HORAS; i++) {
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

    for (unsigned i = 0; i < NUM_HORAS; i++) {
        suma += gasto.precio[i] * gasto.consumo[i] / 1000;
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
//He cambiado esta función porque pienso que lo que pide es el coste de todo un día
//aplicado con el precio más barato de ese día, no el coste más barato del día.