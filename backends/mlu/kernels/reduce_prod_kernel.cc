// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
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

#include "kernels/funcs/reduce_op.h"

namespace custom_kernel {

template <typename T, typename Context>
void ProdRawKernel(const Context& dev_ctx,
                   const phi::DenseTensor& x,
                   const phi::IntArray& axes,
                   bool keep_dim,
                   bool reduce_all,
                   phi::DenseTensor* out) {
  MLUReduceOp<T>(
      dev_ctx, x, axes.GetData(), keep_dim, reduce_all, "reduce_prod", out);
}

template <typename T, typename Context>
void ProdKernel(const Context& dev_ctx,
                const phi::DenseTensor& x,
                const phi::IntArray& dims,
                bool keep_dim,
                phi::DenseTensor* out) {
  bool reduce_all = false;
  custom_kernel::ProdRawKernel<T>(dev_ctx, x, dims, keep_dim, reduce_all, out);
}

}  // namespace custom_kernel

PD_REGISTER_PLUGIN_KERNEL(prod_raw,
                          CustomMLU,
                          ALL_LAYOUT,
                          custom_kernel::ProdRawKernel,
                          int,
                          phi::dtype::float16,
                          float) {}

PD_REGISTER_PLUGIN_KERNEL(prod,
                          CustomMLU,
                          ALL_LAYOUT,
                          custom_kernel::ProdKernel,
                          int,
                          phi::dtype::float16,
                          float) {}
