using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InputTextToSpeach : MonoBehaviour
{
    [SerializeField]
    Text input = null;
    [SerializeField]
    TTS tts = null;

    private void Awake()
    {
        if (input == null)
            input = transform.GetChild(1).GetComponent<Text>();
        if (tts == null)
            tts = GameObject.Find("TTS").GetComponent<TTS>();
    }

    public void SpeechText()
    {
        tts.Speech(input.text);
    }
}
