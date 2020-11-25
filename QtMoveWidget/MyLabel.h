#pragma once
#include <qwidget.h>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
class MyLabel :
    public QLabel
{
    Q_OBJECT
public:
    MyLabel(int _serial, int _height, QString _info, QWidget* parent = Q_NULLPTR);
    ~MyLabel();
    int getSerial()  { return m_serial; };
    inline const int getHeight() { return m_height; };
    void setSerial(int _serial);
    void setRange(int _min, int _max);
    int getRangeMin() { return range_min; };
    int getRangeMax() { return range_max; };
    int getLastY() { return last_y; }
    int m_serial;
private:
    QPoint mLastMousePosition;
    int first_y;
    int off_y;
    int last_y;
    bool mMoving;

    void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* e) Q_DECL_OVERRIDE;

    QLabel* lb_serial;
    QPushButton* pb_up;
    QPushButton* pb_down;
    QLabel* lb_info;
    QLabel* lb_min;
    QLabel* lb_max;
  
    int range_min;
    int range_max;
    int m_height;
    QString m_info;
    bool isup;
    void moveUp();
    void moveDown();

signals:
    void onMoveUp(QObject*);
    void onMoveDown(QObject*);
    void onMovePress(QObject*);
    void onMoveRelease(QObject*);
};

