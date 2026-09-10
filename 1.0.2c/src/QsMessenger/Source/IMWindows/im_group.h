#ifndef IM_GROUP_H
#define IM_GROUP_H

#include <QWidget>

namespace Ui {
class IM_Group;
}

class IM_Group : public QWidget
{
    Q_OBJECT

public:
    explicit IM_Group(QWidget *parent = nullptr);
    ~IM_Group();

    QString groupName;

private:
    Ui::IM_Group *ui;

private slots:
    void sendMessage();

signals:

    void sendGroupMessageSignal(QString message, QString groupName);
};

#endif // IM_GROUP_H
