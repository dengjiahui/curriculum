#ifndef COOKIES_H
#define COOKIES_H

#include <utility>
#include <QNetworkCookie>
//#include <QVariant>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;
class QUrlQuery;
class QFile;

class cookies: public QObject {
	Q_OBJECT
public:
	cookies(const QString& file, const QString& username,
		const QString& password);
	~cookies() override;
	void login() noexcept;
	QList<QNetworkCookie> get_cookies() const noexcept;
	const QString get_url() const noexcept;
	void cookie_get(const QVariant& cookie, const QString& url) noexcept;
private slots:
	void request_finished();
	void request_ready() noexcept;
private:
	void set_cookies(const QList<QNetworkCookie>& cookie_list) noexcept;
	void start_post(const QUrlQuery& params) noexcept;
	void start_get() noexcept;
	void connect_slots() noexcept;

	QList<QNetworkCookie> cookie_info_;
	QUrl url_;
	QUrl url_after_login_;
//	QVariant cookie;
	QNetworkReply* reply_ = nullptr;
	QNetworkAccessManager* manager_;
	QFile* information_ = nullptr;
	QString user_;
	QString passwd_;
	bool http_status_ = true;

	static const QString HFUT_URL_;
};

inline
QList<QNetworkCookie> cookies::get_cookies() const noexcept
{
	return cookie_info_;
}

inline
const QString cookies::get_url() const noexcept
{
	return HFUT_URL_;
}

//inline void cookies::set_cookies(const QList<QNetworkCookie>& cookie_list)
//									noexcept
//{
//	if(!this) {
//		return;
//	}
//	this->setAllCookies(cookie_list);
//}

#endif // COOKIES_H
