#ifndef RADIO_H
#define RADIO_H
#include<vector>
#include<iostream>

struct radioNode {
    double power; // dBm
    double gain; // dBi
    double xo; // starting x pos (linear/static), center (circle)
    double yo; // starting x pos (linear/static), center (circle)
    double x; // x pos (m)
    double y; // y pos (m)
    double h; // heading (rad),only used for linear motion
    double r; // radius (m)
    double v; // velocity (mps)
    int motion_model; //0 - static, 1 - linear, 2 - circle

    radioNode() {
        power = 0; //100mW
        gain = 0;
        xo = 0;
        yo = 0;
        x = 0;
        y = 0;
        h = 0;
        r = 0;
        v = 0;
        motion_model = 0;
    };

    radioNode(double p, double g, double xo, double yo, double x, double y, double h, double r, double v, int mm)
        :power(p), gain(g), xo(xo), yo(yo), x(xo), y(yo), h(h), r(r), v(v), motion_model(mm) {};
};

class Radio
{
public:
    Radio();
    ~Radio();
    int getTXrate(radioNode r2);
    void setNode(radioNode r);
    radioNode getNode();
    void updatePosition(std::string rName, double dt);
protected:
private: 
    radioNode node;
    const int centerFreq = 2412; //MHz, 802.11 ch1
    const int RXsensitivityTable[8] = { -98, -95, -92, -89, -86, -83, -80, -77}; // Receive signal strength values corresponding to throughput rates in TXrateTable
    const int TXrateTable[8]  =       {   7,  13,  20,  26,  39,  52,  59,  65}; // https://en.wikipedia.org/wiki/IEEE_802.11n-2009
    const int thrmNoise = -101; //dB, for 20 MHz wide RF channel
    const int fadeMargin = 5; //dB, assumed environmental property
    const int noiseFigure = 4; //dB, assumed radio property
    double getRange_km(radioNode r1, radioNode r2);
    double getPathLoss(radioNode r1, radioNode r2);
    double getRXsignal(radioNode r1, radioNode r2);
    void motionModels(std::string rName, double dt);
};

#endif // RADIO_H