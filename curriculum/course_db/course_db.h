#ifndef COURSE_DB_H
#define COURSE_DB_H

#include <QSqlDatabase>
#include <QSqlQuery>

class course_db {
public:
	course_db();
	bool is_open() noexcept;
private:
	QSqlDatabase course = QSqlDatabase::addDatabase("QSQLITE");
	QSqlQuery query;
};

inline
bool course_db::is_open() noexcept
{
	if (!course.open()) {
		return false;
	}
	return true;
}

#endif // COURSE_DB_H
