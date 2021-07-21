# Windows-Unity-TTS-Plugin

Windows Unity Text To Speech API with SpVoice

TTS_Example: Unity TTS example scene

![image](https://user-images.githubusercontent.com/86466517/126476917-ad189f21-09b5-4ab4-8c1d-e5a46e73c4a0.png)

TTS_Application: C++ TTS example code

![image](https://user-images.githubusercontent.com/86466517/126476893-bc7088ac-65da-4954-802c-29d3554c6f98.png)


set TTSDLL.dll to Assets/Plugins

TTS.cs

GetVoice()
  -> get now voice name
 
GetVoice(int)
  -> get voice by num
 
GetVoiceNames()
  -> get voice name list

Speech(string)
  -> string to speech sound
  
SetVoice(int)
  -> set voice by num
  
SetVoice(string)
  -> set voice by name

TTS DLL code in TTSDLL


