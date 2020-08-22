#include "pid.h"

int8_t update_pid(pid_struct *pid, int8_t error, uint8_t position)
{
    int16_t pterm, iterm, dterm, res;

    //proportional calculation
    pterm = pid->pgain * error;

    // update integrator state
    pid->istate += error;
    if (pid->istate > pid->imax)
        pid->istate = pid->imax;
    else if (pid->istate < pid->imin)
        pid->istate = pid->imin;

    //integral calcucation
    iterm = pid->igain * pid->istate;

    //differential calculation
    dterm = pid->dgain * (position - pid->dstate);

    pid->dstate = position;

    res = pterm + iterm - dterm;
    //cut by limits
    if (res > pid->vmax)
        res = pid->vmax;
    else if (res < pid->vmin)
        res = pid->vmin;

    return res;
}

int8_t pid_guard(uint16_t desired, uint16_t current)
{

    int16_t temp_error;

    temp_error = desired - current;
    if (temp_error > 127)
        temp_error = 127;
    else if (temp_error < -127)
        temp_error = -127;

    return (int8_t)temp_error;
}