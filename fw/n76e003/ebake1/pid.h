#ifndef PID_H
#define PID_H

#include <N76E003.h>
#include <SFR_Macro.h>
#include <Function_define.h>
#include <Common.h>
#include <Delay.h>
#include <stdbool.h>

typedef signed char int8_t;
typedef int int16_t;

typedef struct {
    int8_t dstate;	//last position input
    int8_t istate;	//integrator state
    int8_t imax, imin;	//integratir limits
    int8_t vmax,vmin;	//result limits
    int8_t pgain, igain, dgain;
} pid_struct;


int8_t update_pid(pid_struct *pid, int8_t error, uint8_t position);
int8_t pid_guard(uint16_t desired, uint16_t current);

#endif /* PID_H */