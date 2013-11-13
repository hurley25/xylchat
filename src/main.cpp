// =====================================================================================
// 
//       Filename:  main.cpp
//
//    Description:  主程序文件
//
//        Version:  1.0
//        Created:  2013年06月03日 18时07分10秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	// 处理中文乱码问题
	QTextCodec *codec = QTextCodec::codecForName("system");

	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	
	QApplication app(argc, argv);

	//加载Qt自带的控件汉化文件
	QTranslator translator;

	translator.load(":/res/language/qt_zh_CN.qm");
	app.installTranslator(&translator);

	// 使用共享内存的方法确保本程序只运行一个实例
	QSystemSemaphore sema("xylchat_key", 1, QSystemSemaphore::Open);   
	sema.acquire();

	QSharedMemory mem("xylchat_lock");
	if (!mem.create(1)) {
		QMessageBox::information(0, "xylchat", "本程序只允许运行一个实例哦～亲");
		sema.release();
		return 0;   
	}
	
	MainWindow *mainwindow = new MainWindow();
	
	// 窗口显示在屏幕正中间
	mainwindow->move((QApplication::desktop()->width() - mainwindow->width()) >> 1,
				(QApplication::desktop()->height() - mainwindow->height()) >> 1);
	mainwindow->show();

	sema.release();

	return app.exec();
}

