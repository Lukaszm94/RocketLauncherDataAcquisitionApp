#ifndef DATALOGGINGWIDGET_H
#define DATALOGGINGWIDGET_H
#include <QWidget>
#include <QtWidgets>

class DataLoggingWidget : public QWidget
{
	Q_OBJECT
public:
	DataLoggingWidget(QWidget* parent = 0);
	void appendLog(QString str);
	void clearLog();
	void setLogging(bool logging = true);

private slots:
	void onSaveButtonClicked();
	void onStartButtonClicked();
	void onClearButtonClicked();

signals:
	void saveButtonClicked();
	void startButtonClicked();
	void clearLogButtonClicked();

private:
	QTextEdit* logTextEdit;
	QPushButton* saveLogButton;
	QPushButton* clearLogButton;
	QPushButton* startLoggingButton;
};

#endif // DATALOGGINGWIDGET_H
