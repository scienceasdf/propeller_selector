#include "report.h"
#include "ui_report.h"

#include<string>
#include<QString>
#include<objects.h>
#include<detail.h>

#ifdef _MSC_VER
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#endif

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

report::report(propulsion& p1) :
    ui(new Ui::report),pro(p1.U_ub,p1.I_ub,p1.mot,p1.gear_rto,p1.eta_gear)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags (flags);

    pro.speed=p1.speed;

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
    if(ui->propBox->count()==0){
        ui->detailButton->setEnabled(false);
    }
}

void report::on_propBox_currentIndexChanged(int index)
{
    ui->thruLabel->setText("静拉力为"+QString::number(thrust[index])+"牛顿");
    ui->dynamicThruLabel->setText("动拉力为"+QString::number(dynamicThrust[index])+"牛顿");
    ui->etaPropLabel->setText("空速下螺旋桨效率为"+QString::number(etaProp[index]*100.0)+"%");
    ui->etaTotalLabel->setText("空速下动力系统总效率为"+QString::number(etaTotal[index]*100.0)+"%");
}

void report::on_detailButton_clicked()
{
    auto detailWidget=new detail(pro);
    //detailWidget->pro1=pro;
    detailWidget->propPath=files[ui->propBox->currentIndex()];
    detailWidget->initShow();

}
