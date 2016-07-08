#include "connectiontabwidget.h"
#include <QtSerialPort/QSerialPortInfo>



ConnectionTabWidget::ConnectionTabWidget(QWidget *parent) : QWidget(parent)
{
	serialPortComboBox = new QComboBox;
	refreshButton = new QPushButton("Refresh");
	connectButton = new QPushButton("Connect");
	mainLayout = new QVBoxLayout;

	QHBoxLayout* serialPortLayout = new QHBoxLayout;
	serialPortLayout->addWidget(serialPortComboBox);
	serialPortLayout->addWidget(refreshButton);
	serialPortLayout->addStretch();

	QHBoxLayout* connectLayout = new QHBoxLayout;
	connectLayout->addWidget(connectButton);
	connectLayout->addStretch();

	mainLayout->addLayout(serialPortLayout);
	mainLayout->addLayout(connectLayout);
	mainLayout->addStretch();

	this->setLayout(mainLayout);
	refreshSerialPorts();
	connect(connectButton, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));
	connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshSerialPorts()));
}

void ConnectionTabWidget::setSerialConnected(bool connected)
{
	if(connected) {
		refreshButton->setEnabled(false);
		serialPortComboBox->setEnabled(false);
		connectButton->setText("Disconnect");
	} else {
		refreshButton->setEnabled(true);
		serialPortComboBox->setEnabled(true);
		connectButton->setText("Connect");
	}
}

void ConnectionTabWidget::refreshSerialPorts()
{
	serialPortComboBox->clear();
	auto portsList = QSerialPortInfo::availablePorts();
	for(auto port : portsList) {
		QString portName = port.portName();
		serialPortComboBox->addItem(portName);
	}
}

void ConnectionTabWidget::onConnectButtonClicked()
{
	QString portName = serialPortComboBox->currentText();
	if(portName.isEmpty()) {
		return;
	}
	emit connectButtonClicked(portName);
}
