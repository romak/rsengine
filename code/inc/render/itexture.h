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

#ifndef __ITEXTURE_H__
#define __ITEXTURE_H__

namespace rengine3d {

	class ITexture: public IResource {
	public:
		ITexture(const string_t& name);
		virtual ~ITexture();

		uint GetWidth(void)						{return m_width;};
		uint GetHeight(void)					{return m_height;};
		uint GetDepth(void)						{return m_depth;};
		uint GetBpp(void)						{return m_bpp;};
		textureType_t GetTextureType(void)		{return m_textureType;};
		textureTarget_t GetTarget(void)			{return m_target;};
		textureWrap_t GetWrapS(void)			{return m_wrapS;};
		textureWrap_t GetWrapT(void)			{return m_wrapT;};
		textureWrap_t GetWrapR(void)			{return m_wrapR;};
		textureFilter_t GetFilter(void)			{return m_filter;};
		real GetAnisotropyDegree(void)			{return m_anisotropyDegree;};
		bool IsUseMipMaps(void)					{return m_useMipMaps;};
		bool IsUseCompress(void)				{return m_useCompress;};

		void SetWidth(uint width)				{m_width = width;};
		void SetHeight(uint height)				{m_height = height;};
		void SetDepth(uint depth)				{m_depth = depth;};
		void SetBpp(uint bpp)					{m_bpp = bpp;};
		void SetTextureType(textureType_t type)	{m_textureType = type;};
		void SetTarget(textureTarget_t target)	{m_target = target;};
		void SetWrapS(textureWrap_t wrap)		{m_wrapS = wrap;};
		void SetWrapT(textureWrap_t wrap)		{m_wrapT = wrap;};
		void SetWrapR(textureWrap_t wrap)		{m_wrapR = wrap;};
		void SetFilter(textureFilter_t filter)	{m_filter = filter;};
		void SetAnisotropyDegree(real value)	{m_anisotropyDegree = value;};
		void SetUseMipMaps(bool value)			{m_useMipMaps = value;};
		void SetUseCompress(bool value)			{m_useCompress = value;};
	protected:
		int			m_width;
		int			m_height;
		int			m_depth;
		int			m_bpp;

		textureType_t	m_textureType;
		textureTarget_t	m_target;
		textureWrap_t	m_wrapS;
		textureWrap_t	m_wrapT;
		textureWrap_t	m_wrapR;
		textureFilter_t	m_filter;
		real			m_anisotropyDegree;
		bool			m_useMipMaps;
		bool			m_useCompress;
	};

	r_inline ITexture::ITexture(const string_t& name):m_height(0),m_width(0),m_depth(0),m_bpp(0),m_textureType(textureType_Normal),m_target(textureTarget_2D),m_wrapS(textureWrap_Repeat),
		m_wrapT(textureWrap_Repeat),m_wrapR(textureWrap_Repeat),m_filter(textureFilter_Trilinear),m_anisotropyDegree(1.0f),m_useMipMaps(false),m_useCompress(false),IResource(name, resourceType_t ::Texture)
	{
			
	}

	r_inline ITexture::~ITexture() {
	}

}

#endif
