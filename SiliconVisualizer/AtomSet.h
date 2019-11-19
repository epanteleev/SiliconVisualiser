#pragma once
#include <unordered_set>
#include <QVector3D>
#include <functional>


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

    class AtomPair {
    public:
        AtomPair() = default;

        AtomPair(atom::AtomSet set, atom::AtomLevel levels) :
            m_set(set),
            m_levels(levels)
        {

        }

        AtomLevel& first() noexcept {
            return m_levels;
        }

        atom::AtomSet& second() noexcept {
            return m_set;
        }
    private:
        atom::AtomSet m_set{};
        AtomLevel m_levels{};
    };

	inline atom::AtomSet map(std::function<QVector3D(QVector3D)> f, const atom::AtomSet& pos) {
		std::unordered_set<QVector3D, Hash> ret;
		for (auto& i : pos) {
			ret.insert(f(i));
		}
		return atom::AtomSet(ret.begin(), ret.end());
	}

	template<typename Type>
	inline std::vector<Type> map(std::function<Type(Type)> f, const std::vector<Type>& pos) {
		std::vector<Type> ret;
		for (auto& i : pos) {
			ret.push_back(f(i));
		}
		return ret;
	}
}
