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

#ifndef __IXML_H__
#define __IXML_H__

namespace rengine3d {

	enum XMLNodeType {
		XML_NODE_UNKNOWN,
		XML_NODE_DOCUMENT,
		XML_NODE_ELEMENT,
		XML_NODE_COMMENT,
		XML_NODE_TEXT,
		XML_NODE_TEXT_NO_CHECK,
		XML_NODE_DECLARATION
	};

	class IXMLAttrib {
	public:
		IXMLAttrib( const char* name, const char* value ){};
		IXMLAttrib( const char* name, int value ){};
		IXMLAttrib( const char* name, float value ){};

		virtual ~IXMLAttrib(){};

		virtual void SetString( const char *value ) = 0;
		virtual void SetInt( const int value ) = 0;
		virtual void SetFloat( const float value ) = 0;
		virtual void SetVec3( const CVec3& vec ) = 0;
		virtual void SetVec4( const CVec4& vec ) = 0;

		virtual const char* GetName( void ) = 0;
		virtual const char* GetString( void ) = 0;
		virtual int GetInt( void ) = 0;
		virtual float GetFloat( void ) = 0;
		virtual const CVec2& GetVec2( void ) = 0;
		virtual const CVec3& GetVec3( void ) = 0;
		virtual const CVec4& GetVec4( void ) = 0;
	};

	class IXMLNode {
	public:
		virtual ~IXMLNode(){};

		virtual void SetType( XMLNodeType type ) = 0;
		virtual void SetName( const char* name ) = 0;
		virtual void SetString( const char* value ) = 0;
		virtual void SetInt( const int value ) = 0;
		virtual void SetFloat( const float value ) = 0;

		virtual XMLNodeType GetType( void ) = 0;
		virtual const char* GetName( void ) = 0;
		virtual const char* GetString( void ) = 0;
		virtual int GetInt( void ) = 0;
		virtual float GetFloat( void ) = 0;
		virtual const CVec3& GetVec3( void ) = 0;
		virtual const CVec4& GetVec4( void ) = 0;

		virtual IXMLNode* GetNextSibling( void ) = 0;
		virtual void SetNextSibling( IXMLNode *nextSibling ) = 0;

		virtual IXMLNode* GetParent( void ) = 0;
		virtual void SetParent( IXMLNode *parent ) = 0;

		virtual int GetChildCount( void) = 0;

		virtual IXMLNode* GetChildElement( int index = 0 ) = 0;
		virtual IXMLNode* GetChildElement( const char* name ) = 0;

		virtual IXMLNode* AddChildElement( const char* childName) = 0;
		virtual IXMLNode* AddChildElementText( const char* childName, const char* textValue, bool textValueNoCheck = false ) = 0;
		virtual IXMLNode* AddChildElementInteger( const char* childName, int integerValue ) = 0;

		virtual int GetAttributeCount( void ) = 0;
		virtual IXMLAttrib* GetAttribute( int index ) = 0;
		virtual IXMLAttrib* GetAttribute( const char* name ) = 0;

		virtual void SetAttribute( const char* name, const char * _value ) = 0;
		virtual void SetAttribute( const char* name, int _value ) = 0;
		
		virtual bool FindAttribute( const char* name ) = 0;

		virtual void AddAttribute( IXMLAttrib* attribute ) = 0;
		virtual void AddChild( IXMLNode* child ) = 0;
	};

	class IXML {
	public:
		virtual ~IXML(){};

		virtual bool Load( const char* fileName ) = 0;
		virtual void Save( const char* fileName ) = 0;

		virtual void SetRoot( IXMLNode *root ) = 0;
		virtual void SetEncoding( const char* encoding ) = 0;
		virtual void SetVersion( const char* version ) = 0;
		virtual void SetStandalone( const char* standalone ) = 0;

		virtual IXMLNode* CreateNode( const char* name, XMLNodeType type, IXMLNode* parent ) = 0;

		virtual IXMLNode *GetRoot( void ) = 0;
		virtual const char* GetVersion( void ) = 0;
		virtual const char* GetEncoding( void ) = 0;
		virtual const char* GetStandalone( void ) = 0;
	};
}

#endif
