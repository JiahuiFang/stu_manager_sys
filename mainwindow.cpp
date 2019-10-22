#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect_mysql();
    connect(ui->btn_login, SIGNAL(clicked(bool)), this, SLOT(login()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_mysql()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("mysql_connect")) {
        db = QSqlDatabase::database("mysql_connect");
    } else {
        //�������ݿ�
        db = QSqlDatabase::addDatabase("QMYSQL", "mysql_connect"); //���ݿ�����
        db.setHostName("localhost");    //����Ϊ��������
        db.setDatabaseName("stu_db");   //ѡ�����ݿ�����
        db.setUserName("root");         //�����û���
        db.setPassword("passwordmysql");//��������
        if(!db.open())
            QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���ݿ�����ʧ��!"), QString::fromLocal8Bit("ȷ��"));
        //	else
        //		QMessageBox::information(this, QString::fromLocal8Bit("��Ϣ"), QString::fromLocal8Bit("���ݿ����ӳɹ�!"), QString::fromLocal8Bit("ȷ��"));
    }

}

bool MainWindow::is_stu() {
    return (user_type == "stu" ? 1 : 0);
}

void MainWindow::login()
{
    //��ȡ��¼��Ϣ
    QString user_t = ui->typeGroup->checkedButton()->text();
    QString id = ui->le_user->text();
    QString password = ui->le_password->text();
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);
    //    db.exec("SET NAMES 'GBK'");
    user_type = (user_t == QString::fromLocal8Bit("ѧ��")) ? "Stu" : "admin";
    //��֤��¼��Ϣ
    if(user_type == "admin") { //����Ա��Ϣ��֤
        query.exec("select id, password, name from admin");
        bool flag = false;
        while(query.next()) {
            QString id_temp = query.value(0).toString();
            QString password_temp = query.value(1).toString();
            user_name = query.value(2).toString();
            if (id == id_temp && password == password_temp) {
                flag = true;
            }
        }
        if(flag) {  //�û�������ȷ, �����menu_admin����
            this->hide();
            m_a = new menu_admin;
            connect(m_a, SIGNAL(signal_ret()), this, SLOT(reshow()));
            connect(this, SIGNAL(send_name(QString)), m_a, SLOT(get_name(QString))); //�����û������Ӵ���
            emit send_name(user_name);
            m_a->show();
        } else {
            QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˻��������,����������!"), QString::fromLocal8Bit("ȷ��"));
            clearUI();
        }
    } else {                    //ѧ����Ϣ��֤
        query.exec("select stu_id, password, name from stu");
        bool flag = false;
        while(query.next()) {
            QString stu_id_temp = query.value(0).toString();
            QString password_temp = query.value(1).toString();
            user_name = query.value(2).toString();
            if (id == stu_id_temp && password == password_temp) {
                flag = true;
            }
        }
        if(flag) {  //�û�������ȷ, �����menu_stu����
            this->hide();
            m_s = new menu_stu;
            connect(m_s, SIGNAL(signal_ret()), this, SLOT(reshow()));
            connect(this, SIGNAL(send_name(QString)), m_s, SLOT(get_name(QString)));
            emit send_name(user_name);
            connect(this, SIGNAL(send_stu_id(QString)), m_s, SLOT(get_stu_id(QString)));
            emit send_stu_id(id);
            m_s->show();
        } else {
            QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�˻��������,����������!"), QString::fromLocal8Bit("ȷ��"));
            clearUI();
        }
    }
}

void MainWindow::reshow() {
    clearUI();
    this->show();
}

void MainWindow::clearUI() {
    ui->le_user->clear();
    ui->le_password->clear();
    ui->rbtn_stu->setChecked(true);
}


