#include<iostream>
#include"Capacitor.h"
double deltaTime = 0.0000000001f;
double finalTime = 0.000005f;
int Num_of_timesteps = 50000;
int currentTimeStep;
double resistence = 1;
double capacitance = 0.000000000100;
double initialCurrent = 0.01f;
double current[];
double initialVoltage = 10.0f;
double voltage[];
Capacitor constVoltCap;
Capacitor constCurrentCap;

using namespace std;
double CalculateCurrent(Capacitor constVoltCap, int time ){
    return 
        constVoltCap.current[time-1] - (constVoltCap.current[time-1]/resistence*constVoltCap.C)*deltaTime;
}
double CalculateVoltage(Capacitor constCurrentCap, int time){
    return 
        constCurrentCap.voltage[time-1] + (constCurrentCap.current[time-1]*(1/constVoltCap.C)*deltaTime);
}

int main(int argc, char const *argv[])
{
    //const current power source
    constCurrentCap.current[0] = initialCurrent;
    constCurrentCap.C = capacitance;
    constCurrentCap.time = 0;
    constCurrentCap.voltage[0] = CalculateVoltage(constCurrentCap, 0);

    //const Voltage power source
    constVoltCap.voltage[0] = initialVoltage;
    constVoltCap.C = capacitance;
    constVoltCap.time = 0;
    constVoltCap.current[0] = CalculateCurrent(constVoltCap, 0);

    for( int i = 1; i< Num_of_timesteps; i++){
        constVoltCap.voltage[i] = initialVoltage;
        constCurrentCap.voltage[i] = CalculateVoltage(constCurrentCap, i);

        constVoltCap.current[i] = CalculateCurrent(constVoltCap, i);
        constCurrentCap.current[i] = initialCurrent;
        if(i %200 == 0){
            cout << " For the Current Independant source, the voltage is " << constCurrentCap.voltage[i]
            <<" at time" << deltaTime *i << ". " << endl;
            cout << " For the Voltage Independant source, the Current is " << constCurrentCap.current[i]
            <<" at time" << deltaTime *i << ". " << endl;
        }
    }
    return 0;
}
