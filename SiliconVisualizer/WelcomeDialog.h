#pragma once

#include <QDialog>
#include "AbstractDialog.h"

namespace Ui {
class WelcomeDialog;
}

class WelcomeDialog : public AbstractDialog {
    Q_OBJECT

public:
    WelcomeDialog(const Settings& set, QWidget* parent = Q_NULLPTR);
    ~WelcomeDialog();

private:
    Ui::WelcomeDialog *ui;
};


class DialogWelcomeFabric : public AbstractDialogFabric {
public:
    AbstractDialog* build(QWidget* parent, const Settings& set) const override {
        return new WelcomeDialog(set, parent);
    }
};
