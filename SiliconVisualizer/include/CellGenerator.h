#pragma once
#include"AtomSet.h"

class CellGenerator {
public:
    static atom::Cell initialCubeCell(const QVector3D& s, const float len);
};

