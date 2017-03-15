#ifndef SELECTOR_H
#define SELECTOR_H

#include <QWidget>
#include<objects.h>

namespace Ui {
class Selector;
}

class Selector : public QWidget{
    Q_OBJECT

public:
    explicit Selector(QWidget *parent = 0);
    ~Selector();

    propeller p1;

private slots:
    void on_selectButton_clicked(bool checked);

    void on_condBox_currentIndexChanged(int index);

private:
    Ui::Selector *ui;
};

#endif // SELECTOR_H
