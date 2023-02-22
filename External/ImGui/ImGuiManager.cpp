#include "ImGuiManager.h"

void ImGuiManager::Initialize(DirectXCommon* dXCommon_, WinApp* winApp_) {
	HRESULT result;

	// ImGui�̃R���e�L�X�g�𐶐�
	ImGui::CreateContext();
	// ImGui�̃X�^�C����ݒ�
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(winApp_->GetHwnd());

	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	// �f�X�N���v�^�q�[�v����
	result = dXCommon_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvHeap_));
	assert(SUCCEEDED(result));

	ImGui_ImplDX12_Init(
		dXCommon_->GetDevice(),
		static_cast<int>(dXCommon_->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap_.Get(),
		srvHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvHeap_->GetGPUDescriptorHandleForHeapStart()
	);

	ImGuiIO& io = ImGui::GetIO();
	// �W���t�H���g��ǉ�����
	io.Fonts->AddFontDefault();
}

void ImGuiManager::Finalize()
{
	// ��n��
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// �f�X�N���v�^�q�[�v�̉��
	srvHeap_.Reset();
}

void ImGuiManager::Begin()
{
	// ImGui�t���[���J�n
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{
	// �`�揀��
	ImGui::Render();
}

void ImGuiManager::Draw(DirectXCommon* dXCommon_)
{
	ID3D12GraphicsCommandList* commandList = dXCommon_->GetCommandList();

	// �f�X�N���v�^�q�[�v�̔z����Z�b�g����R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap_.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	// �`��R�}���h�𔭍s
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);
}

void ImGuiManager::MySaveFunction()
{
}