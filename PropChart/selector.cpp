#include "selector.h"
#include "ui_selector.h"

#include "fileops.h"
#include "report.h"

Selector::Selector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selector)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags (flags);

}

Selector::~Selector()
{
    delete ui;
}

void Selector::on_selectButton_clicked(bool checked)
{
    ui->selectButton->setEnabled(false);

    int index=ui->condBox->currentIndex();
    double speed=ui->speedInput->text().toDouble();
    double thrust=ui->staticThrustInput->text().toDouble();
    double dynaThru=ui->dynamicThrustInput->text().toDouble();
    double minEta=ui->etaInput->text().toDouble()/100.0;

    report* rep=new report();

    if(!index){
        double RPM=ui->condInput->text().toDouble();
        double maxPower=ui->powerInput->text().toDouble();
        getAll_on_RPM(*rep,RPM,speed,thrust,dynaThru,minEta,maxPower,p1);
        rep->type=0;
        rep->second=RPM;

    }
    else{
        double power=ui->condInput->text().toDouble();
        getAll_on_power(*rep,power,speed,thrust,dynaThru,minEta,p1);
        rep->type=1;
        rep->second=power;
    }

    rep->initShow();
    rep->activateWindow();
    ui->selectButton->setEnabled(true);

}

void Selector::on_condBox_currentIndexChanged(int index)
{
    if(index==0){
        ui->condLabel->setText("转速/RPM");
        ui->powerInput->setVisible(true);
        ui->wattLabel->setVisible(true);
    }
    else{
        ui->condLabel->setText("功率/瓦");
        ui->powerInput->setVisible(false);
        ui->wattLabel->setVisible(false);
    }
}
