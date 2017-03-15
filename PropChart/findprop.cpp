#include "findprop.h"
#include "ui_findprop.h"
#include<fileops.h>

findProp::findProp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findProp)
{
    ui->setupUi(this);
}

findProp::~findProp()
{
    delete ui;
}


void findProp::on_keyInput_textChanged(const QString &arg1)
{

}

void findProp::on_searchButton_clicked()
{
    searchProp(ui->keyInput->text().toStdString(),nameLists,pathLists);
    ui->resBox->clear();
    std::vector<std::string>::iterator p2=nameLists.end();
    for(std::vector<std::string>::iterator p1=nameLists.begin();p1!=p2;++p1){
        ui->resBox->addItem(QString::fromStdString(*p1));
    }
}

void findProp::on_buttonBox_accepted()
{
    if(ui->resBox->count())
        emit dlgReturn(pathLists[ui->resBox->currentIndex()]);
}
