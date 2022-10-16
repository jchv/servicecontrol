#ifndef SERVICECONTROL_H
#define SERVICECONTROL_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class ServiceControl;
}

class ServiceControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServiceControl(QWidget *parent = nullptr);
    ~ServiceControl() override;

private:
    QScopedPointer<Ui::ServiceControl> m_ui;
};

#endif // SERVICECONTROL_H
