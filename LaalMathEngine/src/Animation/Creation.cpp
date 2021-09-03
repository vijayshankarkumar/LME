#include "Animation/Creation.h"

namespace laal
{
	Create::Create(Shape* root, double runtime, double lagtime) :
		Animation(root, runtime, lagtime)
	{

	}

	Create::~Create()
	{

	}

	void Create::Begin()
	{
		Animation::Begin();
		SetMap(m_pRootShape);
		m_pRootShape->FillStyleType(STYLE_NONE);
		m_pRootShape->StrokeOpacity(0.0);
	}

	void Create::SetMap(Shape* root)
	{
		m_FillTypesMap[root] = root->FillStyleType();
		m_OpacitiesMap[root] = root->StrokeOpacity();
		for (Path* path : root->Paths())
		{
			m_ClosedMap[root].push_back(path->IsClosed());
			path->BecomePartial();
		}

		if (root->IsLeaf())
		{
			return;
		}
		for (Shape* shape : root->ChildShapes())
		{
			SetMap(shape);
		}
	}

	void Create::Update(Shape* root, unsigned int frameCount)
	{
		if (root->IsLeaf())
		{
			root->StrokeOpacity(m_OpacitiesMap[root]);
			double alpha = GetAlpha(frameCount);
			for (Path* path : root->Paths())
			{
				path->AlphaValue(0.0, alpha);
				//std::cout << "alpha => " << alpha << std::endl;
			}
		}

		for (Shape* shape : root->ChildShapes())
		{
			Update(shape, frameCount);
		}
	}
}