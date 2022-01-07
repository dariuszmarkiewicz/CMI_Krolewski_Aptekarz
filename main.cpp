#include <iostream>
#include <algorithm>
#include <limits>

typedef int64_t i64;
constexpr auto g_maxValue = std::numeric_limits<i64>::max();

// Sk³adnik leku.
struct Item
{
	i64 m_req;   // Wymagana iloœæ uncji dla jednej dawki.
	i64 m_stock; // Iloœæ uncji danego sk³adnika w magazynie.
	i64 m_dose;  // Iloœæ dawek, na ile pozwala na to sk³adnik.

	i64 GetExcessDose(); // Zwraca nadmiar sk³adnika.
	void CalculateDose(); // Oblicza iloœæ dawek.
};

int main()
{
	i64 n, p; // n - liczba sk³adników, p - iloœæ panaceum.
	std::cin >> n >> p;

	// Alokacja tablicy ze sk³adnikami.
	Item *const items = new Item[n + 1];
	Item *const lastItem = items + n;

	*lastItem = { 1, g_maxValue, g_maxValue };

	// Pobieranie danych wejœciowych.
	for (Item *item = items; item != lastItem; item++)
		std::cin >> item -> m_req;

	for (Item *item = items; item != lastItem; item++)
	{
		std::cin >> item -> m_stock;
		item -> CalculateDose();
	}

	// Sortowanie sk³adników.
	std::sort(items, lastItem, [](const Item& a, const Item& b) -> bool { return a.m_dose < b.m_dose; });

	i64 cost = 0;
	i64 result = items[0].m_dose;

	// U¿ywanie panaceum.
	for (Item* item = items; item != lastItem; item++)
	{
		p += item -> GetExcessDose();
		cost += item -> m_req;

		const i64 rise = (item + 1) -> m_dose - item -> m_dose;
		if (rise == 0) continue;

		const i64 pAfter = p - cost * rise;
		if (pAfter < 0)
		{
			result += p / cost;
			break;
		}
		else
		{
			p = pAfter;
			result += rise;
		}
	}

	// Wypisanie wyniku.
	std::cout << result;

	// Sprz¹tanie (dealokacja pamiêci).
	delete[] items;

	return 0;
}

inline i64 Item::GetExcessDose()
{
	return m_stock % m_req;
}

inline void Item::CalculateDose()
{
	m_dose = m_stock / m_req;
}
