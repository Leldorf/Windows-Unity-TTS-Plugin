#pragma once
#include "pch.h"

class TTS
{
private:
    int count;
    int voiceNum;
    wchar_t** names;
    wchar_t* outputPath;
    wchar_t* errorMessage;

    void SetErrorMessage(const wchar_t* message) { wcscpy_s(this->errorMessage, wcslen(message), message); }
public:
    TTS();

    BOOL Speech(const wchar_t* text, bool out = false);

    BOOL SetVoice(const wchar_t* voiceName);

    BOOL SetVoice(const int voiceNum);

    BOOL SetOutput(const wchar_t* path);

    const wchar_t* GetError() { return this->errorMessage; }

    const int GetVoiceCount() { return this->count; }

    const wchar_t* GetVoiceByNum(int num) { return this->names[num]; }

    const wchar_t* GetNowVoice() { return this->names[this->voiceNum]; }
};
