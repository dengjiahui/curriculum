#include "ui_login.h"
#include "widget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <utility>

const QString HFUT_URL("http://210.45.240.29/");

widget::widget(QWidget* parent): QWidget(parent), ui(new Ui::login)
{
	ui->setupUi(this);
	manager = new QNetworkAccessManager(this);
}

widget::~widget()
{
	delete ui;
	ui = nullptr;
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
	auto id = ui->line_edit_id->text();
	auto passwd = ui->line_edit_pwd->text();

	connect(reply, &QNetworkReply::finished,
		this, &widget::request_finished);
	login(id, passwd);
}

// deal with the reply
void widget::request_finished()
{
	if (QNetworkReply::NoError == reply->error()) {
		information = new QFile(":/info/main_info");
		if (information->open(QFile::WriteOnly)) {
			information->write(reply->readAll());
		}
		information->close();
		delete information;
		information = nullptr;
	} else {
		// leave to complete later
	}
	reply->deleteLater();
	reply = nullptr;
}

// post a request and save the returned result
void widget::login(const QString& id, const QString& passwd)
{
	url = std::move(QUrl(HFUT_URL + "pass.asp"));
	QByteArray info("user=" + id + "&password=" + passwd);

	reply = manager->post(QNetworkRequest(url), info);
}
