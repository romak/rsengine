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

#ifndef __IEVENT_H__
#define __IEVENT_H__

namespace rengine3d {

	typedef struct {

	}event_t;

	class ISystemEvent {
	public:
		ISystemEvent(){};
		virtual ~ISystemEvent(){};
		
		virtual void OnInit(void){};
		virtual void OnShutdown(void){};
		virtual void OnDraw(void){};

		virtual void OnUpdate(real timeStep){};

		virtual void OnPostSceneDraw(){};
		virtual void OnPostGUIDraw(){};

		virtual void OnInputFocus() {};
        virtual void OnInputBlur() {};
        virtual void OnKeyDown(int sym, int mod, uint unicode) {};
        virtual void OnKeyUp(int sym, int mod, uint unicode) {};
		virtual void OnMouseFocus() {};
        virtual void OnMouseBlur() {};
        virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool left,bool right,bool middle) {};
        virtual void OnMouseWheel(bool up, bool down) {};
		virtual void OnLButtonDown(int mX, int mY) {};
        virtual void OnLButtonUp(int mX, int mY) {};
        virtual void OnRButtonDown(int mX, int mY) {};
        virtual void OnRButtonUp(int mX, int mY) {};
        virtual void OnMButtonDown(int mX, int mY) {};
        virtual void OnMButtonUp(int mX, int mY) {};
		virtual void OnMinimize() {};
        virtual void OnRestore() {};
        virtual void OnResize(int w,int h) {};
        virtual void OnExpose() {};
        virtual void OnUser(uint type, int code, void* data1, void* data2) {};
	};
}

#endif
