using System;
using System.IO;
using System.Runtime.InteropServices;
using UnityEngine;
using System.Collections;


public class TTS : MonoBehaviour
{
    const int TRUE = 1, FALSE = 0;
    [DllImport("TTSDLL", EntryPoint = "CreateTTS")]
    static extern IntPtr CreateTTS();

    [DllImport("TTSDLL", EntryPoint = "GetVoiceCount")]
    static extern int GetVoiceCount(IntPtr tts);

    [DllImport("TTSDLL", EntryPoint = "GetNowVoice", CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr GetNowVoice(IntPtr tts);

    [DllImport("TTSDLL", EntryPoint = "GetVoiceByNum", CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr GetNowVoiceByNum(IntPtr tts, int num);

    [DllImport("TTSDLL", EntryPoint = "GetErrorMessage", CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr GetErrorMessage(IntPtr tts);

    [DllImport("TTSDLL", EntryPoint = "SetVoiceByName", CallingConvention = CallingConvention.Cdecl)]
    //[return: MarshalAs(UnmanagedType.I1)]
    static extern int SetVoiceByName(IntPtr tts, [MarshalAs(UnmanagedType.LPStr)] string name);

    [DllImport("TTSDLL", EntryPoint = "SetVoiceByNum", CallingConvention = CallingConvention.Cdecl)]
    //[return: MarshalAs(UnmanagedType.I1)]
    static extern int SetVoiceByNum(IntPtr tts, int num);

    [DllImport("TTSDLL", EntryPoint = "SetOutputPath", CallingConvention = CallingConvention.Cdecl)]
    //[return: MarshalAs(UnmanagedType.I1)]
    static extern int SetOutputPath(IntPtr tts, [MarshalAs(UnmanagedType.LPStr)] string filePath);


    [DllImport("TTSDLL", EntryPoint = "TextToSpeech", CallingConvention = CallingConvention.Cdecl)]
    //[return: MarshalAs(UnmanagedType.I1)]
    static extern int TextToSpeech(IntPtr tts, [MarshalAs(UnmanagedType.LPStr)] string text, bool output = false);

    IntPtr tts;
    AudioSource ttsAudio;
    string ttsFilePath = Application.streamingAssetsPath + "/";
    string ttsFileName = "tts_cache.wav";

    private void Awake()
    {
        ttsAudio = gameObject.AddComponent<AudioSource>();
        tts = CreateTTS();
        SetPath(ttsFilePath, ttsFileName);
    }

    string GetVoice(int num = -1)
    {
        IntPtr ptr;
        string str;
        if (num < 0)
            ptr = GetNowVoice(tts);
        else
            ptr = GetNowVoiceByNum(tts, num);
        str = Marshal.PtrToStringAnsi(ptr);
        Marshal.FreeHGlobal(ptr);
        return str;
    }

    public void Speech(string text)
    {
        if (tts == null)
            return;
        if(TextToSpeech(tts, text, true) == 0)
        {
            Debug.Log(GetMessage());
        }
        PlayTTS();
    }

    private void SetPath(string path, string file)
    {
        if (!Directory.Exists(path))
        {
            Directory.CreateDirectory(path);
        }

        if (tts == null)
        {
            return;
        }

        if (SetOutputPath(tts, path + file) == FALSE)
        {
            Debug.Log("fail to set output:" + GetMessage());
        }
    }

    void SetVoice(int num)
    {
        if (num > 0)
        {
            if(SetVoiceByNum(tts, num) == FALSE)
            {
                Debug.Log(GetMessage());
            }
        }
    }

    void SetVoice(string name)
    {
        if (name.Length > 0)
        {
            if(SetVoiceByName(tts, name) == FALSE)
            {
                Debug.Log(GetMessage());
            }
        }
    }

    string GetMessage()
    {
        IntPtr ptr = GetErrorMessage(tts);
        string err = Marshal.PtrToStringAnsi(ptr);
        Marshal.FreeHGlobal(ptr);
        return err;
    }

    void PlayTTS()
    {
        if (ttsAudio.clip != null)
        {
            ttsAudio.Stop();
            AudioClip clip = ttsAudio.clip;
            ttsAudio.clip = null;
            clip.UnloadAudioData();
            DestroyImmediate(clip, false); // This is important to avoid memory leak
        }

        // Load Clip then assign to audio source and play
        StartCoroutine(LoadClipCoroutine("file:///" + ttsFilePath+ttsFileName, 
            (clip) => { ttsAudio.clip = clip; ttsAudio.Play(); }));
    }

    IEnumerator LoadClipCoroutine(string file, Action<AudioClip> onLoadingCompleted)
    {
        WWW request = new WWW(file);
        yield return request;

        if (onLoadingCompleted != null)
            onLoadingCompleted(request.GetAudioClip(true, true));

        request.Dispose();
    }
}
