#include "Tile.h"

void CTile::Render() {
	CSprites* s = CSprites::GetInstance();

	s->Get(this->tileId)->Draw(x, y);
}
