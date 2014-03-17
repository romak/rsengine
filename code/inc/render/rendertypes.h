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

#ifndef __RENDER_TYPES_H__
#define __RENDER_TYPES_H__

namespace rengine3d {

	// Renderer types
	typedef enum {
		renderCaps_VertexBufferObject,
		renderCaps_TwoSideStencil,

		renderCaps_MaxTextureImageUnits,
		renderCaps_MaxTextureCoordUnits,

		renderCaps_AnisotropicFiltering,
		renderCaps_MaxAnisotropicFiltering,

		renderCaps_Multisampling,

		renderCaps_GL_VertexProgram,
		renderCaps_GL_FragmentProgram,

		renderCaps_Count
	} renderCaps_t;

	typedef struct {
		uint	width;
		uint	height;
		uint	bpp;
		bool	fullScreen;
		uint	multiSampling;
	} renderDriverParam_t;

	typedef enum {
		renderAPI_Directx9,
		renderAPI_Directx10,
		renderAPI_Directx11,
		renderAPI_OpenGL,
		renderAPI_Null,
		renderAPI_Count
	} renderAPI_t;

	typedef enum  {
		cullMode_Clockwise,
		cullMode_CounterClockwise,
		cullMode_Count
	} cullMode_t;

	typedef enum {
		blendFunc_Zero,
		blendFunc_One,
		blendFunc_SrcColor,
		blendFunc_OneMinusSrcColor,
		blendFunc_DestColor,
		blendFunc_OneMinusDestColor,
		blendFunc_SrcAlpha,
		blendFunc_OneMinusSrcAlpha,
		blendFunc_DestAlpha,
		blendFunc_OneMinusDestAlpha,
		blendFunc_SrcAlphaSaturate,
		blendFunc_Count
	} blendFunc_t;

	// Texture types
	typedef enum  {
		textureFormat_RGB8, 
		textureFormat_BGR8,
		textureFormat_RGBX8,
		textureFormat_BGRX8,
		textureFormat_RGBA8,
		textureFormat_BGRA8,
		textureFormat_DXT1,
		textureFormat_DXT3,
		textureFormat_DXT5,
		textureFormat_RGBA16F,
		textureFormat_RGBA32F,
		textureFormat_Count
	} textureFormat_t;	

	//! Возможные типы текстур
	typedef enum {
		textureType_Normal,
		textureType_RenderTarget
	} textureType_t;

	//! Фильтрация текстур
	typedef enum {
		textureFilter_None,
		textureFilter_Nearest,					//! Point filtering
		textureFilter_Bilinear,					//! Bilinear filtering
		textureFilter_Trilinear,				//! Trilinear filtering
		textureFilter_Anisotropic				//! Anisotropic filtering
	} textureFilter_t;

	typedef enum {
		textureTarget_1D,
		textureTarget_2D,
		textureTarget_3D,
		textureTarget_Rect,
		textureTarget_CubeMap,
		textureTarget_Count
	} textureTarget_t;

	typedef enum {
		textureWrap_Repeat,
		textureWrap_Clamp,
		textureWrap_ClampToEdge,
		textureWrap_ClampToBorder,
		textureWrap_Count
	} textureWrap_t;

	typedef enum {
		textureAnimationMode_None,
		textureAnimationMode_Loop
	} textureAnimationMode_t;

	//! Тип используемого фильтра в текстуре
	typedef enum {
		filterType_Min	= (1<<0),				//! Minimize filter
		filterType_Mag  = (1<<1),				//! Magnification filter
		filterType_Mip	= (1<<2)				//! Mip-mapping filter
	} filterType_t;

	//! Адресация в текстурке
	typedef enum {
		texture_Addressing_Unknown,
		texture_Addressing_Clamp,
		texture_Addressing_Wrap,
		texture_Addressing_Border,
		texture_Addressing_Mirror
	} texture_Addressing_t;

	typedef enum {
		textureParam_ColorFunc,
		textureParam_AlphaFunc,
		textureParam_ColorSource0,
		textureParam_ColorSource1,
		textureParam_ColorSource2,
		textureParam_AlphaSource0,
		textureParam_AlphaSource1,
		textureParam_AlphaSource2,
		textureParam_ColorOp0,
		textureParam_ColorOp1,
		textureParam_ColorOp2,
		textureParam_AlphaOp0,
		textureParam_AlphaOp1,
		textureParam_AlphaOp2,
		textureParam_ColorScale,
		textureParam_AlphaScale,
		textureParam_Count
	}textureParam_t;

