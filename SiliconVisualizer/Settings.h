#pragma once
#include "SiliconCell.h"

class Settings {
public:
	Settings() = default;
	virtual ~Settings() = default;
};

class SettingsSizeScatter : public Settings  {
public:
    SettingsSizeScatter(float& range,OscilationType& type, SiliconSell* cell, QtDataVisualization::Q3DScatter* graph):
        m_type(type),
        m_graph(graph),
		m_cell(cell),
		m_range(range)
	{
		
	}
    OscilationType& m_type;
	const QtDataVisualization::Q3DScatter* m_graph;
	SiliconSell* m_cell{};
	float& m_range;
};
