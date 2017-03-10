#include "demo.h"
#include "ui_demo.h"
#include<vector>
#include<algorithm>
#include<iostream>
#include <chrono>
#include<string>
#include<thread>

#include<spline.h>
#include<objects.h>
#include<fileops.h>
#include<report.h>

Demo::Demo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Demo),ing(false)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags (flags);

    //ui->CalcButton->setEnabled(false);


}

Demo::~Demo()
{
    delete ui;
}

void Trim(std::string &str)
{
   int s=str.find_first_not_of(" \t");
   int e=str.find_last_not_of(" \t");
   str=str.substr(s,e-s+1);
}

void Demo::on_CalcButton_clicked()
{
    ui->CalcButton->setEnabled(false);

    QString valueStr=ui->KV_Input->text();
    double KV=valueStr.toDouble();
    valueStr=ui->r_Input->text();
    double r=valueStr.toDouble();
    motor mt1(KV,r);

    valueStr=ui->currInput->text();
    double curr=valueStr.toDouble();
    valueStr=ui->voltInput->text();
    double volt=valueStr.toDouble();
    valueStr=ui->gearRtoInput->text();
    double gearRto=valueStr.toDouble();
    valueStr=ui->gearEtaInput->text();
    double gearEta=valueStr.toDouble()/100.0;
    propulsion p1(volt,curr,mt1,gearRto,gearEta);
    valueStr=ui->spdInput->text();
    p1.speed=valueStr.toDouble();


    valueStr=ui->minStaThruInput->text();
    double minStaThru=valueStr.toDouble();
    valueStr=ui->minDyThruInput->text();
    double minDyThru=valueStr.toDouble();
    valueStr=ui->minEtaInput->text();
    double etaProp=valueStr.toDouble()/100.0;

    auto reportWidget=new report(p1);

    getAll(*reportWidget,minStaThru,minDyThru,etaProp,ui->etaTolInput->text().toDouble()/100.0,p1);
    reportWidget->initShow();
    ui->CalcButton->setEnabled(true);

    reportWidget->activateWindow();


}
