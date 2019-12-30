#pragma once

#include <QDialog>
#include "AbstractDialog.h"

namespace Ui {
class WelcomeDialog;
}

class DialogWelcome : public AbstractDialog {
    Q_OBJECT

public:
    DialogWelcome(const Settings& set, QWidget* parent = Q_NULLPTR);
    ~DialogWelcome();

private:
    Ui::WelcomeDialog *ui;
};


class DialogWelcomeFabric : public AbstractDialogFabric {
public:
    AbstractDialog* build(QWidget* parent, const Settings& set) const override {
        return new DialogWelcome(set, parent);
    }
};
