/*
 * ReactOS ATL
 *
 * Copyright 2009 Andrew Hill <ash77@reactos.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

//#include "atldef.h"
//#include "atlcore.h"
#include "atlcomcli.h"
#include "atlalloc.h"
#include "atlexcept.h"

namespace ATL
{

class CComAllocator
{
public:
    static void* Allocate(_In_ size_t size)
    {
        return ::CoTaskMemAlloc(size);
    }

    static void* Reallocate(_In_opt_ void* ptr, _In_ size_t size)
    {
        return ::CoTaskMemRealloc(ptr, size);
    }

    static void Free(_In_opt_ void* ptr)
    {
        ::CoTaskMemFree(ptr);
    }
};

template<class T>
class CComHeapPtr : public CHeapPtr<T, CComAllocator>
{
public:
    CComHeapPtr()
    {
    }

    explicit CComHeapPtr(T *lp) :
        CHeapPtr<T, CComAllocator>(lp)
    {
    }
};

}; // namespace ATL

#ifndef _ATL_NO_AUTOMATIC_NAMESPACE
using namespace ATL;
#endif //!_ATL_NO_AUTOMATIC_NAMESPACE
