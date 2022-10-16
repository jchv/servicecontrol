#include "servicecontrol.h"
#include "ui_servicecontrol.h"

ServiceControl::ServiceControl(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::ServiceControl)
{
    m_ui->setupUi(this);
}

ServiceControl::~ServiceControl() = default;
