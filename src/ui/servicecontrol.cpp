#include "servicecontrol.h"
#include "ui_servicecontrol.h"

ServiceControl::ServiceControl(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::ServiceControl)
{
    m_ui->setupUi(this);

    // Can't seem to set stretch factors for QSplitter in designer?
    m_ui->paneSplitter->setStretchFactor(0, 1);
    m_ui->paneSplitter->setStretchFactor(1, 4);
    m_ui->paneSplitter->setStretchFactor(2, 2);

    connect(m_ui->actionAddDomain, &QAction::triggered,
            this, &ServiceControl::showAddDomainPrompt);

    connect(m_ui->actionQuit, &QAction::triggered,
            qApp, &QApplication::quit);
}

ServiceControl::~ServiceControl() = default;

void ServiceControl::showAddDomainPrompt() {

}
