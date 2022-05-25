//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// clock_replacer.cpp
//
// Identification: src/buffer/clock_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/clock_replacer.h"

namespace bustub {

ClockReplacer::ClockReplacer(size_t num_pages) {
  this->placeholders = std::vector<std::pair<bool, bool>>(num_pages, std::make_pair<bool, bool>(false, false));
  this->clock_hand = 0;
}

ClockReplacer::~ClockReplacer() = default;

bool ClockReplacer::Victim(frame_id_t *frame_id) {
  size_t cnt = this->placeholders.capacity() + 1;
  while (cnt) {
    if (this->placeholders[this->clock_hand].first ) {
      if (!this->placeholders[this->clock_hand].second) {
        this->placeholders[this->clock_hand].first = false;
        this->placeholders[this->clock_hand].second = false;
        *frame_id = this->clock_hand;
        return true;
      }
      this->placeholders[this->clock_hand].second = false;
    }
    this->clock_hand = (this->clock_hand + 1) % this->placeholders.capacity();
    cnt --;
  }
  return false; 
}

void ClockReplacer::Pin(frame_id_t frame_id) {
  this->placeholders[frame_id].first = false;
  this->placeholders[frame_id].second = false;
}

void ClockReplacer::Unpin(frame_id_t frame_id) {
  this->placeholders[frame_id].first = true;
  this->placeholders[frame_id].second = true;
}

size_t ClockReplacer::Size() { 
  size_t cnt = 0;

  for (size_t i = 0; i < this->placeholders.capacity(); i++)
  {
    if (this->placeholders[i].first) cnt++;
  }
  
  return cnt; 
}

}  // namespace bustub
