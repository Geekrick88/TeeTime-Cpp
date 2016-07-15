/**
 * Copyright (C) 2016 Johannes Ohlemacher (https://github.com/eXistence/TeeTime-Cpp)
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
#include "stages/AbstractStage.h"

namespace teetime
{
  template<typename TIn, typename TOut, TOut(*TFunc)(TIn)>
  class FunctionStage;

  template<typename TIn, typename TOut>
  class FunctionPtrStage;

  template<typename TIn, typename TOut>
  class FunctionObjectStage;

  class Configuration
  {
  public:
    Configuration();
    ~Configuration();

    void executeBlocking();

  protected:
    template<typename T, typename ...TArgs>
    shared_ptr<T> createStage(TArgs... args)
    {
      auto stage = std::make_shared<T>(args...);
      m_stages.push_back(stage);
      return stage;
    }

    template<typename TIn, typename TOut, TOut(*TFunc)(TIn)>
    shared_ptr<FunctionStage<TIn, TOut, TFunc>> createStageFromFunction(const char* name = "function")
    {
      return createStage<FunctionStage<TIn, TOut, TFunc>>(name);
    }

    template<typename TIn, typename TOut>
    shared_ptr<FunctionPtrStage<TIn, TOut>> createStageFromFunctionPointer(TOut(*f)(TIn), const char* name = "function_pointer")
    {
      return createStage<FunctionPtrStage<TIn, TOut>>(f, name);
    }

    template<typename TIn, typename TOut>
    shared_ptr<FunctionObjectStage<TIn, TOut>> createStageFromFunctionObject(std::function<TOut(TIn)> f, const char* name = "function_object")
    {
      return createStage<FunctionObjectStage<TIn, TOut>>(f, name);
    }

  private:    
    std::vector<shared_ptr<AbstractStage>> m_stages;
  };
}