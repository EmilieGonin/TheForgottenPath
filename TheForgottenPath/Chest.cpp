#include "Chest.h"
#include "ConsoleRenderer.h"

Chest::Chest()
{
	m_stat = SetRandomStat();
	m_amount = std::rand() % 10 + 1;
}

void Chest::Open(Entity* e, ConsoleRenderer* console)
{
	e->SetStat(m_stat, m_amount);
	std::string s = "Chest opened ! +" + std::to_string(static_cast<int>(m_amount)) + " " + console->GetStatsTitle()[m_stat];
	console->SetLog(s);
}

Stat Chest::SetRandomStat()
{
	std::vector<Stat> possibleStats;

	for (auto statData : GameManager::GetInstance()->GetPlayer()->GetStats())
	{
		if (statData.first != Stat::PA && statData.first != Stat::PM)
		{
			possibleStats.push_back(statData.first);
		}
	}

	return possibleStats[std::rand() % possibleStats.size()];
}