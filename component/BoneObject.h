#pragma once
#include "../Base/BaseComponent.h"
#include "../Maths/Matrix.h"

class AnimationController;

class BoneObject : public BaseComponent
{
	DECLARE_CLASS_RTTI(BoneObject);

public:
	static std::shared_ptr<BoneObject> Create(std::weak_ptr<AnimationController> pRootBone);

protected:
	bool Init(const std::shared_ptr<BoneObject>& pSelf, std::weak_ptr<AnimationController> pRootBone);

public:
	void OnAnimationUpdate() override;
	void OnPreRender() override;

public:
	void SetRootBone(std::weak_ptr<AnimationController> pRootBone) { m_pRootBone = pRootBone; }
	std::weak_ptr<AnimationController> GetRootBone() const { return m_pRootBone; }

private:
	std::weak_ptr<AnimationController>	m_pRootBone;
};