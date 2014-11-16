#include "cookies.h"
#include <QTextCodec>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QFile>
#include <QVariant>
//#include <QCoreApplication>
#include <QDebug>

// the common url
const QString cookies::HFUT_URL_("http://210.45.240.29/");

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
		qWarning() << "ERROR:" << reply_->errorString();
		http_status_ = false;

		return;
	}
	cookie_info_ = manager_->cookieJar()->cookiesForUrl(url_);
//	qDebug() << cookie;
//	qDebug() << cookie_info_ << endl;
	reply_->deleteLater();
	reply_ = nullptr;
//	if (!url_after_login_.isEmpty()) {
//		url_ = url_after_login_;
//		information_->open(QIODevice::WriteOnly);
//		information_->resize(0);
//		url_after_login_.clear();
//		start_get();
//	}
//	qDebug() << QCoreApplication::applicationDirPath();
//	information_ = new QFile("info.html");
//	information_->open(QIODevice::ReadWrite);
//	qDebug() << tr(information_->readAll());
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
void cookies::login() noexcept
{
//	if (!target.isEmpty()) {
//		url_after_login_ = std::move(QUrl(target));
//	}
	url_ = std::move(QUrl(HFUT_URL_ + "pass.asp"));
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
	connect_slots();
}

// the get way
void cookies::start_get() noexcept
{
	reply_ = manager_->get(QNetworkRequest(url_));
//	reply_ = manager_->get(QNetworkRequest(QUrl("http://www.baidu.com/")));
	connect_slots();
}

void cookies::connect_slots() noexcept
{
	connect(reply_, &QNetworkReply::readyRead,
		this, &cookies::request_ready);
	connect(reply_, &QNetworkReply::finished,
		this, &cookies::request_finished);
}

// get html using cookies
void cookies::cookie_get(const QVariant& cookie, const QString& url) noexcept
{
	QNetworkRequest request(std::move(QUrl(HFUT_URL_ + url)));

	request.setHeader(QNetworkRequest::CookieHeader, cookie);
	reply_ = manager_->get(request);
	connect_slots();
}
