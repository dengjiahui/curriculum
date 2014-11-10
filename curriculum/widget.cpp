#include "ui_login.h"
#include "widget.h"
#include "cookies.h"
#include <QPainter>
#include <QFile>
#include <utility>

widget::widget(QWidget* parent): QWidget(parent), ui_(new Ui::login)
{
	ui_->setupUi(this);
}

widget::~widget()
{
	delete ui_;
	ui_ = nullptr;
	delete info_cookies;
	info_cookies = nullptr;
}

// paint the login background
void widget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	QPixmap login_picture =
		std::move(QPixmap(":/images/login_pic").scaled(this->size()));

	painter.drawPixmap(this->rect(), login_picture);
}

// load a qss file
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

// the login action
void widget::on_button_login_clicked()
{
	auto id = ui_->line_edit_id->text();
	auto passwd = ui_->line_edit_pwd->text();

	info_cookies = new cookies(QCoreApplication::applicationDirPath() +
				   "index.html", id, passwd);
	if (!info_cookies) {
		qDebug() << "No enough memory available to do the login work";

		return;
	}
	info_cookies->login();
}
