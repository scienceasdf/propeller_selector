#include "chart.h"
#include "ui_chart.h"
#include<QVector>
#include<QtAlgorithms>
#include<findprop.h>

chart::chart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags (flags);

}

chart::~chart()
{
    delete ui;
}

void chart::initShow(int first, double second)
{
    ui->condBox->setCurrentIndex(first);
    ui->condInput->setText(QString::number(second));
    QVector<double> x(30),y(30);

    if(first==0){
        double maxSpeed=1.4*second/60.0*pro1.diameter;
        for(int i=0;i<30;++i){
            x[i]=maxSpeed/30.0*i;
            y[i]=pro1.thrust_on_RPM(second,x[i]);
        }
        ui->plot->addGraph();
        ui->plot->graph(0)->setData(x,y);
        ui->plot->xAxis->setRange(.0,maxSpeed);



    }
    else{
        ui->condLabel->setText("功率/瓦");
        double RPM=pro1.RPM_on_power(second,.0);
        double maxSpeed=1.0*RPM/60.0*pro1.diameter;
        for(int i=0;i<30;++i){
            x[i]=maxSpeed/30.0*i;
            y[i]=pro1.thrust_on_power(second,x[i]);
        }
        ui->plot->addGraph();
        ui->plot->graph(0)->setData(x,y);
        ui->plot->xAxis->setRange(.0,maxSpeed);


    }

    ui->plot->xAxis->setLabel("速度/(m/s)");
    ui->plot->yAxis->setLabel("拉力/牛");
    ui->plot->yAxis->setRange(0.0,1.3*y.at(0));
    show();
}

void chart::on_condBox_currentIndexChanged(int index)
{
    /*pro1.getCurve(path);
    int y=ui->typeBox->currentIndex();
    updateChart(index,y);*/
    if(index==0){
        ui->condLabel->setText("转速/RPM");
        ui->typeBox->setItemText(2,"功率曲线");
    }
    else{
        ui->condLabel->setText("功率/瓦");
        ui->typeBox->setItemText(2,"转速曲线");
    }
}

void chart::on_typeBox_currentIndexChanged(int index)
{

}


void chart::on_updateButton_clicked()
{
    int a=ui->condBox->currentIndex(), b=ui->typeBox->currentIndex();
    updateChart(a,b);
}

void chart::updateChart(int cond, int yType)
{
    double maxSpeed;
    QVector<double> x(30),y(30);
    double second=ui->condInput->text().toDouble();
    pro1.getCurve(path);

    if(cond==0){
        maxSpeed=1.4*second/60.0*pro1.diameter;

        if(yType==0){
            for(int i=0;i<30;++i){
                x[i]=maxSpeed/30.0*i;
                y[i]=pro1.thrust_on_RPM(second,x[i]);
            }
            ui->plot->yAxis->setLabel("拉力/牛");
        }

        if(yType==1){
            for(int i=0;i<30;++i){
                x[i]=maxSpeed/30.0*i;
                y[i]=100.0*pro1.eta_on_RPM(second,x[i]);
            }
            ui->plot->yAxis->setLabel("效率%");
        }

        if(yType==2){
            for(int i=0;i<30;++i){
                x[i]=maxSpeed/30.0*i;
                y[i]=pro1.power_on_RPM(second,x[i]);
            }
            ui->plot->yAxis->setLabel("功率/瓦");
        }

    }

    else{
        double RPM=pro1.RPM_on_power(second,.0);

        maxSpeed=1.0*RPM/60.0*pro1.diameter;


        if(yType==0){
            for(int i=0;i<30;++i){
                x[i]=maxSpeed/30.0*i;
                y[i]=pro1.thrust_on_power(second,x[i]);
            }
            ui->plot->yAxis->setLabel("拉力/牛");
        }

        if(yType==1){
            for(int i=0;i<30;++i){
                x[i]=maxSpeed/30.0*i;
                y[i]=100.0*pro1.eta_on_power(second,x[i]);
                ui->plot->yAxis->setLabel("效率%");
            }
        }

        if(yType==2){
            for(int i=0;i<30;++i){
                x[i]=maxSpeed/30.0*i;
                y[i]=pro1.RPM_on_power(second,x[i]);
            }
            ui->plot->yAxis->setLabel("转速/RPM");
        }

    }

    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x,y);
    ui->plot->xAxis->setRange(.0,maxSpeed);
    ui->plot->xAxis->setLabel("速度/(m/s)");

    auto max=std::max_element(y.begin(),y.end());
    ui->plot->yAxis->setRange(.0,(*max)*1.25);
    ui->plot->replot();
}

void chart::on_searchButton_clicked()
{
    findProp* dlg=new findProp(this);
    connect(dlg,SIGNAL(dlgReturn(std::string&)),this,SLOT(resetProp(std::string&)));
    dlg->show();
}

void chart::resetProp(std::string &str)
{
    path=str;
    //ui->condLabel->setText(QString::fromStdString(str));
    int a=ui->condBox->currentIndex(), b=ui->typeBox->currentIndex();
    updateChart(a,b);
}
