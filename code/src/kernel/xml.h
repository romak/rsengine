/*
* Copyright (C) 2009-2010 - Roman Kalynchuk
*
* This file is part of REngine.
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
* along with REngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __CXML_H__
#define __CXML_H__

//#include "tinyxml/tinyxml.h"

namespace rengine3d {



	// tiny xml reader
	class CXMLAttribute: public IXMLAttrib {
	public:
		CXMLAttribute( const char* name, const char* value );
		CXMLAttribute( const char* name, int value );
		CXMLAttribute( const char* name, float value );

		virtual ~CXMLAttribute();

		virtual void SetString( const char *value );
		virtual void SetInt( const int value );
		virtual void SetFloat( const float value );
		virtual void SetVec3( const CVec3& vec );
		virtual void SetVec4( const CVec4& vec );

		virtual const char* GetName( void );
		virtual const char* GetString( void );
		virtual int GetInt( void );
		virtual float GetFloat( void );
		virtual const CVec2& GetVec2( void );
		virtual const CVec3& GetVec3( void );
		virtual const CVec4& GetVec4( void );
	protected:
		string_t m_name;
		string_t m_value;
	};

	class CXMLNode: public IXMLNode {
	public:
		CXMLNode();
		CXMLNode( XMLNodeType type );
		CXMLNode( XMLNodeType type, const char* name );
		CXMLNode( XMLNodeType type, const char* name, IXMLNode* parent );

		virtual ~CXMLNode();

		virtual void SetType( XMLNodeType type );
		virtual void SetName( const char* name );
		virtual void SetString( const char* value );
		virtual void SetInt( const int value );
		virtual void SetFloat( const float value );

		virtual XMLNodeType GetType( void );
		virtual const char* GetName( void );
		virtual const char* GetString( void );
		virtual int GetInt( void );
		virtual float GetFloat( void );
		virtual const CVec3& GetVec3( void );
		virtual const CVec4& GetVec4( void );

		virtual IXMLNode* GetNextSibling( void );
		virtual void SetNextSibling( IXMLNode *nextSibling );

		virtual IXMLNode* GetParent( void );
		virtual void SetParent( IXMLNode *parent );

		virtual int GetChildCount( void);

		virtual IXMLNode* GetChildElement( int index = 0 );
		virtual IXMLNode* GetChildElement( const char* name );

		virtual IXMLNode* AddChildElement( const char* childName);
		virtual IXMLNode* AddChildElementText( const char* childName, const char* textValue, bool textValueNoCheck = false );
		virtual IXMLNode* AddChildElementInteger( const char* childName, int integerValue );

		virtual int GetAttributeCount( void );
		virtual IXMLAttrib* GetAttribute( int index );
		virtual IXMLAttrib* GetAttribute( const char* name );

		virtual void SetAttribute( const char* name, const char * _value );
		virtual void SetAttribute( const char* name, int _value );

		virtual bool FindAttribute( const char* name );

		virtual void AddAttribute( IXMLAttrib* attribute );
		virtual void AddChild( IXMLNode* child );
	protected:
		XMLNodeType		m_type;
		string_t		m_name;
		string_t		m_value;

		std::vector< IXMLAttrib* >	m_attributes;
		std::vector< IXMLNode* >	m_childs;

		IXMLNode*		m_parent;
		IXMLNode*		m_nextSibling;
	};

	class CXML: public IXML {
	public:
		CXML( IFileSystem* fs );
		virtual ~CXML();

		virtual bool Load( const char* fileName );
		virtual void Save( const char* fileName );

		virtual void SetRoot( IXMLNode *root );
		virtual void SetEncoding( const char* encoding );
		virtual void SetVersion( const char* version );
		virtual void SetStandalone( const char* standalone );

		virtual IXMLNode* CreateNode( const char* name, XMLNodeType type, IXMLNode* parent );

		virtual IXMLNode *GetRoot( void );
		virtual const char* GetVersion( void );
		virtual const char* GetEncoding( void );
		virtual const char* GetStandalone( void );
	private:
		IXMLNode* ParseNode( void *node );

		void AppendString( string_t &sAppend, bool isElementText = false );
		void WriteHeader( void );
		void WriteNode( IXMLNode *node, int tab );
	protected:
		IFileSystem*	m_fileSystem;
		IXMLNode*		m_root;

		string_t		m_encoding;
		string_t		m_version;
		string_t		m_standalone;

		char*			m_buffer;
		int				m_size;

		int				m_bufferedSize;
		int				m_blockCount;
	};

}
#endif
