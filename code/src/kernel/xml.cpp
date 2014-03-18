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

#pragma hdrstop
#include "kernel/precompiled.h"

#include "tinyxml/tinyxml.h"
#include "xml.h"

namespace rengine3d {

#define TAB_SIZE                    "  "
#define BUFFER_BLOCK_SIZE           1024*256

	enum TiNodeType {
		TI_NODE_ELEMENT = 1,
		TI_NODE_COMMENT = 2,
		TI_NODE_TEXT	= 4
	};

	CXMLAttribute::CXMLAttribute( const char* name, const char* value ):IXMLAttrib(name,value) {
		m_name = name;
		m_value = value;
	}

	CXMLAttribute::CXMLAttribute( const char* name, int value ):IXMLAttrib(name,value) {
		static char szValue[ 128 ];
		_itoa( value, szValue, 10 );

		m_name = name;
		m_value = szValue;
	}

	CXMLAttribute::CXMLAttribute( const char* name, float value ):IXMLAttrib(name,value) {
		static char szValue[ 128 ];
		sprintf( szValue, "%f", value ); 

		m_name = name;
		m_value = szValue;
	}

	CXMLAttribute::~CXMLAttribute() {
	}

	void CXMLAttribute::SetString( const char *value ) {
		m_value = value;
	}

	void CXMLAttribute::SetInt( const int value ) {
		static char szValue[ 128 ];
		_itoa( value, szValue, 10 );

		m_value = szValue;
	}

	void CXMLAttribute::SetFloat( const float value ) {
		static char szValue[ 128 ];
		sprintf( szValue, "%f", value); 

		m_value = szValue;
	}

	void CXMLAttribute::SetVec3( const CVec3& vec ) {
		static char szValue[ 128 ];
		sprintf( szValue, "%f %f %f", vec.x, vec.y, vec.z); 
		m_value = szValue;
	}

	void CXMLAttribute::SetVec4( const CVec4& vec ) {
		static char szValue[ 128 ];
		sprintf( szValue, "%f %f %f %f", vec.x, vec.y, vec.z, vec.w); 
		m_value = szValue;
	}

	const char* CXMLAttribute::GetName( void ) {
		return m_name.c_str();
	}

	const char* CXMLAttribute::GetString( void ) {
		return m_value.c_str();
	}

	int CXMLAttribute::GetInt( void ) {
		return atoi( m_value.c_str() );
	}

	float CXMLAttribute::GetFloat( void ) {
		return (float) atof( m_value.c_str() );
	}

	const CVec2& CXMLAttribute::GetVec2( void ) {
		static CVec2 vec;
		sscanf( m_value.c_str(),"%f %f", &vec.x, &vec.y );
		return vec;
	}

	const CVec3& CXMLAttribute::GetVec3( void ) {
		static CVec3 vec;
		sscanf( m_value.c_str(),"%f %f %f", &vec.x, &vec.y, &vec.z );
		return vec;
	}

	const CVec4& CXMLAttribute::GetVec4( void ) {
		static CVec4 vec;
		sscanf( m_value.c_str(),"%f %f %f %f", &vec.x, &vec.y, &vec.z, &vec.w );
		return vec;
	}

	CXMLNode::CXMLNode() {
		m_type			= XML_NODE_UNKNOWN;
		m_parent		= NULL;
		m_nextSibling	= NULL;
	}

	CXMLNode::CXMLNode( XMLNodeType type ): m_parent(NULL), m_nextSibling(NULL), m_type(type) {
	}

	CXMLNode::CXMLNode( XMLNodeType type, const char* name ): m_parent(NULL), m_nextSibling(NULL), m_type(type),m_name(name)  {
	}

	CXMLNode::CXMLNode( XMLNodeType type, const char* name, IXMLNode* parent ): m_parent(parent), m_nextSibling(NULL), m_type(type),m_name(name) {
	}

	CXMLNode::~CXMLNode() {
		size_t i;

		for ( i = 0; i < m_attributes.size(); i++ )
			SafeDelete(m_attributes[i]);

		for ( i = 0; i < m_childs.size(); i++ )
			SafeDelete(m_childs[i]);

		m_attributes.clear();
		m_childs.clear();
	}

	void CXMLNode::SetType( XMLNodeType type ) {
		m_type = type;
	}

	void CXMLNode::SetName( const char* name ) {
		m_name = name;
	}

	void CXMLNode::SetString( const char* value ) {
		m_value = value;
	}

	void CXMLNode::SetInt( const int value ) {
		static char szValue[ 128 ];
		_itoa( value, szValue, 10 );

		m_value = szValue;
	}

	void CXMLNode::SetFloat( const float value ) {
		static char szValue[ 128 ];
		sprintf( szValue, "%f", value); 

		m_value = szValue;
	}

