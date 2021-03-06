#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QSettings>
#include <qwt_plot.h>
#include "Cuts.h"
#include "ui_dialogActiveCuts.h"
#include "Dialogs/ActiveCutsDialog.h"
#include "Dialogs/PolygonalCutEditDialog.h"
#include "Dialogs/LinearCutEditDialog.h"
class PlotWindow: public QMainWindow
{
	Q_OBJECT
public:
    PlotWindow (QWidget * parent=0, int s_chPrimary=0);	
	void setCutVectors(QVector<LinearCut>*s_cuts,QVector<PolygonalCut>*s_polygonalCuts, bool updateConditions=true);
	virtual void setProjectorMode(bool s_projectorMode){ projectorMode = s_projectorMode; }
public slots:
	void onLinearCutAdded(LinearCut& cut, bool updateConditions=true);
	void onPolygonalCutAdded(PolygonalCut& cut, bool updateConditions=true);
	void onCutRemoved(int index, bool isPolygonal);	
	void onActiveCutsClicked();
	void onSaveImageClicked();
	void onRenameClicked();
	
	void closeEvent(QCloseEvent* event);
	
	virtual void onAddLinearCutAddClicked(){}
	virtual void onEditLinearCutClicked();
	virtual void onRemoveLinearCutClicked();
	virtual void timerUpdate(){}
	virtual void clearValues(){}
	virtual void onSaveDataClicked(){}

signals:
	void plotClosed();
	void cutRemoved(int cutIndex, bool isPolygonal);
protected:
	bool isInActiveRegion(EventStatistics* stats);
	void updateSettings();
public:
	int chPrimary = 0;
	int tabIndex = 0;
	QVector<Condition>conditions;
	QVector<Condition>polygonalConditions;
	
protected:
	Ui::DialogActiveCuts uiDialogActiveCuts;	
	QVector<LinearCut>*cuts=nullptr;
	QVector<PolygonalCut>*polygonalCuts=nullptr;
	//conditions (for each cut):
	//1: include region; -1: exclude region; 0: ignore cut
	
	QTimer* refreshTimer;
	QwtPlot* plot;
	QSettings settings;
	QString name;
	int numEvents=0;
	bool projectorMode;

	friend QDataStream &operator<<(QDataStream &out, const PlotWindow &obj);
	friend QDataStream &operator>>(QDataStream &in, PlotWindow &obj);
};
//Q_DECLARE_METATYPE(PlotWindow)

