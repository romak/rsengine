/*
* Copyright (C) 2009-2014 - Roman Kalynchuk
*
* This file is part of rsengine.
*
* REngine is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* REngine is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rsengine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __RENGINE_VERSION_H__
#define __RENGINE_VERSION_H__

namespace rengine3d {

#define RENGINE_VERSION_MAJOR 0
#define RENGINE_VERSION_MINOR 1
#define RENGINE_VERSION_RELEASE 1
#define RENGINE_VERSION_TYPE "a"

#define mkstr(a) # a
#define mkver(a, b, c) mkstr(a) "." mkstr(b) "." mkstr(c)

#define RENGINE_VERSION_STRING mkver(RENGINE_VERSION_MAJOR, RENGINE_VERSION_MINOR, RENGINE_VERSION_RELEASE) RENGINE_VERSION_TYPE

}

#endif