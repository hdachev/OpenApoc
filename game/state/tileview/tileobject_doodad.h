#pragma once

#include "game/state/tileview/tileobject.h"
#include "library/sp.h"
#include "library/vec.h"

namespace OpenApoc
{

class Doodad;

class TileObjectDoodad : public TileObject
{
  public:
	void draw(Renderer &r, TileTransform &transform, Vec2<float> screenPosition, TileViewMode mode,
	          int, bool, bool) override;
	~TileObjectDoodad() override;

	wp<Doodad> doodad;

	Vec3<float> getPosition() const override;
	float getZOrder() const override;

  private:
	friend class TileMap;
	TileObjectDoodad(TileMap &map, sp<Doodad> doodad);
};

} // namespace OpenApoc
