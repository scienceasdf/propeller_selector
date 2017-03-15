#ifndef REPORT_H
#define REPORT_H

#include <QWidget>
#include<objects.h>
#include<map>
#include<tuple>

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
    std::vector<std::string> files;
    propeller pro;


    int type;
    double second;

    void initShow();


private slots:
    void on_resBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::report *ui;
};

#endif // REPORT_H
