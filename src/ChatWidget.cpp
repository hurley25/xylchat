// =====================================================================================
// 
//       Filename:  ChatWidget.cpp
//
//    Description:  聊天显示控件
//
//        Version:  1.0
//        Created:  2013年06月03日 18时41分50秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "ChatWidget.h"

ChatWidget::ChatWidget()
{
	createWidget();
    createNetLink();
}

ChatWidget::ChatWidget(OnlineList *onlineList)
{
    this->onlineList = onlineList;
    createWidget();
    createNetLink();
}

ChatWidget::~ChatWidget()
{
    delete sockServer;
}

void ChatWidget::createWidget()
{
	chatText = new QTextBrowser();
	sendText = new QTextEdit();
    sendText->setMaximumHeight(sendText->sizeHint().height() >> 1);

    fontSizeButton = new QPushButton(QIcon(":/res/images/fonts.png"), tr(""));
    connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(fontSize()));
    fontBoldButton = new QPushButton(QIcon(":/res/images/textbold.png"), tr(""));
    connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(fontBold()));
    fontItalicButton = new QPushButton(QIcon(":/res/images/textitalic.png"), tr(""));
    connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(fontItalic()));
    fontColorButton = new QPushButton(QIcon(":/res/images/textcolor.png"), tr(""));;
    connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(fontColor()));
    saveChatInfoButton = new QPushButton(QIcon(":/res/images/save.png"), tr(""));
    connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(saveChatInfo()));
    clearChatInfoButton = new QPushButton(QIcon(":/res/images/bin_empty.png"), tr(""));
    connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(clearChatInfo()));

	toolHBoxLayout = new QHBoxLayout;
    toolHBoxLayout->addWidget(fontSizeButton);
	toolHBoxLayout->addWidget(fontBoldButton);
    toolHBoxLayout->addWidget(fontItalicButton);
	toolHBoxLayout->addWidget(fontColorButton);
	toolHBoxLayout->addWidget(saveChatInfoButton);
	toolHBoxLayout->addWidget(clearChatInfoButton);
	toolHBoxLayout->addStretch();
	
    onlineLabel = new QLabel(tr("当前在线 1 人"));
	closeButton = new QPushButton(tr("关闭(&C)"));
	sendButton = new QPushButton(tr("发送(&S)"));

	buttonHBoxLayout = new QHBoxLayout();
    buttonHBoxLayout->addWidget(onlineLabel);
	buttonHBoxLayout->addStretch();
	buttonHBoxLayout->addWidget(closeButton);
	buttonHBoxLayout->addWidget(sendButton);

	mainVBoxLayout = new QVBoxLayout();
	mainVBoxLayout->addWidget(chatText);
	mainVBoxLayout->addLayout(toolHBoxLayout);
	mainVBoxLayout->addWidget(sendText);
	mainVBoxLayout->addLayout(buttonHBoxLayout);

	setLayout(mainVBoxLayout);
}

void ChatWidget::createNetLink()
{
    sockServer = new QUdpSocket();
    listen_port = 9527;
    sockServer->bind(listen_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(sockServer, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    sendMessage(MyLogin);
}

void ChatWidget::sendMessage(MessageType type, QString sendInfo)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    QString address = getIP();

    out << type << getUserName() << localHostName;

    switch (type) {
        case Message:
            if (sendText->toPlainText() == "") {
                return;
            }
            out << address << getMessage();
        break;
        case MyLogin:
        break;
        case UserLogin:
        break;
        case Userleft:
        break;
        default:
        break;
    }
    sockServer->writeDatagram(data, data.length(), QHostAddress::Broadcast, listen_port);
}

void ChatWidget::recvMessage()
{
    while (sockServer->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(sockServer->pendingDatagramSize());
        sockServer->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName, localHostName, ipAddress, message;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        switch (messageType) {
            case Message:
            break;
            case UserLogin:
            break;
            case Userleft:
            break;
            default:
            break;
        }
    }
}

QString ChatWidget::getMessage()
{
    QString msg = sendText->toHtml();

    sendText->clear();
    sendText->setFocus();

    return msg;
}

QString ChatWidget::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            return address.toString();
        }
    }

    return 0;
}

QString ChatWidget::getUserName()
{
    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
        << "HOSTNAME.*" << "DOMAINNAME.*";
    QStringList environment = QProcess::systemEnvironment();
    foreach (QString string, envVariables) {
        int index = environment.indexOf(QRegExp(string));
        if (index != -1) {
            QStringList stringList = environment.at(index).split('=');
            if (stringList.size() == 2) {
                return stringList.at(1);
                break;
            }
        }
    }

    return NULL;
}

void ChatWidget::fontSize()
{

}

void ChatWidget::fontBold()
{

}

void ChatWidget::fontItalic()
{

}

void ChatWidget::fontColor()
{

}

void ChatWidget::saveChatInfo()
{

}

void ChatWidget::clearChatInfo()
{

}
