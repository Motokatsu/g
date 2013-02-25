/*
 * KLine.h
 *
 *  Created on: 2013/02/17
 *      Author: moto
 */

#ifndef KLINE_H_
#define KLINE_H_

#include <QVector>
#include <QString>

class KLine {
public:
    KLine();
    KLine(const QVector<double>& aData, double aConvert, double aMax, double aMin, const QString& aLabel, const QString& aUnit);
    virtual ~KLine();

    const QVector<double>& data() const { return mData_;}
    double convert() const { return mConvert_;}
    double max() const { return mMax_;}
    double min() const { return mMin_;}
    QString label() const { return mLabel_;}
    QString unit() const { return mUnit_;}
private:
    QVector<double> mData_;
    double mConvert_;
    double mMax_;
    double mMin_;
    QString mLabel_;
    QString mUnit_;
};

#endif /* KLINE_H_ */
