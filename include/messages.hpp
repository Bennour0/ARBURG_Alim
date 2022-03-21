/*client/serveur
	Sending :
		*ID
		*Freq sensor
		*Areq sensor
		*Flevel sensor
	Receiving :
		*ID
		*start*/

#pragma once

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
} t_c2s;
