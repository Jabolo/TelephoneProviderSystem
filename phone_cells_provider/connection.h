#pragma once
#include "pch.h"

class connection
{
public:
	connection(int, int, int, int);
	void setIdConnection(int x);
	void setFrom(int x);
	void setTo(int x);
	void setStatus(int x);
	void setDuration(int x);

	int getIdConnection(int) const;
	int getFrom(int) const;
	int getTo(int) const;
	int getStatus(int) const;
	int getDuration(int) const;

	~connection();
private:
	int idConnection;
	int from;
	int to;
	int status;
	int duration;
};

