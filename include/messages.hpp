#pragma once

typedef struct
{
	int in = 0;
	int out = 0;
} t_inout;

typedef struct s2c
{
	int ID = -1;
	bool start = false;
} t_s2c;

typedef struct c2s
{
	int ID;
	bool Freq_sensor = false;
	bool Areq_sensor = false;
	bool Flevel_sensor = false;
	int qs;
	t_inout inout;
} t_c2s;

