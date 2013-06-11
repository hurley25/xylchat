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
#include <QtNetwork>

class QVBoxLayout;
class QHBoxLayout;
class QSplitter;
class QTextBrowser;
class QTextEdit;
class QListView;
class QPushButton;
class OnlineList;

// 用户消息类型的枚举变量
enum MessageType {
	Message      = 0,
	UserLogin    = 1,
	Userleft     = 2,
	AskWhoOnline = 3,
	IamOnline    = 4
};

class ChatWidget : public QWidget
{
	Q_OBJECT
public:
	ChatWidget();
	ChatWidget(OnlineList *onlineList);
	~ChatWidget();

	void createWidget();
	void createNetLink();

protected:
	void closeEvent(QCloseEvent *);
	bool eventFilter(QObject *target, QEvent *event);

public slots:
	void fontSize();
	void fontBold();
	void fontItalic();
	void fontUnderline();
	void fontColor();
	void insertImage();
	void saveChatInfo();
	void clearChatInfo();
	void sendSlot();

	// 发送数据包
	void sendMessage(MessageType type, QString ipAddr = "");
	// 接收处理数据包
	void recvMessage();

private:
	// 获取IP地址
	QString getIP();
	// 获取用户名
	QString getUserName();
	// 获取输入信息
	QString getMessage();

	// 聊天框添加一条聊天信息
	void addUserChatInfoOnce(QString username, QString message);

	// 处理用户上线
	void disUserLogin(QString username, QString hostname, QString ipAddr);
	// 处理用户离线
	void disUserLeft(QString username, QString hostname, QString ipAddr);

private:
	QUdpSocket *sockServer;
	qint16      listen_port;

	OnlineList *onlineList;

	QVBoxLayout  *mainVBoxLayout;
	QHBoxLayout  *toolHBoxLayout;
	QHBoxLayout  *buttonHBoxLayout;

	QTextBrowser *chatText;
	QTextEdit    *sendText;

	QPushButton  *closeButton;
	QPushButton  *sendButton;

	QPushButton  *fontSizeButton;
	QPushButton  *fontBoldButton;
	QPushButton  *fontItalicButton;
	QPushButton  *fontUnderlineButton;
	QPushButton  *fontColorButton;
	QPushButton  *insertImageButton;
	QPushButton  *saveChatInfoButton;
	QPushButton  *clearChatInfoButton;
};

#endif // CHATWIDGET_H_
