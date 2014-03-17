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

#ifndef __CBOUNDBOX_H__
#define __CBOUNDBOX_H__

namespace rengine3d {

	class IRenderDriver;

	class CBoundBox {
	public:
		CBoundBox();
		CBoundBox(const CVec3& _min, const CVec3& _max);
		~CBoundBox(){};

		CVec3 GetCenter() const;
		real GetRadius() const;
		real GetSize() const;

		void Draw(IRenderDriver* renderDriver);
	public:
		CVec3 m_min;
		CVec3 m_max;
	};

	r_inline CBoundBox::CBoundBox() {
	}

	r_inline CBoundBox::CBoundBox(const CVec3& _min, const CVec3& _max): m_min(_min), m_max(_max) {
	}

	r_inline CVec3 CBoundBox::GetCenter() const {
		return (m_min + m_max) * 0.5f;
	}

	r_inline real CBoundBox::GetRadius() const {
		return GetSize() * 0.5f;
	}

	r_inline real CBoundBox::GetSize() const {
	    return (m_max - m_min).Len();
	}

	r_inline void CBoundBox::Draw(IRenderDriver* renderDriver) {
	}

}

#endif