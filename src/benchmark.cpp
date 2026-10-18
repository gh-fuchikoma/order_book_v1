#include "order_book.hpp"
#include <benchmark/benchmark.h>

static void BM_ExactCrossingPair(benchmark::State &state) {
  OrderBook book;
  Id id = 1;
  for (auto _ : state) {
    book.submit_order({1, 100, id++, Side::Buy});
    book.submit_order({1, 100, id++, Side::Sell});
  }
  state.SetItemsProcessed(state.iterations() * 2);
}

BENCHMARK(BM_ExactCrossingPair);

static void BM_SparseHighPricePair(benchmark::State &state) {
  OrderBook book;
  Id id = 1;
  book.submit_order({130, 100, id++, Side::Sell});
  for (auto _ : state) {
    book.submit_order({130, 100, id++, Side::Buy});
    book.submit_order({130, 100, id++, Side::Sell});
  }
  state.SetItemsProcessed(state.iterations() * 2);
}

BENCHMARK(BM_SparseHighPricePair);

static void BM_SparseVeryHighPricePair(benchmark::State &state) {
  OrderBook book;
  Id id = 1;
  book.submit_order({65'536, 100, id++, Side::Sell});
  for (auto _ : state) {
    book.submit_order({65'536, 100, id++, Side::Buy});
    book.submit_order({65'536, 100, id++, Side::Sell});
  }
  state.SetItemsProcessed(state.iterations() * 2);
}

BENCHMARK(BM_SparseVeryHighPricePair);
