#pragma once
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dgraph.h>

#include "AtomSet.h"

enum class OscilationT{acousticTransverse, acousticLongitudinal, opticalTransverse, opticalLongitudinal};

class SiliconSell {
public:
	SiliconSell(QtDataVisualization::Q3DScatter* graph, const float atomScaling = 0.05f);

	~SiliconSell() = default;
	
	void setScale(float scale) const {
		m_atom->setItemSize(scale);
	}
	
	void init();
	
	void generateData(const QVector3D& scale, const float len = 4.0);

    void oscilation(const double q, const double a, const OscilationT& t);

	const QVector3D& scale() const{
		return m_scale;
	}
private:
	void update() const;
    QVector3D getNormShift(const OscilationT& t);

private:
	QtDataVisualization::Q3DScatter* m_graph;
	static const size_t size = 18;
	QtDataVisualization::QScatter3DSeries* m_atom;
	QtDataVisualization::QScatterDataArray* m_data;

    // Ура!! Говнокод!!
    std::pair<atom::AtomSet, std::vector<int>> m_setCoordsAndLevels;
    #define m_setCoordAtoms (m_setCoordsAndLevels.first)
    #define m_levels (m_setCoordsAndLevels.second)
    atom::AtomSet m_setCoordAtomsNew;
	QVector3D m_scale;

};
