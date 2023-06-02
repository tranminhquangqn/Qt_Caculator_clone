#include "standard.h"
#include <math.h>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <algorithm>
#include <QRegularExpression>

Standard::Standard(QObject *parent) : QObject(parent)
{
    result=0;
    a=0;
    atemp=0;
    b=0;
    btemp=0;
    equalCalFunc=0;
    currentVar=0;
    botShowStr="0";
    botHideStr="0";
    recentStr="";
    MemoLog="";
    HistLog="";
    isInputf=false;
    isHistoryLog=false;
    currentFunc=0;
    fDigit=0;
}
void Standard::printBot(QString botHideStr){
    botShowStr=Standard::addCommas(botHideStr);
    emit sendResult(botShowStr);
}
QString Standard::doubleToString(double number)
{
    // Chuyển đổi số double sang QString bằng cách sử dụng hàm QString::number()
    QString stringNumber = QString::number(number, 'g', 15);
    return stringNumber;
}

QString Standard::funcToString(int number)
{
    QString func;
    switch (number){
    case 0:
        func="";
        break;
    case 1:
        func="+";
        break;
    case 2:
        func="-";
        break;
    case 3:
        func="x";
        break;
    case 4:
        func="/";
        break;
    }
    return func;
}

QString Standard::addCommas(QString number) {
    bool isNegative = false;
    if (number.startsWith("-")) {
        isNegative = true;
        number = number.mid(1); // Bỏ qua dấu trừ đầu tiên
    }

    int decimalIndex = number.indexOf('.');
    int startIndex = (decimalIndex != -1) ? decimalIndex - 3 : number.length() - 3;

    while (startIndex > 0) {
        number.insert(startIndex, ',');
        startIndex -= 3;
    }

    if (isNegative) {
        number = "-" + number; // Thêm dấu trừ nếu số âm
    }

    return number;
}
void Standard::buttonCClicked() //copy constructor
{
    result=0;
    a=0;
    atemp=0;
    b=0;
    btemp=0;
    equalCalFunc=0;
    currentVar=0;
    botShowStr="0";
    botHideStr="0";
    recentStr="";
    MemoLog="";
    HistLog="";
    isInputf=false;
    isHistoryLog=false;
    currentFunc=0;
    fDigit=0;
    printBot(botHideStr);
    emit sendRecent(recentStr);
}

void Standard::buttonCEClicked()
{
    if(currentFunc==0){
        result=0;
        b=0;
        botShowStr="0";
        botHideStr="0";
        MemoLog="";
        HistLog="";
        isInputf=false;
        isHistoryLog=false;
        currentFunc=0;
        fDigit=0;
    }
    else{
        result=0;
        a=0;
        atemp=0;
        b=0;
        btemp=0;
        equalCalFunc=0;
        currentVar=0;
        botShowStr="0";
        botHideStr="0";
        recentStr="";
        MemoLog="";
        HistLog="";
        isInputf=false;
        isHistoryLog=false;
        currentFunc=0;
        fDigit=0;
    }
    printBot(botHideStr);
    emit sendRecent(recentStr);
}

void Standard::buttonDelClicked() //////////////
{
    if(currentVar==2){
        currentVar=1;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){

        if(botHideStr.at(botHideStr.length() - 1)=="."){
            botHideStr.chop(1);
            isInputf=false;
            fDigit=0;
        }
        else if(result==0){
        }

        else if(result>0&&isInputf==true){
            result=std::floor(result * pow(10, fDigit-2)) / pow(10, fDigit-2);
            if(fDigit!=1){
                fDigit--;
            }
            botHideStr.chop(1);
        }
        else if(result>=10){
            result=floor(result/10);
            botHideStr.chop(1);
        }
        else if(result>0){
            result=0;
            botHideStr="0";
        }
        else if (result<0&&isInputf==true){
            result=std::ceil(result * pow(10, fDigit-2)) / pow(10, fDigit-2);
            if(fDigit!=1){
                fDigit--;
            }
            botHideStr.chop(1);;
        }
        else if (result<=-10){
            result=ceil(result/10);
            botHideStr.chop(1);
        }
        else if (result<0){
            result=0;
            botHideStr="0";
        }
        //show

        printBot(botHideStr);
    }
    qDebug()<<qSetRealNumberPrecision(15)<<"result:"<<result<<"  "<<fDigit<<"  a:"<<a;
}
void Standard::buttonDotClicked()
{
    if(!isInputf){
        botHideStr.append('.');
        isInputf=true;
        fDigit=1;
        printBot(botHideStr);
    }
}

