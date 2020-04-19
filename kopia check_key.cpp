#include "Car.h"

extern Form *u;
extern Man *m;

void Car::check_key(bool &run)
{
    if      (key[KEY_ESC] && esc_on == false ) { esc_on = true; rest(250); }
    else if (key[KEY_ESC] && esc_on == true ) { esc_on = false; rest(250); }
    else if (key[KEY_ENTER] && esc_on == true) { run = false; }
    else if (key[KEY_ENTER] && speed == 0) { get_out_car(); }
    else if (key[KEY_SPACE] && key[KEY_LEFT]) { brake(); turn_left(); }
    else if (key[KEY_SPACE] && key[KEY_RIGHT]) { brake(); turn_right(); }
    else if (key[KEY_SPACE]) { brake(); }
    else if( key[KEY_UP] && key[KEY_LEFT] && (direction == 1 || motion == 0) ) { go_forward(); turn_left(); }
    else if( key[KEY_UP] && key[KEY_RIGHT] && (direction == 1 || motion == 0) ) { go_forward(); turn_right(); }
    else if( key[KEY_DOWN] && key[KEY_LEFT] && (direction == 0 || motion == 0) ) { go_back(); turn_left(); }
    else if( key[KEY_DOWN] && key[KEY_RIGHT] && (direction == 0 || motion == 0) ) { go_back(); turn_right(); }
    else if( key[KEY_UP] && (direction == 1 || motion == 0) ) { go_forward(); }
    else if( key[KEY_DOWN] && (direction == back || motion == 0) ) { go_back(); }
    else if( key[KEY_LEFT] && motion == 1 )
    {
        if      (direction == 1) { roll_forward(); }
        else if (direction == 0) { roll_back(); }
        turn_left();
    }
    else if( key[KEY_RIGHT] && motion == 1 )
    {
        if      (direction == 1) { roll_forward(); }
        else if (direction == 0) { roll_back(); }
        turn_right();
    }
    else if( motion == 1 && direction == 1 ) { roll_forward(); }
    else if( motion == 1 && direction == 0 ) { roll_back(); }
    if( speed == 0) { motion = 0; }
    form = car;
}

void Car::brake()
{
    speed -= brakes;
    if (speed < 0) speed = 0;
    if (direction == 1) { drawing_position_forward(); }
    if (direction == 0) { drawing_position_back(); }
}
void Car::go_forward()
{
    motion = 1;
    direction = 1;
    speed += acceleration;
    if (speed > max_speed) { speed = max_speed; }
    drawing_position_forward();
}
void Car::go_back()
{
    motion = 1;
    direction = 0;
    speed += acceleration;
    if (speed > min_speed) { speed = min_speed; }
    drawing_position_back();
}
void Car::roll_forward()
{
    direction = 1;
    speed -= deceleration;
    if (speed < 0) { speed = 0; }
    drawing_position_forward();
}
void Car::roll_back()
{
    direction = 0;
    speed -= deceleration;
    if (speed < 0) { speed = 0; }
    drawing_position_back();
}
void Car::turn_left()
{
    if(speed != 0)
    {
        if      (direction == forward) { angle -= handling; }
        else if (direction == back) { angle += handling; }
        if      (angle > 255) { angle = 0; }
        else if (angle < 0) { angle = 255; }
    }
}
void Car::turn_right()
{
    if(speed != 0)
    {
        if      (direction == forward) { angle += handling; }
        else if (direction == back) { angle -= handling; }
        if      (angle > 255) { angle = 0; }
        else if (angle < 0) { angle = 255; }
    }
}

void Car::get_out_car()
{
    u = m; rest(200);
    m->map_x = map_x;
    m->map_y = map_y;
    m->scn_x = scn_x;
    m->scn_y = scn_y;
    m->scl_x = scl_x;
    m->scl_y = scl_y;
}
