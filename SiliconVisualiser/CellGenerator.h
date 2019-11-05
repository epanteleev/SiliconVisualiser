#pragma once
#include"AtomSet.h"

class CellGenerator {
public:
	static atom::AtomSet initialCubeCell(const QVector3D& s, const float len);
};

