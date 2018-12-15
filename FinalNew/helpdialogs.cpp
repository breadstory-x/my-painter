#include "helpdialogs.h"
#include "ui_helpdialogs.h"

HelpDialogs::HelpDialogs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialogs)
{
    ui->setupUi(this);
}

HelpDialogs::~HelpDialogs()
{
    delete ui;
}
