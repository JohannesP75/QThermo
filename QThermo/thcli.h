#ifndef THCLI_H
#define THCLI_H

#include <QDialog>
#include "ui_thcli.h"
#include "thsrv.h"

class ThCli : public QDialog
{
	Q_OBJECT

	QTcpSocket sock;
public:
	ThCli(QWidget *parent = 0);
	~ThCli();
public slots:
	void on_m_connect_released(){ // Demande de connexion
		sock.connectToHost(ui.m_srvAddr->text(),SERV_PORT);
		ui.m_connect->setEnabled(false);
	}
	void on_connected(){ // Connexion acceptée
		ui.m_lcd->setEnabled(true);
		ui.m_connect->setText("Disconnect");
		//ui.m_connect->setEnabled(true); // Dernière ligne pas encore implémentée
	}
	void on_read(){ // Lire la température
		char temp;
		qint64 nb=sock.read(&temp,sizeof(temp));

		if(nb==sizeof(temp))ui.m_lcd->display(QString("%1'").arg((int)temp));
	}
	void on_disconnected(){ // Fermeture de connexion
		sock.close();
		ui.m_lcd->display("----");
		ui.m_lcd->setEnabled(false);
	}

private:
	Ui::ThCli ui;
};

#endif // THCLI_H
