#pragma once

typedef struct s2c // From Server to Client
{
	int ID = 0;
	bool start = false;
} t_s2c;

typedef struct c2s // From Client to Server
{
	int ID = 0;
	bool Freq_sensor = false;
	bool Areq_sensor = false;
	bool Flevel_sensor = false;
} t_c2s;
