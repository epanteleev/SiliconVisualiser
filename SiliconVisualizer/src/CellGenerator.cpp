#include "CellGenerator.h"

atom::Cell CellGenerator::initialCubeCell(const QVector3D& s, const float len) {
	using namespace atom;
	const size_t size = 18;
	const std::vector<float> posX{ 1, -1,  1,  1, -1,  1, -1, -1,    0,   0,  0,  0,  1, -1,   0.50, -0.50,  0.50, -0.50 };
	const std::vector<float> posY{ 1,  1, -1,  1, -1, -1,  1, -1,    0,   0,  1, -1,  0,  0,   0.50, -0.50, -0.50,  0.50 };
	const std::vector<float> posZ{ 1,  1,  1, -1,  1, -1, -1, -1,    1,  -1,  0,  0,  0,  0,   0.50,  0.50, -0.50, -0.50 };

    std::unordered_set<QVector3D, atom::Hash> set;
    for (int shX = -static_cast<int>(s.x() / 2); shX < s.x() / 2; ++shX) {
        for (int shY = -static_cast<int>(s.y() / 2); shY < s.y() / 2; ++shY) {
            for (int shZ = -static_cast<int>(s.z() / 2); shZ < s.z() / 2; ++shZ) {
				auto posx = map<float>([=](float i) { return shX * 2 + i; }, posX);
				auto posy = map<float>([=](float i) { return shY * 2 + i; }, posY);
				auto posz = map<float>([=](float i) { return shZ * 2 + i; }, posZ);
                for (size_t i = 0; i < size; i++) {
                    set.emplace(QVector3D(posx[i], posy[i], posz[i]));
				}
			}
		}
	}
    AtomSet setRes(set.size());
    std::vector<int> levels(set.size());
    auto it = set.begin();
    for(size_t i = 0; i < levels.size(); ++i, ++it) {
        levels[i] = -(static_cast<int>((*it).x()) + static_cast<int>((*it).y()) + static_cast<int>((*it).z()));
        setRes[i] = (*it) * len;
    }
    return Cell(atom::AtomSet(setRes.begin(), setRes.end()), levels);
}
