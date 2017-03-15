#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include<objects.h>

namespace Ui {
class chart;
}

class chart : public QWidget
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = 0);
    ~chart();

    propeller pro1;
    std::string path;

    void initShow(int first, double second);
    void updateChart(int cond, int yType);

private slots:
    void on_condBox_currentIndexChanged(int index);

    void on_typeBox_currentIndexChanged(int index);

    void on_updateButton_clicked();

    void on_searchButton_clicked();

    void resetProp(std::string& str);

private:
    Ui::chart *ui;
};

#endif // CHART_H
