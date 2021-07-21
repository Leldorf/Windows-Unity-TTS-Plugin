#include "pch.h"
#include "TTS.h"
#include "sp_token_helper.h"
#include <functional>


inline void for_each_voice(
	std::function<bool(CComPtr<ISpVoice>&, CComPtr<ISpObjectToken>&, int)> action)
{
    {
        if (FAILED(CoInitialize(nullptr)))
        {
            //std::cout << "Cannot call CoInitialize" << std::endl;
            throw std::exception("Cannot call CoInitialize");
        }

        CComPtr<ISpVoice> voice;
        if (FAILED(voice.CoCreateInstance(CLSID_SpVoice)))
        {
            //std::cout << "Cannot call CoCreateInstance(CLSID_SpVoice)" << std::endl;
            throw std::exception("Cannot call CoCreateInstance(CLSID_SpVoice)");
        }

        CComPtr<IEnumSpObjectTokens> enumerator;
        if (FAILED(SpEnumTokens(SPCAT_VOICES, NULL, NULL, &enumerator)))
        {
            //std::cout << "Cannot call SpEnumTokens" << std::endl;
            throw std::exception("Cannot call SpEnumTokens");
        }

        ULONG voiceCount = 0UL;
        if (FAILED(enumerator->GetCount(&voiceCount)))
        {
            //std::cout << "Cannot call IEnumSpObjectTokens::GetCount" << std::endl;
            throw std::exception("Cannot call IEnumSpObjectTokens::GetCount");
        }

        for (auto i = 0UL; i < voiceCount; ++i)
        {
            CComPtr<ISpObjectToken> voiceToken;
            if (FAILED(enumerator->Next(1, &voiceToken, nullptr)))
            {
                //std::cout << "Cannot call IEnumSpObjectTokens::Next" << std::endl;
                throw std::exception("Cannot call IEnumSpObjectTokens::Next");
            }

            if (!action(voice, voiceToken, voiceCount))
            {
                break;
            }
        }
        enumerator.Release();
    }
    CoUninitialize();
}

inline wchar_t* get_voice_name(CComPtr<ISpObjectToken>& token)
{
    LPWSTR name = nullptr;
    if (FAILED(token->GetStringValue(nullptr, &name)))
    {
        return new wchar_t();
    }
    return name;
}

TTS::TTS()
{
    int count = 0;
    wchar_t** names = NULL;
    for_each_voice([=, &names, &count](auto voice, auto token, int voiceCount)
        {
            if (names == NULL)
                names = new wchar_t*[voiceCount];
            names[count] = get_voice_name(token);
            count++;
            return true;
        });
    this->count = count;
    this->voiceNum = count - 1;
    this->names = names;
    this->outputPath = new wchar_t();
}

BOOL TTS::SetVoice(const wchar_t* voiceName)
{
    for (int i = 0; i < count; i++)
    {
        if (wcscmp(voiceName, this->names[i]) == 0)
        {
            voiceNum = i;
            return TRUE;
        }
    }
    this->SetErrorMessage(L"Exception: Not found voice name");
    return FALSE;
}

BOOL TTS::SetVoice(const int voiceNum)
{
    if (this->count > voiceNum && voiceNum >= 0)
    {
        this->voiceNum = voiceNum;
        return TRUE;
    }
    else
    {
        this->SetErrorMessage(L"Exception: Out of voices index range");
        return FALSE;
    }
}

BOOL TTS::SetOutput(const wchar_t* path)
{
	int len = wcslen(path) + 1;
	this->outputPath = new wchar_t[len];
	wcscpy_s(this->outputPath, len, path);
	return TRUE;
}

BOOL TTS::Speech(const wchar_t* text, bool out)
{
    const int num = voiceNum;
    int counter = 0;
    wchar_t* path = this->outputPath;
    BOOL isSuccess = FALSE;

    for_each_voice([=, &isSuccess, &counter, &num, &out, &text, &path](auto voice, auto token, int count)
        {
            if (num != counter)
            {
                counter++;
                return true;
            }

            if (FAILED(voice->SetVoice(token)))
            {
                this->SetErrorMessage(L"Cannot call ISpVoice::SetVoice");
                return false;
            }

            if (out && wcslen(path) != 0)
            {
                CComPtr<ISpeechFileStream> outputStream;
                if (FAILED(outputStream.CoCreateInstance(CLSID_SpFileStream)))
                {
                    this->SetErrorMessage(L"Cannot call CoCreateInstance(CLSID_SpFileStream)");
                    return false;
                }

                if (FAILED(outputStream->Open(outputPath, SSFMCreateForWrite)))
                {
                    this->SetErrorMessage(L"Cannot open the output file");
                    return false;
                }

                if (FAILED(voice->SetOutput(outputStream, true)))
                {
                    this->SetErrorMessage(L"Cannot call ISpVoice::SetOutput");
                    return false;
                }
                outputStream.Release();
            }

            if (FAILED(voice->Speak(text, SPF_PARSE_SAPI, nullptr)))
            {
                this->SetErrorMessage(L"Cannot call ISpVoice::Speak");
                return false;
            }

            isSuccess = TRUE;
            return false;
        });
    return isSuccess;
}