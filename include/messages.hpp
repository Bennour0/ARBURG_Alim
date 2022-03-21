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
	int ID;
	bool start;
} t_s2c;

typedef struct c2s
{
	int ID;
	bool Freq_sensor;
	bool Areq_sensor;
	bool Flevel_sensor;
} t_c2s;
