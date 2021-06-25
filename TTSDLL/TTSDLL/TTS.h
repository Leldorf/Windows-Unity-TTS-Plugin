#pragma once
#include "pch.h"

class TTS
{
private:
    int count;
    int voiceNum;
    wchar_t** names;
    wchar_t* outputPath;
    char* errorMessage;

    void SetErrorMessage(const char* message) { strcpy_s(this->errorMessage, strlen(message), message); }
public:
    TTS();

    BOOL Speech(const wchar_t* text, bool out = false);

    BOOL SetVoice(const wchar_t* voiceName);

    BOOL SetVoice(const int voiceNum);

    BOOL SetOutput(const wchar_t* path);

    const char* GetError() { return this->errorMessage; }

    const int GetVoiceCount() { return this->count; }

    const wchar_t* GetVoiceByNum(int num) { return this->names[num]; }

    const wchar_t* GetNowVoice() { return this->names[this->voiceNum]; }
};
