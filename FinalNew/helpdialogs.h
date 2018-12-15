#ifndef HELPDIALOGS_H
#define HELPDIALOGS_H

#include <QDialog>

namespace Ui {
class HelpDialogs;
}

class HelpDialogs : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialogs(QWidget *parent = 0);
    ~HelpDialogs();

private:
    Ui::HelpDialogs *ui;
};

#endif // HELPDIALOGS_H
