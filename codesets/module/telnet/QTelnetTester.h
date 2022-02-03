#ifndef QTELNETTESTER_H
#define QTELNETTESTER_H

#include <QMainWindow>
#include <QTimer>
#include "QTelnet.h"

namespace Ui
{
	class QTelnetTester;
}

class QTelnetTester : public QMainWindow
{
	Q_OBJECT

	Ui::QTelnetTester *ui;
	QTelnet telnet;

public:
	explicit QTelnetTester(QWidget *parent = 0);
	~QTelnetTester();

private slots:
	void onStateChanged(QAbstractSocket::SocketState s);

	void on_btConnect_clicked();
	void onCommand(const QString &cmd);

    void on_action_focus_to_cmd_triggered();

    void on_action_clear_cmd_triggered();

public slots:
	void setStatusText(const QString &msg, bool onMainWindow = false);
	void addText(const char *msg, int count);

private:
    QTimer *pCmdTimer;

public slots:
    void onCmdTimeOut();
};

#endif // QTELNETTESTER_H
