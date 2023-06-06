#include <QApplication>
#include <QListWidget>
#include "chatmessagewrapperwidget.h"
#include "chatwidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    ChatWidget w;
//    w.resize(1190, 1200);
//    w.show();
    ChatMessageWrapperWidget w("要在 Qt5 中实现聊天气泡的效果，可以使用 QListView 和自定义 QStyledItemDelegate。以下是基本步骤：\n"
                               "\n"
                               "创建一个 QListView，用来显示聊天记录。\n"
                               "设置该 QListView 的模型为一个 QStringListModel 或自定义的 Model。\n"
                               "自定义 QStyledItemDelegate，在 paint 函数中绘制气泡和文本内容，通过调整大小和位置使其看起来像聊天记录气泡。\n"
                               "将 QStyledItemDelegate 分别应用于发送者和接收者的消息项。\n"
                               "下面是一个简单的示例代码，演示如何创建自定义 QStyledItemDelegate 来实现聊天气泡的效果：", ChatMessageWrapperWidget::MessageType::from_other);
    w.resize(500, 500);
    w.show();
    return QApplication::exec();
}