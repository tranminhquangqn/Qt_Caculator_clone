#ifndef STANDARD_H
#define STANDARD_H

#include <QObject>
#include <QString>
#include <QDebug>

class Standard : public QObject
{
    Q_OBJECT
public:
    explicit Standard(QObject *parent = nullptr);
    QString addCommas(QString number);
    void printBot(QString botHideStr);
    QString doubleToString(double number);
    QString funcToString(int number);
private:
    double a,atemp,b,btemp,result,numbtn;
    QString botShowStr,botHideStr,recentStr,HistLog,HistLogContainer,MemoLog;
    bool isInputf; //is input float?
    bool isHistoryLog;
    int currentFunc; //0:input result 1:+ ; 2:- ; 3:* ; 4:/ ; 5:=
    int equalCalFunc; // 1:+ ; 2:- ; 3:* ; 4:/ ; 5:=
    int currentVar; // 0: a=0 and recentStr empty ;  1: a and recentStr occupied ; 2 ignore ;3: lock
    int fDigit; // count digit after "."


signals:
    void sendRecent(QString recentStr);
    void sendResult(QString botShowStr);
    void sendMemoLog(QString MemoLog);
    void sendHistLog(QString HistTopLog,QString HistBotLog);
    void lockDashboard();
    void unlockDashboard();


public slots:

    void buttonCClicked();
    void buttonCEClicked();
    void buttonDelClicked();
    void buttonDotClicked();
    void buttonPlusClicked();
    void buttonMinusClicked();
    void buttonMulClicked();
    void buttonDivClicked();
    void buttonEqualClicked();
    void button0Clicked();
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();
    void button5Clicked();
    void button6Clicked();
    void button7Clicked();
    void button8Clicked();
    void button9Clicked();

    void buttonNegateClicked();
    void buttonSqrtClicked();
    void buttonP2Clicked();
    void buttonFracClicked();

    void buttonMCClicked();
    void buttonMRClicked();
    void buttonMplClicked();
    void buttonMmnClicked();
    void buttonMSClicked();
};

#endif // STANDARD_H
