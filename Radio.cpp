#include "Radio.h"
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

const double pi = 3.14159;
const double d2r = pi/180;

Radio::Radio() {      
}

Radio::~Radio() {
    //dtor
}

void Radio::setNode(radioNode r) {
    node = r;
}

radioNode Radio::getNode() {
    return node;
}

void Radio::updatePosition(string rName, double dt) {
    motionModels(rName, dt);
}

int Radio::getTXrate(radioNode r2) {
    double ss = getRXsignal(node, r2);
    for (int i = 7; i >=0; i--) {
        if (ss > RXsensitivityTable[i])
            return TXrateTable[i];
    }
    return 0;
}

double Radio::getRange_km(radioNode r1, radioNode r2) {
    double range;
    double dx = r1.x - r2.x;
    double dy = r1.y - r2.y;
    range = sqrt(dx * dx + dy * dy);
    range = range / 1000; // meters to km
    return range;
}

double Radio::getPathLoss(radioNode r1, radioNode r2) { // compute path loss between two radios
    double range_km, pathLoss;
    range_km = getRange_km(r1, r2);
    pathLoss = 20 * log10(centerFreq) + 20 * log10(range_km) + 32.44;
    return pathLoss;
}

double Radio::getRXsignal(radioNode r1, radioNode r2) {// compute SNR between any two radios
    // PWR = (TX_PWR + TX_GAIN + RX_GAIN)
    // rxSignalStrength = PWR � PATH_LOSS � NOISE_FIGURE - FADE_MARGIN
    // SNR = rxSignalStrength - THRM_NOISE 
    int pwr = r1.power + r1.gain + r2.gain;
    double rxSignalStrength = (double)pwr - getPathLoss(r1, r2) - noiseFigure - fadeMargin;
    return rxSignalStrength;
}

void Radio::motionModels(string rName, double dt) { 
    // fstream output;
    // output.open(rName+"positionOutput.csv", fstream::app);
    switch(node.motion_model){
    case(0) : // static node     
        break;//node is static, do not update
    case(1) : // linear motion
        node.x = node.x + node.v * dt * sin(node.h * d2r);
        node.y = node.y + node.v * dt * cos(node.h * d2r);
        break;
    case(2) : // node is moving in a counter clockwise circle
        double w = node.v / node.r;//angular rate = velocity/radius
        double theta = atan2(node.y-node.yo,node.x-node.xo); 
        theta = theta + w * dt+(2*pi);//euler integration//add 2 pi so the solution is always positive
        node.x = node.xo + node.r * cos(theta);//new x
        node.y = node.yo + node.r * sin(theta);//new y
        break;
    }
    // output<<node.x<<", " <<node.y<<"\n";
    // output.close();
}