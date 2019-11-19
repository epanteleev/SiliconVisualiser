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

class SiliconCell {
public:
    SiliconCell(QtDataVisualization::Q3DScatter* graph, const float atomScaling = 0.05f);

    ~SiliconCell() = default;
	
	void setScale(float scale) const {
		m_atom->setItemSize(scale);
	}
	
	void init();
	
    void generateData(const QVector3D& scale);

    void oscilation(const double t);

    const QVector3D& scale() const {
		return m_scale;
	}

    void setOscilT(const OscilationT &value);

    OscilationT getOscilT() const;

    double getAmpl() const;
    void setAmpl(double value);

    double getQ() const;
    void setQ(double value);

    double getFreq() const;
    void setFreq(double value);

private:
    void update();
    QVector3D getNormShift(const OscilationT& t);

private:
	QtDataVisualization::Q3DScatter* m_graph;
	static const size_t size = 18;
	QtDataVisualization::QScatter3DSeries* m_atom;
	QtDataVisualization::QScatterDataArray* m_data;
    float m_distanceBetweenAtoms = 5.4307f;
    atom::AtomPair m_setCoordsAndLevels;
    atom::AtomSet m_originalSetCoordAtom;
	QVector3D m_scale;
    double m_ampl = 0.1f;
    double m_q = 1.;
    double m_freq = 1.;
    OscilationT oscilT = OscilationT::acousticLongitudinal;
};
