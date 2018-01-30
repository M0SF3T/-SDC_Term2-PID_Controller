#ifndef PID_H
#define PID_H
#include <chrono>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  const double Kp = 0.6; // Slighlty large value of Kp as a fast response is needed at somewhat high speeds (30mph or higehr) on deep curves
  const double Ki = 0.0015; // Low Ki allows for smooth recovers after strong turn responses
  const double Kd = 0.35; // Kd manually tuned for good responses based on the time interval measurements

  //initializer toggle variable
  bool is_initialized = false;

  //Assist variables for derivative and integrative parts
  double prev_cte;
  double int_cte;
  double diff_cte;

  double steer;

  std::chrono::steady_clock::time_point prev_time;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd, std::chrono::steady_clock::time_point time_stamp);
  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte, std::chrono::steady_clock::time_point time_stamp);



  /*
  * Calculate the total PID error.
  */
  //double TotalError();
};

#endif /* PID_H */
