#include "thsrv.h"
#include "thcli.h"
#include <QtGui/QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ThSrv wSrv;
	ThCli wCli;
	QMessageBox box(QMessageBox::Question,QString("Client ou serveur?"),QString("Client ou serveur?"),QMessageBox::Cancel);
	QAbstractButton* bCli=(QAbstractButton*)box.addButton(QString("Client"),QMessageBox::AcceptRole);
	QAbstractButton* bSrv=(QAbstractButton*)box.addButton(QString("Serveur"),QMessageBox::AcceptRole);

	box.exec();
	QAbstractButton* S=box.clickedButton();

	if(S==bCli){
		wCli.show();
		
		return a.exec();
	}else if(S==bSrv){
		wSrv.show();

		return a.exec();
	}else{
		return a.exec(); 
	}	
}
