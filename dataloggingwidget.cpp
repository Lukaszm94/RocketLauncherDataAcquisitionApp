#include "dataloggingwidget.h"



DataLoggingWidget::DataLoggingWidget(QWidget *parent) : QWidget(parent)
{
	logTextEdit = new QTextEdit;
	saveLogButton = new QPushButton("Save");
	clearLogButton = new QPushButton("Clear");
	startLoggingButton = new QPushButton("Start");

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(startLoggingButton);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(saveLogButton);
	buttonsLayout->addWidget(clearLogButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(buttonsLayout);
	mainLayout->addWidget(logTextEdit);
	this->setLayout(mainLayout);
	logTextEdit->setReadOnly(true);
	connect(saveLogButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
	connect(startLoggingButton, SIGNAL(clicked(bool)), this, SLOT(onStartButtonClicked()));
	connect(clearLogButton, SIGNAL(clicked(bool)), this, SLOT(onClearButtonClicked()));
}

void DataLoggingWidget::appendLog(QString str)
{
	logTextEdit->append(str);
}

void DataLoggingWidget::clearLog()
{
	logTextEdit->clear();
}

void DataLoggingWidget::setLogging(bool logging)
{
	if(logging) {
		startLoggingButton->setText("Stop");
	} else {
		startLoggingButton->setText("Start");
	}
}

void DataLoggingWidget::onSaveButtonClicked()
{
	emit saveButtonClicked();
}

void DataLoggingWidget::onStartButtonClicked()
{
	emit startButtonClicked();
}

void DataLoggingWidget::onClearButtonClicked()
{
	emit clearLogButtonClicked();
}
