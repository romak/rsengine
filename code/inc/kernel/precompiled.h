/*
* Copyright (C) 2009-2013 - Roman Kalynchuk
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

#ifndef __PRECOMPILED_H__
#define __PRECOMPILED_H__

#include "kernel\platform.h"
#include "kernel\kerneltypes.h"
#include "kernel\debug.h"
#include "kernel\crc.h"

#include "mathlib\mathlib.h"
#include "mathlib\vec2.h"
#include "mathlib\vec3.h"
#include "mathlib\vec4.h"
#include "mathlib\mat4.h"
#include "mathlib\quat.h"
#include "mathlib\boundbox.h"
#include "mathlib\boundsphere.h"
#include "mathlib\plane.h"
#include "mathlib\frustum.h"
#include "mathlib\transform.h"

#include "kernel\refcount.h"
#include "kernel\args.h"
#include "kernel\idynlib.h"
#include "kernel\isubsystem.h"
#include "kernel\ifile.h"
#include "kernel\iarchive.h"
#include "kernel\ixml.h"
#include "kernel\ifilesystem.h"
#include "kernel\icmdsystem.h"
#include "kernel\ivarsystem.h"
#include "kernel\iarchive.h"
#include "kernel\ilog.h"
#include "kernel\ilogwriter.h"
#include "kernel\ikernel.h"
#include "kernel\node.h"
#include "kernel\iupdateable.h"
#include "kernel\iupdatesystem.h"
#include "kernel\imutex.h"
#include "kernel\isystem.h"

#include "input\inputtypes.h"
#include "input\iinputaction.h"
#include "input\iinputdevice.h"
#include "input\ikeyboarddevice.h"
#include "input\imousedevice.h"
#include "input\iinputsystem.h"
#include "input\actionkeyboard.h"
#include "input\actionmouse.h"

#include "render\rendertypes.h"
#include "render\imesh.h"

#endif /* !__PRECOMPILED_H__ */
