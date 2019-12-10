#include "WelcomeDialog.h"
#include "ui_WelcomeDialog.h"
#include <QPixmap>

WelcomeDialog::WelcomeDialog(const Settings& set, QWidget* parent) :
    AbstractDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
}

WelcomeDialog::~WelcomeDialog() {
    delete ui;
}