void Standard::buttonPlusClicked()
{
    isHistoryLog=false;
    b=0;
    atemp=0;

    if(currentVar!=2){

        if(currentVar==0){ //cal

            currentVar=1;
            result+=a;
            a=result;
            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

        }
        else if(currentVar==1){
            isHistoryLog=true;
            currentVar=2; // ignore spam
            atemp=a;
            b=result;
            btemp=result;

            result+=a;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result
        }

    }
    //show
    recentStr=doubleToString(a);
    recentStr.append(" +");
    emit sendRecent(recentStr); //display recent

    currentFunc=1; // +
    equalCalFunc=1;

    if(isHistoryLog){
        emit sendHistLog(doubleToString(atemp)+funcToString(equalCalFunc)+doubleToString(b)+"=",Standard::addCommas(botHideStr));
        isHistoryLog=false;
    }

}
void Standard::buttonMinusClicked()
{
    isHistoryLog=false;
    b=0;
    atemp=0;

    if(currentVar!=2){
        if(currentVar==0){
            a=result;
            currentVar=1;
            recentStr=doubleToString(a);
            recentStr.append(" -");
            emit sendRecent(recentStr); //display recent
        }

        else if(currentVar==1){ //cal
            isHistoryLog=true;
            currentVar=2; // ignore spam
            atemp=a;
            b=result;
            btemp=result;
            result=a-result;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

        }

    }
    //show
    recentStr=doubleToString(a);
    recentStr.append(" -");
    emit sendRecent(recentStr); //display recent

    currentFunc=2; // -
    equalCalFunc=2;

    if(isHistoryLog){
        emit sendHistLog(doubleToString(atemp)+funcToString(equalCalFunc)+doubleToString(b)+"=",Standard::addCommas(botHideStr));
        isHistoryLog=false;
    }

}
void Standard::buttonMulClicked()
{
    isHistoryLog=false;
    b=0;
    atemp=0;

    if(currentVar!=2){
        if(currentVar==0){
            a=result;
            currentVar=1;
            recentStr=doubleToString(a);
            recentStr.append(" x");
            emit sendRecent(recentStr); //display recent
        }

        else if(currentVar==1){ //cal
            isHistoryLog=true;
            currentVar=2; // ignore spam

            atemp=a;
            b=result;
            btemp=result;

            result=a*result;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

        }

    }
    //show
    recentStr=doubleToString(a);
    recentStr.append(" x");
    emit sendRecent(recentStr); //display recent

    currentFunc=3; //x
    equalCalFunc=3;

    if(isHistoryLog){
        emit sendHistLog(doubleToString(atemp)+funcToString(equalCalFunc)+doubleToString(b)+"=",Standard::addCommas(botHideStr));
        isHistoryLog=false;
    }

}
void Standard::buttonDivClicked()
{
    isHistoryLog=false;
    b=0;
    atemp=0;

    if(currentVar!=2){
        if(currentVar==0){
            a=result;
            currentVar=1;
            recentStr=doubleToString(a);
            recentStr.append(" /");
            emit sendRecent(recentStr); //display recent
        }

        else if(currentVar==1){ //cal
            isHistoryLog=true;
            currentVar=2; // ignore spam

            atemp=a;
            b=result;
            btemp=result;

            result=a/result;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

        }
    }
    //show
    recentStr=doubleToString(a);
    recentStr.append(" /");
    emit sendRecent(recentStr); //display recent


    currentFunc=4; // /
    equalCalFunc=4;

    if(isHistoryLog){
        emit sendHistLog(doubleToString(atemp)+funcToString(equalCalFunc)+doubleToString(b)+"=",Standard::addCommas(botHideStr));
        isHistoryLog=false;
    }

}
void Standard::buttonEqualClicked()
{
    isHistoryLog=false;
    b=0;
    atemp=0;

    if(currentVar==0){ //input a
        a=result;
        currentVar=1;
        currentFunc=5;
        recentStr=doubleToString(a);
        recentStr.append(" =");
        emit sendRecent(recentStr); //display recent
    }

    else if(currentVar==1){ //cal
        currentFunc=equalCalFunc;
        currentVar=2;

        switch(equalCalFunc){
        case 0:
            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(a);
            recentStr.append(" =");
            emit sendRecent(recentStr); //display recent
            break;
        case 1: // +
            isHistoryLog=true;
            atemp=a;
            b=result;
            btemp=result;
            result+=a;
            a=result;
            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"+"+doubleToString(b)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        case 2: // -
            isHistoryLog=true;
            atemp=a;
            b=result;
            btemp=result;
            result=a-result;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"-"+doubleToString(b)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        case 3: // *
            isHistoryLog=true;
            atemp=a;
            b=result;
            btemp=result;
            result=a*result;
            a=result;
            qDebug()<<"case:"<<equalCalFunc;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"x"+doubleToString(b)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        case 4: // /
            isHistoryLog=true;
            atemp=a;
            b=result;
            btemp=result;
            result=a/result;
            a=result;

            qDebug()<<"case:"<<equalCalFunc;
            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"/"+doubleToString(b)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        }
    }
    else if(currentVar==2){ //cal
        currentFunc=equalCalFunc;

        switch(equalCalFunc){
        case 0:
            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(a);
            recentStr.append(" =");
            emit sendRecent(recentStr); //display recent
            break;
        case 1: // +
            isHistoryLog=true;
            atemp=a;
            result+=btemp;
            a=result;
            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"+"+doubleToString(btemp)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        case 2: // -
            isHistoryLog=true;
            atemp=a;
            result=a-btemp;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"-"+doubleToString(btemp)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        case 3: // *
            isHistoryLog=true;
            atemp=a;
            result=a*btemp;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"x"+doubleToString(btemp)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        case 4: // /
            isHistoryLog=true;
            atemp=a;
            result=a/btemp;
            a=result;

            botHideStr = doubleToString(result);
            printBot(botHideStr); // display the result

            recentStr=doubleToString(atemp)+"/"+doubleToString(btemp)+"=";
            emit sendRecent(recentStr); //display recent
            break;
        }
    }
    if(isHistoryLog&&currentVar==2){
        emit sendHistLog(doubleToString(atemp)+funcToString(equalCalFunc)+doubleToString(btemp)+"=",Standard::addCommas(botHideStr));
        isHistoryLog=false;
    }
    else if(isHistoryLog){
        emit sendHistLog(doubleToString(atemp)+funcToString(equalCalFunc)+doubleToString(b)+"=",Standard::addCommas(botHideStr));
        isHistoryLog=false;
    }


}

