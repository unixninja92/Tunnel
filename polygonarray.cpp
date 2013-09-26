#include "polygonarray.h"
#include <stdio.h>

PolygonArray::PolygonArray(int s)
{
    size = s;
    array = new polygonBlock[size];
}

polygonBlock PolygonArray::get(int pos)
{
    return array[pos];
}

void PolygonArray::set(polygonBlock newBlock, int pos)
{
    array[pos] = newBlock;
}

void PolygonArray::rotate(polygonBlock newPoly)
{
    for(int i = size-1; i > 0; i--){
        array[i] = array[i-1];
    }
    array[0]=newPoly;
}

int PolygonArray::getSize()
{
    return size;
}
