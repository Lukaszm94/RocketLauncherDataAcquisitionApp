#include "statuswidget.h"




StatusWidget::StatusWidget(QWidget *parent) : QWidget(parent)
{
	greenIcon = new QPixmap(":img/img/greenIcon.png");
	grayIcon = new QPixmap(":img/img/grayIcon.png");
	redIcon = new QPixmap(":img/img/redIcon.png");
	connectedIconLabel = new QLabel;
	receivingDataIconLabel = new QLabel;
	loggingIconLabel = new QLabel;
	QLabel* connectedTextLabel = new QLabel("Connected");
	QLabel* receivingDataTextLabel = new QLabel("Receiving data");
	QLabel* loggingTextLabel = new QLabel("Logging");

	QHBoxLayout* connectedLayout = new QHBoxLayout;
	connectedLayout->addWidget(connectedIconLabel);
	connectedLayout->addWidget(connectedTextLabel);
	connectedLayout->addStretch();

	QHBoxLayout* receivingDataLayout = new QHBoxLayout;
	receivingDataLayout->addWidget(receivingDataIconLabel);
	receivingDataLayout->addWidget(receivingDataTextLabel);
	receivingDataLayout->addStretch();

	QHBoxLayout* loggingLayout = new QHBoxLayout;
	loggingLayout->addWidget(loggingIconLabel);
	loggingLayout->addWidget(loggingTextLabel);
	loggingLayout->addStretch();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(connectedLayout);
	mainLayout->addLayout(receivingDataLayout);
	mainLayout->addLayout(loggingLayout);
	this->setLayout(mainLayout);

	QFont* font = new QFont("Arial", 12);
	connectedTextLabel->setFont(*font);
	receivingDataTextLabel->setFont(*font);
	loggingTextLabel->setFont(*font);

	connectedIconLabel->setPixmap(*grayIcon);
	receivingDataIconLabel->setPixmap(*grayIcon);
	loggingIconLabel->setPixmap(*grayIcon);
}

void StatusWidget::setConnected(bool on)
{
	if(on) {
		connectedIconLabel->setPixmap(*greenIcon);
	} else {
		connectedIconLabel->setPixmap(*grayIcon);
	}
}

void StatusWidget::setReceivingData(bool on)
{
	if(on) {
		receivingDataIconLabel->setPixmap(*greenIcon);
	} else {
		receivingDataIconLabel->setPixmap(*redIcon);
	}
}

void StatusWidget::setLogging(bool on)
{
	if(on) {
		loggingIconLabel->setPixmap(*greenIcon);
	} else {
		loggingIconLabel->setPixmap(*grayIcon);
	}
}