void Standard::button0Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            qDebug()<<qSetRealNumberPrecision(16)<<"result:"<<result<<"  "<<fDigit<<"  a:"<<a;
            fDigit++;
            botHideStr.append("0");
        }
        else if(result==0){
        }

        else if(result>0&&isInputf==true){

            fDigit++;
            botHideStr.append("0");
        }
        else if(result>0){
            result=result*10;
            botHideStr.append("0");
        }
        else if (result<0&&isInputf==true){
            fDigit++;
            botHideStr.append("0");
        }
        else if (result<0){
            result=result*10;
            botHideStr.append("0");
        }


        //show

        printBot(botHideStr);
    }

}
void Standard::button1Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(pow(10,-fDigit));
            fDigit++;
            botHideStr.append("1");
        }
        else if(result==0){
            result=1;
            botHideStr="1";
        }
        else if(result>0&&isInputf==true){
            result=result+(pow(10,-fDigit));
            fDigit++;
            botHideStr.append("1");
        }
        else if(result>0){
            result=result*10+1;
            botHideStr.append("1");
        }
        else if (result<0&&isInputf==true){
            result=result-(pow(10,-fDigit));
            fDigit++;
            botHideStr.append("1");
        }
        else if (result<0){
            result=result*10-1;
            botHideStr.append("1");
        }
        //show

        printBot(botHideStr);
    }
    qDebug()<<qSetRealNumberPrecision(16)<<"result:"<<result<<"  "<<fDigit<<"  a:"<<a;
}
void Standard::button2Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(2*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("2");
        }
        else if(result==0){
            result=2;
            botHideStr="2";
        }
        else if(result>0&&isInputf==true){
            result=result+(2*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("2");
        }
        else if(result>0){
            result=result*10+2;
            botHideStr.append("2");
        }
        else if (result<0&&isInputf==true){
            result=result-(2*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("2");
        }
        else if (result<0){
            result=result*10-2;
            botHideStr.append("2");
        }
        //show

        printBot(botHideStr);
    }
    qDebug()<<qSetRealNumberPrecision(16)<<"result:"<<result<<"  "<<fDigit<<"  a:"<<a;
}

