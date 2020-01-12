#pragma once
#include <unordered_set>
#include <QVector3D>
#include <functional>
#include <memory>

#include "CellProperty.h"

namespace atom {
	struct Hash {
		size_t operator() (const QVector3D& vec) const {
            return static_cast<size_t>(vec.x()) * 300 +
                static_cast<size_t>(vec.y()) * 200 +
				static_cast<size_t>(vec.z());
		}
	};

	using AtomSet = std::vector<QVector3D>;
    using AtomLevel = std::vector<int>;


    class Cell {
    public:
        Cell() = default;

        Cell(atom::AtomSet set, atom::AtomLevel levels) :
            m_set(set),
            m_levels(levels)
        {

        }

        inline AtomLevel& levels() noexcept {
            return m_levels;
        }

        inline atom::AtomSet& atomSet() noexcept {
            return m_set;
        }

        inline atom::CellProperty& property() {
            return m_property;
        }

        inline void setProperty(const CellProperty& property) {
            m_property.copy(property);
        }
    private:
        atom::AtomSet m_set{};
        AtomLevel m_levels{};
        CellProperty m_property{};
    };

	inline atom::AtomSet map(std::function<QVector3D(QVector3D)> f, const atom::AtomSet& pos) {
		std::unordered_set<QVector3D, Hash> ret;
		for (auto& i : pos) {
            ret.emplace(f(i));
		}
		return atom::AtomSet(ret.begin(), ret.end());
	}

	template<typename Type>
	inline std::vector<Type> map(std::function<Type(Type)> f, const std::vector<Type>& pos) {
		std::vector<Type> ret;
		for (auto& i : pos) {
            ret.emplace_back(f(i));
		}
		return ret;
	}
}
