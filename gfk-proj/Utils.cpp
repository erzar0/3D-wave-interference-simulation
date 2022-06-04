#include "Utils.h"
    
double utils::mapInterval(double start1, double stop1, double start2, double stop2, double value)
{
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}
