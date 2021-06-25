#include "pch.h"
#include "tts_interface.h"
#include<stdlib.h>

wchar_t* CharToWchar(const char* ch)
{
    const size_t size = strlen(ch) + 1;
    wchar_t* wch = new wchar_t[size];
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wch, size, ch, _TRUNCATE);
    return wch;
}

char* WcharToChar(const wchar_t* wch)
{
    const size_t size = wcslen(wch) + 1;
    char* ch = new char[size];
    size_t convertedChars = 0;
    wcstombs_s(&convertedChars, ch, size, wch, _TRUNCATE);
    return ch;
}


TTS* CreateTTS() { return new TTS(); }

int GetVoiceCount(TTS* tts)
{
    return tts->GetVoiceCount();
}

char* GetNowVoice(TTS* tts)
{
    return WcharToChar(tts->GetNowVoice());
}

char* GetVoiceByNum(TTS* tts, int num)
{
    return WcharToChar(tts->GetVoiceByNum(num));
}

char* GetErrorMessage(TTS* tts)
{
    const char* ch = tts->GetError();
    char* err = new char[strlen(ch) + 1];
    strcpy_s(err, strlen(ch)+1, ch);
    return err;
}

BOOL SetVoiceByName(TTS* tts, const char* name)
{
    return tts->SetVoice(CharToWchar(name));
}

BOOL SetVoiceByNum(TTS* tts, int num)
{
    return tts->SetVoice(num);
}

BOOL SetOutputPath(TTS* tts, const char* path)
{
    return tts->SetOutput(CharToWchar(path));
}

BOOL TextToSpeech(TTS* tts, const char* text, bool out)
{
    return tts->Speech(CharToWchar(text), out);
}
