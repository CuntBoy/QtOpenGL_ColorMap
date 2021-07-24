#include "drawdata.h"

DrawData::DrawData()
{
    vertices_.clear();
    indices_.clear();
}

DrawData::~DrawData()
{
    vertices_.clear();
    indices_.clear();
}

void DrawData::resizeVerticesData(uint64_t dataSize)
{
    vertices_.resize(dataSize);
}

double *DrawData::verticesData()
{
    return vertices_.data();
}

void DrawData::resizeIndicesData(uint64_t dataSize)
{
    indices_.resize(dataSize);
}

unsigned int *DrawData::indicesData()
{
    return indices_.data();
}
