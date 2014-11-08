#include "ui_login.h"
#include "widget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QFile>
#include <utility>

widget::widget(QWidget* parent): QWidget(parent), ui(new Ui::login)
{
	ui->setupUi(this);
//	qApp->setStyleSheet(load_qss("login"));
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

QString widget::load_qss(const QString& file_name) const
{
	QFile file(":/qss/" + file_name + "_qss");

	if (!file.open(QFile::ReadOnly)) {
		return std::move(QString(""));
	}
	QString style_sheet = std::move(tr(file.readAll()));

	file.close();

	return std::move(style_sheet);
}
