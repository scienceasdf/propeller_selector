#include "detail.h"
#include "ui_detail.h"
//#include<objects.h>
#include<findprop.h>

detail::detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detail)
{
    ui->setupUi(this);
}

detail::detail(propulsion& p1) :
    pro1(p1.U_ub,p1.I_ub,p1.mot,p1.gear_rto,p1.eta_gear),
    ui(new Ui::detail)
{
    ui->setupUi(this);

    pro1.speed=p1.speed;

}


detail::~detail()
{
    delete ui;
}

void detail::initShow()
{
    ui->voltInput->setText(QString::number(pro1.U_ub));
    ui->currInput->setText(QString::number(pro1.I_ub));
    ui->KV_input->setText(QString::number(pro1.mot.Kv));
    ui->resInput->setText(QString::number(pro1.mot.Ra));
    ui->rtoInput->setText(QString::number(pro1.gear_rto));
    ui->etaGearInput->setText(QString::number(pro1.eta_gear*100.0));
    ui->speedInput->setText(QString::number(pro1.speed));

    pro1.get_curve(propPath);
    pro1.run();
    //QString info="螺旋桨型号： "+QString::fromStdString(pro1.prop_name);
    QString info="螺旋桨型号： "+QString::fromStdString(pro1.prop_name)+"\n静止状态下：\n工作电压："+QString::number(pro1.volt);
    info=info+" V\n工作电流："+QString::number(pro1.current);
    info=info+" A\n静拉力："+QString::number(pro1.thru);
    info=info+" N\n螺旋桨转速："+QString::number(pro1.rot);

    bool iFlag=pro1.current<(pro1.I_ub*.9);
    bool uFlag=pro1.volt<(pro1.U_ub*.9);

    pro1.dynamic_run();
    info=info+"RPM\n空速下：\n工作电压："+QString::number(pro1.volt);
    info=info+" V\n工作电流："+QString::number(pro1.current);
    info=info+" A\n拉力："+QString::number(pro1.thru);
    info=info+" N\n螺旋桨转速："+QString::number(pro1.rot);
    info=info+" RPM\n总效率："+QString::number(pro1.eta*100.0);
    info=info+" %\n螺旋桨效率："+QString::number(pro1.eta_prop()*100.0)+" %";
    ui->detailLabel->setText(info);

    bool iFlag2=pro1.current<(pro1.I_ub*.9);
    bool uFlag2=pro1.volt<(pro1.U_ub*.9);

    if(iFlag && iFlag2){
        info="电压接近电源电压而电流远离电流上限，应该是低转速电机带小桨，"
             "负载较小，应该换用高KV值电机或用大桨或减小减速比";
    }
    if(uFlag && uFlag2){
        info="电流接近电流上限而电压远离电源电压，应该是高转速电机带大桨，"
             "负载较大，在限流值附近继续推油门转速可能反而会下降，"
             "应该换用低KV值电机或用增大减速比或用小桨";
    }

    if(uFlag && !uFlag2 && pro1.speed>1.0){
        info="在静止状态下电流接近电流上限而电压远离电源电压，"
             "应该是高转速电机带大桨，负载较大，在限流值附近继续推油门转速可能反而会下降，"
             "不过在空速条件下由于负载下降，转速能够提升，工作状况比较好";
    }

    ui->adviceLabel->setText(info);

    show();
}

