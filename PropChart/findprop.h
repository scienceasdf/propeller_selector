#ifndef FINDPROP_H
#define FINDPROP_H

#include <QDialog>

namespace Ui {
class findProp;
}

class findProp : public QDialog
{
    Q_OBJECT

public:
    explicit findProp(QWidget *parent = 0);
    ~findProp();

    std::vector<std::string> pathLists;
    std::vector<std::string> nameLists;

signals:
    void dlgReturn(std::string&);

private slots:


    void on_keyInput_textChanged(const QString &arg1);

    void on_searchButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::findProp *ui;
};

#endif // FINDPROP_H
