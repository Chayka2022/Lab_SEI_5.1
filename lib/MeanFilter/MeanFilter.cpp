#include "MeanFilter.h"

void MeanFilter_Init(MeanFilter_t *meanFilter, uint16_t *buffer, uint8_t bufferSize)
{
    meanFilter->buffer = buffer;
    meanFilter->bufferSize = bufferSize;
    meanFilter->oldestIndex = 0;
    for (uint8_t i = 0; i < bufferSize; i++)
    {
        buffer[i] = 0;
    }
}

int16_t MeanFilter_Insert(MeanFilter_t *meanFilter, uint16_t value)
{
    meanFilter->buffer[meanFilter->oldestIndex] = value;
    meanFilter->oldestIndex = (meanFilter->oldestIndex + 1) % meanFilter->bufferSize;
    return MeanFilter_Calculate(meanFilter);
}

int16_t MeanFilter_Calculate(MeanFilter_t *meanFilter)
{   
    uint32_t sum = 0;
    for (uint8_t i = 0; i < meanFilter->bufferSize; i++)
    {
        sum += meanFilter->buffer[i];
    }
    return sum / meanFilter->bufferSize;
}