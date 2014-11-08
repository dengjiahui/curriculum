#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUrl>

namespace Ui {
	class login;
}

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

class widget: public QWidget {
	Q_OBJECT
public:
	explicit widget(QWidget* parent = nullptr);
	~widget();
protected:
	void paintEvent(QPaintEvent *) override;
private slots:
	void on_button_login_clicked();
private:
	void request_finished();
	void request_ready() const noexcept;
	void login(const QString& id, const QString& passwd);
	QString load_qss(const QString& file_name) const;

	QUrl url;
	QNetworkReply* reply = nullptr;
	QNetworkAccessManager* manager = nullptr;
	QFile* information = nullptr;
	Ui::login* ui = nullptr;	
};

#endif // WIDGET_H
