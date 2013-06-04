// =====================================================================================
// 
//       Filename:  OnlineList.cpp
//
//    Description:  在线用户列表
//
//        Version:  1.0
//        Created:  2013年06月04日 08时45分48秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>
#include <QtNetwork>

#include "OnlineList.h"

OnlineList::OnlineList()
{
    createViewTitle();
    insertUserInfo("hurley", "fedora", "127.0.0.1");
}

OnlineList::~OnlineList()
{

}

void OnlineList::createViewTitle()
{
    // 只允许单选
    setSelectionMode(QAbstractItemView::SingleSelection);
    // 每次选中一行
    setSelectionBehavior(QAbstractItemView::SelectRows);
    // 默认不允许用户编辑数据
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 使列完全填充并平分
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    // 数据头左对齐
    horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    // 隐藏左边垂直列号
    verticalHeader()->setVisible(false);
    // 设置列数
    setColumnCount(3);
    // 设置不显示格子线
    setShowGrid(false);
    // 设置表头
    setHorizontalHeaderItem(0, new QTableWidgetItem(tr("昵称")));
    setHorizontalHeaderItem(1, new QTableWidgetItem(tr("主机名")));
    setHorizontalHeaderItem(2, new QTableWidgetItem(tr("IP地址")));
}

void OnlineList::insertUserInfo(QString nickname, QString hostname, QString ipaddr)
{
    bool isAdded = findItems(QHostInfo::localHostName(), Qt::MatchExactly).isEmpty();
    if (isAdded) {
        insertRow(0);
        setItem(0, 0, new QTableWidgetItem(nickname));
        setItem(0, 1, new QTableWidgetItem(hostname));
        setItem(0, 2, new QTableWidgetItem(ipaddr));
    }
}

void OnlineList::removeUserInfo(QString userName, QString localHostName)
{
    int rowNum = findItems(localHostName,Qt::MatchExactly).first()->row();
    removeRow(rowNum);
}

