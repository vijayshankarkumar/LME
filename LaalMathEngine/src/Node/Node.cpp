#include "Node/Node.h"

namespace laal
{
	Node::Node(Config* config)
	{
		m_Parent = nullptr;
		m_ChildNodes = std::list<Node*>();
	}

	Node::~Node()
	{

	}

	std::string Node::NodeType() const
	{
		return "Node";
	}

	void Node::Add(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		m_ChildNodes.push_back(node);
		node->m_Parent = this;
	}

	void Node::Remove(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		auto it = std::find(m_ChildNodes.begin(), m_ChildNodes.end(), node);
		if (it == m_ChildNodes.end())
		{
			return;
		}
		m_ChildNodes.erase(it);
		node->m_Parent = nullptr;
	}

	bool Node::IsLeaf()
	{
		return m_ChildNodes.empty();
	}

	bool Node::Contains(Node* node) const
	{
		return node != nullptr && std::find(m_ChildNodes.begin(), m_ChildNodes.end(), node) != m_ChildNodes.end();
	}

	Node* Node::DeepCopy()
	{
		return this;
	}
}