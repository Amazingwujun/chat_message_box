//
// Created by admin on 2023/5/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatMessageWrapperWidget.h" resolved

#include "chatmessagewrapperwidget.h"
#include "qabstracttextdocumentlayout.h"


ChatMessageWrapperWidget::ChatMessageWrapperWidget(const QString &msg, ChatMessageWrapperWidget::MessageType type,
                                                   QWidget *parent) :
        QWidget(parent), messageType(type), msg(msg) {
    if (type == _time) {
        return;
    }

    // 头像位置
    avatar = new QLabel("头像", this);
    avatarImg = QPixmap(":/resources/img/jun.jpg");
    avatar->setFixedSize(avatarSize);
    avatar->setPixmap(avatarImg.scaled(avatarSize));

    // 聊天内容处理
    content = new QTextEdit(this);
    content->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
    content->setReadOnly(true);
    content->setWordWrapMode(QTextOption::WrapMode::WrapAnywhere);
    content->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    content->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto font = QFont("Microsoft Yahei"); // 字体配置
    font.setPointSize(10);
    content->setFont(font);
    content->setText(msg);

    switch (type) {
        case _myself: {
            this->avatar->move(this->width() - this->avatar->width() - 30, 5);
            content->move(avatar->x() - 12 - content->width(), avatar->y());

            this->content->setStyleSheet("background-color: #95ec69;border-radius: 5px;border: 0px; padding: 5px;");
            break;
        }
        case _other: {
            avatar->move(20, 5);
            content->move(avatar->x() + avatar->width() + 12, avatar->y());

            content->setStyleSheet("border-radius: 5px; background-color: white; border: 0px; padding: 5px;");
            break;
        }
    }
}


void ChatMessageWrapperWidget::resizeEvent(QResizeEvent *event) {
    qDebug("ChatMessageWrapperWidget::resizeEvent");
    auto size = calculateSizeByContent();
    if (messageType != _time) {
        content->setFixedSize(size);
    }
}

void ChatMessageWrapperWidget::paintEvent(QPaintEvent *event) {
    qDebug() << "ChatMessageWrapperWidget::paintEvent: " << this->msg;

    // 左边三角绘制
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    switch (this->messageType) {
        case _time: {
            QFont font{"Microsoft Yahei", 8};
            QFontMetrics fm(font);

            // 计算时间戳 x, y
            auto rect = fm.boundingRect({0, 0, 400, 100}, 0, msg);
            auto x = (this->width() - rect.width()) / 2;

            qDebug() << "x: " << x << " " << msg;

            QRect drawRect{x, 0, rect.width(), rect.height()};
            painter.setBrush(QBrush(Qt::lightGray));
            painter.setPen(QPen(Qt::lightGray));
            painter.drawRoundedRect(drawRect, 5, 5);
            painter.setPen(QPen(Qt::white));
            painter.setFont(font);
            painter.drawText(drawRect, msg, QTextOption{Qt::AlignLeft | Qt::AlignVCenter});
            break;
        }
        case _other: {
            // 指定位置
            auto ah = avatar->height();
            auto ay = avatar->y();
            auto centerY = ay + ah / 2;

            QPoint points[] = {
                    QPoint(this->content->x(), centerY - 7),
                    QPoint(this->content->x() - 7, centerY),
                    QPoint(this->content->x(), centerY + 7)
            };

            painter.setPen(QPen(QColor(Qt::white)));
            painter.setBrush(QBrush(QColor(Qt::white)));
            painter.drawPolygon(points, 3);
            break;
        }
        case _myself: {
            this->avatar->move(this->width() - this->avatar->width() - 30, 5);
            content->move(avatar->x() - 12 - content->width(), avatar->y());

            auto ah = avatar->height();
            auto ay = avatar->y();
            auto centerY = ay + ah / 2;

            QPoint points[] = {
                    QPoint(this->content->x() + this->content->width(), centerY - 7),
                    QPoint(this->content->x() + this->content->width() + 7, centerY),
                    QPoint(this->content->x() + this->content->width(), centerY + 7)
            };

            QColor wxGreen{149, 236, 105}; // 微信绿
            painter.setPen(QPen(wxGreen));
            painter.setBrush(QBrush(wxGreen));
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
    if (messageType == _time) {
        QFont font{"Microsoft Yahei", 8};
        QFontMetrics fm(font);

        // 计算时间戳 x, y
        auto rect = fm.boundingRect({0, 0, 400, 100}, 0, msg);
        return rect.size();
    }

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
        case _other: {
            auto lineWidth = (int) (suggestedWidth * 0.8 - (content->x()));
            auto nowrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), 0, text);
            auto wrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), Qt::TextWrapAnywhere, text);

            // 判断是否需要换行处理
            if (wrap_rec.height() == fh) {
                // 不需要换行
                return {nowrap_rec.width() + 20 + 22, nowrap_rec.height() + 20};
            } else {
                // 需要换行
                return {wrap_rec.width() + 20, wrap_rec.height() + 20};
            }
        }
        case _myself: {
            auto lineWidth = (int) (suggestedWidth * 0.8 - this->avatar->width() - 20 - 10);
            auto nowrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), 0, text);
            auto wrap_rec = fm.boundingRect(QRect(0, 0, lineWidth, 1000), Qt::TextWrapAnywhere, text);

            // 判断是否需要换行处理
            if (wrap_rec.height() == fh) {
                // 不需要换行
                return {nowrap_rec.width() + 20 + 22, nowrap_rec.height() + 20};
            } else {
                // 需要换行
                return {wrap_rec.width() + 20, wrap_rec.height() + 20};
            }
        }
    }
}
