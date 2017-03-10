#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include<objects.h>

namespace Ui {
class detail;
}

class detail : public QWidget
{
    Q_OBJECT

public:
    explicit detail(QWidget *parent = 0);
    detail(propulsion& p1);
    ~detail();

    propulsion pro1;
    std::string propPath;

    void initShow();

private slots:
    void on_analyzeButton_clicked();

    void on_propButton_clicked();
    void resetProp(std::string& str);

private:
    Ui::detail *ui;
};

#endif // DETAIL_H
