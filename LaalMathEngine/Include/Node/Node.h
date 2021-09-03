#ifndef LAAL_NODE_HPP
#define LAAL_NODE_HPP

#include <list>
#include <string>
#include <gmtl/gmtl.h>

#include "Utils/Constants.h"
#include "Utils/Config.h"

namespace laal
{
	//! ===================================================
	//! [Node]
	//! ===================================================
	
	class Node
	{

	protected:

		Node* m_Parent;

		std::list<Node*> m_ChildNodes;

	public:

		Node(Config* config = nullptr);

		virtual ~Node();

		virtual std::string NodeType() const;

		void Add(Node* node);

		void Remove(Node* node);

		virtual bool IsLeaf();

		bool Contains(Node* node) const;

		Node* DeepCopy();
	};
}

#endif // !LAAL_NODE_HPP
