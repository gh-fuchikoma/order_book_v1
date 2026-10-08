#include "order_book.hpp"

int main() {
  OrderBook book;
  book.submit_order({Side::Buy, 100, 5, 1});
  book.print_book();

  book.submit_order({Side::Buy, 100, 3, 2});
  book.print_book();

  book.submit_order({Side::Sell, 101, 2, 3});
  book.print_book();

  book.submit_order({Side::Sell, 100, 4, 4});
  book.print_book();

  return 0;
}
