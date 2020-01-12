#pragma once
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dgraph.h>

#include "AtomSet.h"

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

    const atom::CellProperty property(){
        return m_setCoordsAndLevels.property().clone();
    }

    void setProperty(const atom::CellProperty& property) {
        m_setCoordsAndLevels.setProperty(property);
    }

private:
    void updatePosition(const atom::AtomSet& setCoordAtomsNew);
    QVector3D getNormShift(const atom::OscilationT& t);

private:
    QtDataVisualization::Q3DScatter* m_graph{};
    QtDataVisualization::QScatter3DSeries* m_atom{};
    QtDataVisualization::QScatterDataArray* m_data{};
    float m_distanceBetweenAtoms = 5.4307f;
    atom::Cell m_setCoordsAndLevels;
    atom::AtomSet m_originalSetCoordAtom;
};
