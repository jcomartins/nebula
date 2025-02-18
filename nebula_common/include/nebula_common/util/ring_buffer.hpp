// Copyright 2025 TIER IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace nebula::util
{

template <typename T>
class RingBuffer
{
public:
  explicit RingBuffer(std::size_t capacity) { buffer_.reserve(capacity); }

  void push_back(const T & value)
  {
    if (is_full()) {
      sum_ -= buffer_[index_];
      buffer_[index_] = value;
    } else {
      buffer_.push_back(value);
    }

    sum_ += value;
    index_ = (index_ + 1) % buffer_.capacity();
  }

  std::size_t size() const { return buffer_.size(); }

  bool is_full() const { return buffer_.size() == buffer_.capacity(); }

  T get_average() const { return sum_ / buffer_.size(); }

private:
  T sum_{};
  std::vector<T> buffer_;
  std::size_t index_{0};
};

}  // namespace nebula::util
