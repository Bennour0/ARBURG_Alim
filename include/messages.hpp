#pragma once
#include "my_debug.hpp"

typedef struct s2c // From Server to Client
{
	int ID;
	bool start;
} t_s2c;

typedef struct c2s // From Client to Server
{
	DBG_BID1(int ID = 1;)
	DBG_BID2(int ID = 2;)
	bool Freq_sensor;
	bool Areq_sensor;
	bool Flevel_sensor;
} t_c2s;
