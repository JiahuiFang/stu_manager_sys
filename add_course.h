﻿#ifndef ADD_COURSE_H
#define ADD_COURSE_H

#include <QDialog>

namespace Ui {
class add_course;
}

class add_course : public QDialog
{
    Q_OBJECT

public:
    explicit add_course(QWidget *parent = nullptr);
    ~add_course();
    void initUI();

signals:
    void signal_ret();

private slots:
    void slot_ret();
    void add();

private:
    Ui::add_course *ui;
};

#endif // ADD_COURSE_H
