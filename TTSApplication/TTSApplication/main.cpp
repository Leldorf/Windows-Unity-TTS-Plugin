#include "../../TTSDLL/TTSDLL/tts_interface.h"
#pragma comment (lib, "../../TTSDLL/x64/Release/TTSDLL.lib")
#include <iostream>
#include <string>
using namespace std;

int main()
{
	TTS* tts = CreateTTS();
	int count = GetVoiceCount(tts);
	cout << "voice count : " << count << endl;
	if (count == 0)
	{
		cout << "no voicces" << endl;
		return 1;
	}

	//print voices
	for (int i = 0; i < count; i++)
	{
		//get voice name by num
		wcout << i << L": " << GetVoiceByNum(tts, i) << endl;
	}
	int num = 0;
	cout << "Select voice(number): ";
	cin >> num;
	if (num < 0 || num >= count)
		num = count - 2;
	cout << num;

	//set voice by voice num
	if (!SetVoiceByNum(tts, num))
		wcout << GetErrorMessage(tts) << endl << endl;

	cout << "selected voice:";
	wcout << GetNowVoice(tts) << endl << endl;

	//set voice by voice name
	//if (!SetVoiceByName(tts, "Microsoft Zira Desktop - English (United States)"))
	//	cout << GetErrorMessage(tts) << endl;


	bool output = true;
	cout << "output with wav file(no:0 / yes:1): ";
	cin >> num;
	if (num != 0)
	{
		//set output path of tts wav
		if (!SetOutputPath(tts, L"./output.wav"))
			wcout << GetErrorMessage(tts) << endl << endl;
		output = false;
	}

	wstring buffer;
	getline(wcin, buffer);
	while (1)
	{
		cout << "\ninput: ";
		getline(wcin, buffer);

		//text to speech
 		if (!TextToSpeech(tts, buffer.c_str(), output))
		{
			wcout << GetErrorMessage(tts) << endl;
		}
	}
	tts = NULL;
	return 0;
}