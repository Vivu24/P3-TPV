#include "SDLApplication.h"

Texture* SDLApplication::getTexture(TextureName name) const {
	return textures[name];
}