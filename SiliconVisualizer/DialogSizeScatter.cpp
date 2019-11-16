#include "DialogSizeScatter.h"

DialogSizeScatter::DialogSizeScatter(const Settings& set, QWidget* parent):
	AbstractDialog(parent)
{
	m_set = dynamic_cast<const SettingsSizeScatter*>(&set);
	m_backupSizeItem = m_set->m_graph->seriesList().first()->itemSize();
	m_backupScale = m_set->m_cell->scale();
    m_backupType = m_set->m_type;
    m_prevRange = m_set->m_range;
	ui.setupUi(this);

	connect(ui.applyButton, &QPushButton::released, this, &DialogSizeScatter::apply);
	connect(ui.cancelButton, &QPushButton::released, this, &DialogSizeScatter::cancel);
	
	connect(ui.rangeSlider, &QSlider::sliderReleased, this, &DialogSizeScatter::update);
	
	connect(ui.xSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCell()));
	connect(ui.zSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCell()));
	connect(ui.ySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCell()));

    connect(ui.opticalRadioButton, &QRadioButton::released, this, &DialogSizeScatter::refreshType);
    connect(ui.acousticRadioButton, &QRadioButton::released, this, &DialogSizeScatter::refreshType);
    connect(ui.transverseRadioButton, &QRadioButton::released, this, &DialogSizeScatter::refreshType);
    connect(ui.longitudinalRadioButton, &QRadioButton::released, this, &DialogSizeScatter::refreshType);

    //set value
	ui.rangeSlider->setValue(m_set->m_range);
	
    const auto spinValue = m_set->m_cell->scale();
    ui.xSpinBox->setValue(spinValue.x());
    ui.ySpinBox->setValue(spinValue.y());
    ui.zSpinBox->setValue(spinValue.z());
    setDown();

}

void DialogSizeScatter::setDown() {
    const auto type = m_set->m_type;
    if(type == OscilationType::OpticalLongitudinal) {
        ui.opticalRadioButton->setChecked(true);
        ui.longitudinalRadioButton->setChecked(true);
    } else if (type == OscilationType::OpticalTransverse) {
        ui.opticalRadioButton->setChecked(true);
        ui.transverseRadioButton->setChecked(true);
    } else if (type == OscilationType::AcousticLongitudinal) {
        ui.acousticRadioButton->setChecked(true);
        ui.longitudinalRadioButton->setChecked(true);
    } else if (type == OscilationType::AcousticTransverse) {
        ui.acousticRadioButton->setChecked(true);
        ui.transverseRadioButton->setChecked(true);
    } else {
        qDebug()<<"error in DialogSizeScatter::refreshType";
        std::terminate();
    }
}

void DialogSizeScatter::update() {
	const auto s = m_set->m_graph;
	const auto verticalRange = ui.rangeSlider->value();
	const auto horizontalRange = verticalRange * 2;
	s->axisX()->setRange(-horizontalRange, horizontalRange);
	s->axisY()->setRange(-verticalRange, verticalRange);
	s->axisZ()->setRange(-horizontalRange, horizontalRange);

	const auto size = s->seriesList().first()->itemSize();
    const auto newSize = (m_prevRange * size) / float(verticalRange);
	
	qDebug() << "DialogSizeScatter::update new size " << newSize;
	s->seriesList().first()->setItemSize(newSize);
	
    m_prevRange = verticalRange;
}

void DialogSizeScatter::updateCell() {
	QVector3D vec;
	vec.setX(ui.xSpinBox->value());
	vec.setY(ui.ySpinBox->value());
	vec.setZ(ui.zSpinBox->value());
	m_set->m_cell->generateData(vec);
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
	m_set->m_cell->generateData(m_backupScale);
    m_set->m_type = m_backupType;
	this->close();
}

void DialogSizeScatter::refreshType() {
    bool opt = ui.opticalRadioButton->isChecked();
    bool acoust = ui.acousticRadioButton->isChecked();
    bool longtd = ui.longitudinalRadioButton->isChecked();
    bool transv = ui.transverseRadioButton->isChecked();

    if(opt && longtd){
        m_set->m_type = OscilationType::OpticalLongitudinal;
    } else if (opt && transv) {
        m_set->m_type = OscilationType::OpticalTransverse;
    } else if (acoust && longtd) {
        m_set->m_type = OscilationType::AcousticLongitudinal;
    } else if (acoust && transv) {
        m_set->m_type = OscilationType::AcousticTransverse;
    } else {
        qDebug()<<"error in DialogSizeScatter::refreshType";
        std::terminate();
    }
}
