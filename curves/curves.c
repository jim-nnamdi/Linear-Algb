#include <curves.h>

uint64_t slope(uint64_t y2, uint64_t y1, uint64_t x2, uint64_t x1)
{
    if (y2 == y1 || x2 == x1)
        fprintf(stderr, "Negative value computations");
    uint64_t nums_t = y2 - y1;
    uint64_t dens_t = x2 - x1;
    uint64_t result = (nums_t) / (dens_t);
    return result;
}

uint64_t slopevalx(uint64_t slope, uint64_t x1, uint64_t x2)
{
    if (slope == NULL || slope == 0 && x1 == 0 || x2 == 0) return;
    uint64_t slopex3 = slope - x1 - x2;
    return slopex3;
}

uint64_t slopevaly(uint64_t slope, uint64_t x1, uint64_t x3, uint64_t y1)
{
    if (x1 == NULL || x3 == NULL || y1 == NULL) return;
    uint64_t slopey3 = slope * (x1 - x3) - y1;
    return slopey3;    
}
