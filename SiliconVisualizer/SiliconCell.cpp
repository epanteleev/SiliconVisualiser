#include "SiliconCell.h"
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dgraph.h>
#include <QtDataVisualization/qcustom3ditem.h>
#include <Qt3DRender/QMesh>
#include <memory>

#include "CellGenerator.h"

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
	if (m_setCoordAtoms.size() != m_data->size()) {
		m_data->resize(m_setCoordAtoms.size());
	}
	auto v = m_setCoordAtoms.begin();
	for (auto i = m_data->begin(); i != m_data->end(); ++i, ++v) {
		i->setPosition(*v);
	}
	
	if (m_graph->selectedSeries() == m_atom) {
		m_graph->clearSelection();
	}
	m_atom->dataProxy()->resetArray(m_data);
}

void SiliconSell::map(const QVector3D& change) {
	//Todo
	m_setCoordAtoms = atom::map([=](QVector3D p) { return change + p; }, m_setCoordAtoms);
	update();
}

void SiliconSell::generateData(const QVector3D& scale, const float len) {
	m_scale = scale;
	m_setCoordAtoms = CellGenerator::initialCubeCell(scale, len);
	update();
}
