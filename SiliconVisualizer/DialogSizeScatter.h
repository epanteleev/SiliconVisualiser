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
    void refreshType();
    void setDown();

private:
	const SettingsSizeScatter* m_set;
	Ui::DialogSizeScatter ui{};
	float m_backupSizeItem;
	QVector3D m_backupScale;
    OscilationType m_backupType;
    float m_prevRange;

};

class DialogSizeScatterFabric : public AbstractDialogFabric {
public:
	AbstractDialog* build(QWidget* parent, const Settings& set) const override {
		return new DialogSizeScatter(set, parent);
	}
};
