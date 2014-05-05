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

#ifndef __INODE_H__
#define __INODE_H__

namespace rengine3d {

#define SerialiseBase(baseClass, rootNode)							\
	IXMLNode* baseClassNode =  rootNode->AddChildElement(#baseClass); \
	baseClass::Serialize(baseClassNode);							  \

#define DeserialiseBase(baseClass, rootNode)												\
	IXMLNode* baseClassNode = rootNode->GetChildElement(baseClass::GetClassName().c_str());	\
	baseClass::Deserialize (baseClassNode);

	class INode: public IRefCount {
	public:
		INode(const string_t& name);
		INode();
		virtual ~INode();

		INode* GetChild() const;
		INode* GetParent() const;
		INode* GetSibling() const;

		INode* GetRoot() const;
		INode* GetFirst() const;
		INode* GetNext() const;
		INode* GetLast() const;
		INode* GetPrev() const;

		virtual void Clear();

		virtual void Detach();
		virtual void Attach(INode* parent, bool addFirst = false);

		virtual void PrintHierarchy(int count = 0);

		string_t GetName() const			{ return m_name; };
		void SetName(const string_t& name)	{ m_name = name; m_id = MakeCRC(m_name.c_str()); };

		int GetId() { return m_id; };

		virtual void Serialize(IXMLNode* rootNode) const; 
		virtual bool Deserialize(IXMLNode* rootNode);

	protected:
		string_t	m_name;
		string_t	m_parentName; // for serialization
		INode*		m_parent;
		INode*		m_child;
		INode*		m_sibling;
		int			m_id;
	};

	r_inline INode::INode(const string_t& name) {
		m_name		= name;
		m_id		= MakeCRC(m_name.c_str());
		m_parent	= NULL;
		m_child		= NULL;
		m_sibling	= NULL;
	}

	r_inline INode::INode() {

		m_name		= "";
		m_id		= MakeCRC(m_name.c_str());
		m_parent	= NULL;
		m_child		= NULL;
		m_sibling	= NULL;
	}

	r_inline INode::~INode(){
		INode* ptr;
		INode* tmp;

		if (m_child) {
			for (ptr = m_child; ptr && ptr->Release(); ptr = tmp) {
				tmp = ptr->m_sibling;
				ptr->m_parent = NULL;
				ptr->m_sibling = NULL;
			}
		}

		for (ptr = m_sibling; ptr && ptr->Release(); ptr = tmp) {
			tmp = ptr->m_sibling;
			ptr->m_parent = NULL;
			ptr->m_sibling = NULL;
		}
	}

	r_inline INode* INode::GetChild() const {
		return m_child;
	}

	r_inline INode* INode::GetParent() const {
		return m_parent;
	}

	r_inline INode* INode::GetSibling() const {
		return m_sibling;
	}

	r_inline void INode::Clear() {
		m_parent	= NULL;
		m_child		= NULL;
		m_sibling	= NULL;
	}

	r_inline void INode::Detach() {
		if (m_parent) {
			if (m_parent->m_child == this) {
				m_parent->m_child = m_sibling;
			} else {
				INode *ptr;
				for (ptr = m_parent->m_child; ptr->m_sibling != this; ptr = ptr->m_sibling)	{
				}
				ptr->m_sibling = m_sibling;
			}
			m_parent = NULL;
			m_sibling = NULL;
			Release();
		}
	}

	r_inline void INode::Attach(INode* parent, bool addFirst) {
		INode* obj;

		m_parent = parent;
		if (m_parent->m_child) {
			if (addFirst) {
				m_sibling = m_parent->m_child;
				m_parent->m_child = this;
			} else {
				for (obj = m_parent->m_child; obj->m_sibling; obj = obj->m_sibling)
				{

				}
				obj->m_sibling = this;
			}
		} else {
			parent->m_child = this;
		}

		//AddRef();
	}

	r_inline INode* INode::GetRoot() const {
		const INode* root;
		for (root = this; root->m_parent; root = root->m_parent){
		}
		return (INode*)root;
	}

	r_inline INode* INode::GetFirst() const {
		INode* ptr;
		for (ptr = (INode*)this; ptr->m_child; ptr = ptr->m_child){
		}
		return ptr;
	}

	r_inline INode* INode::GetNext() const {
		INode* x;
		INode* ptr;

		if (m_sibling) {
			return m_sibling->GetFirst();
		}

		x = (INode*)this;
		for (ptr = m_parent; ptr && (x == ptr->m_sibling); ptr = ptr->m_parent) {
			x = ptr;
		}
		return ptr;
	}

	r_inline INode* INode::GetLast() const {
		INode* ptr;

		for (ptr = (INode *)this; ptr->m_sibling; ptr = ptr->m_sibling) {
		}
		return ptr;
	}

	r_inline INode* INode::GetPrev() const {
		INode*		x;
		INode*		ptr;

		if (m_child) {
			return m_child->GetNext();
		}

		x = (INode*)this;
		for (ptr = m_parent; ptr && (x == ptr->m_child); ptr = ptr->m_child) {
			x = ptr;
		}
		return ptr;
	}

	r_inline void INode::PrintHierarchy(int count) {
		INode*	node;

		if (m_child) {
			Log("%s   id = %d\n", m_name.c_str(), m_id);
		}else {
			Log("\t%s id = %d\n", m_name.c_str(), m_id);
		}

		count++;
		for (node = m_child; node; node = node->m_sibling) {
			node->PrintHierarchy(count);
		} 
	}

	r_inline void INode::Serialize(IXMLNode* rootNode) const {
		rootNode->SetAttribute("name", m_name.c_str());
		if (m_parent) {
			rootNode->SetAttribute("parent", m_parent->GetName().c_str());
		}
	}

	r_inline bool INode::Deserialize(IXMLNode* rootNode) {
		SetName(rootNode->GetAttribute("name")->GetString());
		if (rootNode->FindAttribute("parent")) {
			m_parentName = rootNode->GetAttribute("parent")->GetString();
		}

		return true;
	}

}

#endif
