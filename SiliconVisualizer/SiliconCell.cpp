#include "SiliconCell.h"
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dgraph.h>
#include <QtDataVisualization/qcustom3ditem.h>
#include <Qt3DRender/QMesh>
#include <memory>
#include <cmath>
#include "CellGenerator.h"

static const double pi = 3.14159265359;

using namespace  QtDataVisualization;

SiliconCell::SiliconCell(QtDataVisualization::Q3DScatter* graph, const float atomScaling):
	m_atom(new QtDataVisualization::QScatter3DSeries),
	m_data(new QtDataVisualization::QScatterDataArray),
	m_graph(graph),
	m_scale(QVector3D(1.0f,1.0f,1.0f))
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

void SiliconCell::update() {

    atom::AtomSet& setCoordAtomsNew = m_setCoordsAndLevels.second();

    if (setCoordAtomsNew.size() != m_data->size()) {
        m_data->resize(setCoordAtomsNew.size());
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

QVector3D SiliconCell::getNormShift(const OscilationT &t) {
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

OscilationT SiliconCell::getOscilT() const
{
    return oscilT;
}

void SiliconCell::setOscilT(const OscilationT &value)
{
    oscilT = value;
}

void SiliconCell::oscilation(const double q, const double a) {
    QVector3D shift = getNormShift(oscilT);
    size_t size = m_setCoordsAndLevels.second().size();
    atom::AtomSet& setCoordAtomsNew = m_setCoordsAndLevels.second();
    atom::AtomLevel& levels = m_setCoordsAndLevels.first();

    if (oscilT == OscilationT::acousticTransverse || oscilT == OscilationT::acousticLongitudinal) {
        for (size_t i = 0; i < size; ++i) {
            setCoordAtomsNew[i] = m_originalSetCoordAtom[i] + a * std::cos(pi * q * levels[i]) * shift;
        }
    } else if (oscilT == OscilationT::opticalTransverse || oscilT == OscilationT::opticalLongitudinal) {
        for (size_t i = 0; i < size; ++i) {
            if (levels[i] % 2 == 0) {
                setCoordAtomsNew[i] = m_originalSetCoordAtom[i] + a * std::cos(pi * q * levels[i]) * shift;
            } else {
                setCoordAtomsNew[i] = m_originalSetCoordAtom[i] - a * std::cos(pi * q * levels[i]) * shift;
            }
        }
    } else{
        qDebug()<<"error in SiliconSell::oscilation";
        std::terminate();
    }
    update();
}

void SiliconCell::generateData(const QVector3D& scale, const float len) {
	m_scale = scale;
    m_setCoordsAndLevels = CellGenerator::initialCubeCell(scale, len);
    m_originalSetCoordAtom = m_setCoordsAndLevels.second();
	update();
}
