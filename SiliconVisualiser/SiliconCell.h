#pragma once
#include <QtDataVisualization\q3dscatter.h>
#include <QtDataVisualization\qabstract3dgraph.h>

#include "AtomSet.h"

class SiliconSell {
public:
	SiliconSell(QtDataVisualization::Q3DScatter* graph, const float atomScaling = 0.05f);

	~SiliconSell() = default;
	
	void setScale(float scale) const {
		m_atom->setItemSize(scale);
	}
	
	void init();
	
	void generateData(const QVector3D& scale, const float len = 4.0);
	
	void map(const QVector3D& change);

	const QVector3D& scale() const{
		return m_scale;
	}
private:
	void update() const;
	
private:
	QtDataVisualization::Q3DScatter* m_graph;
	static const size_t size = 18;
	QtDataVisualization::QScatter3DSeries* m_atom;
	QtDataVisualization::QScatterDataArray* m_data;
	atom::AtomSet m_setCoordAtoms;
	QVector3D m_scale;
};