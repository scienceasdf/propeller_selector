#include "report.h"
#include "ui_report.h"
#include "chart.h"

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
        ui->resBox->addItem(s1);
    }
    show();
}


void report::on_resBox_currentIndexChanged(int index)
{
    ui->thrustLabel->setText("静拉力为"+QString::number(thrust[index])+"牛顿");
    ui->dynamicThrustLabel->setText("动拉力为"+QString::number(dynamicThrust[index])+"牛顿");
    ui->etaLabel->setText("空速下螺旋桨效率为"+QString::number(etaProp[index]*100.0)+"%");
}

void report::on_pushButton_clicked()
{
    chart* res=new chart();
    res->pro1.getCurve(files[ui->resBox->currentIndex()]);
    res->path=files[ui->resBox->currentIndex()];
    res->initShow(type,second);
}
