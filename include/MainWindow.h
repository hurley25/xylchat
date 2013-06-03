// =====================================================================================
// 
//       Filename:  MainWindow.h
//
//    Description:  主窗口的声明
//
//        Version:  1.0
//        Created:  2013年06月03日 18时09分44秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
	
protected:
	void closeEvent(QCloseEvent *event);

private:
	void createMainWeiget(); 	// 创建主窗口控件
	void createActions(); 		// 创建动作
	void createToolBars(); 		// 创建工具栏
	void createStatusBar(); 	// 创建状态栏
private:
	ChatWidget *chatWidget; 	// 主窗口控件
	QLabel *statusLabel; 		// 状态栏文本
	QAction *aboutAction; 		// 关于本程序
};

#endif // MAIN_WINDOW_H_
