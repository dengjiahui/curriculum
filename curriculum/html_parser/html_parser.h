#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <QHash>
#include <QNetworkCookie>
#include <QVariant>

class cookies;

class html_parser {
public:
	html_parser(const QString& file, const QString& id,
		    const QString& passwd);
	~html_parser();
	void login() noexcept;
	QHash<QString, QString> get_person_info() const;
private:
	cookies* cookies_info_ = nullptr;
	QList<QNetworkCookie> cookie;
};

#endif // HTML_PARSER_H
