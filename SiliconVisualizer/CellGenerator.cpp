#include "CellGenerator.h"

std::pair<atom::AtomSet, std::vector<int>> CellGenerator::initialCubeCell(const QVector3D& s, const float len) {
	using namespace atom;
	const size_t size = 18;
	const std::vector<float> posX{ 1, -1,  1,  1, -1,  1, -1, -1,    0,   0,  0,  0,  1, -1,   0.50, -0.50,  0.50, -0.50 };
	const std::vector<float> posY{ 1,  1, -1,  1, -1, -1,  1, -1,    0,   0,  1, -1,  0,  0,   0.50, -0.50, -0.50,  0.50 };
	const std::vector<float> posZ{ 1,  1,  1, -1,  1, -1, -1, -1,    1,  -1,  0,  0,  0,  0,   0.50,  0.50, -0.50, -0.50 };

    std::unordered_set<QVector3D, atom::Hash> set;
    for (size_t shX = 0; shX < s.x(); ++shX) {
        for (size_t shY = 0; shY < s.y(); ++shY) {
            for (size_t shZ = 0; shZ < s.z(); ++shZ) {
				auto posx = map<float>([=](float i) { return shX * 2 + i; }, posX);
				auto posy = map<float>([=](float i) { return shY * 2 + i; }, posY);
				auto posz = map<float>([=](float i) { return shZ * 2 + i; }, posZ);
                for (auto i = 0; i < size; i++) {
                    set.insert(QVector3D(posx[i], posy[i], posz[i]));
				}
			}
		}
	}
    std::vector<int> levels(set.size());
    auto it = set.begin();
    for(size_t i = 0; i < levels.size(); ++i, ++it) {
        levels[i] = -(static_cast<int>((*it).x()) + static_cast<int>((*it).y()) + static_cast<int>((*it).z()));
    }
    std::unordered_set<QVector3D, atom::Hash> setRes;
    for (auto& elem : set) {
        setRes.insert(elem * len);
    }
    return std::pair<atom::AtomSet, std::vector<int>> (atom::AtomSet(setRes.begin(), setRes.end()), levels);
}
