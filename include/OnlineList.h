// =====================================================================================
// 
//       Filename:  OnlineList.h
//
//    Description:  在线用户列表
//
//        Version:  1.0
//        Created:  2013年06月04日 08时46分22秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef ONLINELIST_H_
#define ONLINELIST_H_

#include <QTableWidget>

class OnlineList : public QTableWidget
{
	Q_OBJECT
public:
	OnlineList();
	~OnlineList();
    void createViewTitle();
    void insertUserInfo(QString nickname, QString hostname, QString ipaddr);
    void removeUserInfo(QString userName, QString localHostName);
};

#endif // ONLINELIST_H_
