#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtmovewidget.h"
#include "MyLabel.h"
using namespace std;

class QtMoveWidget : public QMainWindow
{
    Q_OBJECT

public:
    QtMoveWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtMoveWidgetClass ui;
    vector<MyLabel*> m_labs;

    static bool compareMyLabel(MyLabel const* a, MyLabel const* b);
    void resetMyLabel();

private slots:
    void onMoveUp(QObject*);
    void onMoveDown(QObject*);
    void onMovePress(QObject*);
    void onMoveRelease(QObject*);
};
