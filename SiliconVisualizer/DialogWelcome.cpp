#include "DialogWelcome.h"
#include "ui_DialogWelcome.h"
#include <QPixmap>

DialogWelcome::DialogWelcome(const Settings& set, QWidget* parent) :
    AbstractDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
}

DialogWelcome::~DialogWelcome() {
    delete ui;
}
