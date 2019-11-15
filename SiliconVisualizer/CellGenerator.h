#pragma once
#include"AtomSet.h"

class CellGenerator {
public:
    static atom::AtomPair initialCubeCell(const QVector3D& s, const float len);
};

