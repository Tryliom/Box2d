#include "module/Module.h"

#include "entity/Entity.h"

Module::Module(const Stats::EntityStats stats, const Stats::WeaponStats weaponStats)
{
	_stats = stats;
	_weaponStats = weaponStats;
}

std::vector<TextLine> Module::GetDescription() const
{
	std::vector<TextLine> description;
	std::vector<TextLine> entityStats = _stats.GetTextLines();
	std::vector<TextLine> weaponStats = _weaponStats.GetTextLines();

	description.insert(description.end(), entityStats.begin(), entityStats.end());
	description.insert(description.end(), weaponStats.begin(), weaponStats.end());

	return description;
}
