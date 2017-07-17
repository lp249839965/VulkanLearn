#pragma once

#include "DeviceObjectBase.h"
#include <map>

class CommandBuffer;
class Fence;
class PerFrameResource;
class CommandBuffer;

class FrameManager
{
	typedef std::map<uint32_t, std::vector<std::shared_ptr<PerFrameResource>>> FrameResourceTable;
	typedef std::map<uint32_t, std::vector<std::shared_ptr<CommandBuffer>>> FrameCommandBufferTable;

public:
	std::shared_ptr<PerFrameResource> AllocatePerFrameResource(uint32_t frameIndex);
	uint32_t FrameIndex() const { return m_currentFrameIndex; }
	std::shared_ptr<Fence> GetCurrentFrameFence() const { return m_frameFences[m_currentFrameIndex]; }
	void WaitForFence();

protected:
	bool Init(const std::shared_ptr<Device>& pDevice, uint32_t maxFrameCount);
	static std::shared_ptr<FrameManager> Create(const std::shared_ptr<Device>& pDevice, uint32_t maxFrameCount);

	void ReserveCommandBuffer(const std::shared_ptr<CommandBuffer>& pCmdBuffer) { m_frameCommandBufferes[m_currentFrameIndex].push_back(pCmdBuffer); }
	void ReserveCommandBuffer(const std::vector<std::shared_ptr<CommandBuffer>>& cmdBufferList) 
	{
		std::vector<std::shared_ptr<CommandBuffer>> list = m_frameCommandBufferes[m_currentFrameIndex];
		list.insert(list.end(), cmdBufferList.begin(), cmdBufferList.end());
	}
	void SetFrameIndex(uint32_t index);

private:
	FrameResourceTable						m_frameResTable;
	std::vector<std::shared_ptr<Fence>>		m_frameFences;

	FrameCommandBufferTable					m_frameCommandBufferes;

	uint32_t m_currentFrameIndex;
	uint32_t m_maxFrameCount;

	friend class SwapChain;
	friend class Queue;
};