#include "mainwindow.h"
#include <QMessageBox>

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect_mysql(db);




}

mainwindow::~mainwindow()
{
	mysql_close(db); //�ر�����
}

void mainwindow::connect_mysql(MYSQL* db)
{
	//�������ݿ�
	db = mysql_init(NULL); //��ʼ��
	if (db == NULL)
		QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ʼ��ʧ��!"), QString::fromLocal8Bit("ȷ��"));
	MYSQL* conn = mysql_real_connect(db, "localhost", "root", "passwordmysql", "stu_db", 0, NULL, 0); //��������
	if (conn == NULL)
		QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ݿ�����ʧ��!"), QString::fromLocal8Bit("ȷ��"));
	/*
	else
		QMessageBox::information(this, QString::fromLocal8Bit("��Ϣ"), QString::fromLocal8Bit("���ݿ����ӳɹ�!"), QString::fromLocal8Bit("ȷ��"));
	*/
}
