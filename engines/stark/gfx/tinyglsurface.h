/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef STARK_GFX_TINYGL_SURFACE_H
#define STARK_GFX_TINYGL_SURFACE_H

#include "engines/stark/gfx/surfacerenderer.h"
#include "engines/stark/gfx/tinygl.h"

#include "graphics/tinygl/zgl.h"
#include "graphics/tinygl/zblit.h"

#include "math/vector2d.h"

namespace Stark {
namespace Gfx {

class TinyGLDriver;
class Texture;

/**
 * An programmable pipeline TinyGL surface renderer
 */
class TinyGLSurfaceRenderer : public SurfaceRenderer {
public:
	TinyGLSurfaceRenderer(TinyGLDriver *gfx);
	virtual ~TinyGLSurfaceRenderer();

	// SurfaceRenderer API
	void render(const Texture *texture, const Common::Point &dest) override;
	void render(const Texture *texture, const Common::Point &dest, uint width, uint height) override;

private:
	Math::Vector2d normalizeOriginalCoordinates(int x, int y) const;
	Math::Vector2d normalizeCurrentCoordinates(int x, int y) const;

	TinyGLDriver *_gfx;
};

} // End of namespace Gfx
} // End of namespace Stark

#endif // STARK_GFX_TINYGL_SURFACE_H
