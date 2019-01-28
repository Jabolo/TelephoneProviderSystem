#include "pch.h"
#include "connection.h"

connection::connection(int fr, int t, int stat, int dur)
	: from(fr), to(t), status(stat), duration(dur)
{
}

void connection::setIdConnection(int x)
{
	this->idConnection = x;
}

void connection::setFrom(int x)
{
	this->from = x;
}

void connection::setTo(int x)
{
	this->to = x;
}

void connection::setStatus(int x)
{
	this->status = x;
}

void connection::setDuration(int x)
{
	this->duration = x;
}

int connection::getIdConnection(int) const
{
	return idConnection;
}

int connection::getFrom(int) const
{
	return from;
}

int connection::getTo(int) const
{
	return to;
}

int connection::getStatus(int) const
{
	return status;
}

int connection::getDuration(int) const
{
	return duration;
}
