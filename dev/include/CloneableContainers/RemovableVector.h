#pragma once

#include <type_traits>
#include <utility>
#include "CloneableContainers/Vector.h"

// Use a boolean flag to mark if an item has been removed or not

namespace CloneableContainers
{
	template <typename ItemType>
	class RemovableVector
	{
	private:
		struct InternalItemType
		{
			InternalItemType(InternalItemType const& rhs) = default;
			InternalItemType(InternalItemType && rhs) = default;
			explicit InternalItemType(ItemType && item) : removed(false), item(std::move(item)) {}

			bool removed;
			ItemType item;
		};

	public:
		class Identifier
		{
			friend class RemovableVector<ItemType>;
			friend class RemovableVector::IdentifierHasher;

			typedef typename CloneableContainers::Vector<InternalItemType>::Identifier impl_identifier_type;

		public:
			Identifier(const Identifier & rhs) = default;
			Identifier(Identifier && rhs) = default;

			bool operator==(const Identifier& rhs) const { return identifier_ == rhs.identifier_; }
			bool operator!=(const Identifier& rhs) const { return identifier_ != rhs.identifier_; }

		private:
			Identifier(const impl_identifier_type & identifier) : identifier_(identifier) {}
			Identifier(impl_identifier_type && identifier) : identifier_(std::move(identifier)) {}

			impl_identifier_type identifier_;
		};

		class IdentifierHasher
		{
		public:
			size_t operator()(const Identifier & id) const { return std::hash()(id.identifier_); }
		};

	public:
		RemovableVector() {}
		RemovableVector(size_t default_capacity) : items_(default_capacity) {}

		template <typename T>
		Identifier PushBack(T&& item) {
			return items_.PushBack(InternalItemType(std::forward<T>(item)));
		}

		template <typename T>
		const ItemType * Get(T&& identifier) const {
			static_assert(std::is_same<std::decay_t<T>, Identifier>::value, "Wrong type");

			auto & item = items_.Get(identifier.identifier_);
			if (item.removed) return nullptr;
			else return &item.item;
		}

		template <typename T>
		ItemType * Get(T&& identifier) {
			static_assert(std::is_same<std::decay_t<T>, Identifier>::value, "Wrong type");

			auto & item = items_.Get(identifier.identifier_);
			if (item.removed) return nullptr;
			else return &item.item;
		}

		template <typename T>
		void Remove(T&& identifier) {
			static_assert(std::is_same<std::decay_t<T>, Identifier>::value, "Wrong type");

			items_.Get(identifier.identifier_).removed = true;
		}

	public: // iterate
		Identifier GetBegin() { return Identifier(items_.GetBegin()); }
		void StepNext(Identifier & id) { items_.StepNext(id.identifier_); }
		Identifier GetEnd() { return Identifier(items_.GetEnd()); }

	private:
		CloneableContainers::Vector<InternalItemType> items_;
	};
}