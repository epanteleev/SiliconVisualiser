#include "CellGenerator.h"

atom::AtomSet CellGenerator::initialCubeCell(const QVector3D& s, const float len) {
	using namespace atom;
	const size_t size = 18;
	const std::vector<float> posX{ 1, -1,  1,  1, -1,  1, -1, -1,    0,   0,  0,  0,  1, -1,   0.50, -0.50,  0.50, -0.50 };
	const std::vector<float> posY{ 1,  1, -1,  1, -1, -1,  1, -1,    0,   0,  1, -1,  0,  0,   0.50, -0.50, -0.50,  0.50 };
	const std::vector<float> posZ{ 1,  1,  1, -1,  1, -1, -1, -1,    1,  -1,  0,  0,  0,  0,   0.50,  0.50, -0.50, -0.50 };

	std::unordered_set<QVector3D,atom::Hash> set;
	for (size_t shX = 0; shX < s.x(); shX++) {
		for (size_t shY = 0; shY < s.y(); shY++) {
			for (size_t shZ = 0; shZ < s.z(); shZ++) {
				auto posx = map<float>([=](float i) { return shX * 2 + i; }, posX);
				auto posy = map<float>([=](float i) { return shY * 2 + i; }, posY);
				auto posz = map<float>([=](float i) { return shZ * 2 + i; }, posZ);
				for (auto i = 0; i < size; i++) {
					set.insert(QVector3D(posx[i] * len, posy[i] * len, posz[i] * len));
				}
			}
		}
	}
	return atom::AtomSet(set.begin(), set.end());
}