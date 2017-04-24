#pragma once

#include <functional>
#include <vector>
#include <string>
#include "Utils/FuncPtrArray.h"
#include "state/Cards/EnchantableStates.h"
#include "state/Cards/Callbacks.h"
#include "FlowControl/onplay/Handler.h"
#include "FlowControl/deathrattle/Handler.h"
#include "FlowControl/enchantment/Handler.h"

namespace state
{
	namespace Cards
	{
		class CardData
		{
		public:
			CardData() :
				card_id(-1), card_type(kCardTypeInvalid), card_race(kCardRaceInvalid), card_rarity(kCardRarityInvalid), overload(0),
				zone(kCardZoneInvalid), zone_position(-1),
				play_order(-1), damaged(0), just_played(false), num_attacks_this_turn(0),
				pending_destroy(false), used_this_turn(0), usable(true), armor(0),
				taunt(false), shielded(false), cant_attack(false), freezed(false),
				silenced(false)
			{
			}

			static constexpr int kFieldChangeId = 2;

			int card_id; // TODO: use Cards::CardId
			CardType card_type;
			CardRace card_race;
			CardRarity card_rarity;
			int overload; // 0: no overload; 1: overload 1 crystal; etc.

			CardZone zone;
			int zone_position; // only meaningful for minions in play zone, and for hand cards

			int play_order;
			int damaged;
			bool just_played;
			int num_attacks_this_turn;
			EnchantableStates enchanted_states;

			bool pending_destroy;

			int used_this_turn; // for hero power
			bool usable; // for hero power

			int armor; // for hero

		public: // for minions
			bool taunt;
			bool shielded;
			bool cant_attack;
			bool freezed;

			bool silenced;

		public: // zone-changed callbacks invoked by state::State 
			Utils::FuncPtrArray<AddedToPlayZoneCallback*, 1> added_to_play_zone;
			Utils::FuncPtrArray<AddedToHandZoneCallback*, 1> added_to_hand_zone;

		public:
			FlowControl::enchantment::Handler enchantment_handler;
			FlowControl::onplay::Handler onplay_handler;
			FlowControl::deathrattle::Handler deathrattle_handler;
		};
	}
}