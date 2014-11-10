#include "cookies.h"
#include <QTextCodec>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QFile>
#include <utility>
#include <QCoreApplication>
#include <QDebug>

// the common url
const QString cookies::HFUT_URL("http://210.45.240.29/");

cookies::cookies(const QString& file, const QString& username,
		 const QString& password): user_(username), passwd_(password)
{
	manager_ = new QNetworkAccessManager(this);
	information_ = new QFile(file);
	if (!information_->open(QIODevice::WriteOnly)) {
		qDebug() <<  "file open error";
		delete information_;
		information_ = nullptr;
	}
}

cookies::~cookies()
{
	delete information_;
	information_ = nullptr;
}

// do the clean work
void cookies::request_finished()
{
	information_->flush();
	information_->close();
	QVariant redirectionTarget =
		reply_->attribute(QNetworkRequest::RedirectionTargetAttribute);

	if (QNetworkReply::NoError == reply_->error()) {
		if (!redirectionTarget.isNull()) {
			url_ = url_.resolved(redirectionTarget.toUrl());
			reply_->deleteLater();
			information_->open(QIODevice::WriteOnly);
			information_->resize(0);
			start_get();

			return;
		}
	} else {
		http_status_ = false;
	}
	reply_->deleteLater();
	reply_ = nullptr;
	delete information_;
	information_ = nullptr;
	information_ = new QFile("index.html");
	information_->open(QIODevice::ReadOnly);
	qDebug() << tr(information_->readAll());
}

// write returned information into the file
void cookies::request_ready() noexcept
{
	if (information_) {
		QTextCodec* tc = QTextCodec::codecForName("GBK");

		information_->write(
			tc->toUnicode(reply_->readAll()).toStdString().c_str());
	}
}

// post a request and prepare for the result
void cookies::login()
{
	url_ = std::move(QUrl(HFUT_URL + "pass.asp"));
	QUrlQuery params;

	params.addQueryItem("UserStyle", "student");
	params.addQueryItem("user", user_);
	params.addQueryItem("password", passwd_);

	start_post(params);
//	start_get();
}

// the connect part using post way
void cookies::start_post(const QUrlQuery& params) noexcept
{
	QNetworkRequest request(url_);

	request.setHeader(QNetworkRequest::ContentTypeHeader,
			  QVariant("application/x-www-form-urlencoded"));
	reply_ = manager_->post(request,
			      params.query(QUrl::FullyEncoded).toUtf8());

	connect(reply_, &QNetworkReply::readyRead,
		this, &cookies::request_ready);
	connect(reply_, &QNetworkReply::finished,
		this, &cookies::request_finished);
}

// the get way
void cookies::start_get() noexcept
{
	reply_ = manager_->get(QNetworkRequest(url_));
//	reply_ = manager_->get(QNetworkRequest(QUrl("http://www.baidu.com/")));

	connect(reply_, &QNetworkReply::readyRead,
		this, &cookies::request_ready);
	connect(reply_, &QNetworkReply::finished,
		this, &cookies::request_finished);
}
