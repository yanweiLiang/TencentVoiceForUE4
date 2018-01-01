// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceClient.h"

UVoiceClient* UVoiceClient::VoiceClient = nullptr;

UVoiceClient::UVoiceClient(const FObjectInitializer& ObjectInitializer) : UObject(ObjectInitializer)
{
	bTickable = false;
	bRoomStatus = false;
	CurrentRoomName = "";
	m_voiceengine = gcloud_voice::GetVoiceEngine();
}

UVoiceClient::~UVoiceClient()
{

}

void UVoiceClient::Tick(float DeltaTime)
{
	m_voiceengine->Poll();
}

FORCEINLINE bool UVoiceClient::IsTickable() const
{
	return bTickable;
}

FORCEINLINE TStatId UVoiceClient::GetStatId() const
{
	return TStatId();
}

UVoiceClient * UVoiceClient::GetVoiceClient()
{
	if (nullptr == VoiceClient)
	{
		VoiceClient = NewObject<UVoiceClient>();
		VoiceClient->AddToRoot();
	}
	return VoiceClient;
}

void UVoiceClient::ToggleTickable(bool Tickable)
{
	bTickable = Tickable;
}

void UVoiceClient::SetRoomStatus(bool RoomStatus)
{
	bRoomStatus = RoomStatus;
}

bool UVoiceClient::GetRoomStatus()
{
	return bRoomStatus;
}

bool UVoiceClient::SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID)
{
	//UE_LOG(TencentVoicePlugin, Display, TEXT("SetAppInfo return code %d!"), static_cast<int32>(m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*OpenID))));

	if ((nullptr != m_voiceengine)
		&& (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*OpenID))))
	{
		return true;
	}
	return false;
}

void UVoiceClient::InitVoiceEngine()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("InitVoiceEngine return code %d!"), static_cast<int32>(m_voiceengine->Init()));
}

void UVoiceClient::SetMode(EVoiceMode VoiceMode)
{
	//UE_LOG(TencentVoicePlugin, Display, TEXT("SetMode return code %d!"), static_cast<int32>(static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMode>(VoiceMode)));
	UE_LOG(TencentVoicePlugin, Display, TEXT("SetMode return code %d!"), static_cast<int32>(m_voiceengine->SetMode(static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMode>(VoiceMode))));
}

void UVoiceClient::SetServerInfo(const FString & ServerAddr)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("SetServerInfo return code %d!"), static_cast<int32>(m_voiceengine->SetServerInfo(TCHAR_TO_ANSI(*ServerAddr))));
}

void UVoiceClient::OnPause()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OnPause return code %d!"), static_cast<int32>(m_voiceengine->Pause()));
}

void UVoiceClient::OnResume()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OnResume return code %d!"), static_cast<int32>(m_voiceengine->Resume()));
}

bool UVoiceClient::SetNotify(UNotifyBase* NotifyInstance)
{
	//UE_LOG(TencentVoicePlugin, Display, TEXT("SetNotify return code %d!"), static_cast<int32>(m_voiceengine->SetNotify(NotifyInstance)));
	
	if ((nullptr != NotifyInstance)
		&& (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->SetNotify(NotifyInstance)))
	{
		return true;
	}
	return false;
}

void UVoiceClient::JoinTeamRoom(const FString & RoomName, int32 msTimeout)
{
	if (bRoomStatus)
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("UVoiceClient::JoinTeamRoom report : Already joined the voice room"));
	}
	else
	{
		CurrentRoomName = RoomName;

		UE_LOG(TencentVoicePlugin, Display, TEXT("JoinTeamRoom return code %d!"), static_cast<int32>(m_voiceengine->JoinTeamRoom(TCHAR_TO_ANSI(*RoomName), msTimeout)));
	}
}

void UVoiceClient::OpenMic()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OpenMic return code %d!"), static_cast<int32>(m_voiceengine->OpenMic()));
}

void UVoiceClient::CloseMic()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("CloseMic return code %d!"), static_cast<int32>(m_voiceengine->CloseMic()));
}

void UVoiceClient::OpenSpeaker()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OpenSpeaker return code %d!"), static_cast<int32>(m_voiceengine->OpenSpeaker()));
}

void UVoiceClient::CloseSpeaker()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("CloseSpeaker return code %d!"), static_cast<int32>(m_voiceengine->CloseSpeaker()));
}

void UVoiceClient::QuitCurrentJoinedRoom(int32 msTimeout)
{
	if (bRoomStatus)
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("UVoiceClient::QuitCurrentJoinedRoom return code %d!"), static_cast<int32>(m_voiceengine->QuitRoom(TCHAR_TO_ANSI(*CurrentRoomName), msTimeout)));

		CurrentRoomName = "";
	}
	else
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("UVoiceClient::QuitCurrentJoinedRoom report : No voice room is currently available"));
	}
}