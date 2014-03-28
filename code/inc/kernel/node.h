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

#ifndef __CNODE_H__
#define __CNODE_H__

namespace rengine3d {

	class CNode: public CRefCount {
	public:
		CNode(const string_t& name);
		CNode();
		~CNode();

		CNode* GetChild() const;
		CNode* GetParent() const;
		CNode* GetSibling() const;

		CNode* GetRoot() const;
		CNode* GetFirst() const;
		CNode* GetNext() const;
		CNode* GetLast() const;
		CNode* GetPrev() const;

		void Clear();

		void Detach();
		void Attach(CNode* parent, bool addFirst = false);

		void PrintHierarchy(int count = 0);

		string_t GetName() const { return m_name; };
		void SetName(const string_t& name) { m_name = name; m_id = MakeCRC(m_name.c_str()); };

		int GetId() { return m_id; };

	protected:
		string_t	m_name;
		CNode*		m_parent;
		CNode*		m_child;
		CNode*		m_sibling;
		int			m_id;
	};

	r_inline CNode::CNode(const string_t& name) {
		m_name		= name;
		m_id		= MakeCRC(m_name.c_str());
		m_parent	= NULL;
		m_child		= NULL;
		m_sibling	= NULL;
	}

	r_inline CNode::CNode() {

		m_name		= "";
		m_id		= MakeCRC(m_name.c_str());
		m_parent	= NULL;
		m_child		= NULL;
		m_sibling	= NULL;
	}

	r_inline CNode::~CNode(){
		CNode* ptr;
		CNode* tmp;

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

	r_inline CNode* CNode::GetChild() const {
		return m_child;
	}

	r_inline CNode* CNode::GetParent() const {
		return m_parent;
	}

	r_inline CNode* CNode::GetSibling() const {
		return m_sibling;
	}

	r_inline void CNode::Clear() {
		m_parent	= NULL;
		m_child		= NULL;
		m_sibling	= NULL;
	}

	r_inline void CNode::Detach() {
		if (m_parent) {
			if (m_parent->m_child == this) {
				m_parent->m_child = m_sibling;
			} else {
				CNode *ptr;
				for (ptr = m_parent->m_child; ptr->m_sibling != this; ptr = ptr->m_sibling)	{
				}
				ptr->m_sibling = m_sibling;
			}
			m_parent = NULL;
			m_sibling = NULL;
			Release();
		}
	}

	r_inline void CNode::Attach(CNode* parent, bool addFirst) {
		CNode* obj;

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

	r_inline CNode* CNode::GetRoot() const {
		const CNode* root;
		for (root = this; root->m_parent; root = root->m_parent){
		}
		return (CNode*)root;
	}

	r_inline CNode* CNode::GetFirst() const {
		CNode* ptr;
		for (ptr = (CNode*)this; ptr->m_child; ptr = ptr->m_child){
		}
		return ptr;
	}

	r_inline CNode* CNode::GetNext() const {
		CNode* x;
		CNode* ptr;

		if (m_sibling) {
			return m_sibling->GetFirst();
		}

		x = (CNode*)this;
		for (ptr = m_parent; ptr && (x == ptr->m_sibling); ptr = ptr->m_parent) {
			x = ptr;
		}
		return ptr;
	}

	r_inline CNode* CNode::GetLast() const {
		CNode* ptr;

		for (ptr = (CNode *)this; ptr->m_sibling; ptr = ptr->m_sibling) {
		}
		return ptr;
	}

	r_inline CNode* CNode::GetPrev() const {
		CNode*		x;
		CNode*		ptr;

		if (m_child) {
			return m_child->GetNext();
		}

		x = (CNode*)this;
		for (ptr = m_parent; ptr && (x == ptr->m_child); ptr = ptr->m_child) {
			x = ptr;
		}
		return ptr;
	}

	r_inline void CNode::PrintHierarchy(int count) {
		CNode*	node;
		
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

}

#endif