	XMLNodeType CXMLNode::GetType( void ) {
		return m_type;
	}

	const char* CXMLNode::GetName( void ) {
		return m_name.c_str();
	}

	const char* CXMLNode::GetString( void ) {
		return m_value.c_str();
	}

	int CXMLNode::GetInt( void ) {
		return atoi( m_value.c_str() );
	}

	float CXMLNode::GetFloat( void ) {
		return (float) atof( m_value.c_str() );
	}

	const CVec3& CXMLNode::GetVec3( void ) {
		static CVec3 vec;
		sscanf( m_value.c_str(),"%f %f %f", &vec.x, &vec.y, &vec.z  );
		return vec;

	}

	const CVec4& CXMLNode::GetVec4( void ) {
		static CVec4 vec;
		sscanf( m_value.c_str(),"%f %f %f %f", &vec.x, &vec.y, &vec.z, &vec.w );
		return vec;
	}

	IXMLNode* CXMLNode::GetNextSibling( void ) {
		return m_nextSibling;
	}

	void CXMLNode::SetNextSibling( IXMLNode *nextSibling ) {
		m_nextSibling = nextSibling;
	}

	IXMLNode* CXMLNode::GetParent( void ) {
		return m_parent;
	}

	void CXMLNode::SetParent( IXMLNode *parent ) {
		m_parent = parent;
	}

	int CXMLNode::GetChildCount( void) {
		return (int)m_childs.size();
	}

	IXMLNode* CXMLNode::GetChildElement( int index ) {
		if ( m_childs.size() <= 0 )
			return NULL;

		return m_childs[index];
	}
	
	IXMLNode* CXMLNode::GetChildElement( const char* name ) {
		size_t i;

		for ( i = 0; i < m_childs.size(); i++ )
			if ( strcmp(m_childs[i]->GetName(), name ) == 0 )
				return m_childs[i];

		for ( i = 0; i < m_childs.size(); i++ ) {
			IXMLNode *node = m_childs[i]->GetChildElement( name );
			if ( node )
				return node;
		}

		return NULL;
	}

	IXMLNode* CXMLNode::AddChildElement( const char* childName) {
		IXMLNode *node = new CXMLNode( XML_NODE_ELEMENT, childName );

		AddChild( node );

		return node;
	}

	IXMLNode* CXMLNode::AddChildElementText( const char* childName, const char* textValue, bool textValueNoCheck ) {
		IXMLNode *node		= new CXMLNode( XML_NODE_ELEMENT, childName);
		IXMLNode *nodeChild = new CXMLNode();

		if ( !textValueNoCheck )
			nodeChild->SetType( XML_NODE_TEXT );
		else
			nodeChild->SetType( XML_NODE_TEXT_NO_CHECK );

		nodeChild->SetString( textValue );

		node->AddChild( nodeChild );
		AddChild( node );

		return node;
	}

	IXMLNode* CXMLNode::AddChildElementInteger( const char* childName, int integerValue ) {
		string_t textValue;

		textValue = integerValue;
		//	textValue.format( "%d", integerValue );

		IXMLNode *node		= new CXMLNode( XML_NODE_ELEMENT, childName );
		IXMLNode *nodeChild = new CXMLNode( XML_NODE_TEXT, textValue.c_str() );

		node->AddChild( nodeChild );
		AddChild( node );

		return node;
	}

	int CXMLNode::GetAttributeCount( void ) {
		return (int)m_attributes.size();
	}

	IXMLAttrib* CXMLNode::GetAttribute( int index ) {
		return m_attributes[index];
	}

	IXMLAttrib* CXMLNode::GetAttribute( const char* name ) {
		for ( size_t i = 0; i < m_attributes.size(); i++ )
			if ( strcmp(m_attributes[i]->GetName(), name ) == 0 )
				return m_attributes[i];

		IXMLAttrib *attribute = new CXMLAttribute( name, "");

		m_attributes.push_back( attribute );

		return attribute;
	}

	void CXMLNode::SetAttribute( const char* name, const char * _value ) {
		for ( size_t i = 0; i < m_attributes.size(); i++ )
			if ( strcmp(m_attributes[i]->GetName(), name ) == 0 ) {
				m_attributes[i]->SetString(_value);
				return;
			}

		IXMLAttrib *attribute = new CXMLAttribute( name, _value );

		m_attributes.push_back( attribute );

	}

	bool CXMLNode::FindAttribute( const char* name ) {
		for ( size_t i = 0; i < m_attributes.size(); i++ )
			if ( strcmp(m_attributes[i]->GetName(), name ) == 0 ) {
				return true;
			}
		return false;
	}

