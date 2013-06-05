// =====================================================================================
// 
//       Filename:  MainWindow.cpp
//
//    Description:  主窗口的实现
//
//        Version:  1.0
//        Created:  2013年06月03日 18时09分12秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "MainWindow.h"
#include "ChatWidget.h"
#include "OnlineList.h"

MainWindow::MainWindow()
{
	createMainWeiget();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    /*
    int res = QMessageBox::question(NULL, this->windowTitle(),
						tr("您真的要退出本程序吗？"),
						QMessageBox::Yes | QMessageBox::No);
    if (res == QMessageBox::Yes) {
		event->accept();
	} else{
		event->ignore();
    }
    */
    event->accept();
}

void MainWindow::createMainWeiget()
{
    onlineList = new OnlineList();
    chatWidget = new ChatWidget(onlineList);

    listLayout = new QVBoxLayout();
    listLayout->addWidget(onlineList);

    QWidget *listWidget = new QWidget();
    listWidget->setLayout(listLayout);

    mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(chatWidget);
    mainSplitter->addWidget(listWidget);
	
    setCentralWidget(mainSplitter);
    setWindowIcon(QIcon(":/res/images/logo.png"));
    resize(800, 550);
    setWindowTitle(tr("Xiyou Linux Group 交流工具"));
}
