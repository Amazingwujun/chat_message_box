//
// Created by admin on 2023/5/30.
//

#ifndef CHAT_MESSAGE_BOX_CHATMESSAGEWRAPPERWIDGET_H
#define CHAT_MESSAGE_BOX_CHATMESSAGEWRAPPERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QDebug>
#include <QBitmap>
#include <QPainter>


class ChatMessageWrapperWidget : public QWidget {
Q_OBJECT


public:
    enum MessageType {
        _other,
        _myself,
        _time
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
    QLabel *name;
    /** 文字内容 */
    QTextEdit *content;
    QPixmap avatarImg;
    MessageType messageType;
    QSize avatarSize{48,48};

    /**
     * 圆角矩形的绘制
     *
     * @param src
     * @param radius
     * @return
     */
    static QPixmap pixmapToRound(const QPixmap &src, int radius){
        if (src.isNull())
        {
            return {};
        }
        QSize size(src.size());
        QBitmap mask(size);
        QPainter painter(&mask);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.fillRect(mask.rect(), Qt::white);
        painter.setBrush(QColor(0, 0, 0));
        painter.drawRoundedRect(mask.rect(), radius, radius);
        QPixmap image = src;
        image.setMask(mask);
        return image;
    }
};


#endif //CHAT_MESSAGE_BOX_CHATMESSAGEWRAPPERWIDGET_H
