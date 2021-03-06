#pragma once

#include "state/Types.h"

namespace state
{
	namespace Cards
	{
		class EnchantableStates
		{
		public:
			EnchantableStates() :
				player(), cost(-1), attack(-1), max_hp(-1), charge(false), stealth(false), max_attacks_per_turn(1),
				immune_to_spell(false), poisonous(false), freeze_attack(false), cant_attack_hero(false), immune(false),
				spell_damage(0)
			{
				static_assert(kFieldChangeId == 17, "field changed");
			}

			bool operator==(EnchantableStates const& rhs) const
			{
				static_assert(kFieldChangeId == 17, "field changed");
				if (player != rhs.player) return false;
				if (cost != rhs.cost) return false;
				if (attack != rhs.attack) return false;
				if (max_hp != rhs.max_hp) return false;
				if (charge != rhs.charge) return false;
				if (stealth != rhs.stealth) return false;
				if (max_attacks_per_turn != rhs.max_attacks_per_turn) return false;
				if (immune_to_spell != rhs.immune_to_spell) return false;
				if (poisonous != rhs.poisonous) return false;
				if (freeze_attack != rhs.freeze_attack) return false;
				if (cant_attack_hero != rhs.cant_attack_hero) return false;
				if (immune != rhs.immune) return false;
				if (spell_damage != rhs.spell_damage) return false;
				return true;
			}

			bool operator!=(EnchantableStates const& rhs) const { return !(*this == rhs); }

			void RestoreToSilenceDefault() {
				static_assert(kFieldChangeId == 17, "field changed");
				// only preserve cost/attack/hp
				charge = false;
				stealth = false;
				max_attacks_per_turn = 1;
				immune_to_spell = false;
				poisonous = false;
				freeze_attack = false;
				cant_attack_hero = false;
				immune = false;
				spell_damage = 0;
			}

		public:
			static constexpr int kFieldChangeId = 17; // Change this if any field is changed. This helps to see where you should also modify

			PlayerIdentifier player;
			int cost;
			int attack;
			int max_hp;
			bool charge;
			bool stealth;
			int max_attacks_per_turn;
			bool immune_to_spell;
			bool poisonous;
			bool freeze_attack;
			bool cant_attack_hero;
			bool immune;

			int spell_damage;
		};
	}
}