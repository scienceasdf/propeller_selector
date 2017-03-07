#ifndef REPORT_H
#define REPORT_H

#include <QWidget>
#include<vector>
#include<string>
#include<objects.h>

namespace Ui {
class report;
}

class report : public QWidget
{
    Q_OBJECT

public:
    explicit report(QWidget *parent = 0);
    ~report();

    std::vector<std::string> props;
    std::vector<double> thrust;
    std::vector<double> dynamicThrust;
    std::vector<double> etaProp;
    std::vector<double> etaTotal;
    std::vector<std::string> files;
    propulsion pro;

    void initShow();

private slots:
    void on_propBox_currentIndexChanged(int index);

private:
    Ui::report *ui;
};

#endif // REPORT_H
