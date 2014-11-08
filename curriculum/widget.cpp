#include "ui_login.h"
#include "widget.h"
#include <QPainter>
#include <utility>

widget::widget(QWidget* parent): QWidget(parent), ui(new Ui::login)
{
	ui->setupUi(this);
}

widget::~widget()
{
	delete ui;
	ui = nullptr;
}

void widget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	QPixmap login_picture =
		std::move(QPixmap(":/images/login_pic").scaled(this->size()));

	painter.drawPixmap(this->rect(), login_picture);
}
