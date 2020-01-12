#include "DialogSizeScatter.h"

DialogSizeScatter::DialogSizeScatter(const Settings& set, QWidget* parent):
	AbstractDialog(parent)
{
    m_set = static_cast<const SettingsSizeScatter*>(&set);
	m_backupSizeItem = m_set->m_graph->seriesList().first()->itemSize();

    m_backupProperty = m_set->m_cell->property();
	ui.setupUi(this);

	connect(ui.applyButton, &QPushButton::released, this, &DialogSizeScatter::apply);
    connect(ui.cancelButton, &QPushButton::released, this, &DialogSizeScatter::cancel);
	
    connect(ui.rangeSlider, &QSlider::sliderReleased, this, &DialogSizeScatter::updateScale);
	
    connect(ui.xSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCellShape()));
    connect(ui.zSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCellShape()));
    connect(ui.ySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCellShape()));

    connect(ui.amplitudeSlider, &QSlider::sliderReleased, this, &DialogSizeScatter::updatePhysParams);
    connect(ui.qSlider, &QSlider::sliderReleased, this, &DialogSizeScatter::updatePhysParams);
    connect(ui.freqSlider, &QSlider::sliderReleased, this, &DialogSizeScatter::updatePhysParams);

    connect(ui.amplitudeSlider, SIGNAL(valueChanged(int)), this, SLOT(changedSliders()));
    connect(ui.qSlider, SIGNAL(valueChanged(int)), this, SLOT(changedSliders()));
    connect(ui.freqSlider, SIGNAL(valueChanged(int)), this, SLOT(changedSliders()));

    connect(ui.optical, SIGNAL(toggled(bool)), this, SLOT(updatePhysParams()));
    connect(ui.acoustic, SIGNAL(toggled(bool)), this, SLOT(updatePhysParams()));
    connect(ui.longitudinal, SIGNAL(toggled(bool)), this, SLOT(updatePhysParams()));
    connect(ui.transverse, SIGNAL(toggled(bool)), this, SLOT(updatePhysParams()));

    //initiated

	ui.rangeSlider->setValue(m_set->m_range);
    ui.amplitudeSlider->setValue(m_backupProperty.m_ampl * 20);
    ui.qSlider->setValue(m_backupProperty.m_q);
    ui.freqSlider->setValue(m_backupProperty.m_freq * 10);
    const auto spinValue = m_backupProperty.m_scale;
    ui.xSpinBox->setValue(spinValue.x());
    ui.ySpinBox->setValue(spinValue.y());
    ui.zSpinBox->setValue(spinValue.z());

	m_prev = m_set->m_range;

    using namespace atom;
    on_acoustic_toggled(m_backupProperty.m_oscilT == OscilationT::acousticTransverse ||
                        m_backupProperty.m_oscilT == OscilationT::acousticLongitudinal);
    on_longitudinal_toggled(m_backupProperty.m_oscilT == OscilationT::acousticLongitudinal ||
                            m_backupProperty.m_oscilT == OscilationT::opticalLongitudinal);

    changedSliders();
}

void DialogSizeScatter::updateScale() {
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

void DialogSizeScatter::updateCellShape() {
    QVector3D vec;
    vec.setX(ui.xSpinBox->value());
    vec.setY(ui.ySpinBox->value());
    vec.setZ(ui.zSpinBox->value());
    m_set->m_cell->generateData(vec);
}

void  DialogSizeScatter::changedSliders() {
    ui.amplitudeNumber->display(QString::number(ui.amplitudeSlider->value() / 20.) + QString(" A"));
    ui.qNumber->display(ui.qSlider->value());
    ui.freqNumber->display(ui.freqSlider->value() / 10.);
}

void DialogSizeScatter::updatePhysParams() {
    changedSliders();
    atom::CellProperty set;
    set.m_oscilT = getOscilT();
    set.m_ampl = ui.amplitudeSlider->value() / 20.0;
    set.m_q = ui.qSlider->value();
    set.m_freq = ui.freqSlider->value() / 10.0;
    m_set->m_cell->setProperty(set);
    updateCellShape();
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
    m_set->m_cell->generateData(m_backupProperty.m_scale);

    m_set->m_cell->setProperty(m_backupProperty);
	this->close();
}

void DialogSizeScatter::on_acoustic_toggled(bool checked) {
    if (checked) {
        ui.acoustic->setCheckState(Qt::CheckState::Checked);
        ui.optical->setCheckState(Qt::CheckState::Unchecked);
    } else {
        ui.acoustic->setCheckState(Qt::CheckState::Unchecked);
        ui.optical->setCheckState(Qt::CheckState::Checked);
    }

}

void DialogSizeScatter::on_optical_toggled(bool checked) {
    if (checked) {
        ui.acoustic->setCheckState(Qt::CheckState::Unchecked);
        ui.optical->setCheckState(Qt::CheckState::Checked);
    } else {
        ui.acoustic->setCheckState(Qt::CheckState::Checked);
        ui.optical->setCheckState(Qt::CheckState::Unchecked);
    }
}

void DialogSizeScatter::on_transverse_toggled(bool checked) {
    if (checked) {
        ui.transverse->setCheckState(Qt::CheckState::Checked);
        ui.longitudinal->setCheckState(Qt::CheckState::Unchecked);
    } else {
        ui.transverse->setCheckState(Qt::CheckState::Unchecked);
        ui.longitudinal->setCheckState(Qt::CheckState::Checked);
    }
}

void DialogSizeScatter::on_longitudinal_toggled(bool checked) {
    if (checked) {
        ui.transverse->setCheckState(Qt::CheckState::Unchecked);
        ui.longitudinal->setCheckState(Qt::CheckState::Checked);
    } else {
        ui.transverse->setCheckState(Qt::CheckState::Checked);
        ui.longitudinal->setCheckState(Qt::CheckState::Unchecked);
    }
}

atom::OscilationT DialogSizeScatter::getOscilT() {
    using namespace atom;
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
