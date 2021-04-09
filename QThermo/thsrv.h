#ifndef THSRV_H
#define THSRV_H

#include <QtGui/QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "ui_thsrv.h"

#define SERV_PORT 4040
#define MAX_CLIENTS 50

class ThSrv : public QDialog
{
	Q_OBJECT

	QTcpServer srv;
	QTcpSocket* client[MAX_CLIENTS];
	QTimer timer;
	void showMsg(const QString& s){
		ui.m_msgList->addItem(s);
		ui.m_msgList->scrollToBottom();
		ui.m_msgList->repaint();
	}
public:
	ThSrv(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ThSrv();
public slots:
	void on_m_send_released(){ // Emission de température
		char temp=(char)ui.m_thermo->value();

		for(size_t idx=0;idx<MAX_CLIENTS;idx++)
			if(client[idx])
				client[idx]->write(&temp,sizeof(temp));

		showMsg(QString("Nouvelle température : %1").arg((int)temp));
		timer.start();
	}
	void on_m_kill_all_released(){ // Deconnection de tout le monde
		for(size_t idx=0;idx<MAX_CLIENTS;idx++)
			if(client[idx]){
				client[idx]->close();
				client[idx]->deleteLater();
				client[idx]=0;
			}
	}
	void on_connexion(){ // Demande de connection
		size_t idx=0;

		while(client[idx]&&idx<MAX_CLIENTS)
			idx++;

		QTcpSocket* pCli=srv.nextPendingConnection();

		if(idx<MAX_CLIENTS){
			// On accepte
			showMsg(QString("Connexion acceptée pour %1:%2")
				.arg(pCli->peerAddress().toString()) // Adresse du client
				.arg(pCli->peerPort())); // Port de communication

			client[idx]=pCli;
			connect(client[idx],SIGNAL(disconnected()),this,SLOT(on_disconnected()));
		}else{
			// On refuse
			showMsg(QString("Connexion refusée pour %1:%2")
				.arg(pCli->peerAddress().toString())
				.arg(pCli->peerPort()));
			
			pCli->close();

			delete pCli;
		}
	}
	void on_disconnected(){ // Client perdu
		QTcpSocket* pCli=(QTcpSocket*)sender(); // Qui a envoyé le signal?

		if(!pCli)
			return;
		else{
			for(size_t idx=0;idx<MAX_CLIENTS;idx++)
				if(pCli==client[idx]){
					showMsg(QString("Fin de connexion refusée pour %1:%2")
						.arg(pCli->peerAddress().toString())
						.arg(pCli->peerPort()));
					pCli->close();
					pCli->deleteLater();
					client[idx]=0;
				}
		}
	}
	void on_timer(){
		char temp=(char)ui.m_thermo->value();

		for(size_t idx=0;idx<MAX_CLIENTS;idx++)
			if(client[idx])
				client[idx]->write(&temp,sizeof(temp));

		showMsg(QString("Température : %1").arg((int)temp));
	}
private:
	Ui::ThSrvClass ui;
};

#endif // THSRV_H
