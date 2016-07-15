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
#include <teetime/stages/AbstractConsumerStage.h>
#include <string>

namespace teetime
{
  class File;

  class Directory2Files final : public AbstractConsumerStage<std::string>
  {
  public:
    explicit Directory2Files(const char* debugName = "Directory2Files");
    OutputPort<File>& getOutputPort();

  private:
    static void collectFilesName(const std::string& directoy, std::vector<std::string>& filenames, bool recursive);

    virtual void execute(const std::string& value) override;

    OutputPort<File>* m_outputPort;
  };
}