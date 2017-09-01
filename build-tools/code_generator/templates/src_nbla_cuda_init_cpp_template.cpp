// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
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

// *WARNING*
// THIS FILE IS AUTO-GENERATED BY CODE GENERATOR.
// PLEASE DO NOT EDIT THIS FILE BY HAND!
// If you want to modify this file, edit following files.
// - build-tools/code_generator/templates/src_nbla_cuda_init_cpp_template.cpp
// - build-tools/code_generator/generator/generate_src_nbla_cuda_init_cpp.py

#include <nbla/init.hpp>
#include <nbla/cuda/init.hpp>
#include <nbla/cuda/cuda.hpp>
#include <nbla/cuda/common.hpp>
#include <nbla/array_registry.hpp>
#include <nbla/function_registry.hpp>
#include <nbla/array/cpu_array.hpp>
#include <nbla/cuda/array/cuda_array.hpp>
{include_functions}
#include <nbla/cuda/solver/adadelta.hpp>
#include <nbla/cuda/solver/adagrad.hpp>
#include <nbla/cuda/solver/adam.hpp>
#include <nbla/cuda/solver/adamax.hpp>
#include <nbla/cuda/solver/momentum.hpp>
#include <nbla/cuda/solver/nesterov.hpp>
#include <nbla/cuda/solver/rmsprop.hpp>
#include <nbla/cuda/solver/sgd.hpp>

#ifdef FEATURE_DIST_TRAIN
  #include <nbla/cuda/communicator/data_parallel_communicator.hpp>
  #include <nbla/cuda/communicator/multi_process_data_parallel_communicator.hpp>
#endif

#include <nbla/garbage_collector.hpp>

namespace nbla {{

void init_cuda() {{
  static bool is_initialized = false;
  if (is_initialized)
    return;

  // Init CPU features
  init_cpu();

  // Array registration
  NBLA_REGISTER_ARRAY_CREATOR(CudaArray);
  SingletonManager::get<Cuda>()->register_array_class("CudaArray");
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CpuArray, CudaArray,
                                   synchronizer_cpu_array_cuda_array);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CudaArray, CpuArray,
                                   synchronizer_cuda_array_cpu_array);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CpuCachedArray, CudaArray,
                                   synchronizer_cpu_array_cuda_array);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CudaArray, CpuCachedArray,
                                   synchronizer_cuda_array_cpu_array);
  NBLA_REGISTER_ARRAY_CREATOR(CudaCachedArray);
  SingletonManager::get<Cuda>()->register_array_class("CudaCachedArray");
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CpuArray, CudaCachedArray,
                                   synchronizer_cpu_array_cuda_array);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CudaCachedArray, CpuArray,
                                   synchronizer_cuda_array_cpu_array);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CpuCachedArray, CudaCachedArray,
                                   synchronizer_cpu_array_cuda_array);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CudaCachedArray, CpuCachedArray,
                                   synchronizer_cuda_array_cpu_array);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CudaCachedArray, CudaArray,
                                   synchronizer_default);
  NBLA_REGISTER_ARRAY_SYNCHRONIZER(CudaArray, CudaCachedArray,
                                   synchronizer_default);

  // Function registration
{register_functions}

  // Solver registration
  typedef AdadeltaCuda<float> AdadeltaCudaf;
  NBLA_REGISTER_SOLVER_IMPL(Adadelta, AdadeltaCudaf, 1, "cuda", "default", float, float,
    float);
  typedef AdagradCuda<float> AdagradCudaf;
  NBLA_REGISTER_SOLVER_IMPL(Adagrad, AdagradCudaf, 1, "cuda", "default", float, float);
  typedef AdamCuda<float> AdamCudaf;
  NBLA_REGISTER_SOLVER_IMPL(Adam, AdamCudaf, 1, "cuda", "default", float, float,
    float, float);
  typedef AdamaxCuda<float> AdamaxCudaf;
  NBLA_REGISTER_SOLVER_IMPL(Adamax, AdamaxCudaf, 1, "cuda", "default", float, float,
    float, float);
  typedef MomentumCuda<float> MomentumCudaf;
  NBLA_REGISTER_SOLVER_IMPL(Momentum, MomentumCudaf, 1, "cuda", "default", float, float);
  typedef NesterovCuda<float> NesterovCudaf;
  NBLA_REGISTER_SOLVER_IMPL(Nesterov, NesterovCudaf, 1, "cuda", "default", float, float);
  typedef RMSpropCuda<float> RMSpropCudaf;
  NBLA_REGISTER_SOLVER_IMPL(RMSprop, RMSpropCudaf, 1, "cuda", "default", float, float,
    float);
  typedef SgdCuda<float> SgdCudaf;
  NBLA_REGISTER_SOLVER_IMPL(Sgd, SgdCudaf, 1, "cuda", "default", float);

  // Communicator registration
#ifdef FEATURE_DIST_TRAIN
  typedef DataParallelCommunicatorNccl<float> DataParallelCommunicatorNcclf;
  NBLA_REGISTER_COMMUNICATOR_IMPL(DataParallelCommunicator, DataParallelCommunicatorNcclf, 1, "cuda", "default");
  typedef MultiProcessDataParallelCommunicatorNccl<float> MultiProcessDataParallelCommunicatorNcclf;
  NBLA_REGISTER_COMMUNICATOR_IMPL(MultiProcessDataParallelCommunicator, MultiProcessDataParallelCommunicatorNcclf, 1, "cuda", "default");
#endif

  // Register finalize function to ensure freeing all CUDA memory before unloading CUDA driver.
  auto finalize = []()->void {{
    SingletonManager::get<GarbageCollector>()->collect();
    SingletonManager::clear();
    }};
  NBLA_CHECK(std::atexit(finalize) == 0, error_code::unclassified, "atexit registration error");
  is_initialized = true;
}}

void clear_cuda_memory_cache() {{
  SingletonManager::get<Cuda>()->memcache().clear();
}}

/** Get CUDA array classes.
*/
vector<string> cuda_array_classes() {{
  return SingletonManager::get<Cuda>()->array_classes();
}}

/** Set CUDA array classes
*/
void _cuda_set_array_classes(const vector<string> &a) {{
  return SingletonManager::get<Cuda>()->_set_array_classes(a);
}}

void cuda_device_synchronize(int device) {{
  cuda_set_device(device);
  NBLA_CUDA_CHECK(cudaDeviceSynchronize());
}}

int cuda_get_device_count() {{
  int count;
  NBLA_CUDA_CHECK(cudaGetDeviceCount(&count));
  return count;
}}

}}

