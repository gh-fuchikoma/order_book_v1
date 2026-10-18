#pragma once

#include <list>
#include <map>
#include <optional>

using Price = int;
using Quantity = int;
using Id = int;

enum class Side {
  Buy,
  Sell,
};

struct Order {
  Price price;
  Quantity quantity;
  Id id;
  Side side;
};

using OrderQueue = std::list<Order>;

struct PriceLevel {
  OrderQueue orders;
  Quantity total_quantity{0};
};

using OrderBookSide = std::map<Price, PriceLevel>;

class OrderBook {
private:
  OrderBookSide asks;
  OrderBookSide bids;

public:
  void add_order(const Order &order);
  std::optional<Price> best_bid();
  std::optional<Price> best_ask();
  void submit_order(Order order);
  void match_price_level(Order &incoming, PriceLevel &level);
  void print_book();
};
