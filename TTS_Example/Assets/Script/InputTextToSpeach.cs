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
        if(input.text.Length != 0)
            tts.Speech(input.text);
    }
}
