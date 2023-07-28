

#include "map.h"


// devuelve una valor float que será el multiplicador para convertir valor de adc a volts
float MAP(float input_min, float input_max, float output_min, float output_max)
{
    return ((output_max - output_min)/((input_max - input_min) + output_min));
}