void detail::on_analyzeButton_clicked()
{
    pro1.U_ub=ui->voltInput->text().toDouble();
    pro1.I_ub=ui->currInput->text().toDouble();
    pro1.mot.Kv=ui->KV_input->text().toDouble();
    pro1.mot.Ra=ui->resInput->text().toDouble();
    pro1.gear_rto=ui->rtoInput->text().toDouble();
    pro1.eta_gear=ui->etaGearInput->text().toDouble()/100.0;
    pro1.speed=ui->speedInput->text().toDouble();

    pro1.run();
    //QString info="螺旋桨型号： "+QString::fromStdString(pro1.prop_name);
    QString info="螺旋桨型号： "+QString::fromStdString(pro1.prop_name)+"\n静止状态下：\n工作电压："+QString::number(pro1.volt);
    info=info+" V\n工作电流："+QString::number(pro1.current);
    info=info+" A\n静拉力："+QString::number(pro1.thru);
    info=info+" N\n螺旋桨转速："+QString::number(pro1.rot);

    bool iFlag=pro1.current<(pro1.I_ub*.9);
    bool uFlag=pro1.volt<(pro1.U_ub*.9);

    pro1.dynamic_run();
    info=info+" RPM\n空速下：\n工作电压："+QString::number(pro1.volt);
    info=info+" V\n工作电流："+QString::number(pro1.current);
    info=info+" A\n拉力："+QString::number(pro1.thru);
    info=info+" N\n螺旋桨转速："+QString::number(pro1.rot);
    info=info+" RPM\n总效率："+QString::number(pro1.eta*100.0);
    info=info+" %\n螺旋桨效率："+QString::number(pro1.eta_prop()*100.0)+" %";
    ui->detailLabel->setText(info);

    bool iFlag2=pro1.current<(pro1.I_ub*.9);
    bool uFlag2=pro1.volt<(pro1.U_ub*.9);

    if(iFlag && iFlag2){
        info="电压接近电源电压而电流远离电流上限，应该是低转速电机带小桨，"
             "负载较小，应该换用高KV值电机或用大桨或减小减速比";
    }
    if(uFlag && uFlag2){
        info="电流接近电流上限而电压远离电源电压，应该是高转速电机带大桨，"
             "负载较大，在限流值附近继续推油门转速可能反而会下降，"
             "应该换用低KV值电机或用增大减速比或用小桨";
    }

    if(uFlag && !uFlag2 && pro1.speed>1.0){
        info="在静止状态下电流接近电流上限而电压远离电源电压，"
             "应该是高转速电机带大桨，负载较大，在限流值附近继续推油门转速可能反而会下降，"
             "不过在空速条件下由于负载下降，转速能够提升，工作状况比较好";
    }

    ui->adviceLabel->setText(info);

}

void detail::on_propButton_clicked()
{
    findProp* dlg=new findProp(this);



    connect(dlg,SIGNAL(dlgReturn(std::string&)),this,SLOT(resetProp(std::string&)));
    dlg->show();
}

void detail::resetProp(std::string &str)
{
    pro1.U_ub=ui->voltInput->text().toDouble();
    pro1.I_ub=ui->currInput->text().toDouble();
    pro1.mot.Kv=ui->KV_input->text().toDouble();
    pro1.mot.Ra=ui->resInput->text().toDouble();
    pro1.gear_rto=ui->rtoInput->text().toDouble();
    pro1.eta_gear=ui->etaGearInput->text().toDouble()/100.0;
    pro1.speed=ui->speedInput->text().toDouble();
    pro1.get_curve(str);


    pro1.run();
    //QString info="螺旋桨型号： "+QString::fromStdString(pro1.prop_name);
    QString info="螺旋桨型号： "+QString::fromStdString(pro1.prop_name)+"\n静止状态下：\n工作电压："+QString::number(pro1.volt);
    info=info+" V\n工作电流："+QString::number(pro1.current);
    info=info+" A\n静拉力："+QString::number(pro1.thru);
    info=info+" N\n螺旋桨转速："+QString::number(pro1.rot);

    bool iFlag=pro1.current<(pro1.I_ub*.9);
    bool uFlag=pro1.volt<(pro1.U_ub*.9);

    pro1.dynamic_run();
    info=info+" RPM\n空速下：\n工作电压："+QString::number(pro1.volt);
    info=info+" V\n工作电流："+QString::number(pro1.current);
    info=info+" A\n拉力："+QString::number(pro1.thru);
    info=info+" N\n螺旋桨转速："+QString::number(pro1.rot);
    info=info+" RPM\n总效率："+QString::number(pro1.eta*100.0);
    info=info+" %\n螺旋桨效率："+QString::number(pro1.eta_prop()*100.0)+" %";
    ui->detailLabel->setText(info);

    bool iFlag2=pro1.current<(pro1.I_ub*.9);
    bool uFlag2=pro1.volt<(pro1.U_ub*.9);

    if(iFlag && iFlag2){
        info="电压接近电源电压而电流远离电流上限，应该是低转速电机带小桨，"
             "负载较小，应该换用高KV值电机或用大桨或减小减速比";
    }
    if(uFlag && uFlag2){
        info="电流接近电流上限而电压远离电源电压，应该是高转速电机带大桨，"
             "负载较大，在限流值附近继续推油门转速可能反而会下降，"
             "应该换用低KV值电机或用增大减速比或用小桨";
    }

    if(uFlag && !uFlag2 && pro1.speed>1.0){
        info="在静止状态下电流接近电流上限而电压远离电源电压，"
             "应该是高转速电机带大桨，负载较大，在限流值附近继续推油门转速可能反而会下降，"
             "不过在空速条件下由于负载下降，转速能够提升，工作状况比较好";
    }

    ui->adviceLabel->setText(info);



}
