#include "linear_cycle.h"

linear_cycle::linear_cycle()
{

}

void linear_cycle::perform_unit_test(){

    std::cout<<"- Perform unit test -"<<std::endl;

    double velocity_begin_x     =   8.8;
    double displacement_x       =   21.21-19.36;
    double velocity_begin_y     =   8.8;
    double displacement_y       =   21.20-19.36;
    double velocity_begin_z     =   8.8;
    double displacement_z       =   21.16-19.36;
    double acceleration_max     =   2;
    double cycletime            =   0.2;

    linear_cycle *lc = new linear_cycle();
    lc->set_debug(true);
    lc->set_cycle_values(velocity_begin_x,
                         displacement_x,
                         velocity_begin_y,
                         displacement_y,
                         velocity_begin_z,
                         displacement_z,
                         acceleration_max,
                         cycletime);

    lc->calculate();

    double velocity_end_x;
    double acceleration_x;
    double velocity_end_y;
    double acceleration_y;
    double velocity_end_z;
    double acceleration_z;

    lc->get_cycle_results(displacement_x,
                          velocity_end_x,
                          acceleration_x,
                          displacement_y,
                          velocity_end_y,
                          acceleration_y,
                          displacement_z,
                          velocity_end_z,
                          acceleration_z);

    delete lc;
}

void linear_cycle::set_debug(bool state){
    debug=state;
}

double linear_cycle::a_given_s_vo_t(double s, double vo, double t) {
    return 2 * (s - vo * t) / (t * t);
}

double linear_cycle::s_given_a_vo_t(double a, double vo, double t) {
    return vo * t + 0.5 * a * t * t;
}

double linear_cycle::ve_given_vo_a_t(double vo, double a, double t) {
    // Calculate final velocity given time t.
    return vo + a * t;
}

double linear_cycle::s_ratio_cycle(double vo, double s, double am, double cycletime){

    // Set precision to 2 decimal places
    std::cout << std::fixed << std::setprecision(3);

    double t=cycletime;

    double ratio=0;

    double a=a_given_s_vo_t(s,vo,t);

    double sx1=s_given_a_vo_t(am,vo,t);
    double sx2=s_given_a_vo_t(a,vo,t);

    if(sx2>sx1){ // s exceeds am, set s to fit am.
        ratio=sx1/sx2;
        s=sx1;
        a=am;
    }
    return ratio;
}

void linear_cycle::set_ratio_cycle(double ratio, double vo, double s, double &sr, double &ar, double &ve){
    sr=s*ratio;
    ar=a_given_s_vo_t(sr,vo,t);
    ve=ve_given_vo_a_t(vo,ar,t);
}

double linear_cycle::get_lowest_ratio() {
    ratio=0;

    is_x = (ratio_x < ratio_y) && (ratio_x < ratio_z);
    is_y = (ratio_y < ratio_x) && (ratio_y < ratio_z);
    is_z = (ratio_z < ratio_x) && (ratio_z < ratio_y);

    if(is_x){
        ratio=ratio_x;
    }
    if(is_y){
        ratio=ratio_y;
    }
    if(is_z){
        ratio=ratio_z;
    }
    return ratio;
}

void linear_cycle::calculate(){
    ratio_x=s_ratio_cycle(vox,sx,am,t);
    ratio_y=s_ratio_cycle(voy,sy,am,t);
    ratio_z=s_ratio_cycle(voz,sz,am,t);

    ratio=get_lowest_ratio();

    set_ratio_cycle(ratio,vox,sx,srx,arx,vex);
    set_ratio_cycle(ratio,voy,sy,sry,ary,vey);
    set_ratio_cycle(ratio,voz,sz,srz,arz,vez);

    print_cycles();
}

void linear_cycle::get_cycle_results(double &displacement_x,
                       double &velocity_end_x,
                       double &acceleration_x,
                       double &displacement_y,
                       double &velocity_end_y,
                       double &acceleration_y,
                       double &displacement_z,
                       double &velocity_end_z,
                       double &acceleration_z){


    displacement_x=srx;
    velocity_end_x=vex;
    acceleration_x=arx;
    displacement_y=sry;
    velocity_end_y=vey;
    acceleration_y=ary;
    displacement_z=srz;
    velocity_end_z=vez;
    acceleration_z=arz;
}

void linear_cycle::print_cycles(){
    if(debug){

        // Set the output to fixed-point notation
        std::cout << std::fixed << std::setprecision(3);

        std::cout<<"- Ratio values -"<<std::endl;
        std::cout<<"x:"<<ratio_x<<std::endl;
        std::cout<<"y:"<<ratio_y<<std::endl;
        std::cout<<"z:"<<ratio_z<<std::endl;
        std::cout<<""<<std::endl;

        std::cout<<"- Ratio bool -"<<std::endl;
        std::cout<<"x:"<<std::boolalpha<<is_x<<std::endl;
        std::cout<<"y:"<<std::boolalpha<<is_y<<std::endl;
        std::cout<<"z:"<<std::boolalpha<<is_z<<std::endl;
        std::cout<<""<<std::endl;

        std::cout<<"- X -"<<std::endl;
        std::cout<<"s:"<<srx<<std::endl;
        std::cout<<"a:"<<arx<<std::endl;
        std::cout<<"vo:"<<vox<<std::endl;
        std::cout<<"ve:"<<vex<<std::endl;
        std::cout<<""<<std::endl;

        std::cout<<"- Y -"<<std::endl;
        std::cout<<"s:"<<sry<<std::endl;
        std::cout<<"a:"<<ary<<std::endl;
        std::cout<<"vo:"<<voy<<std::endl;
        std::cout<<"ve:"<<vey<<std::endl;
        std::cout<<""<<std::endl;

        std::cout<<"- Z -"<<std::endl;
        std::cout<<"s:"<<srz<<std::endl;
        std::cout<<"a:"<<arz<<std::endl;
        std::cout<<"vo:"<<voz<<std::endl;
        std::cout<<"ve:"<<vez<<std::endl;
        std::cout<<""<<std::endl;
    }
}
