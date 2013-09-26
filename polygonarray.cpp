/*
 *Copyright 2013 unixninja92
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
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
