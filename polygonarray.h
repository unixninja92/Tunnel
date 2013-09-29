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
#ifndef POLYGONARRAY_H
#define POLYGONARRAY_H

#include <QPointer>
#include <QGraphicsPolygonItem>

typedef struct polygonBlock {
    QGraphicsPolygonItem* left;
    QGraphicsPolygonItem* right;
}polygonBlock;

class PolygonArray
{
public:
    PolygonArray(int);
    ~PolygonArray();
    polygonBlock get(int);
    void rotate(polygonBlock);
    void set(polygonBlock, int);
    int getSize();
private:
    polygonBlock* array;
    int size;
};

#endif // POLYGONARRAY_H
