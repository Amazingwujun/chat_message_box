//
// Created by admin on 2023/5/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatMessageWrapperWidget.h" resolved

#include "chatmessagewrapperwidget.h"
#include "qabstracttextdocumentlayout.h"
#include <QPainter>


ChatMessageWrapperWidget::ChatMessageWrapperWidget(const QString &msg, ChatMessageWrapperWidget::MessageType type,
                                                   QWidget *parent) :
        QWidget(parent), messageType(type) {
    // 头像位置
    avatar = new QLabel("头像", this);
    avatarImg = QPixmap(":/resources/img/jun.jpg");
    avatar->setFixedHeight(40);
    avatar->setFixedWidth(40);
    avatar->setPixmap(avatarImg.scaled(avatar->size()));
    avatar->setStyleSheet("border-radius: 5px;");

    // 聊天内容处理
    content = new QTextEdit(this);
    content->setReadOnly(true);
    content->setWordWrapMode(QTextOption::WrapMode::WrapAnywhere);
    content->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    content->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto font = QFont("Microsoft Yahei"); // 字体配置
    font.setPointSize(10);
    content->setFont(font);
    content->setText(msg);
    content->setStyleSheet("border-radius: 5px; background-color: white; border: 0px; padding: 5px;");

//    this->setFixedWidth(parent->width());
    switch (type) {
        case time_: {
            break;
        }
        case from_other: {
            this->avatar->move(this->width() - this->avatar->width() - 20, 5);
            content->move(avatar->x() - 10 - content->width(), avatar->y());
            break;
        }
        case from_myself: {
            avatar->move(20, 5);
            content->move(avatar->x() + avatar->width() + 10, avatar->y());
            break;
        }
    }
}


void ChatMessageWrapperWidget::resizeEvent(QResizeEvent *event) {
    qDebug("Chat Message Wrapper widget resizeEvent: ", this->width());

//    switch (this->messageType) {
//        case from_other:{
//            qDebug("this.w: %d", this->width());
//            this->avatar->move(this->width() - this->avatar->width() - 20, this->height() - this->avatar->height() - 5);
//            content->move(avatar->x() - 15 - content->width(), avatar->y());
//            break;
//        }
//    }

    auto size = calculateSizeByContent();
    qInfo("size[w: %d h: %d]", size.width(), size.height());
    content->setFixedWidth(size.width());
    content->setFixedHeight(size.height());
}

void ChatMessageWrapperWidget::paintEvent(QPaintEvent *event) {
//    qInfo() << "ChatMessageWrapperWidget::paintEvent 事件触发";

    // 左边三角绘制
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    switch (this->messageType) {
        case time_: {
            break;
        }
        case from_myself: {
            // 指定位置
            auto ah = avatar->height();
            auto ay = avatar->y();
            auto centerY = ay + ah / 2;

            QPoint points[] = {
                    QPoint(this->content->x(), centerY - 5),
                    QPoint(this->content->x() - 5, centerY),
                    QPoint(this->content->x(), centerY + 5)
            };

            painter.setPen(QPen(QColor(Qt::white)));
            painter.setBrush(QBrush(QColor(Qt::white)));
            painter.drawPolygon(points, 3);
            break;
        }
        case from_other: {
            this->avatar->move(this->width() - this->avatar->width() - 20, 5);
            content->move(avatar->x() - 10 - content->width(), avatar->y());

            auto ah = avatar->height();
            auto ay = avatar->y();
            auto centerY = ay + ah / 2;

            QPoint points[] = {
                    QPoint(this->content->x() + this->content->width(), centerY - 5),
                    QPoint(this->content->x() + this->content->width() + 5, centerY),
                    QPoint(this->content->x() + this->content->width(), centerY + 5)
            };

            painter.setPen(QPen(QColor(Qt::white)));
            painter.setBrush(QBrush(QColor(Qt::white)));
            painter.drawPolygon(points, 3);
            break;
        }
    }
}

/**
 * 根据指定内容计算获取 QSize
 *
 * @param suggestedWidth
 * @return
 */
QSize ChatMessageWrapperWidget::calculateSizeByContent(int suggestedWidth) {
    // 文档、内容、字体度量
    auto text = content->toPlainText();
    auto fm = content->fontMetrics();
    if (suggestedWidth <= 0) {
        suggestedWidth = this->width();
    }

    // 内容长度
    auto fh = fm.height();

    // 获取长度
    switch (messageType) {
        case from_myself:{
            auto lineWidth = (int) (suggestedWidth * 0.8 - (content->x()));
            qInfo("suggestedWidth: %d lineWidth: %d", suggestedWidth,lineWidth);
            auto nowrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), 0, text);
            auto wrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), Qt::TextWrapAnywhere, text);

            // 判断是否需要换行处理
            if (wrap_rec.height() == fh) {
                // 不需要换行
                return {nowrap_rec.width() + 20 + 22, nowrap_rec.height() + 20};
            } else {
                // 需要换行
                return {lineWidth + 20, wrap_rec.height() + 20};
            }
        }
        case from_other: {
            auto lineWidth = (int)(suggestedWidth * 0.8 - this->avatar->width() - 20 - 10);
            auto nowrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), 0, text);
            auto wrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), Qt::TextWrapAnywhere, text);

            qInfo("suggestedWidth: %d lineWidth: %d wr.h: %d", suggestedWidth,lineWidth, wrap_rec.height());

            // 判断是否需要换行处理
            if (wrap_rec.height() == fh) {
                // 不需要换行
                return {nowrap_rec.width() + 20 + 22, nowrap_rec.height() + 20};
            } else {
                // 需要换行
                return {lineWidth + 20, wrap_rec.height() + 20};
            }
        }
        case time_: {

        }
    }
}
