#include"Cinema.h"

Cinema::Cinema()
{
	sessions = nullptr;
	count = 0;
}

Cinema::Cinema(const Cinema& _cinema)
{
	count = _cinema.count;
	sessions = new Session[count];
	memcpy(sessions, _cinema.sessions, sizeof(_cinema.sessions));
}

Cinema::Cinema(int _count, istream& _stream)
{
	count = _count;
	sessions = new Session[count];
	for (int i = 0; i < count; ++i)
		_stream >> sessions[i];
}

Cinema::~Cinema()
{
	delete[] sessions;
	count = 0;
}