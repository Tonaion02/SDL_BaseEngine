#pragma once

#include "PrecompiledHeaders.h"

#include "Format.h"





//Non so se gestirlo come una sorta di stack oppure come un normale vettore(penso come stack)
template<typename Status>
class StatusHandler
{
public:
	StatusHandler() : m_indexIncrement(0) {}

	void addStatus(Status status)
	{
		m_status.emplace(m_status.begin(), status);
		m_indexIncrement++;
	}

	void clearStatus()
	{
		m_status.clear();
		m_indexIncrement = 0;
	}
	
	int searchStatus(Status status)
	{
		for (int i = 0; i < m_status.size(); i++)
		{
			if (m_status[i] == status)
			{
				return i;
			}
		}

		return -1;
	}

	Status& getStatus(int index)
	{
		//Aggiungere assert per index
		return m_status[index];
	}

	int getSize()
	{
		return m_status.size();
	}

	//void deleteStatus(Status status);
private:
	std::vector<Status> m_status;
	unsigned int m_indexIncrement;
};