#include "pch.h"
#include "tts_interface.h"

TTS* CreateTTS() { return new TTS(); }

int GetVoiceCount(TTS* tts)
{
    return tts->GetVoiceCount();
}

const WCHAR* GetNowVoice(TTS* tts)
{
    return tts->GetNowVoice();
}

const WCHAR* GetVoiceByNum(TTS* tts, int num)
{
    return tts->GetVoiceByNum(num);
}

const WCHAR* GetErrorMessage(TTS* tts)
{
    return tts->GetError();
}

BOOL SetVoiceByName(TTS* tts, const WCHAR* name)
{
    return tts->SetVoice(name);
}

BOOL SetVoiceByNum(TTS* tts, int num)
{
    return tts->SetVoice(num);
}

BOOL SetOutputPath(TTS* tts, const WCHAR* path)
{
    return tts->SetOutput(path);
}

BOOL TextToSpeech(TTS* tts, const WCHAR* text, bool out)
{
    return tts->Speech(text, out);
}
