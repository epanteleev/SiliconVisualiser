#include "DialogSizeScatter.h"

DialogSizeScatter::DialogSizeScatter(const Settings& set, QWidget* parent):
	AbstractDialog(parent)
{
	m_set = dynamic_cast<const SettingsSizeScatter*>(&set);
	m_backupSizeItem = m_set->m_graph->seriesList().first()->itemSize();
	m_backupScale = m_set->m_cell->scale();
    m_backupOscilT = m_set->m_cell->getOscilT();
	ui.setupUi(this);

	connect(ui.applyButton, &QPushButton::released, this, &DialogSizeScatter::apply);
    connect(ui.cancelButton, &QPushButton::released, this, &DialogSizeScatter::cancel);
	
	connect(ui.rangeSlider, &QSlider::sliderReleased, this, &DialogSizeScatter::update);
	
	connect(ui.xSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCell()));
	connect(ui.zSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCell()));
    connect(ui.ySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCell()));

    connect(ui.optical, SIGNAL(toggled(bool)), this, SLOT(updateCell()));
    connect(ui.acoustic, SIGNAL(toggled(bool)), this, SLOT(updateCell()));
    connect(ui.longitudinal, SIGNAL(toggled(bool)), this, SLOT(updateCell()));
    connect(ui.transverse, SIGNAL(toggled(bool)), this, SLOT(updateCell()));

	ui.rangeSlider->setValue(m_set->m_range);
	
    const auto spinValue = m_set->m_cell->scale();
    ui.xSpinBox->setValue(spinValue.x());
    ui.ySpinBox->setValue(spinValue.y());
    ui.zSpinBox->setValue(spinValue.z());

	m_prev = m_set->m_range;

    on_acoustic_toggled(m_backupOscilT == OscilationT::acousticTransverse ||
                        m_backupOscilT == OscilationT::acousticLongitudinal);
    on_longitudinal_toggled(m_backupOscilT == OscilationT::acousticLongitudinal ||
                            m_backupOscilT == OscilationT::opticalLongitudinal);
}

void DialogSizeScatter::update() {
	const auto s = m_set->m_graph;
	const auto verticalRange = ui.rangeSlider->value();
	const auto horizontalRange = verticalRange * 2;
	s->axisX()->setRange(-horizontalRange, horizontalRange);
	s->axisY()->setRange(-verticalRange, verticalRange);
	s->axisZ()->setRange(-horizontalRange, horizontalRange);

	const auto size = s->seriesList().first()->itemSize();
	const auto newSize = (m_prev * size) / float(verticalRange);
	
	qDebug() << "DialogSizeScatter::update new size " << newSize;
	s->seriesList().first()->setItemSize(newSize);
	
	m_prev = verticalRange;
}

void DialogSizeScatter::updateCell() {
	QVector3D vec;
	vec.setX(ui.xSpinBox->value());
	vec.setY(ui.ySpinBox->value());
	vec.setZ(ui.zSpinBox->value());
    m_set->m_cell->generateData(vec);
    m_set->m_cell->setOscilT(getOscilT());
}

void DialogSizeScatter::apply() {
	m_set->m_range = ui.rangeSlider->value();
	this->close();
}

void DialogSizeScatter::cancel() {
	const auto s = m_set->m_graph;
	
	const auto rng = m_set->m_range * 2;
	s->axisX()->setRange(-rng, rng);
	s->axisY()->setRange(-m_set->m_range, m_set->m_range);
	s->axisZ()->setRange(-rng, rng);
	s->seriesList().first()->setItemSize(m_backupSizeItem);
    m_set->m_cell->setOscilT(m_backupOscilT);
	m_set->m_cell->generateData(m_backupScale);
	this->close();
}

void DialogSizeScatter::on_acoustic_toggled(bool checked)
{
    if (checked) {
        ui.acoustic->setCheckState(Qt::CheckState::Checked);
        ui.optical->setCheckState(Qt::CheckState::Unchecked);
    } else {
        ui.acoustic->setCheckState(Qt::CheckState::Unchecked);
        ui.optical->setCheckState(Qt::CheckState::Checked);
    }

}

void DialogSizeScatter::on_optical_toggled(bool checked)
{
    if (checked) {
        ui.acoustic->setCheckState(Qt::CheckState::Unchecked);
        ui.optical->setCheckState(Qt::CheckState::Checked);
    } else {
        ui.acoustic->setCheckState(Qt::CheckState::Checked);
        ui.optical->setCheckState(Qt::CheckState::Unchecked);
    }
}

void DialogSizeScatter::on_transverse_toggled(bool checked)
{
    if (checked) {
        ui.transverse->setCheckState(Qt::CheckState::Checked);
        ui.longitudinal->setCheckState(Qt::CheckState::Unchecked);
    } else {
        ui.transverse->setCheckState(Qt::CheckState::Unchecked);
        ui.longitudinal->setCheckState(Qt::CheckState::Checked);
    }
}

void DialogSizeScatter::on_longitudinal_toggled(bool checked)
{
    if (checked) {
        ui.transverse->setCheckState(Qt::CheckState::Unchecked);
        ui.longitudinal->setCheckState(Qt::CheckState::Checked);
    } else {
        ui.transverse->setCheckState(Qt::CheckState::Checked);
        ui.longitudinal->setCheckState(Qt::CheckState::Unchecked);
    }
}

OscilationT DialogSizeScatter::getOscilT()
{
    if (ui.acoustic->checkState() == Qt::CheckState::Checked) {
        if (ui.transverse->checkState() == Qt::CheckState::Checked) {
            return OscilationT::acousticTransverse;
        } else {
            return OscilationT::acousticLongitudinal;
        }
    } else {
        if (ui.transverse->checkState() == Qt::CheckState::Checked) {
            return OscilationT::opticalTransverse;
        } else {
            return OscilationT::opticalLongitudinal;
        }
    }
}
