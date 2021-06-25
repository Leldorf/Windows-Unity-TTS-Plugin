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
	char* voice = new char();
	for (int i = 0; i < count; i++)
	{
		//get voice name by num
		cout << GetVoiceByNum(tts, i) << endl;
	}

	//set output path of tts wav
	if(!SetOutputPath(tts, "./output.wav"))
		cout << GetErrorMessage(tts) << endl;

	//set voice by voice num
	if (!SetVoiceByNum(tts, count - 1))
		cout << GetErrorMessage(tts) << endl;

	//set voice by voice name
	if (!SetVoiceByName(tts, "Microsoft Zira Desktop - English (United States)"))
		cout << GetErrorMessage(tts) << endl;


	string buffer;
	char* err = new char();
	while (1)
	{
		getline(cin, buffer);
		if (buffer.empty())
			break;
		//text to speech
 		if (!TextToSpeech(tts, buffer.c_str(), false))
		{
			cout << GetErrorMessage(tts) << endl;
			cout << err << endl;
		}
	}
	tts = NULL;
	return 0;
}