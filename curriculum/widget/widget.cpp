#include "ui_login.h"
#include "ui_course_table.h"
#include "../html_parser/html_parser.h"
#include "widget.h"
#include <QPainter>
#include <QFile>
#include <utility>
#include <QDebug>

widget::widget(QWidget* parent): QWidget(parent), ui_login_(new Ui::login),
				ui_course_table_(new Ui::course_table)
{
	ui_login_->setupUi(this);
}

widget::~widget()
{
	delete ui_course_table_;
	ui_course_table_ = nullptr;
	delete ui_login_;
	ui_login_ = nullptr;
	delete parser_;
	parser_ = nullptr;
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
	auto id = ui_login_->line_edit_id->text();
	auto passwd = ui_login_->line_edit_pwd->text();

	parser_ = new html_parser("info.html", id, passwd);
	if (!parser_) {
		qDebug() << "No enough memory available to do the login work";

		return;
	}
	parser_->login();
//	this->c
//	ui_course_table_->setupUi(this);
//	this->show();
}
