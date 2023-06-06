//
// Created by admin on 2023/5/30.
//

#ifndef CHAT_MESSAGE_BOX_CHATMESSAGEWRAPPERWIDGET_H
#define CHAT_MESSAGE_BOX_CHATMESSAGEWRAPPERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QDebug>


class ChatMessageWrapperWidget : public QWidget {
Q_OBJECT


public:

    enum MessageType {
        from_myself,
        from_other,
        time_
    };

    explicit ChatMessageWrapperWidget(const QString &msg,MessageType type, QWidget *parent = nullptr);

    QSize calculateSizeByContent(int suggestedWidth = -1);
protected:
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    /** 头像 */
    QLabel *avatar;
    /** 名字 */
    QLabel *name{};
    /** 文字内容 */
    QTextEdit *content;
    QPixmap avatarImg;
    MessageType messageType;
};


#endif //CHAT_MESSAGE_BOX_CHATMESSAGEWRAPPERWIDGET_H
