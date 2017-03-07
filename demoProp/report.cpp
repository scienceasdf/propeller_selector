#include "report.h"
#include "ui_report.h"

#include<string>
#include<QString>

report::report(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::report)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags (flags);
}

report::~report()
{
    delete ui;
}

void report::initShow()
{
    std::vector<std::string>::iterator iter=props.begin();
    QString s1;
    for(;iter!=props.end();++iter){
        s1=QString::fromStdString(*iter);
        ui->propBox->addItem(s1);
    }
    show();
}

void report::on_propBox_currentIndexChanged(int index)
{
    ui->thruLabel->setText("静拉力为"+QString::number(thrust[index])+"牛顿");
    ui->dynamicThruLabel->setText("动拉力为"+QString::number(dynamicThrust[index])+"牛顿");
    ui->etaPropLabel->setText("空速下螺旋桨效率为"+QString::number(etaProp[index]*100.0)+"%");
    ui->etaTotalLabel->setText("空速下动力系统总效率为"+QString::number(etaTotal[index]*100.0)+"%");
}
