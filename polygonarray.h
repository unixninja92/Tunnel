#ifndef POLYGONARRAY_H
#define POLYGONARRAY_H

#include <QGraphicsPolygonItem>

typedef struct polygonBlock {
    QGraphicsPolygonItem* left;
    QGraphicsPolygonItem* right;
}polygonBlock;

class PolygonArray
{
public:
    PolygonArray(int);
    polygonBlock get(int);
    void rotate(polygonBlock);
    void set(polygonBlock, int);
    int getSize();
private:
    polygonBlock* array;
    int size;
};

#endif // POLYGONARRAY_H
