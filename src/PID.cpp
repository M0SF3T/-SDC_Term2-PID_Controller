#include "PID.h"
#include <iostream>
#include <chrono>
#include <typeinfo>

//using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, std::chrono::steady_clock::time_point time_stamp) {
	// Intialized sets values required for differential and integral components to 0 for use during the next cycle
	prev_cte = 0;
	int_cte = 0;
	prev_time = time_stamp; // sets current time measures as previous time (for delta_t calculation)

	//toggles initialization flag
	is_initialized = true;
	

}

void PID::UpdateError(double cte, std::chrono::steady_clock::time_point time_stamp) {
	//
	using namespace std;

	// Calculates elapsed time between cycles for delta_t measurement, which is used to calculate the differential component
	double delta_t = (std::chrono::duration_cast<std::chrono::microseconds>(time_stamp - prev_time).count())/1000000.0;
	std::cout << "Change in time (delta_t) = " << delta_t << std::endl;

	//Calculates the differential part of equation
	diff_cte = (cte - prev_cte) / delta_t;

	//Sets current measures time and cte as previous ones (for use in the next cycle differential component calculation)
	prev_time = time_stamp;
	prev_cte = cte;

	//Calculates the integral component of the equation
	int_cte += cte;

	// Calculates the steer using all 3 of the PID components
	steer = (-Kp * cte) - (Kd * diff_cte) - (Ki * int_cte);

	//Normalizes steer to be within [1, -1]
	while (steer > 1 || steer < -1)
	{
		if (steer > 1)
			steer = 1; // steer -= 1;
		if (steer < -1)
			steer = -1; // steer +=1
	}
}

//double PID::TotalError() {
//}

