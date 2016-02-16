#pragma once

namespace GameEngine {
namespace BoardObjects {

class ObjectBase
{
public:
	ObjectBase() {}
	virtual ~ObjectBase() {}

	virtual int GetHP() const = 0;

	virtual int GetAttack() const = 0;

	virtual void TakeDamage(int damage, bool poisonous) const = 0;
	virtual bool IsForgetful() const = 0;

	virtual void AttackedOnce() const = 0;

	virtual void SetFreezed(bool freezed) const = 0;
	virtual bool IsFreezeAttacker() const = 0;
	virtual bool IsFreezed() const = 0;

	virtual bool IsPoisonous() const = 0;

	/*
	virtual int GetCardId() = 0;
	virtual int GetMaxHP() = 0;
	*/
};

} // namespace Board
} // namespace GameEngine
