#ifndef TRAFFIC_H_
#define TRAFFIC_H_

typedef	enum {
	SRED,
	SYLW,
	SGRN,
	MOTOR_CW,
	PEDESTRIAN_CROSS,
	MOTOR_ACW
} signal_state;

extern volatile signal_state cs;
extern volatile signal_state ps;

void traffic_init();
void traffic_update();

#endif /* TRAFFIC_H_ */