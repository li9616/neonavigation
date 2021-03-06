/*
 * Copyright (c) 2018, the neonavigation authors
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the copyright holder nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ROTATION_CACHE_H
#define ROTATION_CACHE_H

#include <cyclic_vec.h>

template <int DIM, int NONCYCLIC>
class RotationCache
{
protected:
  std::unique_ptr<CyclicVecFloat<DIM, NONCYCLIC>[]> c_;
  CyclicVecInt<DIM, NONCYCLIC> size_;
  int ser_size_;

public:
  void reset(const CyclicVecInt<DIM, NONCYCLIC> &size)
  {
    size_t ser_size = 1;
    for (int i = 0; i < 3; i++)
    {
      ser_size *= size[i];
    }
    size_ = size;
    ser_size_ = ser_size;

    c_.reset(new CyclicVecFloat<DIM, NONCYCLIC>[ser_size]);
  }
  explicit RotationCache(const CyclicVecInt<DIM, NONCYCLIC> &size)
  {
    reset(size);
  }
  RotationCache()
  {
  }
  CyclicVecFloat<DIM, NONCYCLIC> &operator[](const CyclicVecInt<DIM, NONCYCLIC> &pos)
  {
    size_t addr = pos[2];
    for (int i = 1; i >= 0; i--)
    {
      addr *= size_[i];
      addr += pos[i];
    }
    return c_[addr];
  }
};

#endif  // ROTATION_CACHE_H
