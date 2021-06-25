#pragma once
#include "TTS.h"

#define DLL_TEST_EXPORTS

#ifdef  DLL_TEST_EXPORTS
#define DLL_TEST_API    __declspec(dllexport)
#else
#define DLL_TEST_API    __declspec(dllimport)
#endif //  DLL_TEST_EXPORTS


extern "C" {
    DLL_TEST_API inline TTS* CreateTTS();

    DLL_TEST_API inline int GetVoiceCount(TTS* tts);
    DLL_TEST_API inline char* GetNowVoice(TTS* tts);
    DLL_TEST_API inline char* GetVoiceByNum(TTS* tts, int num);
    DLL_TEST_API inline char* GetErrorMessage(TTS* tts);

    DLL_TEST_API inline BOOL SetVoiceByName(TTS* tts, const char* name);
    DLL_TEST_API inline BOOL SetVoiceByNum(TTS* tts, int num);
    DLL_TEST_API inline BOOL SetOutputPath(TTS* tts, const char* filePath);
    
    //Speech text make sound file to set last parameter true
    DLL_TEST_API inline BOOL TextToSpeech(TTS* tts, const char* text, bool out = false);
}

wchar_t* CharToWchar(const char* ch);
char* WcharToChar(const wchar_t* wch);
