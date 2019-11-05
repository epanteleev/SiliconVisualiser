#pragma once
#include <QDialog>
#include <q3dscatter.h>
#include "Settings.h"

class AbstractDialog : public QDialog {
	Q_OBJECT

public:
	AbstractDialog(QWidget* parent = Q_NULLPTR) :
		QDialog(parent) {
		
	}

	virtual ~AbstractDialog() = default;
	
private slots:
	void action();

};

class AbstractDialogFabric {
public:
	virtual ~AbstractDialogFabric() {}
	
	virtual AbstractDialog* build(QWidget* parent, const Settings& set) const = 0;
};
