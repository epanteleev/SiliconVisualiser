#pragma once
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dgraph.h>

#include "AtomSet.h"

enum class OscilationT {
    acousticTransverse = 0,
    acousticLongitudinal,
    opticalTransverse,
    opticalLongitudinal
};

class SiliconSell {
public:
	SiliconSell(QtDataVisualization::Q3DScatter* graph, const float atomScaling = 0.05f);

	~SiliconSell() = default;
	
	void setScale(float scale) const {
		m_atom->setItemSize(scale);
	}
	
	void init();
	
    void generateData(const QVector3D& scale, const float len = 5.0);

    void oscilation(const double q, const double a, const OscilationT& type);

    const QVector3D& scale() const {
		return m_scale;
	}

private:
    void update();
    QVector3D getNormShift(const OscilationT& t);

private:
	QtDataVisualization::Q3DScatter* m_graph;
	static const size_t size = 18;
	QtDataVisualization::QScatter3DSeries* m_atom;
	QtDataVisualization::QScatterDataArray* m_data;

    atom::AtomPair m_setCoordsAndLevels;
    atom::AtomSet m_originalSetCoordAtom;
	QVector3D m_scale;

};
