#pragma execution_character_set("utf-8")
#include "qtmovewidget.h"
#include <algorithm>

QtMoveWidget::QtMoveWidget(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    MyLabel* lab = new MyLabel(1, 100, "A", ui.wdt_central);
    lab->setStyleSheet(QStringLiteral("background-color: rgb(0, 134, 139);"));
    connect(lab, &MyLabel::onMoveUp, this, &QtMoveWidget::onMoveUp);
    connect(lab, &MyLabel::onMoveDown, this, &QtMoveWidget::onMoveDown);
    connect(lab, &MyLabel::onMoveRelease, this, &QtMoveWidget::onMoveRelease);
    connect(lab, &MyLabel::onMovePress, this, &QtMoveWidget::onMovePress);
    m_labs.push_back(lab);

    lab = new MyLabel(2, 150, "B", ui.wdt_central);
    lab->setStyleSheet(QStringLiteral("background-color: rgb(72, 61, 139);"));
    connect(lab, &MyLabel::onMoveUp, this, &QtMoveWidget::onMoveUp);
    connect(lab, &MyLabel::onMoveDown, this, &QtMoveWidget::onMoveDown);
    connect(lab, &MyLabel::onMoveRelease, this, &QtMoveWidget::onMoveRelease);
    connect(lab, &MyLabel::onMovePress, this, &QtMoveWidget::onMovePress);
    m_labs.push_back(lab);

    lab = new MyLabel(3, 100, "C", ui.wdt_central);
    lab->setStyleSheet(QStringLiteral("background-color: rgb(0, 205, 102);"));
    connect(lab, &MyLabel::onMoveUp, this, &QtMoveWidget::onMoveUp);
    connect(lab, &MyLabel::onMoveDown, this, &QtMoveWidget::onMoveDown);
    connect(lab, &MyLabel::onMoveRelease, this, &QtMoveWidget::onMoveRelease);
    connect(lab, &MyLabel::onMovePress, this, &QtMoveWidget::onMovePress);
    m_labs.push_back(lab);

    lab = new MyLabel(4, 50, "D", ui.wdt_central);
    lab->setStyleSheet(QStringLiteral("background-color: rgb(30, 144, 255);"));
    connect(lab, &MyLabel::onMoveUp, this, &QtMoveWidget::onMoveUp);
    connect(lab, &MyLabel::onMoveDown, this, &QtMoveWidget::onMoveDown);
    connect(lab, &MyLabel::onMoveRelease, this, &QtMoveWidget::onMoveRelease);
    connect(lab, &MyLabel::onMovePress, this, &QtMoveWidget::onMovePress);
    m_labs.push_back(lab);

    lab = new MyLabel(5, 150, "E", ui.wdt_central);
    lab->setStyleSheet(QStringLiteral("background-color: rgb(205, 92, 92);"));
    connect(lab, &MyLabel::onMoveUp, this, &QtMoveWidget::onMoveUp);
    connect(lab, &MyLabel::onMoveDown, this, &QtMoveWidget::onMoveDown);
    connect(lab, &MyLabel::onMoveRelease, this, &QtMoveWidget::onMoveRelease);
    connect(lab, &MyLabel::onMovePress, this, &QtMoveWidget::onMovePress);
    m_labs.push_back(lab);

    lab = new MyLabel(6, 100, "F", ui.wdt_central);
    lab->setStyleSheet(QStringLiteral("background-color: rgb(148, 0, 211);"));
    connect(lab, &MyLabel::onMoveUp, this, &QtMoveWidget::onMoveUp);
    connect(lab, &MyLabel::onMoveDown, this, &QtMoveWidget::onMoveDown);
    connect(lab, &MyLabel::onMoveRelease, this, &QtMoveWidget::onMoveRelease);
    connect(lab, &MyLabel::onMovePress, this, &QtMoveWidget::onMovePress);
    m_labs.push_back(lab);

    resetMyLabel();
}
void QtMoveWidget::resetMyLabel()
{
    sort(m_labs.begin(), m_labs.end(), QtMoveWidget::compareMyLabel);
    int offX = 2, offY = 2, pos_height = offY, cur_height = 0, cur_width = 970;
    for (auto item : m_labs)
    {
        cur_height = item->getHeight();
        item->setGeometry(QRect(offX, pos_height, cur_width - 2 * offX, cur_height));
        item->setRange(pos_height - offY, pos_height + cur_height);
        pos_height += cur_height + offY;

    }
}

bool QtMoveWidget::compareMyLabel(MyLabel const* a, MyLabel const* b)
{
    return a->m_serial < b->m_serial;
}

void QtMoveWidget::onMoveUp(QObject* obj)
{
    MyLabel* myLabel = static_cast<MyLabel*>(obj);
    int cur_serial = myLabel->getSerial();
    if (cur_serial < 2) return;

    //交换序列号
    myLabel->setSerial(cur_serial - 1);
    m_labs[cur_serial - 2]->setSerial(cur_serial);
    resetMyLabel();
}

void QtMoveWidget::onMoveDown(QObject* obj)
{
    MyLabel* myLabel = static_cast<MyLabel*>(obj);
    int cur_serial = myLabel->getSerial();
    if (cur_serial >= m_labs.size()) return;

    //交换序列号
    myLabel->setSerial(cur_serial + 1);
    m_labs[cur_serial]->setSerial(cur_serial);
    resetMyLabel();
}

void QtMoveWidget::onMoveRelease(QObject* obj)
{
    MyLabel* myLabel = static_cast<MyLabel*>(obj);
    int cur_serial = myLabel->getSerial();
    int cur_height = myLabel->getLastY();
    MyLabel* tempLabel = nullptr;
    for (auto item : m_labs)
    {
        if (cur_height >= item->getRangeMin() && cur_height < item->getRangeMax())
        { //定位到插入位置
            if (item == myLabel) return;
            tempLabel = item;
            break;
        }
    }
    if (cur_height >= m_labs[m_labs.size() - 1]->getRangeMax())
    {
        tempLabel = m_labs[m_labs.size() - 1];
    }
    else if (cur_height <= m_labs[0]->getRangeMin())
    {
        tempLabel = m_labs[0];
    }
    if (tempLabel == nullptr) return;

    if (tempLabel->getSerial() < myLabel->getSerial())
    {//目标块向上移动
        int temp = tempLabel->getSerial();
        //依次向下移动 
        for (int serial = tempLabel->getSerial(); serial <= myLabel->getSerial() - 1; serial++)
        {
            m_labs[serial - 1]->setSerial(serial + 1);
        }
        myLabel->setSerial(temp);
    }
    else
    {//目标块向上移动
        int temp = tempLabel->getSerial();
        //依次向上移动 
        for (int serial = myLabel->getSerial() + 1; serial <= tempLabel->getSerial(); serial++)
        {
            m_labs[serial - 1]->setSerial(serial - 1);
        }
        myLabel->setSerial(temp);

    }
    resetMyLabel();
}

void QtMoveWidget::onMovePress(QObject* obj)
{
    MyLabel* myLabel = static_cast<MyLabel*>(obj);
    myLabel->raise();
}
