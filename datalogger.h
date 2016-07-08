#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <QObject>
#include <QTimer>
#include "guipacket.h"

class DataLogger : public QObject
{
	Q_OBJECT
public:
	explicit DataLogger(QObject *parent = 0);
	void clearLog();
	void appendData(GUIPacket packet);
	QString getNewestLine();
	bool saveToFile(QString filePath);
	void enableAutomaticSaving(bool enable = true);
	void setAutomaticSavingFolderPath(QString path);
	void setAutomaticSavingInterval(int intervalS);

private slots:
	void onAutomaticSaveTimerTimeout();
private:
	bool saveBufferToFile(QString filePath, QString buff);

	QString buffer, newestLine;
	bool automaticSavingEnabled;
	QString automaticSavingFolderPath;
	int automaticSavingIntervalS;
	QTimer* automaticSaveTimer;
};

#endif // DATALOGGER_H