	void CXMLNode::SetAttribute( const char* name, int _value ) {
		for ( size_t i = 0; i < m_attributes.size(); i++ )
			if ( strcmp(m_attributes[i]->GetName(), name ) == 0 ) {
				m_attributes[i]->SetInt(_value);
				return;
			}

		IXMLAttrib *attribute = new CXMLAttribute( name, _value );

		m_attributes.push_back( attribute );
	}


	void CXMLNode::AddAttribute( IXMLAttrib *attribute ) {
		m_attributes.push_back( attribute );
	}

	void CXMLNode::AddChild( IXMLNode *child ) {
		m_childs.push_back( child );
	}

	// *** xml *** //
	CXML::CXML(IFileSystem* fs ): m_fileSystem(fs) {
		m_version		= "1.0";
		m_root			= NULL;
		m_encoding		= "utf-8";

		m_buffer		= NULL;
		m_size			= 0;
		m_bufferedSize	= 0;
		m_blockCount	= 0;
	}

	CXML::~CXML() {
		SafeDelete( m_root );
		SafeArrayDelete( m_buffer );
	}

	bool CXML::Load( const char* fileName ) {
		char*			buffer;
		TiXmlDocument	*tiXmlDocument;

		IFile* file = m_fileSystem->OpenFile( fileName, fileMode_Read );
		if ( !file ) {
			Warning( "Failed load xml \"%s\".\n", fileName );
			return false;
		}

		buffer = new char [file->Length()];
		file->Read( buffer, file->Length() );
		m_fileSystem->CloseFile( file );

		tiXmlDocument = new TiXmlDocument();
		tiXmlDocument->Parse( buffer );

		TiXmlDeclaration *tiXmlDeclaration = (TiXmlDeclaration *) tiXmlDocument->RootElement()->Parent()->FirstChild();

		SetVersion( tiXmlDeclaration->Version() );
		SetEncoding( tiXmlDeclaration->Encoding() );
		SetStandalone( tiXmlDeclaration->Standalone() );

		IXMLNode *root = ParseNode( (void *) tiXmlDocument->RootElement() );
		SetRoot( root );

		SafeArrayDelete( buffer );
		SafeDelete( tiXmlDocument );

		return true;
	}

	void CXML::Save( const char* fileName ) {
		if ( m_buffer ) {
			delete [] m_buffer;

			m_buffer		= 0;
			m_size			= 0;
			m_bufferedSize	= 0;
			m_blockCount	= 0;
		}

		IXMLNode *node = GetRoot();

		WriteHeader();
		WriteNode( node, 0 );

		FILE* file = fopen( fileName, "wb" );
		if ( !file )
			return;

		fwrite( m_buffer, m_size, 1, file );
		fclose( file );
	}

	void CXML::SetRoot( IXMLNode *root ) {
		m_root = root;
	}

	void CXML::SetEncoding( const char* encoding ) {
		m_encoding = encoding;
	}

	void CXML::SetVersion( const char* version ) {
		m_version = version;
	}

	void CXML::SetStandalone( const char* standalone ) {
		m_standalone = standalone;
	}

	IXMLNode* CXML::GetRoot( void ) {
		return m_root;
	}

	const char* CXML::GetVersion( void ) {
		return m_version.c_str();
	}

	const char* CXML::GetEncoding( void ) {
		return m_encoding.c_str();
	}

	const char* CXML::GetStandalone( void ) {
		return m_standalone.c_str();
	}

	IXMLNode* CXML::CreateNode( const char* name, XMLNodeType type, IXMLNode* parent ) {

		return new CXMLNode(type, name, parent);
	}


	IXMLNode* CXML::ParseNode( void *node ) {
		TiXmlNode *tiNode = (TiXmlNode *) node;

		if ( !tiNode ) 	{
			return 0;
		}

		IXMLNode *xmlNode = new CXMLNode();

		switch ( tiNode->Type() ) {
		case TI_NODE_ELEMENT: 
			{
				TiXmlElement *tiElement = tiNode->ToElement();
				xmlNode->SetName( tiElement->Value() );
				xmlNode->SetType( XML_NODE_ELEMENT );

				TiXmlAttribute *tiAttribute = tiElement->FirstAttribute();
				while ( tiAttribute ) {
					string_t value = tiAttribute->Value();
					IXMLAttrib *attribute = new CXMLAttribute( tiAttribute->Name(), value.c_str() );
					xmlNode->AddAttribute( attribute );

					tiAttribute = tiAttribute->Next();
				}
			} break;

		case TI_NODE_COMMENT: 
			{
				TiXmlComment *tiComment = tiNode->ToComment();
				xmlNode->SetType( XML_NODE_COMMENT );
				xmlNode->SetName( "xml.comment" );
				xmlNode->SetString( tiComment->Value() );

			} break;

		case TI_NODE_TEXT: 
			{
				TiXmlText *tiText = tiNode->ToText();
				xmlNode->SetType( XML_NODE_TEXT );
				xmlNode->SetName( "xml.text" );
				string_t s;
				s = tiText->Value();
				xmlNode->SetString( s.c_str() );
			} break;

		default:
			break;
		}

		TiXmlNode *tiXmlNode = tiNode->FirstChild();

		IXMLNode *child = 0;
		IXMLNode *childPrevious = 0;

		while ( tiXmlNode ) {
			child = ParseNode( (void *) tiXmlNode );

			if ( child ) {
				child->SetParent( xmlNode );

				if ( childPrevious ) {
					childPrevious->SetNextSibling( child );
				}

				xmlNode->AddChild( child );
			}

			childPrevious = child;
			tiXmlNode = tiXmlNode->NextSibling();
		}

		return xmlNode;
	}

