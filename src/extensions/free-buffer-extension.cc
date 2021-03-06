// Copyright 2013 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "free-buffer-extension.h"
#include "platform.h"
#include "v8.h"

namespace v8 {
namespace internal {


v8::Handle<v8::FunctionTemplate> FreeBufferExtension::GetNativeFunctionTemplate(
    v8::Isolate* isolate,
    v8::Handle<v8::String> str) {
  return v8::FunctionTemplate::New(isolate, FreeBufferExtension::FreeBuffer);
}


void FreeBufferExtension::FreeBuffer(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Handle<v8::ArrayBuffer> arrayBuffer = args[0].As<v8::ArrayBuffer>();
  v8::ArrayBuffer::Contents contents = arrayBuffer->Externalize();
  V8::ArrayBufferAllocator()->Free(contents.Data(), contents.ByteLength());
}


void FreeBufferExtension::Register() {
  static char buffer[100];
  Vector<char> temp_vector(buffer, sizeof(buffer));
  OS::SNPrintF(temp_vector, "native function freeBuffer();");

  static FreeBufferExtension buffer_free_extension(buffer);
  static v8::DeclareExtension declaration(&buffer_free_extension);
}

} }  // namespace v8::internal
