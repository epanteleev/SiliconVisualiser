#pragma once
#include "SiliconCell.h"

#define VERSION "0.1.1"

class Settings {
public:
	Settings() = default;
	virtual ~Settings() = default;
};

class SettingsSizeScatter final : public Settings  {
public:
    SettingsSizeScatter(float& range, SiliconCell* cell, QtDataVisualization::Q3DScatter* graph):
		m_graph(graph),
		m_cell(cell),
		m_range(range)
	{
		
	}
	
	const QtDataVisualization::Q3DScatter* m_graph;
    SiliconCell* m_cell{};
	float& m_range;
};

class SettingsNone final : public Settings {
    //None
};
