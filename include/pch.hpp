// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once

#include <cmath>

#include <D3D12TranslationLayerDependencyIncludes.h>

#ifndef _MSC_VER
__CRT_UUID_DECL(D3D11On12CreatorID,0xedbf5678,0x2960,0x4e81,0x84,0x29,0x99,0xd4,0xb2,0x63,0x0c,0x4e);
__CRT_UUID_DECL(ID3D12DescriptorHeap, 0x8efb471d, 0x616c, 0x4f49, 0x90,0xf7, 0x12,0x7b,0xb7,0x63,0xfa,0x51)
__CRT_UUID_DECL(ID3D12CompatibilityDevice, 0x8f1c0e3c, 0xfae3, 0x4a82, 0xb0, 0x98, 0xbf, 0xe1, 0x70, 0x82, 0x07, 0xff);
__CRT_UUID_DECL(ID3D12Device1, 0x77acce80, 0x638e, 0x4e65, 0x88, 0x95, 0xc1, 0xf2, 0x33, 0x86, 0x86, 0x3e)
#endif

#include <D3D12TranslationLayerIncludes.h>

#include <d3dx11on12.h>

#include "SharedResourceHelpers.hpp"

#ifdef WIN32_LEAN_AND_MEAN
// This defines NTSTATUS and other types that are needed for kernel headers
#include <wincrypt.h>
#endif

#include "d3dkmthk.h"
#include "dxgiddi.h"

#ifndef D3D12_TOKENIZED_PROGRAM_FORMAT_HEADER
#define D3D12_TOKENIZED_PROGRAM_FORMAT_HEADER
#endif
#include "d3d10umddi.h"

#include "D3D11On12DDI.h"

_At_(return, _When_(FAILED(hr), __analysis_noreturn))
inline void ThrowFailure(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw _com_error(hr);
    }
}

template< typename T >
constexpr bool IsPow2(T num)
{
    static_assert(!std::is_signed_v<T>, "Signed type passed to IsPow2");
    return !(num & (num - 1));
}
template< typename T >
constexpr T Align(T uValue, T uAlign)
{
    T uResult;

    if (IsPow2(uAlign))
    {
        T uMask = uAlign - 1;
        uResult = (uValue + uMask) & ~uMask;
    }
    else
    {
        uResult = ((uValue + uAlign - 1) / uAlign) * uAlign;
    }

    assert(uResult >= uValue);
    assert(0 == (uResult % uAlign));
    return uResult;
}
extern bool GetCompatValue(PCSTR, UINT64*);

#if 0
TRACELOGGING_DECLARE_PROVIDER(g_hD3D11On12TraceLoggingProvider);
#endif

#define ASSERT assert

class CDevice;
#include "util.hpp"
#include "DeviceChild.hpp"
#include "PipelineStateCache.hpp"
#include "Shader.hpp"
#include "InputLayout.hpp"
#include "State.hpp"
#include "PipelineState.hpp"
#include "layer.hpp"
#include "adapter.hpp"
#include "VideoTranslate.hpp"
#include "VideoDevice.hpp"
#include "VideoDecode.hpp"
#include "VideoProcess.hpp"
#include "VideoProcessEnum.hpp"
#include "device.hpp"
#include "resource.hpp"
#include "view.hpp"
#include "Query.hpp"
#include "Sampler.hpp"
#include "Fence.hpp"

#include "InputLayout.inl"
#include "view.inl"
#include "Shader.inl"