	void CXML::AppendString( string_t &sAppend, bool isElementText  ) {
		string_t	s;

		if ( !isElementText ) {
			s = sAppend;
		} else {
			for ( int i = 0; i < (int) sAppend.length(); i++ ) {
				switch ( sAppend[i] ) {
				case '&':
					s += "&amp;";
					break;

				case '<':
					s += "&lt;";
					break;

				case '>':
					s += "&gt;";
					break;

				case '"':
					s += "&quot;";
					break;

				case '\'':
					s += "&apos;";
					break;

				default:
					s += (char*) sAppend[i];
					break;
				}
			}
		}

		size_t stringSize = s.length();

		if ( !m_buffer ) {
			m_bufferedSize = BUFFER_BLOCK_SIZE;
			m_blockCount = 1;
			m_buffer = new char[ m_bufferedSize ];
			memcpy( m_buffer, ( const char* )s.c_str(), stringSize );
			m_size = (int)stringSize;

			return;
		}

		if ( ( m_size + (int)stringSize ) < ( m_blockCount * BUFFER_BLOCK_SIZE ) ) {
			memcpy( &m_buffer[ m_size ], ( const char* )s.c_str(), stringSize );
			m_size += (int)stringSize;
		} else {
			m_blockCount++;

			char *buffer = new char[ m_blockCount * BUFFER_BLOCK_SIZE ];
			memcpy( buffer, m_buffer, m_size );
			memcpy( &buffer[ m_size ], ( const char* )s.c_str(), stringSize );

			delete [] m_buffer;
			m_buffer = buffer;

			m_size += (int)stringSize;
		}
	}

	void CXML::WriteHeader( void ) {
		string_t s;
		s += "<?xml";

		if ( this->GetVersion() != "" ) {
			s += " version=\"";
			s += GetVersion();
			s += "\"";
		}

		if ( this->GetEncoding() != "" ) {
			s += " encoding=\"";
			s += GetEncoding();
			s += "\"";
		}
/*
		if ( this->GetStandalone() != "" ) {
			s += " standalone=\"";
			s += GetStandalone();
			s += "\"";
		}
		*/
		s += "?>";
		AppendString(s);
	}

	void CXML::WriteNode( IXMLNode *node, int tab ) {
		if ( !node )
			return;

		int			i;
		string_t	s;

		switch ( node->GetType() ) {
		case XML_NODE_ELEMENT:
			s += "\n";
			for ( i = 0; i < tab; ++i )
				s += TAB_SIZE;

			s += "<";
			s += node->GetName();

			for ( i = 0; i < node->GetAttributeCount(); ++i ) {
				s += " ";
				s += node->GetAttribute( i )->GetName();
				s += "=\"";
				s += node->GetAttribute( i )->GetString();
				s += "\"";
			}

			if ( node->GetChildCount() == 0 ) {
				s += "/>";
			} else {
				s += ">";
			}

			AppendString( s );
			break;

		case XML_NODE_TEXT:
			s += node->GetString();

			AppendString( s, true );
			break;

		case XML_NODE_TEXT_NO_CHECK:
			s += node->GetString();

			AppendString( s );
			break;

		case XML_NODE_COMMENT:
			s += "\n";        
			for ( i = 0; i < tab; ++i ) {
				s += TAB_SIZE;
			}

			s += "<-- ";
			s += node->GetString();
			s += " -->";

			AppendString( s );
			break;
		}

		for ( i = 0; i < node->GetChildCount(); i++ )
			WriteNode( node->GetChildElement( i ), tab + 1 );

		if ( ( node->GetType() == XML_NODE_ELEMENT ) && ( node->GetChildCount() > 0 ) ) {
			s = "";        
			if ( ( node->GetChildElement() ) && ( node->GetChildElement()->GetType() != XML_NODE_TEXT ) ) {
				s += "\n";
				for ( i = 0; i < tab; ++i )	{
					s += TAB_SIZE;
				}
			}

			s += "</";
			s += node->GetName();
			s += ">";
			AppendString( s );
		}
	}
}