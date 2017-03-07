#ifndef DEMO_H
#define DEMO_H

#include <QWidget>
#include<objects.h>

namespace Ui {
class Demo;
}

class Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Demo(QWidget *parent = 0);
    ~Demo();


private slots:
    void on_CalcButton_clicked();

private:
    Ui::Demo *ui;

    bool propOK(std::string name, double staThru, double dyThru, double etaProp, double etaTol);
};

void Trim(std::string &str);


#endif // DEMO_H
