﻿#pragma once

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain, shared_ptr<DescriptorHeap> descHeap);;
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();
	
	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }

private:
	// CommandQueue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는것
	ComPtr<ID3D12CommandQueue>			_cmdQueue;
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;

	// Fence : 울타리?
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;
	
	shared_ptr<SwapChain>				_swapChain;
	shared_ptr<DescriptorHeap>			_descHeap;
};

