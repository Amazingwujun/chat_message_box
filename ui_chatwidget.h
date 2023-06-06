/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QWidget *widget;
    QTextEdit *textEdit;
    QPushButton *send_btn;
    QWidget *tools_widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName(QString::fromUtf8("ChatWidget"));
        ChatWidget->resize(614, 531);
        ChatWidget->setMinimumSize(QSize(500, 400));
        verticalLayout_2 = new QVBoxLayout(ChatWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(ChatWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget \n"
"{\n"
"  background-color: #f5f5f5;\n"
"  border-left: 0px;\n"
"  border-top: 0px;\n"
"  border-right: 0px;\n"
"}\n"
"QScrollBar:vertical\n"
"{\n"
"    width:8px;\n"
"    background:rgba(0,0,0,0%);\n"
"    margin:0px,0px,0px,0px;\n"
"    padding-top:9px;  \n"
"    padding-bottom:9px;\n"
"}\n"
"\n"
"QListView:item:selected:active:\n"
"{\n"
"	background-color: #f5f5f5;\n"
"}\n"
"\n"
"QListView:item:selected:!active\n"
"{\n"
"	background-color: #f5f5f5;\n"
"}\n"
"\n"
"QListView:item:selected:hover\n"
"{\n"
"	background-color: #f5f5f5;\n"
"}"));
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setTextElideMode(Qt::ElideMiddle);
        listWidget->setSpacing(1);

        verticalLayout_2->addWidget(listWidget);

        widget = new QWidget(ChatWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"  border: 0px;\n"
"  background-color: #f5f5f5;\n"
"}"));
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(9, 9, 509, 168));
        textEdit->setStyleSheet(QString::fromUtf8("background-color: #f5f5f5"));
        send_btn = new QPushButton(widget);
        send_btn->setObjectName(QString::fromUtf8("send_btn"));
        send_btn->setGeometry(QRect(430, 140, 111, 31));
        send_btn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: #e9e9e9;\n"
"  font-size: 15px;\n"
"}\n"
"\n"
"QPushButton::hover {\n"
"  background-color: #b3b3b3;\n"
"}"));
        tools_widget = new QWidget(widget);
        tools_widget->setObjectName(QString::fromUtf8("tools_widget"));
        tools_widget->setGeometry(QRect(10, 0, 501, 40));
        tools_widget->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: #f5f5f5;"));
        horizontalLayout = new QHBoxLayout(tools_widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 0, 0);
        label = new QLabel(tools_widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(464, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(widget);

        verticalLayout_2->setStretch(0, 8);
        verticalLayout_2->setStretch(1, 3);

        retranslateUi(ChatWidget);

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QCoreApplication::translate("ChatWidget", "ChatWidget", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatWidget", "\345\217\221\351\200\201", nullptr));
        label->setText(QCoreApplication::translate("ChatWidget", "\350\241\250\346\203\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
