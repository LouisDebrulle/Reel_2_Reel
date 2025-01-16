#ifndef REEL_2_REEL_SYS
#define REEL_2_REEL_SYS


class reel_2_reel_sys
{
private:
public:
    
    double spring_const_m;
    double spring_const_c;

    double rest_pos;

    double spring_curve(double pos){
        return spring_const_m*pos +spring_const_c;
    }

    reel_2_reel_sys(){
        spring_const_m = 5;
        spring_const_c = -14;

        rest_pos = 0;
    }
};









#endif




