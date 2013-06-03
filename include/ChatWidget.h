// =====================================================================================
// 
//       Filename:  ChatWidget.h
//
//    Description:  聊天显示控件的声明
//
//        Version:  1.0
//        Created:  2013年06月03日 18时43分32秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef CHATWIDGET_H_
#define CHATWIDGET_H_

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QSplitter;
class QTextBrowser;
class QTextEdit;
class QListView;
class QPushButton;
class QComboBox;
class QPushButton;

class ChatWidget : public QWidget
{
	Q_OBJECT
public:
	ChatWidget();
	~ChatWidget();

	void createWidget();

private:
	QVBoxLayout  *mainVBoxLayout;
	QHBoxLayout  *toolHBoxLayout;
	QHBoxLayout  *buttonHBoxLayout;

	QTextBrowser *chatText;
	QTextEdit    *sendText;

	QPushButton  *closeButton;
	QPushButton  *sendButton;

	QComboBox    *fontListComboBox;
	QComboBox    *fontSizeComboBox;
	QPushButton  *fontBoldButton;
	QPushButton  *fontInclineButton;
	QPushButton  *fontColorButton;
	QPushButton  *saveChatInfoButton;
	QPushButton  *clearChatInfoButton;
};

#endif // CHATWIDGET_H_
