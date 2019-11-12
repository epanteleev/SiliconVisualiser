#include "SiliconCell.h"
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dgraph.h>
#include <QtDataVisualization/qcustom3ditem.h>
#include <Qt3DRender/QMesh>
#include <memory>
#include <cmath>
#include "CellGenerator.h"

const double pi = 3.14159265359;

using namespace  QtDataVisualization;

SiliconSell::SiliconSell(QtDataVisualization::Q3DScatter* graph, const float atomScaling):
	m_atom(new QtDataVisualization::QScatter3DSeries),
	m_data(new QtDataVisualization::QScatterDataArray),
	m_graph(graph),
	m_scale(QVector3D(1.0f,1.0f,1.0f))
{
	m_atom->setItemSize(atomScaling);
}

void SiliconSell::init() {
	using namespace Qt3DRender;
	

    //					set.insert(QVector3D(posx[i] * len, posy[i] * len, posz[i] * len));
	m_atom->setMesh(QAbstract3DSeries::MeshUserDefined);
	
	m_atom->setUserDefinedMesh(QStringLiteral(":/SiliconVisualiser/Resources/largesphere.obj"));

	QLinearGradient fieldGradient(0, 0, 16, 1024);
	fieldGradient.setColorAt(0.0, Qt::black);
	fieldGradient.setColorAt(1.0, Qt::white);
	m_atom->setBaseGradient(fieldGradient);
	m_atom->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

	m_graph->addSeries(m_atom);
}

void SiliconSell::update() const {
    if (m_setCoordAtomsNew.size() != m_data->size()) {
        m_data->resize(m_setCoordAtomsNew.size());
	}
    auto v = m_setCoordAtomsNew.begin();
	for (auto i = m_data->begin(); i != m_data->end(); ++i, ++v) {
		i->setPosition(*v);
	}
	
	if (m_graph->selectedSeries() == m_atom) {
		m_graph->clearSelection();
	}
    m_atom->dataProxy()->resetArray(m_data);
}

QVector3D SiliconSell::getNormShift(const OscilationT &t)
{
    QVector3D res;
    switch (t) {
    case OscilationT::acousticLongitudinal :
        res = QVector3D(1, 1, 1);
        break;
    case OscilationT::opticalLongitudinal :
        res = QVector3D(1, 1, 1);
        break;
    case OscilationT::acousticTransverse :
        res = QVector3D(-1, 1, 0);
        break;
    case OscilationT::opticalTransverse :
        res = QVector3D(-1, 1, 0);
        break;
    }
    res.normalize();
    return res;
}

void SiliconSell::oscilation(const double q, const double a, const OscilationT &t)
{
    QVector3D shift = getNormShift(t);
    if (t == OscilationT::acousticTransverse || t == OscilationT::acousticLongitudinal) {
        for (int i = 0; i < m_setCoordAtoms.size(); ++i) {
            m_setCoordAtomsNew[i] = m_setCoordAtoms[i] + a * std::cos(pi * q * m_levels[i]) * shift;
        }
    }
    if (t == OscilationT::opticalTransverse || t == OscilationT::opticalLongitudinal) {
        for (int i = 0; i < m_setCoordAtoms.size(); ++i) {
            if (m_levels[i] % 2 == 0) {
                m_setCoordAtomsNew[i] = m_setCoordAtoms[i] + a * std::cos(pi * q * m_levels[i]) * shift;
            } else {
                m_setCoordAtomsNew[i] = m_setCoordAtoms[i] - a * std::cos(pi * q * m_levels[i]) * shift;
            }
        }
    }
    update();
}

void SiliconSell::generateData(const QVector3D& scale, const float len) {
	m_scale = scale;
    m_setCoordsAndLevels = CellGenerator::initialCubeCell(scale, len);
    m_setCoordAtomsNew = m_setCoordAtoms;
	update();
}
