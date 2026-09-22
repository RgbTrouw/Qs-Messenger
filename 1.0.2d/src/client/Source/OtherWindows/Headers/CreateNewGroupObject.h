#include <QWidget>
#include <QTimer>

namespace Ui {
class CreateNewGroupObject;
}

class CreateNewGroupObject : public QWidget
{
    Q_OBJECT

public:
    explicit CreateNewGroupObject(QWidget *parent = nullptr);
    ~CreateNewGroupObject();

private slots:
    void add();
    void close_window();


public slots:
    void feedback(QString message);
    void closeEvent(QCloseEvent *event);


signals:
    void frequest(QString email);


private:
    Ui::CreateNewGroupObject *ui;

    QTimer *st = new QTimer();
};

