#include "SiliconCell.h"
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dgraph.h>
#include <QtDataVisualization/qcustom3ditem.h>
#include <Qt3DRender/QMesh>
#include <memory>
#include <cmath>
#include "CellGenerator.h"

using namespace  QtDataVisualization;

SiliconCell::SiliconCell(QtDataVisualization::Q3DScatter* graph, const float atomScaling):
    m_graph(graph),
    m_atom(new QtDataVisualization::QScatter3DSeries),
    m_data(new QtDataVisualization::QScatterDataArray)
{
	m_atom->setItemSize(atomScaling);
}

void SiliconCell::init() {
	using namespace Qt3DRender;
	
	m_atom->setMesh(QAbstract3DSeries::MeshUserDefined);
	
	m_atom->setUserDefinedMesh(QStringLiteral(":/SiliconVisualiser/Resources/largesphere.obj"));

	QLinearGradient fieldGradient(0, 0, 16, 1024);
	fieldGradient.setColorAt(0.0, Qt::black);
	fieldGradient.setColorAt(1.0, Qt::white);
	m_atom->setBaseGradient(fieldGradient);
	m_atom->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
	m_graph->addSeries(m_atom);
}

void SiliconCell::updatePosition(const atom::AtomSet& setCoordAtomsNew) {

    if (setCoordAtomsNew.size() != static_cast<size_t>(m_data->size())) {
        m_data->resize(static_cast<int>(setCoordAtomsNew.size()));
	}
    auto v = setCoordAtomsNew.begin();
	for (auto i = m_data->begin(); i != m_data->end(); ++i, ++v) {
		i->setPosition(*v);
	}
	
	if (m_graph->selectedSeries() == m_atom) {
		m_graph->clearSelection();
	}
    m_atom->dataProxy()->resetArray(m_data);
}

QVector3D SiliconCell::getNormShift(const atom::OscilationT &t) {
    using namespace atom;
    QVector3D res;
    switch (t) {
    case OscilationT::acousticLongitudinal:
        res = QVector3D(1, 1, 1);
        break;
    case OscilationT::opticalLongitudinal:
        res = QVector3D(1, 1, 1);
        break;
    case OscilationT::acousticTransverse:
        res = QVector3D(-1, 1, 0);
        break;
    case OscilationT::opticalTransverse:
        res = QVector3D(-1, 1, 0);
        break;
    }
    res.normalize();
    return res;
}

void SiliconCell::oscilation(const double t) {
    using namespace atom;
    size_t size = m_setCoordsAndLevels.atomSet().size();
    atom::AtomSet& setCoordAtomsNew = m_setCoordsAndLevels.atomSet();
    atom::AtomLevel& levels = m_setCoordsAndLevels.levels();
    atom::CellProperty property = m_setCoordsAndLevels.property();
    QVector3D shift = getNormShift(property.m_oscilT);

    if (property.m_oscilT == OscilationT::acousticTransverse ||
            property.m_oscilT == OscilationT::acousticLongitudinal) {
        for (size_t i = 0; i < size; ++i) {
            setCoordAtomsNew[i] = m_originalSetCoordAtom[i] +
                    property.m_ampl * std::cos(property.m_q * levels[i] * m_distanceBetweenAtoms / std::sqrt(8.)
                                               + property.m_freq * t) * shift;
        }
    } else if (property.m_oscilT == OscilationT::opticalTransverse ||
               property.m_oscilT == OscilationT::opticalLongitudinal) {
        for (size_t i = 0; i < size; ++i) {
            if (levels[i] % 2 == 0) {
                setCoordAtomsNew[i] = m_originalSetCoordAtom[i] +
                        property.m_ampl * std::cos(property.m_q * levels[i] * m_distanceBetweenAtoms / std::sqrt(8.)
                                                   + property.m_freq * t) * shift;
            } else {
                setCoordAtomsNew[i] = m_originalSetCoordAtom[i] -
                        property.m_ampl * std::cos(property.m_q * levels[i] * m_distanceBetweenAtoms / std::sqrt(8.)
                                                   + property.m_freq * t) * shift;
            }
        }
    } else{
        qDebug()<<"error in SiliconSell::oscilation";
        std::terminate();
    }
    updatePosition(setCoordAtomsNew);
}

void SiliconCell::generateData(const QVector3D& scale) {
    auto p = property();
    p.m_scale = scale;
    m_setCoordsAndLevels = CellGenerator::initialCubeCell(scale, m_distanceBetweenAtoms / 2);
    m_setCoordsAndLevels.setProperty(p);
    m_originalSetCoordAtom = m_setCoordsAndLevels.atomSet();
    updatePosition(m_setCoordsAndLevels.atomSet());
}
