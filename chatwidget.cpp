//
// Created by admin on 2023/6/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChatWidget.h" resolved

#include "chatwidget.h"
#include "ui_ChatWidget.h"


ChatWidget::ChatWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChatWidget) {
    ui->setupUi(this);

    ui->textEdit->setFontFamily("Microsoft Yahei");
    ui->textEdit->setFontPointSize(10);

    connect(this->ui->send_btn, &QPushButton::clicked, [this]() {
        auto msg = this->ui->textEdit->toPlainText();
        emit onMessageReceived(msg, ChatMessageWrapperWidget::_other);
        this->ui->textEdit->clear();
    });
}

ChatWidget::~ChatWidget() {
    delete ui;
}

void ChatWidget::resizeEvent(QResizeEvent *event) {
    qDebug() << "chatwidget resize event" << this->width();
    auto f = this->ui->widget;
    auto te = this->ui->textEdit;
    auto btn = this->ui->send_btn;
    auto lw = this->ui->listWidget;

    // 工具栏处理
    this->ui->tools_widget->setGeometry(0, 0, f->width(), 50);

    // 输入框
    te->setGeometry(0, 50, f->width(), f->height() - 50);

    // 发送按钮
    btn->move(te->width() + te->x() - btn->width() - 50, te->height() + te->y() - btn->height() - 30);

    for (int i = 0; i < lw->count(); ++i) {
        auto it = lw->item(i);
        auto w = (ChatMessageWrapperWidget *) (lw->itemWidget(it));
        auto size = w->calculateSizeByContent(this->width());
        qDebug() << "size: " << size;
        it->setSizeHint({this->width(), size.height() + 10});
        lw->setItemWidget(it, w);
    }
}

/**
 * 报文接收处理函数
 *
 * @param msg
 */
void ChatWidget::onMessageReceived(const QString &msg, ChatMessageWrapperWidget::MessageType type) {
    auto lw = this->ui->listWidget;
    auto dateTimeNow = QDateTime::currentDateTime();
    auto now = dateTimeNow.toSecsSinceEpoch();
    auto preTs = this->latest_msg_ts;

    qDebug("latest_msg_ts: %d, now: %d", this->latest_msg_ts, now);

    // 判断是否需要加入时间戳
    if (now - preTs >= 180) {

        auto cmww = new ChatMessageWrapperWidget(dateTimeNow.toString("yyyy/M/d HH:mm:ss"), ChatMessageWrapperWidget::_time,
                                                 lw);
        auto lwi = new QListWidgetItem(lw);
        auto size = cmww->calculateSizeByContent(this->width());
        lwi->setSizeHint({this->width(), size.height()});
        lw->setItemWidget(lwi, cmww);

        this->latest_msg_ts = now;
    }

    switch (type) {
        case ChatMessageWrapperWidget::_other: {
            auto randomNum = QRandomGenerator::global()->bounded(100);
            auto cmww = new ChatMessageWrapperWidget(msg,
                                                     randomNum > 50 ? ChatMessageWrapperWidget::MessageType::_myself
                                                                    : type,
                                                     lw);
            auto lwi = new QListWidgetItem(lw);
            auto size = cmww->calculateSizeByContent(this->width());
            lwi->setSizeHint({this->width(), size.height() + 10});
            lw->setItemWidget(lwi, cmww);
            break;
        }
        case ChatMessageWrapperWidget::_myself: {
            auto cmww = new ChatMessageWrapperWidget(msg, type, lw);
            auto lwi = new QListWidgetItem(lw);
            auto size = cmww->calculateSizeByContent(this->width());
            lwi->setSizeHint({this->width(), size.height() + 10});
            lw->setItemWidget(lwi, cmww);
            break;
        }
        default:
            qDebug("非法的消息类型");
            exit(0);
    }

    lw->scrollToBottom();
}
