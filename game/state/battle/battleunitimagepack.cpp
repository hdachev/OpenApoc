#include "game/state/battle/battleunitimagepack.h"
#include "game/state/gamestate.h"

namespace OpenApoc
{
template <>
sp<BattleUnitImagePack> StateObject<BattleUnitImagePack>::get(const GameState &state,
                                                              const UString &id)
{
	auto it = state.battle_unit_image_packs.find(id);
	if (it == state.battle_unit_image_packs.end())
	{
		LogError("No BattleUnitImagePack matching ID \"%s\"", id.cStr());
		return nullptr;
	}
	return it->second;
}

template <> const UString &StateObject<BattleUnitImagePack>::getPrefix()
{
	static UString prefix = "BATTLEUNITIMAGEPACK_";
	return prefix;
}
template <> const UString &StateObject<BattleUnitImagePack>::getTypeName()
{
	static UString name = "BattleUnitImagePack";
	return name;
}
template <>
const UString &StateObject<BattleUnitImagePack>::getId(const GameState &state,
                                                       const sp<BattleUnitImagePack> ptr)
{
	static const UString emptyString = "";
	for (auto &a : state.battle_unit_image_packs)
	{
		if (a.second == ptr)
			return a.first;
	}
	LogError("No BattleUnitImagePack matching pointer %p", ptr.get());
	return emptyString;
}

const UString BattleUnitImagePack::getNameFromID(UString id)
{
	static const UString emptyString = "";
	if (id.length() == 0)
		return emptyString;
	auto plen = getPrefix().length();
	if (id.length() > plen)
		return id.substr(plen, id.length() - plen);
	LogError("Invalid BattleUnitImagePack ID %s", id.cStr());
	return emptyString;
}
}
