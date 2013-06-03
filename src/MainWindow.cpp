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

MainWindow::MainWindow()
{
	createMainWeiget();
	createStatusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
	int res = QMessageBox::question(NULL, this->windowTitle(),
						tr("您真的要退出本程序吗？"),
						QMessageBox::Yes | QMessageBox::No);
	if (res == QMessageBox::Yes) {
		event->accept();
	} else{
		event->ignore();
	}
}

void MainWindow::createMainWeiget()
{
	chatWidget = new ChatWidget();
	
	setCentralWidget(chatWidget);
	//setWindowIcon(QIcon(":/res/images/logo.png"));
	setWindowTitle(tr("Xiyou Linux Group 交流工具 ——  仅内部使用"));
}

void MainWindow::createStatusBar()
{
	statusLabel = new QLabel(tr("Xiyou Linux Group"));
	statusLabel->setAlignment(Qt::AlignHCenter);
	statusLabel->setMinimumSize(statusLabel->sizeHint());

	this->statusBar()->addWidget(statusLabel);
}

