#ifndef MEANFILTER_H
#define MEANFILTER_H

#include <stdint.h>

typedef struct MeanFilter
{
    uint16_t *buffer;
    uint8_t bufferSize;
    uint8_t oldestIndex;
    double (*sum)(uint16_t *buffer, uint8_t bufferSize); 
} MeanFilter_t;

void MeanFilter_Init(MeanFilter_t *meanFilter, uint16_t *buffer, uint8_t bufferSize);
int16_t MeanFilter_Insert(MeanFilter_t *meanFilter, uint16_t value);
int16_t MeanFilter_Calculate(MeanFilter_t *meanFilter);

#endif // MEANFILTER_H