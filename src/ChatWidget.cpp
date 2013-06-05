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
#include "OnlineList.h"

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
	chatText->setFocusPolicy(Qt::NoFocus);

	sendText = new QTextEdit();
	sendText->setFocusPolicy(Qt::StrongFocus);
	sendText->setFocus();
	sendText->installEventFilter(this);
	sendText->setMaximumHeight(sendText->sizeHint().height() >> 1);

	fontSizeButton = new QPushButton(QIcon(":/res/images/fonts.png"), tr(""));
	connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(fontSize()));
	fontBoldButton = new QPushButton(QIcon(":/res/images/textbold.png"), tr(""));
	connect(fontBoldButton, SIGNAL(clicked()), this, SLOT(fontBold()));
	fontItalicButton = new QPushButton(QIcon(":/res/images/textitalic.png"), tr(""));
	connect(fontItalicButton, SIGNAL(clicked()), this, SLOT(fontItalic()));
	fontColorButton = new QPushButton(QIcon(":/res/images/textcolor.png"), tr(""));;
	connect(fontColorButton, SIGNAL(clicked()), this, SLOT(fontColor()));
	saveChatInfoButton = new QPushButton(QIcon(":/res/images/save.png"), tr(""));
	connect(saveChatInfoButton, SIGNAL(clicked()), this, SLOT(saveChatInfo()));
	clearChatInfoButton = new QPushButton(QIcon(":/res/images/bin_empty.png"), tr(""));
	connect(clearChatInfoButton, SIGNAL(clicked()), this, SLOT(clearChatInfo()));

	toolHBoxLayout = new QHBoxLayout;
	toolHBoxLayout->addWidget(fontSizeButton);
	toolHBoxLayout->addWidget(fontBoldButton);
	toolHBoxLayout->addWidget(fontItalicButton);
	toolHBoxLayout->addWidget(fontColorButton);
	toolHBoxLayout->addWidget(saveChatInfoButton);
	toolHBoxLayout->addWidget(clearChatInfoButton);
	toolHBoxLayout->addStretch();

	sendButton = new QPushButton(tr("发送(&S)"));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendSlot()));

	buttonHBoxLayout = new QHBoxLayout();
	buttonHBoxLayout->addStretch();
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
	// 监听本机上的 UDP 9527 端口。如果有消息到来，套接字就会发送readyRead()信号
	listen_port = 9527;
	/*
	 * QUdpSocket::ShareAddress
	 * Allow other services to bind to the same address and port.
	 *
	 * QUdpSocket::ReuseAddressHint
	 * Provides a hint to QUdpSocket that it should try to rebind the service
	 * even if the address and port are already bound by another socket.
	 */
	sockServer->bind(listen_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	connect(sockServer, SIGNAL(readyRead()), this, SLOT(recvMessage()));
	sendMessage(UserLogin);
}

void ChatWidget::sendMessage(MessageType type)
{
	QByteArray data;
	QDataStream sendData(&data, QIODevice::WriteOnly);

	// 消息依次是 消息类型-用户名-主机名-IP地址-（发送消息）
	sendData << type << getUserName() << QHostInfo::localHostName() << getIP();

	switch (type) {
		case Message:
			sendData << getMessage();
			break;
		case UserLogin:
		case Userleft:
			// do nothing
			break;
	}
	/*
	 * QHostAddress::Broadcast	1
	 * The IPv4 broadcast address. Equivalent to QHostAddress("255.255.255.255")
	 */
	sockServer->writeDatagram(data, data.length(), QHostAddress::Broadcast, listen_port);
}

void ChatWidget::recvMessage()
{
	while (sockServer->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(sockServer->pendingDatagramSize());
		sockServer->readDatagram(datagram.data(), datagram.size());
		QDataStream recvData(&datagram, QIODevice::ReadOnly);

		int messageType;
		QString username, hostname, ipAddr, message;

		recvData >> messageType >> username >> hostname >> ipAddr;

		switch (messageType) {
			case Message:
				recvData >> message;
				addUserChatInfoOnce(username, message);
				break;
			case UserLogin:
				disUserLogin(username, hostname, ipAddr);
				break;
			case Userleft:
				disUserLeft(username, hostname, ipAddr);
				break;
		}
	}
}

QString ChatWidget::getIP()
{
	QList<QHostAddress> list = QNetworkInterface::allAddresses();

	foreach (QHostAddress address, list) {
		// 只获取 IPv4 协议地址
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
			}
		}
	}

	return NULL;
}

QString ChatWidget::getMessage()
{
	QString msg = sendText->toHtml();

	sendText->clear();
	sendText->setFocus();

	return msg;
}

void ChatWidget::addUserChatInfoOnce(QString username, QString message)
{
	QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

	chatText->setTextColor(Qt::blue);
	chatText->setCurrentFont(QFont("Times New Roman", 12));
	chatText->append(username + " " + time);
	chatText->append(message);
}

void ChatWidget::disUserLogin(QString username, QString hostname, QString ipAddr)
{
	chatText->setTextColor(Qt::gray);
	chatText->setCurrentFont(QFont("Times New Roman", 10));
	chatText->append(tr("%1 [ %2 ] 加入了聊天室。").arg(username).arg(ipAddr));
	onlineList->insertUserInfo(username, hostname, ipAddr);
}

void ChatWidget::disUserLeft(QString username, QString hostname, QString ipAddr)
{
	chatText->setTextColor(Qt::gray);
	chatText->setCurrentFont(QFont("Times New Roman", 10));
	chatText->append(tr("%1 [ %2 ] 离开了聊天室。").arg(username).arg(ipAddr));
	onlineList->removeUserInfo(hostname);
}

void ChatWidget::closeEvent(QCloseEvent *)
{
	sendMessage(Userleft);
}

bool ChatWidget::eventFilter(QObject *target, QEvent *event)
{
	if (target == sendText) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *k = static_cast<QKeyEvent *>(event);
			if (k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
			{
				sendSlot();
				return true;
			}
		}
	}

	return QWidget::eventFilter(target, event);
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
	QColor color = QColorDialog::getColor();
	if (color.isValid()) {
		chatText->setTextColor(color);
		sendText->setFocus();
	}
}

void ChatWidget::saveChatInfo()
{
	if (chatText->document()->isEmpty()) {
		QMessageBox::information(NULL, tr("友情提醒"),
					tr("聊天记录为空，无法保存。"), QMessageBox::Ok);
	} else {
		QString fileName = QFileDialog::getSaveFileName(this,
					tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;All File(*.*)"));
		if (!fileName.isEmpty()) {
			QFile file(fileName);
			if (!file.open(QFile::WriteOnly | QFile::Text)) {
				QMessageBox::warning(this,tr("保存文件"),
							tr("无法保存文件 %1:\n %2").arg(fileName)
							.arg(file.errorString()));
			}
			QTextStream outFile(&file);
			outFile << chatText->toPlainText();
		}
	}
}

void ChatWidget::clearChatInfo()
{
	chatText->clear();
}

void ChatWidget::sendSlot()
{
	if (sendText->toPlainText() == "") {
		QMessageBox::information(NULL, tr("友情提醒"),
					tr("你什么都没输入，发个毛线～～"), QMessageBox::Ok);
	} else {
		sendMessage(Message);
	}
}
