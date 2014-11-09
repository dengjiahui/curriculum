#include "ui_login.h"
#include "widget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QFile>
#include <utility>
#include <QDebug>

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

	information = new QFile("index.html");
	if (!information->open(QIODevice::WriteOnly)) {
		qDebug() <<  "file open error";
		delete information;
		information = nullptr;

		return;
	}
	login(id, passwd);
}

// do the clean work
void widget::request_finished()
{
	information->flush();
	information->close();
	QVariant redirectionTarget =
		reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

	if (QNetworkReply::NoError == reply->error()) {
		if (!redirectionTarget.isNull()) {
			url = url.resolved(redirectionTarget.toUrl());
			reply->deleteLater();
			information->open(QIODevice::WriteOnly);
			information->resize(0);
			start_get();

			return;
		}
	}
	reply->deleteLater();
	reply = nullptr;
	delete information;
	information = nullptr;
	information = new QFile("index.html");
}

// write returned information into the file
void widget::request_ready() noexcept
{
	if (information) {
		information->write((reply->readAll()));
	}
}

// post a request and prepare for the result
void widget::login(const QString& id, const QString& passwd)
{
	url = std::move(QUrl(HFUT_URL + "pass.asp"));
	QUrlQuery params;

	params.addQueryItem("UserStyle", "student");
	params.addQueryItem("user", id);
	params.addQueryItem("password", passwd);

	start_post(params);
//	start_get();
}

// the connect part using post way
void widget::start_post(const QUrlQuery& params) noexcept
{
	QNetworkRequest request(url);

	request.setHeader(QNetworkRequest::ContentTypeHeader,
			  QVariant("application/x-www-form-urlencoded"));
	reply = manager->post(request,
			      params.query(QUrl::FullyEncoded).toUtf8());

	connect(reply, SIGNAL(readyRead()), this, SLOT(request_ready()));
	connect(reply, SIGNAL(finished()), this, SLOT(request_finished()));
}

// the get way
void widget::start_get() noexcept
{
	reply = manager->get(QNetworkRequest(url));

	connect(reply, SIGNAL(readyRead()), this, SLOT(request_ready()));
	connect(reply, SIGNAL(finished()), this, SLOT(request_finished()));
}
