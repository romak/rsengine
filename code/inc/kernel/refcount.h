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

#ifndef __REFCOUNT_H__
#define __REFCOUNT_H__

namespace rengine3d {

	class CRefCount {
	public:
		CRefCount(): m_refCount(1) {}

		void AddRef() {
			m_refCount++;
		}

		int Release() {
			--m_refCount;

			if (!m_refCount) {
				delete this;
				return 0;
			}
			return m_refCount;
		}

		int GetRefCount() {
			return m_refCount;
		}
	protected:
		virtual ~CRefCount(){
		}

	private:
		int m_refCount;
	};
}
#endif
