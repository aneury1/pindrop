// Copyright 2015 Google Inc. All rights reserved.
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

#include "file_loader.h"

namespace pindrop {

void FileLoader::StartLoading() { loader.StartLoading(); }

bool FileLoader::TryFinalize() { return loader.TryFinalize(); }

void FileLoader::QueueJob(Resource* resource) { loader.QueueJob(resource); }

void Resource::LoadFile(const char* filename, FileLoader* loader) {
  set_filename(filename);
  loader->QueueJob(this);
}

}  // namespace pindrop
