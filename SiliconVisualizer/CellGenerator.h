#pragma once
#include"AtomSet.h"

class CellGenerator {
public:
    static std::pair<atom::AtomSet, std::vector<int>> initialCubeCell(const QVector3D& s, const float len);
};

