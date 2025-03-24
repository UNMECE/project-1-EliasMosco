#include<iostream>
#include"Capacitor.h"
double deltaTime = 0.0000000001;
double finalTime = 0.000005;
int Num_of_timesteps = 50000;
double resistence = 1;
double capacitance = 0.000000000100;
double initialCurrent = 0.01;
double initialVoltage = 10.0;
Capacitor constVoltCap;
Capacitor constCurrentCap;

using namespace std;

double CalculateCurrent(const Capacitor& constVoltCap, int time ){
    return 
        constVoltCap.current[time-1] - (constVoltCap.current[time-1]/resistence*constVoltCap.C)*deltaTime;
}

double CalculateVoltage(const Capacitor& constCurrentCap, int time){
    return 
        constCurrentCap.voltage[time-1] + (constCurrentCap.current[time-1]*(1.0/constCurrentCap.C)*deltaTime);
}

void InitCapacitor( Capacitor& cap, int totalSteps, double c){
	cap.time = new double[totalSteps];
	cap.voltage = new double[totalSteps];
	cap.current = new double[totalSteps];
	cap.C = c;
}

void FreeCapacitor(Capacitor &cap) {
	delete[] cap.time;
	delete[] cap.voltage;
	delete[] cap.current;
	}

int main(int argc, char const *argv[])
{
    InitCapacitor(constCurrentCap, Num_of_timesteps, capacitance);
		InitCapacitor(constVoltCap, Num_of_timesteps, capacitance);

    //const current power source
    constCurrentCap.current[0] = initialCurrent;
		constCurrentCap.time[0] = 0.0;
    constCurrentCap.voltage[0] = initialCurrent*(1.0/capacitance)*deltaTime;

    //const Voltage power source
    constVoltCap.voltage[0] = initialVoltage;
		constVoltCap.time[0] = 0.0;
    constVoltCap.current[0] = initialVoltage/resistence;

    for( int i = 1; i< Num_of_timesteps; i++){
				constCurrentCap.time[i] = constCurrentCap.time[i-1] +deltaTime;
				constVoltCap.time[i] = constVoltCap.time[i-1] + deltaTime;

        constVoltCap.voltage[i] = initialVoltage;
        constCurrentCap.voltage[i] = CalculateVoltage(constCurrentCap, i);

        constVoltCap.current[i] = CalculateCurrent(constVoltCap, i);
        constCurrentCap.current[i] = initialCurrent;
        if(i %200 == 0){
            cout << " For the Current Independant source, the voltage is " << constCurrentCap.voltage[i]
            <<"Volts at time" << constCurrentCap.time[i] << " seconds. " << endl;
            cout << " For the Voltage Independant source, the Current is " << constVoltCap.current[i]
            <<"Amps at time" << constVoltCap.time[i] << ". " << endl;
						cout<< "---------------------------------------" << endl;
        }
    }

		FreeCapacitor(constCurrentCap);
		FreeCapacitor(constVoltCap);
    return 0;
}
