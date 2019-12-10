#include "Application.h"
#include <cmath>

#include "WelcomeDialog.h"
#include <qcustom3ditem.h>

#include "SiliconCell.h"
#include <QtWidgets/qmessagebox.h>
#include "DialogSizeScatter.h"

using namespace QtDataVisualization;

Application::Application(QWidget* parent)
	: QMainWindow(parent),
	  m_graph(new Q3DScatter())
{
    m_cell = new SiliconCell(m_graph, 0.015f);
	ui.setupUi(this);
	drawInit();
	toggleRotation();
    setAction();
    showWelcomeWindow();
}

void Application::showWelcomeWindow() {
    createDialog(DialogWelcomeFabric(), SettingsNone());
}

Application::~Application() {
	delete m_graph;
	delete m_cell;
}

void Application::drawInit() {

	QWidget* container = QWidget::createWindowContainer(m_graph, this);

	auto box = new QHBoxLayout(ui.drawWidget);
	box->addWidget(container);

	if (!m_graph->hasContext()) {
		QMessageBox msgBox;
		msgBox.setText("Couldn't initialize the OpenGL context.");
		msgBox.exec();
		close();
		return;
	}


	m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
	m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetIsometricRight);
    m_graph->activeTheme()->setType(Q3DTheme::ThemeRetro);
	m_graph->activeTheme()->setLabelBorderEnabled(true);
	m_graph->activeTheme()->setLabelTextColor(Qt::lightGray);
	m_graph->activeTheme()->setFont(QFont("Arial Black", 30));

    m_cell->init();
    m_cell->generateData(QVector3D(5,5,5));


	const auto horizontalRange = m_verticalRange * 2;
	m_graph->axisX()->setRange(-horizontalRange, horizontalRange);
	m_graph->axisY()->setRange(-m_verticalRange, m_verticalRange);
	m_graph->axisZ()->setRange(-horizontalRange, horizontalRange);
    m_graph->axisX()->setTitle(tr("X"));
    m_graph->axisY()->setTitle(tr("Y"));
    m_graph->axisZ()->setTitle(tr("Z"));

    connect(&m_rotationTimer, &QTimer::timeout, this, &Application::oscillation);
}

void Application::oscillation() {
    m_angle += 1;
    m_cell->oscilation(m_angle * 0.1);
}

void Application::toggleRotation() {
	qDebug() << " called Application::toggleRotation";
	if (m_rotationTimer.isActive()) {
		m_rotationTimer.stop();
	}else{
		m_rotationTimer.start(15);
	}
}

void Application::setAction() {

    const auto viewMenu = ui.menuBar->addMenu(tr("&View"));
	
    viewMenu->addAction(tr("&Settings"), this, [=]() { createDialog(DialogSizeScatterFabric(),
		SettingsSizeScatter(m_verticalRange, m_cell, m_graph)); });

    const auto refMenu = ui.menuBar->addMenu(tr("&Reference"));

    refMenu->addAction(tr("&Actions"), this,
                       [=]() { createDialog(DialogWelcomeFabric(), SettingsNone()); });
}

void Application::createDialog(const AbstractDialogFabric& fabric, const Settings& set) {
    if (m_active == nullptr) {
        m_active = fabric.build(this, set);
	}
    if(! m_active->isVisible()) {
        m_active->show();
        m_active->exec();
        delete m_active;
        m_active = nullptr;
	}
}
