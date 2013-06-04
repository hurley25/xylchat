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
}

ChatWidget::~ChatWidget()
{

}

void ChatWidget::createWidget()
{
	chatText = new QTextBrowser();
	sendText = new QTextEdit();
    sendText->setMaximumHeight(sendText->sizeHint().height() >> 1);

	fontListComboBox = new QComboBox();
	fontSizeComboBox = new QComboBox();
	fontBoldButton = new QPushButton();
	fontInclineButton = new QPushButton();
	fontColorButton = new QPushButton();
	saveChatInfoButton = new QPushButton();
	clearChatInfoButton = new QPushButton();
	
	toolHBoxLayout = new QHBoxLayout;
	toolHBoxLayout->addWidget(fontListComboBox);
	toolHBoxLayout->addWidget(fontSizeComboBox);
	toolHBoxLayout->addWidget(fontBoldButton);
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

