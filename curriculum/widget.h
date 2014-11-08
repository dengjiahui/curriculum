#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
	class login;
}

class widget: public QWidget {
	Q_OBJECT
public:
	explicit widget(QWidget* parent = nullptr);
	~widget();
protected:
	void paintEvent(QPaintEvent *) override;
private:
	QString load_qss(const QString& file_name) const;

	Ui::login* ui = nullptr;
};

#endif // WIDGET_H
