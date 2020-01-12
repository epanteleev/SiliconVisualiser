#pragma once

#include "AbstractDialog.h"
#include "ui_DialogSizeScatter.h"
#include "Settings.h"

class DialogSizeScatter : public AbstractDialog {
	Q_OBJECT

public:
	DialogSizeScatter(const Settings& set, QWidget* parent = Q_NULLPTR);

private slots:
    void updateScale();
    void updateCellShape();
    void updatePhysParams();
	void apply();
	void cancel();
    void changedSliders();
    void on_acoustic_toggled(bool checked);

    void on_optical_toggled(bool checked);

    void on_transverse_toggled(bool checked);

    void on_longitudinal_toggled(bool checked);

private:
    atom::OscilationT getOscilT();

private:
	const SettingsSizeScatter* m_set;
	Ui::DialogSizeScatter ui{};
	float m_backupSizeItem;
	float m_prev;
    atom::CellProperty m_backupProperty;

};

class DialogSizeScatterFabric : public AbstractDialogFabric {
public:
	AbstractDialog* build(QWidget* parent, const Settings& set) const override {
		return new DialogSizeScatter(set, parent);
	}
};
