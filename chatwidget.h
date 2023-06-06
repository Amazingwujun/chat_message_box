//
// Created by admin on 2023/6/1.
//

#ifndef CHAT_MESSAGE_BOX_CHATWIDGET_H
#define CHAT_MESSAGE_BOX_CHATWIDGET_H

#include <QWidget>
#include "chatmessagewrapperwidget.h"
#include <QRandomGenerator>


QT_BEGIN_NAMESPACE
namespace Ui { class ChatWidget; }
QT_END_NAMESPACE

class ChatWidget : public QWidget {
Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);

    ~ChatWidget() override;


public slots:
    void onMessageReceived(const QString &msg, ChatMessageWrapperWidget::MessageType type);

protected:
    void resizeEvent(QResizeEvent *event) override;


private:
    Ui::ChatWidget *ui;
};


#endif //CHAT_MESSAGE_BOX_CHATWIDGET_H
