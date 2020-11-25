#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtmywidget.h"

class QtMyWidget : public QMainWindow
{
    Q_OBJECT

public:
    QtMyWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtMyWidgetClass ui;
};
