#pragma once

#include "AbstractDialog.h"
#include "ui_DialogSizeScatter.h"
#include "Settings.h"

class DialogSizeScatter : public AbstractDialog {
	Q_OBJECT

public:
	DialogSizeScatter(const Settings& set, QWidget* parent = Q_NULLPTR);

private:
	enum TypeScale{
		X = 0,
		Y,
		Z
	};
private slots:
	void update();
	void updateCell();
	void apply();
	void cancel();

    void on_acoustic_toggled(bool checked);

    void on_optical_toggled(bool checked);

    void on_transverse_toggled(bool checked);

    void on_longitudinal_toggled(bool checked);

private:
	const SettingsSizeScatter* m_set;
	Ui::DialogSizeScatter ui{};
	float m_backupSizeItem;
	QVector3D m_backupScale;
    OscilationT m_backupOscilT;
	float m_prev;
    double m_amplitude;
    OscilationT getOscilT();
};

class DialogSizeScatterFabric : public AbstractDialogFabric {
public:
	AbstractDialog* build(QWidget* parent, const Settings& set) const override {
		return new DialogSizeScatter(set, parent);
	}
};
