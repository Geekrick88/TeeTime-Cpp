/**
 * Copyright (C) 2016 Johannes Ohlemacher (https://github.com/teetime-framework/TeeTime-Cpp)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <atomic>

namespace teetime
{
  struct Signal;

  class AbstractPipe
  {
  public:
    AbstractPipe()
    : m_closed(false)
    {
    }

    virtual ~AbstractPipe() = default;

    virtual void addSignal(const Signal& s) = 0;
    virtual void waitForStartSignal() = 0;

    bool isClosed() const
    {
      return m_closed.load(std::memory_order_relaxed);
    }

    void close()
    {
      m_closed = true;
    }

  private:
    //make sure closed flag is stored on it's own cacheline.
    char padding0[64];
    std::atomic<bool> m_closed;
    char padding1[64];
  };
}