#include "thcli.h"

ThCli::ThCli(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.m_lcd->display("----");
	ui.m_lcd->setEnabled(false);
	connect(&sock,SIGNAL(connected()),this,SLOT(on_connedted()));
	connect(&sock,SIGNAL(readyRead()),this,SLOT(on_read()));
	connect(&sock,SIGNAL(disconnected()),this,SLOT(on_disconnedted()));
}

ThCli::~ThCli()
{

}
