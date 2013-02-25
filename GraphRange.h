/*
 * GraphRange.h
 *
 *  Created on: 2013/01/31
 *      Author: moto
 */

#ifndef GRAPHRANGE_H_
#define GRAPHRANGE_H_

class GraphRange {
public:
    GraphRange();
    GraphRange(double aLower, double aUpper);
    GraphRange(const GraphRange& aOther);
    virtual ~GraphRange();

    const GraphRange& operator=(const GraphRange& aOther);

    inline double lower() const { return mLower_;}
    inline double upper() const { return mUpper_;}
    inline double size() const { return mUpper_ - mLower_;}
    double center() const;
    void trans(double aDiff);
private:
    void normalize();
private:
    double mLower_;
    double mUpper_;
};

#endif /* GRAPHRANGE_H_ */