void Standard::button3Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(3*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("3");
        }
        else if(result==0){
            result=3;
            botHideStr="3";
        }
        else if(result>0&&isInputf==true){
            result=result+(3*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("3");
        }
        else if(result>0){
            result=result*10+3;
            botHideStr.append("3");
        }
        else if (result<0&&isInputf==true){
            result=result-(3*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("3");
        }
        else if (result<0){
            result=result*10-3;
            botHideStr.append("3");
        }
        //show

        printBot(botHideStr);
    }
    qDebug()<<qSetRealNumberPrecision(16)<<"result:"<<result<<"  "<<fDigit<<"  a:"<<a;
}
void Standard::button4Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(4*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("4");
        }
        else if(result==0){
            result=4;
            botHideStr="4";
        }
        else if(result>0&&isInputf==true){
            result=result+(4*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("4");
        }
        else if(result>0){
            result=result*10+4;
            botHideStr.append("4");
        }
        else if (result<0&&isInputf==true){
            result=result-(4*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("4");
        }
        else if (result<0){
            result=result*10-4;
            botHideStr.append("4");
        }
        //show

        printBot(botHideStr);
    }
    qDebug()<<qSetRealNumberPrecision(16)<<"result:"<<result<<"  "<<fDigit<<"  a:"<<a;
}
void Standard::button5Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(5*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("5");
        }
        else if(result==0){
            result=5;
            botHideStr="5";
        }
        else if(result>0&&isInputf==true){
            result=result+(5*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("5");
        }
        else if(result>0){
            result=result*10+5;
            botHideStr.append("5");
        }
        else if (result<0&&isInputf==true){
            result=result-(5*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("5");
        }
        else if (result<0){
            result=result*10-5;
            botHideStr.append("5");
        }
        //show

        printBot(botHideStr);
    }
}
void Standard::button6Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(6*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("6");
        }
        else if(result==0){
            result=6;
            botHideStr="6";
        }
        else if(result>0&&isInputf==true){
            result=result+(6*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("6");
        }
        else if(result>0){
            result=result*10+6;
            botHideStr.append("6");
        }
        else if (result<0&&isInputf==true){
            result=result-(6*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("6");
        }
        else if (result<0){
            result=result*10-6;
            botHideStr.append("6");
        }
        //show

        printBot(botHideStr);
    }
}
void Standard::button7Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(7*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("7");
        }
        else if(result==0){
            result=7;
            botHideStr="7";
        }
        else if(result>0&&isInputf==true){
            result=result+(7*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("7");
        }
        else if(result>0){
            result=result*10+7;
            botHideStr.append("7");
        }
        else if (result<0&&isInputf==true){
            result=result-(7*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("7");
        }
        else if (result<0){
            result=result*10-7;
            botHideStr.append("7");
        }
        //show

        printBot(botHideStr);
    }
}
void Standard::button8Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(8*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("8");
        }
        else if(result==0){
            result=8;
            botHideStr="8";
        }
        else if(result>0&&isInputf==true){
            result=result+(8*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("8");
        }
        else if(result>0){
            result=result*10+8;
            botHideStr.append("8");
        }
        else if (result<0&&isInputf==true){
            result=result-(8*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("8");
        }
        else if (result<0){
            result=result*10-8;
            botHideStr.append("8");
        }
        //show

        printBot(botHideStr);
    }
}
void Standard::button9Clicked()
{
    if(currentVar==2){
        currentVar=1;
        equalCalFunc=0;
    }
    if(currentFunc!=0){
        result=0;
        botHideStr="0";
        currentFunc=0;
        fDigit=0;
        isInputf=false;
    }
    if(botHideStr.length()<=15){
        if(result==0&&isInputf==true){
            result=result+(9*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("9");
        }
        else if(result==0){
            result=9;
            botHideStr="9";
        }
        else if(result>0&&isInputf==true){
            result=result+(9*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("9");
        }
        else if(result>0){
            result=result*10+9;
            botHideStr.append("9");
        }
        else if (result<0&&isInputf==true){
            result=result-(9*pow(10,-fDigit));
            fDigit++;
            botHideStr.append("9");
        }
        else if (result<0){
            result=result*10-9;
            botHideStr.append("9");
        }
        //show

        printBot(botHideStr);
    }
}



void Standard::buttonNegateClicked()
{
    if(result==0){}
    else if(result>0){
        if(currentVar==1){
            recentStr=("negate("+doubleToString(result)+")");
            emit sendRecent(recentStr); //display recent
        }
        result=-result;
        botHideStr.prepend("-");
        printBot(botHideStr);
        //show recent

    }
    else if(result<0){
        if(currentVar==1){
            recentStr=("negate("+doubleToString(result)+")");
            emit sendRecent(recentStr); //display recent
        }
        result=-result;
        botHideStr.remove(0,1);
        printBot(botHideStr);
        //show recent
    }

}

void Standard::buttonSqrtClicked()
{
    if(equalCalFunc==0){

        recentStr=("\u221A("+doubleToString(result)+")");

    }
    else{
        recentStr=(recentStr+"\u221A("+doubleToString(result)+")");
        currentVar=1;
    }

    emit sendRecent(recentStr); //display recent
    result=sqrt(result);

    botHideStr=doubleToString(result);
    printBot(botHideStr);



}

void Standard::buttonP2Clicked()
{
    if(equalCalFunc==0){
        recentStr=("sqr("+doubleToString(result)+")");
    }
    else{
        recentStr=(recentStr+"sqr("+doubleToString(result)+")");
        currentVar=1;
    }
    emit sendRecent(recentStr); //display recent
    result=pow(result,2);

    botHideStr=doubleToString(result);
    printBot(botHideStr);
    qDebug()<<qSetRealNumberPrecision(16)<<"result:"<<result<<"  "<<fDigit<<"  equalCalFunc:"<<equalCalFunc;



}

void Standard::buttonFracClicked()
{
    if(result==0){
        recentStr=("1/("+doubleToString(result)+")");
        emit sendRecent(recentStr); //display recent
        botHideStr=("Cannot divide by zero");
        emit sendResult(botHideStr);
        emit lockDashboard();
    }
    else {
        if(equalCalFunc==0){
            recentStr=("1/("+doubleToString(result)+")");
        }
        else{
            recentStr=(recentStr+"1/("+doubleToString(result)+")");
            currentVar=1;
            }
            emit sendRecent(recentStr); //display recent
            result=1/result;

            botHideStr=doubleToString(result);
            printBot(botHideStr);



    }


}

void Standard::buttonMCClicked()
{

}

void Standard::buttonMRClicked()
{

}

void Standard::buttonMplClicked()
{

}

void Standard::buttonMmnClicked()
{

}

void Standard::buttonMSClicked()
{
    emit sendMemoLog(botShowStr);
    qDebug()<<qSetRealNumberPrecision(16)<<"result:"<<result<<"  "<<fDigit<<"  a:"<<a;
}
