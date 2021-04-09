#include "thsrv.h"

ThSrv::ThSrv(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	memset(client,0,MAX_CLIENTS*sizeof(QTcpSocket*)); // Mise à 0 du tableau
	connect(&srv,SIGNAL(newConnection()),this,SLOT(on_connexion()));
	srv.listen(QHostAddress::Any,SERV_PORT);
	timer.setInterval(1000);
	connect(&timer,SIGNAL(timeout()),this,SLOT(on_timer()));
}

ThSrv::~ThSrv()
{
	srv.close();
	for(size_t i=0;i<MAX_CLIENTS;i++)
		if(client[i]){
			client[i]->close();
			client[i]->deleteLater();
		}
}
