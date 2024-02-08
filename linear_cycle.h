#ifndef LINEAR_CYCLE_H
#define LINEAR_CYCLE_H

#include <iostream>
#include <iomanip>

//! This class takes the xyz results of one servo motion cycle as input.
//! Most ot the time this cycle time is 0.001 seconds.
//!
//!
//! This class checks if a xyz motion exceeds the max acceleration for
//! each axis.
//!
//! If so, it sets a new target position for xyz, satisfying the max
//! acceleration for each axis.
class linear_cycle
{
public:
    linear_cycle();

    void set_debug(bool state);

    void set_cycle_values(double velocity_begin_x,
                          double displacement_x,
                          double velocity_begin_y,
                          double displacement_y,
                          double velocity_begin_z,
                          double displacement_z,
                          double acceleration_max,
                          double cycletime
                          ){
        vox=velocity_begin_x;
        sx=displacement_x;
        voy=velocity_begin_y;
        sy=displacement_y;
        voz=velocity_begin_z;
        sz=displacement_z;
        am=acceleration_max;
        t=cycletime;
    }

    void calculate();

    void get_cycle_results(double &displacement_x,
                           double &velocity_end_x,
                           double &acceleration_x,
                           double &displacement_y,
                           double &velocity_end_y,
                           double &acceleration_y,
                           double &displacement_z,
                           double &velocity_end_z,
                           double &acceleration_z);

    void perform_unit_test();

private:

    double vox=0;
    double sx=0;
    double voy=0;
    double sy=0;
    double voz=0;
    double sz=0;
    double am=0;
    double t=0;

    bool is_x=0, is_y=0, is_z=0;
    double ratio_x=0, ratio_y=0, ratio_z=0, ratio=0;

    double srx,arx,vex;
    double sry,ary,vey;
    double srz,arz,vez;

    bool debug=0;

    double a_given_s_vo_t(double s, double vo, double t);

    double s_given_a_vo_t(double a, double vo, double t);

    double ve_given_vo_a_t(double vo, double a, double t);

    double s_ratio_cycle(double vo, double s, double am, double cycletime);

    void set_ratio_cycle(double ratio, double vo, double s, double &sr, double &ar, double &ve);

    double get_lowest_ratio();

    void print_cycles();

};

#endif // LINEAR_CYCLE_H
