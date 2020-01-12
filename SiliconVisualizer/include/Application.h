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
    void init();
    void setAction();

public slots:
	void createDialog(const AbstractDialogFabric& fabric, const Settings& set);

private slots:
    void oscillation();
	void toggleRotation();

private:
    float m_verticalRange = 16.0f;

    SiliconCell* m_cell{};
	QtDataVisualization::Q3DScatter* m_graph;

	QTimer m_rotationTimer;
	Ui::GuiApplicationClass ui;
	unsigned m_angle{};
    QHBoxLayout* m_box{};
    AbstractDialog* m_activeDialog{};
};
