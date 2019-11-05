#pragma once
#include "SiliconCell.h"

class Settings {
public:
	Settings() = default;
	virtual ~Settings() = default;
};

class SettingsSizeScatter : public Settings  {
public:
	SettingsSizeScatter(float& range, SiliconSell* cell, QtDataVisualization::Q3DScatter* graph):
		m_graph(graph),
		m_cell(cell),
		m_range(range)
	{
		
	}
	
	const QtDataVisualization::Q3DScatter* m_graph;
	SiliconSell* m_cell{};
	float& m_range;
};