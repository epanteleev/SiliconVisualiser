#pragma once

#include <QtGui/QScreen>

#include "ui_GuiApplication.h"
#include <QtDataVisualization/q3dscatter.h>
#include <QTimer>

#include "SiliconCell.h"
#include  "AbstractDialog.h"
#include "DialogSizeScatter.h"

class Application : public QMainWindow {
Q_OBJECT

public:
	Application(QWidget* parent = Q_NULLPTR);
	~Application();

private:
	void drawInit();
	void setAction();

public slots:
	void createDialog(const AbstractDialogFabric& fabric, const Settings& set);

private slots:
    void oscillation();
	void toggleRotation();

private:
	float m_verticalRange = 7.0f;

    OscilationT oscilT = OscilationT::acousticLongitudinal;

	SiliconSell* m_cell{};
	QtDataVisualization::Q3DScatter* m_graph;

	QTimer m_rotationTimer;
	Ui::GuiApplicationClass ui;
	unsigned m_angle{};

	AbstractDialog* active{};
};
