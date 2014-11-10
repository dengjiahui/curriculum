#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
	class login;
}

class cookies;

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
	QString load_qss(const QString& file_name) const;
	cookies* info_cookies = nullptr;

	Ui::login* ui_ = nullptr;
};

#endif // WIDGET_H
