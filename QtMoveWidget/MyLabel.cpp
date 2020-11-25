#pragma execution_character_set("utf-8")
#include "MyLabel.h"
MyLabel::MyLabel(int _serial, int _height, QString _info, QWidget* parent) : QLabel(parent)
, m_serial(_serial)
, m_height(_height)
, m_info(_info)
, range_min(0)
, range_max(0)
, isup(true)
{

	QFont font3;
	font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
	font3.setPointSize(24);
	lb_serial = new QLabel(this); 
	lb_serial->setMinimumSize(QSize(50, 0));
	lb_serial->setFont(font3);
	lb_serial->setText(QString("%1").arg(m_serial));
	lb_serial->setGeometry(QRect(10, 5, 50, 50));

	lb_info = new QLabel(this);
	lb_info->setMinimumSize(QSize(50, 0));
	lb_info->setFont(font3);
	lb_info->setText(m_info);
	lb_info->setGeometry(QRect(80, 5, 150, 50));


	QFont font1;
	font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
	font1.setPointSize(8);
	lb_min = new QLabel(this); 
	lb_min->setFont(font1);
	lb_min->setText(QString("最小值：%1").arg(range_min));
	lb_min->setGeometry(QRect(250, 0, 150, 20));
	 
	lb_max = new QLabel(this); 
	lb_max->setFont(font1);
	lb_max->setText(QString("最大值：%1").arg(range_max));
	lb_max->setGeometry(QRect(450, 0, 150, 20));

	pb_up = new QPushButton(this);
	pb_up->setGeometry(QRect(880, 10, 32, 24));
	pb_up->setStyleSheet(QString("QPushButton {\n"
		"	background-color:transparent;\n"
		"	background-image: url(:/QtMoveWidget/UI/images/up.png);\n"
		"   border:0px;\n"
		"}\n"
		""));
	connect(pb_up, &QPushButton::clicked, this, &MyLabel::moveUp);

	pb_down = new QPushButton(this);
	pb_down->setGeometry(QRect(920, 10, 32, 24));
	pb_down->setStyleSheet(QString("QPushButton {\n"
		"	background-color:transparent;\n"
		"	background-image: url(:/QtMoveWidget/UI/images/down.png);\n"
		"   border:0px;\n"
		"}\n"
		""));
	connect(pb_down, &QPushButton::clicked, this, &MyLabel::moveDown);
}
MyLabel::~MyLabel()
{

}


void MyLabel::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		mMoving = true;
		mLastMousePosition = event->globalPos();
		first_y = event->windowPos().y();
		emit onMovePress(this);
	}
}

void MyLabel::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons().testFlag(Qt::LeftButton) && mMoving)
	{
		setCursor(Qt::OpenHandCursor);
		this->move(this->pos() + (event->globalPos() - mLastMousePosition));
		mLastMousePosition = event->globalPos(); 

		isup = true;
		int cur = event->globalPos().y();
		if (event->windowPos().y() - first_y < 0)
		{//向上移动
			last_y = range_min + event->windowPos().y() - first_y;
		}
		else
		{//向下移动
			last_y = range_max + event->windowPos().y() - first_y;
			isup = false;
		}
	}
}

void MyLabel::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		mMoving = false;
		setCursor(Qt::ArrowCursor); 
		emit onMoveRelease(this);
	}
}

void MyLabel::setSerial(int _serial)
{
	m_serial = _serial;
	lb_serial->setText(QString("%1").arg(m_serial));
	lb_info->setText(m_info);
}

void MyLabel::setRange(int _min, int _max) 
{ 
	range_min = _min; 
	range_max = _max; 
	lb_min->setText(QString("最小值：%1").arg(range_min));
	lb_max->setText(QString("最大值：%1").arg(range_max));
}
 
void MyLabel::moveUp()
{
	emit onMoveUp(this);
}

void MyLabel::moveDown()
{
	emit onMoveDown(this);
}