	typedef enum {
		textureOp_Color,
		textureOp_OneMinusColor,
		textureOp_Alpha,
		textureOp_OneMinusAlpha,
		textureOp_Count
	} textureOp_t;

	typedef enum {
		textureSource_Texture,
		textureSource_Constant,
		textureSource_Primary,
		textureSource_Previous,
		textureSource_Count
	} textureSource_t;

	typedef enum {
		textureFunc_Modulate,
		textureFunc_Replace,
		textureFunc_Add,
		textureFunc_Substract,
		textureFunc_AddSigned,
		textureFunc_Interpolate, 
		textureFunc_Dot3RGB,
		textureFunc_Dot3RGBA,
		textureFunc_Count
	} textureFunc_t;

	// Vertex buffer types
	typedef enum {
		vbDrawType_Triangle,
		vbDrawType_Quad,
		vbDrawType_Line,
		vbDrawType_Point,
		vbDrawType_Default
	} vbDrawType_t;

	typedef enum {
		vbUsageType_Static,
		vbUsageType_Dynamic,
		vbUsageType_Stream,
		vbUsageType_Default
	} vbUsageType_t;

#define vbFlag_Normal	BIT(0)
#define vbFlag_Position BIT(1)
#define vbFlag_Color	BIT(2)
#define vbFlag_Texture0	BIT(3)
#define vbFlag_Texture1	BIT(4)
#define vbFlag_Texture2	BIT(5)
#define vbFlag_Texture3	BIT(6)
#define vbFlag_Texture4	BIT(7)

#define vbNumVertexFlags (8)

	const unsigned int vertexFlags[] = { vbFlag_Normal, vbFlag_Position, vbFlag_Color, vbFlag_Texture0, vbFlag_Texture1, vbFlag_Texture2, vbFlag_Texture3, vbFlag_Texture4 };

	const int vertexElements[] =   {3, //Normal
		3, //Position
		4, //Color
		3, //Texture0
		3, //Texture1
		3, //Texture2
		3, //Texture3
		3  //Texture4
	};

	// Matrix routines
	typedef enum  {
		matrixType_ModelView	= 0,
		matrixType_Projection	= 1,
		matrixType_Texture		= 2,
		matrixType_Count		= 3
	} matrixMode_t;

	typedef enum {
		depthTestFunc_Never,
		depthTestFunc_Less,
		depthTestFunc_LessOrEqual,
		depthTestFunc_Greater,
		depthTestFunc_GreaterOrEqual, 
		depthTestFunc_Equal, 
		depthTestFunc_NotEqual, 
		depthTestFunc_Always, 
		depthTestFunc_Count
	} depthTestFunc_t;

	typedef enum {
		alphaTestFunc_Never,
		alphaTestFunc_Less,
		alphaTestFunc_LessOrEqual,
		alphaTestFunc_Greater,
		alphaTestFunc_GreaterOrEqual, 
		alphaTestFunc_Equal, 
		alphaTestFunc_NotEqual, 
		alphaTestFunc_Always, 
		alphaTestFunc_Count
	} alphaTestFunc_t;

	// Stencils types
	typedef enum  {
		stencilFunc_Never,
		stencilFunc_Less,
		stencilFunc_LessOrEqual,
		stencilFunc_Greater,
		stencilFunc_GreaterOrEqual, 
		stencilFunc_Equal, 
		stencilFunc_NotEqual, 
		stencilFunc_Always,
		stencilFunc_Count
	} stencilFunc_t;

	typedef enum  {
		stencilOp_Keep, 
		stencilOp_Zero, 
		stencilOp_Replace, 
		stencilOp_Increment, 
		stencilOp_Decrement, 
		stencilOp_Invert,
		stencilOp_IncrementWrap,
		stencilOp_DecrementWrap,
		stencilOp_Count
	} stencilOp_t;

	typedef enum {
		stencilFace_Front,
		stencilFace_Back,
		stencilFace_Count,
	} stencilFace_t;

	typedef enum {
		indicesType_uint,
		indicesType_ushort,
	} indicesType_t;

	// Constants
	const int MAX_TEXTURE_UNITS	= 8;
	const int MAX_NUM_OF_LIGHTS = 30;
	const int MAX_CLIP_PLANES	= 6;

}

#endif
