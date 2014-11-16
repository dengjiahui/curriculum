#include "html_parser.h"
#include "../cookies/cookies.h"

html_parser::html_parser(const QString& file, const QString& id,
			 const QString& passwd):
	cookies_info_(new cookies(file, id, passwd)) { }

html_parser::~html_parser()
{
	delete cookies_info_;
	cookies_info_ = nullptr;
}

void html_parser::login() noexcept
{
	cookies_info_->login();
	cookie = cookies_info_->get_cookies();
}

QHash<QString, QString> html_parser::get_person_info() const
{
	cookies_info_->cookie_get(qVariantFromValue(cookie),
				  "student/asp/xsxxxxx.asp");

}
