#include "order_book.hpp"
#include <optional>
#include <print>

void OrderBook::add_order(const Order &order) {
  if (order.side == Side::Buy) {
    bids[order.price].orders.push_back(order);
    bids[order.price].total_quantity += order.quantity;
  } else {
    asks[order.price].orders.push_back(order);
    asks[order.price].total_quantity += order.quantity;
  }
}

std::optional<Price> OrderBook::best_bid() {
  if (bids.empty())
    return std::nullopt;

  auto [price, _] = *bids.begin();
  return price;
}

std::optional<Price> OrderBook::best_ask() {
  if (asks.empty())
    return std::nullopt;

  auto [price, _] = *asks.begin();
  return price;
}

void OrderBook::submit_order(Order order) {
  auto &opposing_levels = order.side == Side::Buy ? asks : bids;
  while (order.quantity > 0) {
    auto best_opt = order.side == Side::Buy ? best_ask() : best_bid();
    if (!best_opt) {
      break;
    }
    Price price = *best_opt;
    if (price > order.price) {
      break;
    }
    PriceLevel &level = opposing_levels[price];
    match_price_level(order, level);
    if (level.orders.empty()) {
      asks.erase(price);
    }
  }
  if (order.quantity > 0) {
    add_order(order);
  }
}

void OrderBook::match_price_level(Order &incoming, PriceLevel &level) {
  OrderQueue &order_queue = level.orders;
  while (incoming.quantity > 0 && !order_queue.empty()) {
    Order &resting = order_queue.front();
    if (resting.quantity > incoming.quantity) {
      resting.quantity -= incoming.quantity;
      level.total_quantity -= incoming.quantity;
      incoming.quantity = 0;
    } else {
      incoming.quantity -= resting.quantity;
      level.total_quantity -= resting.quantity;
      order_queue.pop_front();
    }
  }
}

void OrderBook::print_book() {
  std::println("ASKS");
  for (const auto &[price, level] : asks) {
    std::println("{} -> total: {}", price, level.total_quantity);
    for (const auto &order : level.orders) {
      std::println("\tid: {} qty: {}", order.id, order.quantity);
    }
  }

  std::println();
  std::println("BIDS");
  for (const auto &[price, level] : bids) {
    std::println("{} -> total: {}", price, level.total_quantity);
    for (const auto &order : level.orders) {
      std::println("\tid: {} qty: {}", order.id, order.quantity);
    }
  }
  std::println(
      "----------------------------------------------------------------------");
}
