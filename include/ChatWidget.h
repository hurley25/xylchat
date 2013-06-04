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
class QLabel;
class OnlineList;

// 用户消息类型的枚举变量
enum MessageType {
    Message   = 0,
    MyLogin   = 1,
    UserLogin = 2,
    Userleft  = 3
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

private slots:
    void fontSize();
    void fontBold();
    void fontItalic();
    void fontColor();
    void saveChatInfo();
    void clearChatInfo();

    // 发送数据包
    void sendMessage(MessageType type, QString sendInfo = "");
    // 接收处理数据包
    void recvMessage();
    // 获取IP地址
    QString getIP();
    // 获取用户名
    QString getUserName();
    // 获取输入信息
    QString getMessage();

private:
    QUdpSocket *sockServer;
    qint16      listen_port;

    OnlineList *onlineList;

	QVBoxLayout  *mainVBoxLayout;
	QHBoxLayout  *toolHBoxLayout;
	QHBoxLayout  *buttonHBoxLayout;

	QTextBrowser *chatText;
	QTextEdit    *sendText;

    QLabel       *onlineLabel;
	QPushButton  *closeButton;
	QPushButton  *sendButton;

    QPushButton  *fontSizeButton;
    QPushButton  *fontBoldButton;
    QPushButton  *fontItalicButton;
	QPushButton  *fontColorButton;
	QPushButton  *saveChatInfoButton;
	QPushButton  *clearChatInfoButton;
};

#endif // CHATWIDGET_H_
