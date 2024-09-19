#include "Chest.h"
#include "ConsoleRenderer.h"

Chest::Chest()
{
	m_stat = SetRandomStat();
	m_amount = SetAmount();
}

void Chest::Open(Entity* e, ConsoleRenderer* console)
{
	switch (m_stat)
	{
	case Stat::ATK:
		e->SetStat(Stat::MAXATK, m_amount);
		break;
	case Stat::PM:
		e->SetStat(Stat::MAXPM, m_amount);
		break;
	case Stat::PA:
		e->SetStat(Stat::MAXPA, m_amount);
		break;
	case Stat::MAXHP:
		e->SetStat(Stat::HP, m_amount);
		break;
	}

	e->SetStat(m_stat, m_amount);
	string s = "Chest opened ! +" + std::to_string(static_cast<int>(m_amount)) + " " + console->GetStatsTitle()[m_stat];
	console->SetLog(s);
}

Stat Chest::SetRandomStat()
{
	vector<Stat> possibleStats;

	for (auto statData : GameManager::GetInstance()->GetPlayer()->GetStats())
	{
		if (statData.first != Stat::HP) possibleStats.push_back(statData.first);
	}

	return possibleStats[std::rand() % possibleStats.size()];
}

int Chest::SetAmount()
{
	int amount = 0;

	switch (m_stat)
	{
	case Stat::ATK:
	case Stat::DEF:
	case Stat::MAXATK:
		amount = std::rand() % 5 + 1;
		break;
	case Stat::PM:
	case Stat::PA:
	case Stat::MAXPM:
	case Stat::MAXPA:
		amount = std::rand() % 2 + 1;
		break;
	case Stat::MAXHP:
		amount = std::rand() % 10 + 5;
		break;
	}

	return amount;
}