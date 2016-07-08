#include "timeplotwidget.h"
#include <iterator>

#define DEFAULT_X_RANGE_MS 100
#define DEFAULT_Y_MIN_RANGE 0
#define DEFAULT_Y_MAX_RANGE 5

TimePlotWidget::TimePlotWidget(QWidget *parent) : QWidget(parent)
{
	plotXRange = DEFAULT_X_RANGE_MS;

	QVBoxLayout* mainLayout = new QVBoxLayout;
	plot = new QCustomPlot;
	rangeXLineEdit = new QLineEdit;
	saveButton = new QPushButton("Save plot");

	QHBoxLayout* settingsLayout = new QHBoxLayout;
	settingsLayout->addWidget(new QLabel("X range"));
	settingsLayout->addWidget(rangeXLineEdit);
	settingsLayout->addWidget(new QLabel("s"));
	settingsLayout->addStretch();

	mainLayout->addLayout(settingsLayout);
	mainLayout->addWidget(plot);

	rangeXLineEdit->setFixedWidth(50);
	rangeXLineEdit->setText(QString::number(DEFAULT_X_RANGE_MS));

	plot->xAxis->setLabel("Time [s]");
	plot->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	plot->xAxis->setDateTimeSpec(Qt::UTC);
	plot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
	plot->xAxis->setDateTimeFormat("H:mm:ss");
	//plot->xAxis->setAutoTickStep(false);
	//plot->xAxis->setTickStep(10); // 1 minute
	//plot->xAxis->setSubTickCount(3);
	plot->legend->setVisible(true);
	plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);

	this->setLayout(mainLayout);
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	this->setMinimumHeight(300);
	connect(rangeXLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onRangeXTextChanged(QString)));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveButtonPressed()));
}

TimePlotWidget::~TimePlotWidget()
{
	delete plot;
	delete rangeXLineEdit;
}

void TimePlotWidget::addGraph(QString label, QString color)
{
	auto graph = plot->addGraph();
	graph->setName(label);
	graph->setPen(QPen(QColor(color)));

}

void TimePlotWidget::plotNewPoint(int graphNo, int timestamp, double point)
{
	//qDebug()<<"Plotting new point: x= "<<timestamp<<", y= "<<point;
	plot->graph(graphNo)->addData(timestamp, point);
	plot->xAxis->setRange(timestamp+10, plotXRange, Qt::AlignRight);
	plot->graph(graphNo)->removeDataBefore(timestamp - 1.2 * plotXRange);
	plot->replot();
}

void TimePlotWidget::removeAllGraphs()
{
	plot->clearGraphs();
}

void TimePlotWidget::setYAxisLabel(QString label)
{
	plot->yAxis->setLabel(label);
}

void TimePlotWidget::onNewData(float averageWindSpeed, float gustSpeed, float currentSpeed)
{
	QDateTime dateTime;
	//qDebug() << QDateTime::currentDateTime().toString("hh:mm::ss");
	QTime time = QDateTime::currentDateTime().time();
	//int seconds = time.msecsSinceStartOfDay()/1000;
	//qDebug() << seconds << "s elapsed";
	plotNewPoint(0, time.msecsSinceStartOfDay()/1000, averageWindSpeed);
	plotNewPoint(1, time.msecsSinceStartOfDay()/1000, gustSpeed);
	plotNewPoint(2, time.msecsSinceStartOfDay()/1000, currentSpeed);
	updatePlotAxesRanges();
}

void TimePlotWidget::onRangeXTextChanged(QString text)
{
	bool okFlag = true;
	int newXRange = text.toInt(&okFlag);
	if(okFlag) {
		plotXRange = newXRange;
	}
}

/*void TimePlotWidget::onRangeYMinTextChanged(QString text)
{
	bool okFlag = true;
	double newYMinRange = text.toDouble(&okFlag);
	if(okFlag) {
		plotYMinRange = newYMinRange;
		updatePlotAxesRanges();
	}
}

void TimePlotWidget::onRangeYMaxTextChanged(QString text)
{
	bool okFlag = true;
	double newYMaxRange = text.toDouble(&okFlag);
	if(okFlag) {
		plotYMaxRange = newYMaxRange;
		updatePlotAxesRanges();
	}
}*/

void TimePlotWidget::onSaveButtonPressed()
{
	QString saveFolderName = "img";
	QDir saveFolder(saveFolderName);
	if(!saveFolder.exists()) {
		QDir().mkdir(saveFolderName);
	}
	plot->savePng(saveFolderName + "/plot.png", 1024, 768);
}

void TimePlotWidget::updatePlotAxesRanges()
{
	plot->yAxis->setRangeLower(plotYMinRange);
	double max0 = getGraphMaxValue(0);
	double max1 = getGraphMaxValue(1);
	double max = max0;
	if(max1 > max)
		max = max1;
	if(max < 0.1)
		max = 1;
	plot->yAxis->setRangeUpper(max * 1.2);

	plot->replot();
}

double TimePlotWidget::getGraphMaxValue(int index)
{
	QCPDataMap* dataMap = plot->graph(index)->data();
	double max = 0;
	for(auto i = dataMap->begin(); i != dataMap->end(); i++) {
		if((*i).value > max) {
			max = (*i).value;
		}
	}
	return max;
}
