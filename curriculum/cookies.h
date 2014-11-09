#ifndef COOKIES_H
#define COOKIES_H

#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;
class QUrlQuery;
class QFile;

class cookies: public QNetworkCookieJar {
	Q_OBJECT
public:
	cookies(const QString& file, const QString& username,
		const QString& password);
	~cookies();
	QList<QNetworkCookie> get_cookies() const noexcept;
	void set_cookies(const QList<QNetworkCookie>& cookie_list) noexcept;
	void login() noexcept;
private slots:
	void request_finished();
	void request_ready() noexcept;
	void start_post(const QUrlQuery& params) noexcept;
	void start_get() noexcept;
private:
	QUrl url_;
	QNetworkReply* reply_ = nullptr;
	QNetworkAccessManager* manager_ = nullptr;
	QFile* information_ = nullptr;
	QString user_;
	QString passwd_;

	static const QString HFUT_URL;
};

inline QList<QNetworkCookie> cookies::get_cookies() const noexcept
{
	return allCookies();
}

inline void cookies::set_cookies(const QList<QNetworkCookie>& cookie_list)
									noexcept
{
	if(!this) {
		return;
	}
	this->setAllCookies(cookie_list);
}

#endif // COOKIES_H
